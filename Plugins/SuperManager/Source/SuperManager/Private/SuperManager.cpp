// Copyright Epic Games, Inc. All Rights Reserved.

#include "SuperManager.h"

#include "AssetToolsModule.h"
#include "ContentBrowserModule.h"
#include "DebugHeader.h"
#include "EditorAssetLibrary.h"
#include "LevelEditor.h"
#include "ObjectTools.h"
#include "Selection.h"
#include "AssetRegistry/AssetRegistryModule.h"
#include "Chaos/AABB.h"
#include "Chaos/AABB.h"
#include "CustomStyle/SuperManagerStyle.h"
#include "CustomUICommands/SuperManagerUICommands.h"
#include "SlateWidgets/AdvanceDeletionWidget.h"
#include "Subsystems/EditorActorSubsystem.h"

#define LOCTEXT_NAMESPACE "FSuperManagerModule"

void FSuperManagerModule::StartupModule()
{
	FSuperManagerStyle::InitializeIcons();
	InitCBMenuExtension();
	RegisterAdvanceDeletionTab();

	FSuperManagerUICommands::Register();
	InitCustomUICommands();
	
	InitLevelEditorExtension();
	InitCustomSelectionEvent();
}

void FSuperManagerModule::ShutdownModule()
{
	FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(FName("AdvanceDeletion"));
	FSuperManagerStyle::ShutDown();
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

#pragma region ContentBrowserMenuExtension
void FSuperManagerModule::InitCBMenuExtension()
{
	FContentBrowserModule& ContentBrowserModule = FModuleManager::LoadModuleChecked<FContentBrowserModule>(TEXT("ContentBrowser"));
	TArray<FContentBrowserMenuExtender_SelectedPaths>& ContentBrowserModuleMenuExtenders = ContentBrowserModule.GetAllPathViewContextMenuExtenders();

	ContentBrowserModuleMenuExtenders.Add(FContentBrowserMenuExtender_SelectedPaths::CreateRaw(this, &FSuperManagerModule::CustomCBMenuExtender));
}

TSharedRef<FExtender> FSuperManagerModule::CustomCBMenuExtender(const TArray<FString>& SelectedPaths)
{
	TSharedRef<FExtender> MenuExtender(new FExtender());

	if(SelectedPaths.Num() > 0)
	{
		MenuExtender->AddMenuExtension(FName("Delete"), EExtensionHook::After,
			TSharedPtr<FUICommandList>(),FMenuExtensionDelegate::CreateRaw(this,&FSuperManagerModule::AddCBMenuEntry));
		
		FolderPathsSelected = SelectedPaths;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("No path selected"));
	}
	
	return MenuExtender;
}

void FSuperManagerModule::AddCBMenuEntry(FMenuBuilder& MenuBuilder)
{
	MenuBuilder.AddMenuEntry(
		FText::FromString(TEXT("Delete Unused Assets")),
		FText::FromString(TEXT("Safely delete all unused assets in selected folder")),
		FSlateIcon(FSuperManagerStyle::GetStyleSetName(), "ContentBrowser.DeleteUnusedAssets"),
		FExecuteAction::CreateRaw(this, &FSuperManagerModule::OnDeleteUnusedAssetsButtonClicked)
		);
	MenuBuilder.AddMenuEntry(
	FText::FromString(TEXT("Delete Empty Folders")),
	FText::FromString(TEXT("Safely delete all empty folders in selected folder")),
	FSlateIcon(FSuperManagerStyle::GetStyleSetName(), "ContentBrowser.DeleteEmptyFolders"),
	FExecuteAction::CreateRaw(this, &FSuperManagerModule::OnDeleteEmptyFoldersButtonClicked)
	);
	MenuBuilder.AddMenuEntry(
		FText::FromString(TEXT("Advance deletion ")),
		FText::FromString(TEXT("Open advanced deletion tab")),
		FSlateIcon(FSuperManagerStyle::GetStyleSetName(), "ContentBrowser.AdvanceDeletion"),
		FExecuteAction::CreateRaw(this, &FSuperManagerModule::OnOpenAdvanceDeletionTabButtonClicked)
	);
}

void FSuperManagerModule::OnOpenAdvanceDeletionTabButtonClicked()
{
	FixUpRedirectors();
	FGlobalTabmanager::Get()->TryInvokeTab(FName(TEXT("AdvanceDeletion")));
}

