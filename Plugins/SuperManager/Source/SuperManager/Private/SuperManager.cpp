// Copyright Epic Games, Inc. All Rights Reserved.

#include "SuperManager.h"

#include "AssetToolsModule.h"
#include "ContentBrowserModule.h"
#include "EditorAssetLibrary.h"
#include "EditorUtilityLibrary.h"
#include "ObjectTools.h"
#include "AssetRegistry/AssetRegistryModule.h"
#include "SlateWidgets/AdvanceDeletionWidget.h"

#define LOCTEXT_NAMESPACE "FSuperManagerModule"

void FSuperManagerModule::StartupModule()
{
	InitCBMenuExtension();
	RegisterAdvanceDeletionTab();
}

void FSuperManagerModule::ShutdownModule()
{
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
		FSlateIcon(),
		FExecuteAction::CreateRaw(this, &FSuperManagerModule::OnDeleteUnusedAssetsButtonClicked)
		);
	MenuBuilder.AddMenuEntry(
	FText::FromString(TEXT("Delete Empty Folders")),
	FText::FromString(TEXT("Safely delete all empty folders in selected folder")),
	FSlateIcon(),
	FExecuteAction::CreateRaw(this, &FSuperManagerModule::OnDeleteEmptyFoldersButtonClicked)
	);
	MenuBuilder.AddMenuEntry(
		FText::FromString(TEXT("Advance deletion ")),
		FText::FromString(TEXT("Open advanced deletion tab")),
		FSlateIcon(),
		FExecuteAction::CreateRaw(this, &FSuperManagerModule::OnOpenAdvanceDeletionTabButtonClicked)
	);
}

void FSuperManagerModule::OnOpenAdvanceDeletionTabButtonClicked()
{
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
		FOnSpawnTab::CreateRaw(this, &FSuperManagerModule::OnSpawnAdvanceDeletionTab )).SetDisplayName(FText::FromString(TEXT("Advance Deletion")));
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

#pragma endregion 
#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FSuperManagerModule, SuperManager)