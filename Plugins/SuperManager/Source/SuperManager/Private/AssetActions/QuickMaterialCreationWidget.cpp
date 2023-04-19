// Fill out your copyright notice in the Description page of Project Settings.


#include "AssetActions/QuickMaterialCreationWidget.h"
#include "DebugHeader.h"
#include "EditorUtilityLibrary.h"

#pragma region QuickMaterialCreationCore

void UQuickMaterialCreationWidget::CreateMaterialFromSelectedTextures()
{
	if(bCustomMaterialName)
	{
		if(MaterialName.IsEmpty() == MaterialName.Equals(TEXT("M_")))
		{
			ShowMessageDialog("Please Enter a valid name", FText::FromString("Valid Name"), EAppMsgType::Ok);
			return;
		}
	}

	TArray<FAssetData> SelectedAssetsData = UEditorUtilityLibrary::GetSelectedAssetData();
	TArray<UTexture2D*> SelectedTexturesArray;
	FString SelectedTexturePackagePath;
	if(!ProcessSelectedData(SelectedAssetsData, SelectedTexturesArray, SelectedTexturePackagePath)) return;
	
	
}

bool UQuickMaterialCreationWidget::ProcessSelectedData(const TArray<FAssetData>& SelectedDataToProcess,
                                                       TArray<UTexture2D*>& OutSelectedTexturesArray,
                                                       FString& OutSelectedTexturePackagePath)
{
	if(SelectedDataToProcess.Num() == 0)
	{
		ShowMessageDialog("No Texture Selected", FText::FromString("No texture"),EAppMsgType::Ok);
		return false;
	}

	bool bMaterialNameSet = false;
	for(const FAssetData& SelectedData : SelectedDataToProcess)
	{
		UObject* SelectedAsset = SelectedData.GetAsset();

		if(!SelectedAsset) continue;

		UTexture2D* SelectedTexture = Cast<UTexture2D>(SelectedAsset);
		if(!SelectedTexture)
		{
			ShowMessageDialog("Wrong texture selection", FText::FromString("Wrong texture"),EAppMsgType::Ok);
			return false;
		}

		OutSelectedTexturesArray.Add(SelectedTexture);

		if(OutSelectedTexturePackagePath.IsEmpty())
			OutSelectedTexturePackagePath = SelectedData.PackagePath.ToString();

		if(!bCustomMaterialName && !bMaterialNameSet)
		{
			MaterialName = SelectedAsset->GetName();
			MaterialName.RemoveFromStart(TEXT("T_"));
			MaterialName.InsertAt(0, TEXT("M_"));
			bMaterialNameSet = true;
		}
		
		
	}

	return true;
}

#pragma endregion QuickMaterialCreationCore