void FSuperManagerModule::OnDeleteEmptyFoldersButtonClicked()
{
	if(FolderPathsSelected.Num() > 1)
	{
		UE_LOG(LogTemp, Error, TEXT("More than one path selected"));
		return;
	}

	const auto FolderPathsArray = UEditorAssetLibrary::ListAssets(FolderPathsSelected[0], true,true);
	if(!FolderPathsArray.Num()) return;

	TArray<FString> EmptyFoldersPathsArray;
	for(const auto& FolderPath : FolderPathsArray)
	{
		if(FolderPath.Contains(TEXT("Developers")) || FolderPath.Contains(TEXT("Collections"))) continue;
		if(!UEditorAssetLibrary::DoesDirectoryExist(FolderPath)) continue;

		if(!UEditorAssetLibrary::DoesDirectoryHaveAssets(FolderPath))
		{
			EmptyFoldersPathsArray.Add(FolderPath);
		}
	}

	for(const FString& EmptyFolderPath: EmptyFoldersPathsArray)
	{
		UEditorAssetLibrary::DeleteDirectory(EmptyFolderPath);
	}
}

void FSuperManagerModule::OnDeleteUnusedAssetsButtonClicked()
{
	FixUpRedirectors();
	
	if(FolderPathsSelected.Num() > 1)
	{
		UE_LOG(LogTemp, Error, TEXT("More than one path selected"));
		return;
	}
	
	const auto Assets =  UEditorAssetLibrary::ListAssets(FolderPathsSelected[0],true);
	if(!Assets.Num()) return;

	TArray<FAssetData> UnusedAssets;
	for(const auto& Asset : Assets)
	{
		if(Asset.Contains(TEXT("Developers")) || Asset.Contains(TEXT("Collections"))) continue;
		if(!UEditorAssetLibrary::DoesAssetExist(Asset)) continue;
		
		auto AssetReferences = UEditorAssetLibrary::FindPackageReferencersForAsset(Asset, true);
		if(AssetReferences.Num() == 0)
		{
			UnusedAssets.Add(UEditorAssetLibrary::FindAssetData(Asset));
		}
	}

	if(!UnusedAssets.Num()) return;
	ObjectTools::DeleteAssets(UnusedAssets);


}

void FSuperManagerModule::FixUpRedirectors()
{
	FARFilter Filter{};
	Filter.bRecursiveClasses = true;
	Filter.PackagePaths.Emplace("/Game");
	Filter.ClassNames.Emplace("ObjectRedirector");
	
	FAssetRegistryModule& AssetRegistryModule = FModuleManager::Get().LoadModuleChecked<FAssetRegistryModule>(TEXT("AssetTools"));
	TArray<FAssetData> OutRedirectors;
	AssetRegistryModule.Get().GetAssets(Filter, OutRedirectors);

	TArray<UObjectRedirector*> RedirectorsToFixArray;
	RedirectorsToFixArray.Reserve(OutRedirectors.Num());
	for(const auto& RedirectorData: OutRedirectors)
	{
		UObjectRedirector* Redirector = Cast<UObjectRedirector>(RedirectorData.GetAsset());
		if(Redirector)
			RedirectorsToFixArray.Add(Redirector);
	}

	FAssetToolsModule& AssetToolsModule = FModuleManager::LoadModuleChecked<FAssetToolsModule>(TEXT("AssetTools"));
	AssetToolsModule.Get().FixupReferencers(RedirectorsToFixArray);
}
#pragma endregion

#pragma region CustomEditorTab

void FSuperManagerModule::RegisterAdvanceDeletionTab()
{
	FGlobalTabmanager::Get()->RegisterNomadTabSpawner(FName(TEXT("AdvanceDeletion")),
		FOnSpawnTab::CreateRaw(this, &FSuperManagerModule::OnSpawnAdvanceDeletionTab ))
		.SetDisplayName(FText::FromString(TEXT("Advance Deletion")))
		.SetIcon(FSlateIcon(FSuperManagerStyle::GetStyleSetName(), "ContentBrowser.DeleteEmptyFolders"));
}

TSharedRef<SDockTab> FSuperManagerModule::OnSpawnAdvanceDeletionTab(const FSpawnTabArgs& SpawnTabArgs)
{
	return SNew(SDockTab).TabRole(NomadTab)
	[
		SNew(SAdvanceDeletionTab)
		.AssetsDataList(GetAssetsDataUnderSelectedFolder())
	];
}

