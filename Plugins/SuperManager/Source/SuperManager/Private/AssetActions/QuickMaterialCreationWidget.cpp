// Fill out your copyright notice in the Description page of Project Settings.


#include "AssetActions/QuickMaterialCreationWidget.h"

#include "AssetToolsModule.h"
#include "DebugHeader.h"
#include "EditorAssetLibrary.h"
#include "EditorUtilityLibrary.h"
#include "Factories/MaterialFactoryNew.h"

#pragma region QuickMaterialCreationCore

void UQuickMaterialCreationWidget::CreateMaterialFromSelectedTextures()
{
	if(bCustomMaterialName)
	{
		if(MaterialName.IsEmpty() || MaterialName.Equals(TEXT("M_")))
		{
			ShowMessageDialog("Please Enter a valid name", FText::FromString("Valid Name"), EAppMsgType::Ok);
			return;
		}
	}

	TArray<FAssetData> SelectedAssetsData = UEditorUtilityLibrary::GetSelectedAssetData();
	TArray<UTexture2D*> SelectedTexturesArray;
	FString SelectedTexturePackagePath;
	if(!ProcessSelectedData(SelectedAssetsData, SelectedTexturesArray, SelectedTexturePackagePath)) return;
	
	if(CheckIsNameUsed(SelectedTexturePackagePath, MaterialName)) return;

	UMaterial* CreatedMaterial = CreateMaterialAsset(MaterialName, SelectedTexturePackagePath);

	if(!CreatedMaterial)
	{
		ShowMessageDialog("Failed to create material", FText::FromString("Material"), EAppMsgType::Ok);
		return;
	}

	uint32 PinsConnectedCounter = 0;
	for(UTexture2D* SelectedTexture : SelectedTexturesArray)
	{
		if(!SelectedTexture) continue;

		CreateMaterialNodes(CreatedMaterial, SelectedTexture, PinsConnectedCounter);
	}

	if(PinsConnectedCounter > 0)
	{
		ShowNotifyInfo(TEXT("Successfully connected"));
	}
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

bool UQuickMaterialCreationWidget::CheckIsNameUsed(const FString& FolderPathToCheck, const FString& MaterialNameToCheck)
{
	const auto Assets = UEditorAssetLibrary::ListAssets(FolderPathToCheck, false);
	for (const auto Asset : Assets)
	{
		const FString ExistingAssetName = FPaths::GetBaseFilename(Asset);
		if(ExistingAssetName.Equals(MaterialNameToCheck))
		{
			ShowMessageDialog("Name already used", FText::FromString("Name used"),EAppMsgType::Ok);
			return true;
		}
	}
	return false;
}

UMaterial* UQuickMaterialCreationWidget::CreateMaterialAsset(const FString& NameOfMaterial, const FString& Path)
{
	FAssetToolsModule& AssetToolsModule = FModuleManager::LoadModuleChecked<FAssetToolsModule>(TEXT("AssetTools"));
	UMaterialFactoryNew* MaterialFactory = NewObject<UMaterialFactoryNew>();
	UObject* CreatedObject =  AssetToolsModule.Get().CreateAsset(NameOfMaterial, Path, UMaterial::StaticClass(),MaterialFactory);
	return Cast<UMaterial>(CreatedObject);
}

void UQuickMaterialCreationWidget::CreateMaterialNodes(UMaterial* CreatedMaterial, UTexture2D* SelectedTexture,
	uint32& PinConnectedCounter)
{
	auto* TextureSampleNode = NewObject<UMaterialExpressionTextureSample>(CreatedMaterial);
	if(!TextureSampleNode) return;

	if(CreatedMaterial)
	{
		if(!CreatedMaterial->HasBaseColorConnected())
		{
			if(TryConnectBaseColor(TextureSampleNode, SelectedTexture, CreatedMaterial))
			{
				PinConnectedCounter++;
				return;
			}
		}
		if(!CreatedMaterial->HasMetallicConnected())
		{
			if(TryConnectMettalic(TextureSampleNode, SelectedTexture, CreatedMaterial))
			{
				PinConnectedCounter++;
				return;
			}
		}
	}
}

bool UQuickMaterialCreationWidget::TryConnectBaseColor(UMaterialExpressionTextureSample* TextureSampleNode,
	UTexture2D* SelectedTexture, UMaterial* CreatedMaterial)
{
	for(const FString& BaseColorName: BaseColorArray)
	{
		if(SelectedTexture->GetName().Contains(BaseColorName))
		{
			TextureSampleNode->Texture = SelectedTexture;
			CreatedMaterial->GetExpressionCollection().AddExpression(TextureSampleNode);
			CreatedMaterial->GetExpressionInputForProperty(MP_BaseColor)->Connect(0, TextureSampleNode);
			CreatedMaterial->PostEditChange();
			TextureSampleNode->MaterialExpressionEditorX -= 600.0f;
			return true;
		}
	}
	return false;
}

bool UQuickMaterialCreationWidget::TryConnectMettalic(UMaterialExpressionTextureSample* TextureSampleNode,
	UTexture2D* SelectedTexture, UMaterial* CreatedMaterial)
{
	for(const FString& Metalic: MetallicArray)
	{
		if(SelectedTexture->GetName().Contains(Metalic))
		{
			SelectedTexture->CompressionSettings = TextureCompressionSettings::TC_Default;
			SelectedTexture->SRGB = false;
			SelectedTexture->PostEditChange();
			
			TextureSampleNode->Texture = SelectedTexture;
			TextureSampleNode->SamplerType = EMaterialSamplerType::SAMPLERTYPE_LinearColor;
			TextureSampleNode->MaterialExpressionEditorX -= 600.0f;
			TextureSampleNode->MaterialExpressionEditorY += 240.0f;
			
			CreatedMaterial->GetExpressionCollection().AddExpression(TextureSampleNode);
			CreatedMaterial->GetExpressionInputForProperty(MP_Metallic)->Connect(0, TextureSampleNode);
			CreatedMaterial->PostEditChange();
			
			return true;
		}
	}
	return false;
}


#pragma endregion QuickMaterialCreationCore
