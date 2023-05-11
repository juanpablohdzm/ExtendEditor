// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomStyle/SuperManagerStyle.h"
#include "Interfaces/IPluginManager.h"
#include "Styling/SlateStyleRegistry.h"
#include "Styling/StyleColors.h"

FName FSuperManagerStyle::StyleSetName = FName("SuperManagerStyle");
TSharedPtr<FSlateStyleSet> FSuperManagerStyle::CreatedSlateStyleSet = nullptr;

void FSuperManagerStyle::InitializeIcons()
{
	if(!CreatedSlateStyleSet)
	{
		CreatedSlateStyleSet = CreateSlateStyleSet();
		FSlateStyleRegistry::RegisterSlateStyle(*CreatedSlateStyleSet);
	}
}

TSharedRef<FSlateStyleSet> FSuperManagerStyle::CreateSlateStyleSet()
{
	TSharedRef<FSlateStyleSet>CustomStyleSet = MakeShareable(new FSlateStyleSet(StyleSetName));

	const auto IconDirectory =  IPluginManager::Get().FindPlugin(TEXT("SuperManager"))->GetBaseDir()/"Resources";
	const auto Icon16x16  = FVector2d(16.f,16.f);

	CustomStyleSet->SetContentRoot(IconDirectory);
	CustomStyleSet->Set("ContentBrowser.DeleteUnusedAssets",
		new FSlateImageBrush(IconDirectory/"DeleteUnusedAsset.png",
			Icon16x16));
	CustomStyleSet->Set("ContentBrowser.DeleteEmptyFolders",
		new FSlateImageBrush(IconDirectory/"DeleteEmptyFolders.png",
			Icon16x16));
	CustomStyleSet->Set("ContentBrowser.AdvanceDeletion",
		new FSlateImageBrush(IconDirectory/"AdvanceDeletion.png",
			Icon16x16));

	const FCheckBoxStyle SelectionLockToggleButtonStyle =FCheckBoxStyle()
	.SetCheckBoxType(ESlateCheckBoxType::ToggleButton)
	.SetPadding(FMargin(10.0f))
	.SetUncheckedImage(FSlateImageBrush(IconDirectory/"DeleteUnusedAsset.png", Icon16x16,FStyleColors::White25))
	.SetUncheckedHoveredImage(FSlateImageBrush(IconDirectory/"DeleteUnusedAsset.png", Icon16x16,FStyleColors::AccentBlue))
	.SetUncheckedPressedImage(FSlateImageBrush(IconDirectory/"DeleteUnusedAsset.png", Icon16x16,FStyleColors::Foreground))
	.SetCheckedImage(FSlateImageBrush(IconDirectory/"DeleteUnusedAsset.png", Icon16x16,FStyleColors::Foreground))
	.SetCheckedHoveredImage(FSlateImageBrush(IconDirectory/"DeleteUnusedAsset.png", Icon16x16,FStyleColors::AccentBlack))
	.SetCheckedPressedImage(FSlateImageBrush(IconDirectory/"DeleteUnusedAsset.png", Icon16x16,FStyleColors::AccentGray));
	
	
	CustomStyleSet->Set("SceneOutliner.SelectionLock", SelectionLockToggleButtonStyle);
	return CustomStyleSet;
}

void FSuperManagerStyle::ShutDown()
{
	if(CreatedSlateStyleSet.IsValid())
	{
		FSlateStyleRegistry::UnRegisterSlateStyle(*CreatedSlateStyleSet);
		CreatedSlateStyleSet.Reset();
	}
}