TArray<TSharedPtr<FAssetData>> FSuperManagerModule::GetAssetsDataUnderSelectedFolder()
{
	TArray<TSharedPtr<FAssetData>> AvailableAssetsData;

	auto AssetsPathNames = UEditorAssetLibrary::ListAssets(FolderPathsSelected[0]);

	for(const auto& AssetPathName : AssetsPathNames)
	{
		if(AssetPathName.Contains(TEXT("Developers")) ||
			AssetPathName.Contains(TEXT("Collections")) ||
			AssetPathName.Contains(TEXT("__ExternalActors__")) ||
			AssetPathName.Contains(TEXT("__ExternalObjects__")))
				continue;
		
		if(!UEditorAssetLibrary::DoesAssetExist(AssetPathName)) continue;
		
		const auto Data = UEditorAssetLibrary::FindAssetData(AssetPathName);
		AvailableAssetsData.Add(MakeShared<FAssetData>(Data));
	}

	return AvailableAssetsData;
}

void FSuperManagerModule::InitLevelEditorExtension()
{
	auto& LevelEditorModule = FModuleManager::LoadModuleChecked<FLevelEditorModule>(TEXT("LevelEditor"));

	TSharedRef<FUICommandList> ExisitingLevelCommands = LevelEditorModule.GetGlobalLevelEditorActions();
	ExisitingLevelCommands->Append(CustomUICommands.ToSharedRef());

	TArray<FLevelEditorModule::FLevelViewportMenuExtender_SelectedActors>& LevelEditorMenuExtenders = LevelEditorModule.GetAllLevelViewportContextMenuExtenders();
	LevelEditorMenuExtenders.Add(FLevelEditorModule::FLevelViewportMenuExtender_SelectedActors::CreateRaw(this, &FSuperManagerModule::CustomLevelEditorMenuExtender));
}

TSharedRef<FExtender> FSuperManagerModule::CustomLevelEditorMenuExtender(const TSharedRef<FUICommandList> CommandList,
	const TArray<AActor*> SelectedActors)
{
	TSharedRef<FExtender> MenuExtender = MakeShareable(new FExtender());

	if(SelectedActors.Num()> 0)
	{
		MenuExtender->AddMenuExtension(FName("ActorOptions"),
			EExtensionHook::After,
			CommandList,
			FMenuExtensionDelegate::CreateRaw(this, &FSuperManagerModule::AddLevelEditorMenuExtension));
	}
	
	return MenuExtender;
}

void FSuperManagerModule::AddLevelEditorMenuExtension(FMenuBuilder& MenuBuilder)
{
	MenuBuilder.AddMenuEntry(FText::FromString("LockActorInLevel"), FText::FromString("LockActorInLevel"),
		FSlateIcon(), FExecuteAction::CreateRaw(this, &FSuperManagerModule::OnLockActorInLevel));

	MenuBuilder.AddMenuEntry(FText::FromString("UnlockActorInLevel"), FText::FromString("UnlockActorInLevel"),
		FSlateIcon(),FExecuteAction::CreateRaw(this, &FSuperManagerModule::OnUnlockActorInLevel));
}

void FSuperManagerModule::OnLockActorInLevel()
{
	if(!SetEditorActorSubsystem()) return;

	TArray<AActor*> SelectedActors = WeakEditorActorSubsystem->GetSelectedLevelActors();
	if(SelectedActors.Num() == 0) return;

	for(AActor* SelectedActor : SelectedActors)
	{
		LockActorSelection(SelectedActor);
		WeakEditorActorSubsystem->SetActorSelectionState(SelectedActor, false);
	}
}

void FSuperManagerModule::OnUnlockActorInLevel()
{
	if(!SetEditorActorSubsystem()) return;

	TArray<AActor*> AllActorsInLevel = WeakEditorActorSubsystem->GetAllLevelActors();
	TArray<AActor*> AllLockedActors;

	for(AActor* Actor : AllActorsInLevel)
	{
		if(!Actor) continue;

		if(CheckIsActorSelectionLocked(Actor))
		{
			AllLockedActors.Add(Actor);
		}
	}

	if(AllLockedActors.Num()==0)
		return;

	for(AActor* LockedActor : AllLockedActors)
	{
		UnlockActorSelection(LockedActor);
	}
}

void FSuperManagerModule::InitCustomSelectionEvent()
{
	USelection* UserSelection = GEditor->GetSelectedActors();
	UserSelection->SelectObjectEvent.AddRaw(this,&FSuperManagerModule::OnActorSelected);
}

void FSuperManagerModule::OnActorSelected(UObject* SelectedObject)
{
	if(!SetEditorActorSubsystem()) return;
	if(AActor* SelectedActor = Cast<AActor>(SelectedObject);SelectedActor)
	{
		if(CheckIsActorSelectionLocked(SelectedActor))
		{
			WeakEditorActorSubsystem->SetActorSelectionState(SelectedActor, false);
		}
	}
}

