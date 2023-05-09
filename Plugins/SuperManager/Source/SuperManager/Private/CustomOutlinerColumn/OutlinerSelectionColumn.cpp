// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomOutlinerColumn/OutlinerSelectionColumn.h"

#include "CustomStyle/SuperManagerStyle.h"


FOutlinerSelectionLockColumn::FOutlinerSelectionLockColumn(ISceneOutliner& SceneOutliner)
{
}

FName FOutlinerSelectionLockColumn::GetColumnID()
{
	return FName("SelectionLock");
}

SHeaderRow::FColumn::FArguments FOutlinerSelectionLockColumn::ConstructHeaderRowColumn()
{
	return SHeaderRow::Column(GetColumnID())
	.FixedWidth(24.f)
	.HAlignHeader(HAlign_Center)
	.VAlignHeader(VAlign_Center)
	.HAlignCell(HAlign_Center)
	.VAlignCell(VAlign_Center)
	.DefaultTooltip(FText::FromString(TEXT("Actor Selection Lock")))
	[
		SNew(SImage)
		.ColorAndOpacity(FSlateColor::UseForeground())
		.Image(FSuperManagerStyle::GetCreatedStyleSet()->GetBrush(FName("ContentBrowser.DeleteUnusedAssets")))
	];
}

const TSharedRef<SWidget> FOutlinerSelectionLockColumn::ConstructRowWidget(FSceneOutlinerTreeItemRef TreeItem,
	const STableRow<FSceneOutlinerTreeItemPtr>& Row)
{
	return SNullWidget::NullWidget;
}
