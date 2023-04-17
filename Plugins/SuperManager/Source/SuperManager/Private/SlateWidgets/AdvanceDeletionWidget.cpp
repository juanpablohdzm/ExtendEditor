// Fill out your copyright notice in the Description page of Project Settings.


#include "SlateWidgets/AdvanceDeletionWidget.h"
#include "SuperManager.h"
#include "Widgets/Layout/SScrollBox.h"

#define ListAll TEXT("List All Available Assets")
#define ListUnused TEXT("List Unused Assets")
#define ListSameName TEXT("List Assets With Same Name")

void SAdvanceDeletionTab::Construct(const FArguments& InArgs)
{
	bCanSupportFocus = true;
	StoredAssetsData = InArgs._AssetsDataList;
	DisplayAssetData = StoredAssetsData;
	ComboBoxSourceItems.Empty();

	ComboBoxSourceItems.Add(MakeShared<FString>(ListAll));
	ComboBoxSourceItems.Add(MakeShared<FString>(ListUnused));
	ComboBoxSourceItems.Add(MakeShared<FString>(ListSameName));

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
			+SHorizontalBox::Slot()
			.AutoWidth()
			[
				ConstructComboBox()
			]
			
		]
		//Third slot for the asset list
		+SVerticalBox::Slot()
		.VAlign(VAlign_Fill)
		[
			SNew(SScrollBox)
			+SScrollBox::Slot()
			[
				ConstructAssetListView()
				
			]
		]
		//Fourth slot for the buttons
		+SVerticalBox::Slot()
		.AutoHeight()
		[
			SNew(SHorizontalBox)
			+SHorizontalBox::Slot()
			.HAlign(HAlign_Center)
			.VAlign(VAlign_Center)
			[
				SNew(SButton)
				.Text(FText::FromString("Delete All"))
				.OnClicked(this, &SAdvanceDeletionTab::OnDeleteAllButtonClicked)
			]
			+SHorizontalBox::Slot()
			.HAlign(HAlign_Center)
			.VAlign(VAlign_Center)
			[
				SNew(SButton)
				.Text(FText::FromString("Select All"))
				.OnClicked(this, &SAdvanceDeletionTab::OnSelectAllButtonClicked)
			]
			+SHorizontalBox::Slot()
			.HAlign(HAlign_Center)
			.VAlign(VAlign_Center)
			[
				SNew(SButton)
				.Text(FText::FromString("Deselect All"))
				.OnClicked(this, &SAdvanceDeletionTab::OnDeselectAllButtonClicked)
			]
		]
	];
}

TSharedRef<SListView<TSharedPtr<FAssetData>>> SAdvanceDeletionTab::ConstructAssetListView()
{
	ConstructedAssetListView =  SNew(SListView<TSharedPtr<FAssetData>> )
				.ItemHeight(24.f)
				.ListItemsSource(&DisplayAssetData)
				.OnGenerateRow(this, &SAdvanceDeletionTab::OnGenerateRowForList)
	.OnMouseButtonClick(this, &SAdvanceDeletionTab::OnMouseButtonClickForList);

	return ConstructedAssetListView.ToSharedRef();

}

TSharedRef<ITableRow> SAdvanceDeletionTab::OnGenerateRowForList(TSharedPtr<FAssetData> AssetDataToDisplay,
                                                                const TSharedRef<STableViewBase>& OwnerTable)
{
	if(!AssetDataToDisplay.IsValid()) return SNew(STableRow<TSharedPtr<FAssetData>>, OwnerTable);
	const FString DisplayAssetName = AssetDataToDisplay->AssetName.ToString();
	const FString DisplayAssetClassName = AssetDataToDisplay->AssetClassPath.ToString();
	
	
	return SNew(STableRow<TSharedPtr<FAssetData>>, OwnerTable).Padding(FMargin(5.f))
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
		.HAlign(HAlign_Center)
		.VAlign(VAlign_Fill)
		.FillWidth(0.2f)
		[
			ConstructTextForRowWidget(DisplayAssetClassName, FCoreStyle::Get().GetFontStyle("EmbossedText"))
		]
		+SHorizontalBox::Slot()
		[
			ConstructTextForRowWidget(DisplayAssetName, FCoreStyle::Get().GetFontStyle("EmbossedText"))
		]
		+SHorizontalBox::Slot()
		.HAlign(HAlign_Right)
		.VAlign(VAlign_Fill)
		[
			ConstructButtonForRowWidget(AssetDataToDisplay)
		]
	];
}

TSharedRef<SCheckBox> SAdvanceDeletionTab::ConstructCheckbox(const TSharedPtr<FAssetData>& AssetDataToDisplay)
{
	TSharedRef<SCheckBox> CheckBox =  SNew(SCheckBox)
	.Type(ESlateCheckBoxType::CheckBox)
	.OnCheckStateChanged(this, &SAdvanceDeletionTab::OnCheckBoxStateChanged, AssetDataToDisplay)
	.Visibility(EVisibility::Visible);

	ConstructedCheckBoxes.Add(CheckBox);
	return CheckBox;
}

TSharedRef<STextBlock> SAdvanceDeletionTab::ConstructTextForRowWidget(const FString& TextContent,
	const FSlateFontInfo& FontInfo)
{
	return SNew(STextBlock)
	.Text(FText::FromString(TextContent))
	.Font(FontInfo)
	.ColorAndOpacity(FColor::White);
}

