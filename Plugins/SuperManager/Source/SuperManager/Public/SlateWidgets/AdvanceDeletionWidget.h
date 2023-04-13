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
	TArray<TSharedPtr<FAssetData>> StoredAssetsData;
	TSharedRef<ITableRow> OnGenerateRowForList(TSharedPtr<FAssetData> AssetDataToDisplay, const TSharedRef<STableViewBase>& OwnerTable);
	TSharedRef<SCheckBox> ConstructCheckbox(const TSharedPtr<FAssetData>& AssetDataToDisplay);
	void OnCheckBoxStateChanged(ECheckBoxState NewState, TSharedPtr<FAssetData> AssetData);
};
