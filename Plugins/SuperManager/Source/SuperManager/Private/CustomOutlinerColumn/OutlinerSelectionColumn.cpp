// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomOutlinerColumn/OutlinerSelectionColumn.h"

#include "ActorTreeItem.h"
#include "ISceneOutlinerTreeItem.h"
#include "SuperManager.h"
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
	FActorTreeItem* ActorTreeItem = TreeItem->CastTo<FActorTreeItem>();
	if(!ActorTreeItem || !ActorTreeItem->IsValid()) return SNullWidget::NullWidget;

	FSuperManagerModule& SuperManagerModule = FModuleManager::LoadModuleChecked<FSuperManagerModule>(TEXT("SuperManager"));
	const bool bIsActorSelectionLocked = SuperManagerModule.CheckIsActorSelectionLocked(ActorTreeItem->Actor.Get());
	
	TSharedRef<SCheckBox> ConstructedRowWidgetCheckBox = SNew(SCheckBox)
	.Visibility(EVisibility::Visible)
	.HAlign(HAlign_Center)
	.IsChecked(bIsActorSelectionLocked ? ECheckBoxState::Checked : ECheckBoxState::Unchecked)
	.OnCheckStateChanged(this,&FOutlinerSelectionLockColumn::OnRowWidgetCheckStateChanged, ActorTreeItem->Actor);

	return ConstructedRowWidgetCheckBox;
}

void FOutlinerSelectionLockColumn::OnRowWidgetCheckStateChanged(ECheckBoxState NewState, TWeakObjectPtr<AActor> ActorTreeItem)
{
	FSuperManagerModule& SuperManagerModule = FModuleManager::LoadModuleChecked<FSuperManagerModule>(TEXT("SuperManager"));

	switch (NewState) {
	case ECheckBoxState::Unchecked:

		SuperManagerModule.ProcessLockingForOutliner(ActorTreeItem.Get(),false);
		break;
	case ECheckBoxState::Checked:
		SuperManagerModule.ProcessLockingForOutliner(ActorTreeItem.Get(),true);
		break;
	case ECheckBoxState::Undetermined: break;
	default: ;
	}
}