TSharedRef<SButton> SAdvanceDeletionTab::ConstructButtonForRowWidget(const TSharedPtr<FAssetData>& AssetData)
{
	return SNew(SButton)
	.Text(FText::FromString(TEXT("Delete")))
	.OnClicked(this, &SAdvanceDeletionTab::OnDeleteButtonClicked, AssetData);
}

TSharedRef<SComboBox<TSharedPtr<FString>>> SAdvanceDeletionTab::ConstructComboBox()
{
	return SNew(SComboBox<TSharedPtr<FString>>)
	.OptionsSource(&ComboBoxSourceItems)
	.OnGenerateWidget(this, &SAdvanceDeletionTab::OnGenerateComboBoxItem)
	.OnSelectionChanged(this, &SAdvanceDeletionTab::OnComboBoxSelectionChanged)
	[
		SAssignNew(ComboDisplayTextBlock, STextBlock).Text(FText::FromString(TEXT("List Assets Option")))
	];
}

TSharedRef<SWidget> SAdvanceDeletionTab::OnGenerateComboBoxItem(TSharedPtr<FString> SourceItem)
{
	return SNew(STextBlock).Text(FText::FromString(*SourceItem));
}

void SAdvanceDeletionTab::OnComboBoxSelectionChanged(TSharedPtr<FString> SelectedOption, ESelectInfo::Type InSelectInfo)
{
	ComboDisplayTextBlock->SetText(FText::FromString(*SelectedOption));

	FSuperManagerModule& SuperManagerModule = FModuleManager::LoadModuleChecked<FSuperManagerModule>(FName(TEXT("SuperManager")));

	if(*SelectedOption == ListAll)
	{
		DisplayAssetData = StoredAssetsData;
		RefreshAssetListView();
	}
	if(*SelectedOption == ListUnused)
	{
		SuperManagerModule.ListUnusedAssetsForAssetList(StoredAssetsData, DisplayAssetData);
	}
	
	if(*SelectedOption == ListSameName)
	{
		SuperManagerModule.ListSameNameAssetsForAssetList(StoredAssetsData, DisplayAssetData);
	}
	
	RefreshAssetListView();
	
}

void SAdvanceDeletionTab::OnMouseButtonClickForList(TSharedPtr<FAssetData, ESPMode::ThreadSafe> AssetData)
{
	FSuperManagerModule& SuperManagerModule = FModuleManager::LoadModuleChecked<FSuperManagerModule>(FName(TEXT("SuperManager")));
	SuperManagerModule.SyncCBToClickedAssetForAssetList(AssetData->GetObjectPathString());
}

void SAdvanceDeletionTab::OnCheckBoxStateChanged(ECheckBoxState NewState, TSharedPtr<FAssetData> AssetData)
{
	switch (NewState)
	{
		case ECheckBoxState::Unchecked:
			if(CheckedAssetsData.Contains(AssetData))
				CheckedAssetsData.Remove(AssetData);
			break;
		case ECheckBoxState::Checked:
			if(!CheckedAssetsData.Contains(AssetData))
				CheckedAssetsData.Add(AssetData);
			break;
		case ECheckBoxState::Undetermined:
			break;
		default: ;
	}
}

FReply SAdvanceDeletionTab::OnDeleteButtonClicked(TSharedPtr<FAssetData> ClickedAssetData)
{
	FSuperManagerModule& SuperManagerModule = FModuleManager::LoadModuleChecked<FSuperManagerModule>(FName(TEXT("SuperManager")));
	const bool bWasAssetDeleted = SuperManagerModule.DeleteSingleAssetForAssetList(*ClickedAssetData);
	if(bWasAssetDeleted)
	{
		if(StoredAssetsData.Contains(ClickedAssetData))
		{
			StoredAssetsData.Remove(ClickedAssetData);
		}

		if(DisplayAssetData.Contains(ClickedAssetData))
		{
			DisplayAssetData.Remove(ClickedAssetData);
		}
		RefreshAssetListView();
		
	}
	return FReply::Handled();
}

FReply SAdvanceDeletionTab::OnDeleteAllButtonClicked()
{
	FSuperManagerModule& SuperManagerModule = FModuleManager::LoadModuleChecked<FSuperManagerModule>(FName(TEXT("SuperManager")));
	TArray<FAssetData> AssetsToDelete;
	for(const TSharedPtr<FAssetData>& AssetData : CheckedAssetsData)
	{
		AssetsToDelete.Add(*AssetData);
	}
	const int32 DeletedAssetsCount = SuperManagerModule.DeleteAssetsForAssetList(AssetsToDelete);
	if(DeletedAssetsCount == StoredAssetsData.Num())
	{
		StoredAssetsData.Empty();
		RefreshAssetListView();
	}
	return FReply::Handled();
}

FReply SAdvanceDeletionTab::OnSelectAllButtonClicked()
{
	for (const TSharedRef<SCheckBox> CheckBox : ConstructedCheckBoxes)
	{
		if(!CheckBox->IsChecked())
			CheckBox->ToggleCheckedState();
	}

	return FReply::Handled();
}

FReply SAdvanceDeletionTab::OnDeselectAllButtonClicked()
{
	for (const TSharedRef<SCheckBox> CheckBox : ConstructedCheckBoxes)
	{
		if(CheckBox->IsChecked())
			CheckBox->ToggleCheckedState();
	}
	return FReply::Handled();
}

void SAdvanceDeletionTab::RefreshAssetListView()
{
	if(!ConstructedAssetListView.IsValid()) return;

	ConstructedCheckBoxes.Empty();
	CheckedAssetsData.Empty();
	ConstructedAssetListView->RebuildList();
}
