// Copyright Epic Games, Inc. All Rights Reserved.

#include "SuperManager.h"

#include "ContentBrowserModule.h"
#include "EditorAssetLibrary.h"
#include "EditorUtilityLibrary.h"
#include "ObjectTools.h"

#define LOCTEXT_NAMESPACE "FSuperManagerModule"

void FSuperManagerModule::StartupModule()
{
	InitCBMenuExtension();
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
}

void FSuperManagerModule::OnDeleteUnusedAssetsButtonClicked()
{
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
#pragma endregion 
#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FSuperManagerModule, SuperManager)