void FSuperManagerModule::LockActorSelection(AActor* ActorToProcess)
{
	if(!ActorToProcess) return;
	if(ActorToProcess->ActorHasTag(FName("Locked"))) return;
	ActorToProcess->Tags.Add(FName("Locked"));
}

void FSuperManagerModule::UnlockActorSelection(AActor* ActorToProcess)
{
	if(!ActorToProcess) return;
	if(!ActorToProcess->ActorHasTag(FName("Locked"))) return;
	ActorToProcess->Tags.Remove(FName("Locked"));
}

bool FSuperManagerModule::CheckIsActorSelectionLocked(AActor* ActorToProcess)
{
	return ActorToProcess->ActorHasTag(FName("Locked"));
}

void FSuperManagerModule::InitCustomUICommands()
{
	CustomUICommands = MakeShareable(new FUICommandList());
	CustomUICommands->MapAction(FSuperManagerUICommands::Get().LockActorSelection,FExecuteAction::CreateRaw(this, &FSuperManagerModule::OnSelectionLockHotKeyPressed));
	CustomUICommands->MapAction(FSuperManagerUICommands::Get().UnlockActorSelection,FExecuteAction::CreateRaw(this, &FSuperManagerModule::OnSelectionUnlockHotKeyPressed));
}

void FSuperManagerModule::OnSelectionLockHotKeyPressed()
{
	OnLockActorInLevel();
}

void FSuperManagerModule::OnSelectionUnlockHotKeyPressed()
{
	OnUnlockActorInLevel();
}


#pragma endregion

#pragma region ProccessDataForAdvanceDeletionTab

bool FSuperManagerModule::SetEditorActorSubsystem()
{
	if(!WeakEditorActorSubsystem.IsValid())
	{
		WeakEditorActorSubsystem = GEditor->GetEditorSubsystem<UEditorActorSubsystem>();
	}
	return WeakEditorActorSubsystem.IsValid();
}

bool FSuperManagerModule::DeleteSingleAssetForAssetList(const FAssetData& AssetData)
{
	return ObjectTools::DeleteAssets({AssetData},true) != 0;
}

int32 FSuperManagerModule::DeleteAssetsForAssetList(const TArray<FAssetData>& AssetDataList)
{
	return ObjectTools::DeleteAssets(AssetDataList, true);
}

void FSuperManagerModule::ListUnusedAssetsForAssetList(const TArray<TSharedPtr<FAssetData>>& AssetsDataToFilter,
	TArray<TSharedPtr<FAssetData>>& OutUnusedAssetData)
{
	OutUnusedAssetData.Empty();
	for(const TSharedPtr<FAssetData>& DataSharedPtr : AssetsDataToFilter)
	{
		TArray<FString> AssetReferences = UEditorAssetLibrary::FindPackageReferencersForAsset(DataSharedPtr->ObjectPath.ToString());
		if(AssetReferences.Num() == 0)
		{
			OutUnusedAssetData.Add(DataSharedPtr);
		}
	}
}

void FSuperManagerModule::ListSameNameAssetsForAssetList(const TArray<TSharedPtr<FAssetData>>& AssetsDataToFilter,
	TArray<TSharedPtr<FAssetData>>& OutSameNameAssetsData)
{
	OutSameNameAssetsData.Empty();
	TMultiMap<FName, TSharedPtr<FAssetData>> AssetsInfoMultiMap;
	for(const TSharedPtr<FAssetData>& DataSharedPtr : AssetsDataToFilter)
	{
		AssetsInfoMultiMap.Emplace(DataSharedPtr->AssetName, DataSharedPtr);
	}

	for(const TSharedPtr<FAssetData>& DataSharedPtr : AssetsDataToFilter)
	{
		TArray<TSharedPtr<FAssetData>> OutAssetsData;
		AssetsInfoMultiMap.MultiFind(DataSharedPtr->AssetName, OutAssetsData);

		if(OutAssetsData.Num() > 1)
		{
			for(const TSharedPtr<FAssetData>& AssetData : OutAssetsData)
			{
				OutSameNameAssetsData.AddUnique(AssetData);
			}
		}
	}
}

void FSuperManagerModule::SyncCBToClickedAssetForAssetList(const FString& AssetPathToSync)
{
	TArray<FString> Paths{AssetPathToSync};
	UEditorAssetLibrary::SyncBrowserToObjects(Paths);
}
#pragma endregion ProccessDataForAdvanceDeletionTab
#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FSuperManagerModule, SuperManager)