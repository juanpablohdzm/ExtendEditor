// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Widgets/SCompoundWidget.h"

class SAdvanceDeletionTab : public SCompoundWidget
{
	SLATE_BEGIN_ARGS(SAdvanceDeletionTab){}

	SLATE_ARGUMENT(TArray<TSharedPtr<FAssetData>>, AssetsDataList);
	
	SLATE_END_ARGS()
public:
	
	void Construct(const FArguments& InArgs);

private:


#pragma region WidgetConstructor

	TSharedRef<SCheckBox> ConstructCheckbox(const TSharedPtr<FAssetData>& AssetDataToDisplay);
#pragma region ConstructAssetListView
	TSharedRef<SListView<TSharedPtr<FAssetData>>> ConstructAssetListView();
	TSharedRef<STextBlock> ConstructTextForRowWidget(const FString& TextContent, const FSlateFontInfo& FontInfo);
	TSharedRef<SButton> ConstructButtonForRowWidget(const TSharedPtr<FAssetData>& AssetData);
#pragma region ConstructAssetListView
	TSharedRef<SComboBox<TSharedPtr<FString>>> ConstructComboBox();
	TSharedRef<SWidget> OnGenerateComboBoxItem(TSharedPtr<FString> SourceItem);
	void OnComboBoxSelectionChanged(TSharedPtr<FString> SelectedOption, ESelectInfo::Type InSelectInfo);
	void OnMouseButtonClickForList(TSharedPtr<FAssetData, ESPMode::ThreadSafe> AssetData);
	TSharedPtr<STextBlock> ComboDisplayTextBlock;
	
#pragma endregion WidgetConstructor


#pragma region AssetListView
	TSharedRef<ITableRow> OnGenerateRowForList(TSharedPtr<FAssetData> AssetDataToDisplay, const TSharedRef<STableViewBase>& OwnerTable);
	void RefreshAssetListView();
#pragma endregion AssetListView
	
	void OnCheckBoxStateChanged(ECheckBoxState NewState, TSharedPtr<FAssetData> AssetData);
	FReply OnDeleteButtonClicked(TSharedPtr<FAssetData> ClickedAssetData);
	FReply OnDeleteAllButtonClicked();
	FReply OnSelectAllButtonClicked();
	FReply OnDeselectAllButtonClicked();

	TSharedPtr<SListView<TSharedPtr<FAssetData>>> ConstructedAssetListView;
	TArray<TSharedRef<SCheckBox>> ConstructedCheckBoxes;
	TArray<TSharedPtr<FAssetData>> CheckedAssetsData;
	TArray<TSharedPtr<FAssetData>> StoredAssetsData;
	TArray<TSharedPtr<FAssetData>> DisplayAssetData;
	TArray<TSharedPtr<FString>> ComboBoxSourceItems;

};
