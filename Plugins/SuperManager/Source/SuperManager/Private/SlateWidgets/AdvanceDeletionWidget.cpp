// Fill out your copyright notice in the Description page of Project Settings.


#include "SlateWidgets/AdvanceDeletionWidget.h"

#include "Widgets/Layout/SScrollBox.h"

void SAdvanceDeletionTab::Construct(const FArguments& InArgs)
{
	bCanSupportFocus = true;
	StoredAssetsData = InArgs._AssetsDataList;

	FSlateFontInfo TitleTextFont = FCoreStyle::Get().GetFontStyle(FName("EmbossedText"));
	TitleTextFont.Size = 30;
	ChildSlot
	[
		//Main vertical box
		SNew(SVerticalBox)
		//First vertical slot for title text
		+SVerticalBox::Slot()
		.AutoHeight()
		[
			SNew(STextBlock)
			.Text(FText::FromString("Advance Deletion"))
			.Font(TitleTextFont)
			.Justification(ETextJustify::Center)
			.ColorAndOpacity(FColor::White)
		]
		//Second slot for drop down to specify the listing conditions
		+SVerticalBox::Slot()
		.AutoHeight()
		[
			SNew(SHorizontalBox)
			
		]
		//Third slot for the asset list
		+SVerticalBox::Slot()
		.VAlign(VAlign_Fill)
		[
			SNew(SScrollBox)
			+SScrollBox::Slot()
			[
				SNew(SListView<TSharedPtr<FAssetData>> )
				.ItemHeight(24.f)
				.ListItemsSource(&StoredAssetsData)
				.OnGenerateRow(this, &SAdvanceDeletionTab::OnGenerateRowForList)
				
			]
		]
		//Fourth slot for the buttons
		+SVerticalBox::Slot()
		.AutoHeight()
		[
			SNew(SHorizontalBox)
		]
	];
}

TSharedRef<ITableRow> SAdvanceDeletionTab::OnGenerateRowForList(TSharedPtr<FAssetData> AssetDataToDisplay,
	const TSharedRef<STableViewBase>& OwnerTable)
{
	if(!AssetDataToDisplay.IsValid()) return SNew(STableRow<TSharedPtr<FAssetData>>, OwnerTable);
	const FString DisplayAssetName = AssetDataToDisplay->AssetName.ToString();
	
	
	return SNew(STableRow<TSharedPtr<FAssetData>>, OwnerTable)
	[
		SNew(SHorizontalBox)
		+SHorizontalBox::Slot()
		.HAlign(HAlign_Left)
		.VAlign(VAlign_Center)
		.FillWidth(0.05f)
		[
			ConstructCheckbox(AssetDataToDisplay)
		]
		+SHorizontalBox::Slot()
		[
			SNew(STextBlock)
			.Text(FText::FromString(DisplayAssetName))
		]
	];
}

TSharedRef<SCheckBox> SAdvanceDeletionTab::ConstructCheckbox(const TSharedPtr<FAssetData>& AssetDataToDisplay)
{
	return SNew(SCheckBox)
	.Type(ESlateCheckBoxType::CheckBox)
	.OnCheckStateChanged(this, &SAdvanceDeletionTab::OnCheckBoxStateChanged, AssetDataToDisplay)
	.Visibility(EVisibility::Visible);
}

void SAdvanceDeletionTab::OnCheckBoxStateChanged(ECheckBoxState NewState, TSharedPtr<FAssetData> AssetData)
{
	switch (NewState)
	{
		case ECheckBoxState::Unchecked:
			break;
		case ECheckBoxState::Checked:
			break;
		case ECheckBoxState::Undetermined:
			break;
		default: ;
	}
}
