// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

class FSuperManagerModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

private:

#pragma region ContentBrowserMenuExtension

	void InitCBMenuExtension();

	TSharedRef<FExtender> CustomCBMenuExtender(const TArray<FString>& SelectedPaths);

	void AddCBMenuEntry(class FMenuBuilder& MenuBuilder);
	void OnOpenAdvanceDeletionTabButtonClicked();
	void OnDeleteEmptyFoldersButtonClicked();
	void OnDeleteUnusedAssetsButtonClicked();

private:
	TArray<FString> FolderPathsSelected;

	void FixUpRedirectors();

#pragma  endregion

#pragma region CustomEditorTab

public:
	void RegisterAdvanceDeletionTab();
	TSharedRef<SDockTab> OnSpawnAdvanceDeletionTab(const FSpawnTabArgs& SpawnTabArgs);
	TArray<TSharedPtr<FAssetData>> GetAssetsDataUnderSelectedFolder();
	
#pragma endregion

#pragma region LevelEditorMenuExtension

	void InitLevelEditorExtension();

	TSharedRef<FExtender> CustomLevelEditorMenuExtender(const TSharedRef<FUICommandList> CommandList, const TArray<AActor*> SelectedActors);
	void AddLevelEditorMenuExtension(FMenuBuilder& MenuBuilder);
	void OnLockActorInLevel();
	void OnUnlockActorInLevel();
#pragma  endregion 

#pragma region SelectionLock

	void InitCustomSelectionEvent();
	void OnActorSelected(UObject* SelectedObject);
#pragma endregion 

public:
#pragma region ProccessDataForAdvanceDeletionTab

	bool DeleteSingleAssetForAssetList(const FAssetData& AssetData);
	int32 DeleteAssetsForAssetList(const TArray<FAssetData>& AssetDataList);
	void ListUnusedAssetsForAssetList( const TArray<TSharedPtr<FAssetData>>& AssetsDataToFilter, TArray<TSharedPtr<FAssetData>>& OutUnusedAssetData);
	void ListSameNameAssetsForAssetList( const TArray<TSharedPtr<FAssetData>>&AssetsDataToFilter, TArray<TSharedPtr<FAssetData>>& OutSameNameAssetsData);
	void SyncCBToClickedAssetForAssetList(const FString& AssetPathToSync);
	#pragma endregion ProccessDataForAdvanceDeletionTab
};
