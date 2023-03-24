// Fill out your copyright notice in the Description page of Project Settings.


#include "AssetActions/QuickAssetAction.h"
#include "EditorUtilityLibrary.h"
#include "EditorAssetLibrary.h"
#include "DebugHeader.h"
#include "Blueprint/UserWidget.h"
#include "Materials/MaterialInstanceConstant.h"
#include "Particles/ParticleSystem.h"
#include "Sound/SoundCue.h"
#include "NiagaraSystem.h"
#include "NiagaraEmitter.h"
#include "ObjectTools.h"

UQuickAssetAction::UQuickAssetAction()
{
	PrefixMap = TMap<UClass*,FString>
	{
			{UBlueprint::StaticClass(),TEXT("BP_")},
			{UStaticMesh::StaticClass(),TEXT("SM_")},
			{UMaterial::StaticClass(), TEXT("M_")},
			{UMaterialInstanceConstant::StaticClass(),TEXT("MI_")},
			{UMaterialFunctionInterface::StaticClass(), TEXT("MF_")},
			{UParticleSystem::StaticClass(), TEXT("PS_")},
			{USoundCue::StaticClass(), TEXT("SC_")},
			{USoundWave::StaticClass(), TEXT("SW_")},
			{UTexture::StaticClass(), TEXT("T_")},
			{UTexture2D::StaticClass(), TEXT("T_")},
			{UUserWidget::StaticClass(), TEXT("WBP_")},
			{USkeletalMeshComponent::StaticClass(), TEXT("SK_")},
			{UNiagaraSystem::StaticClass(), TEXT("NS_")},
			{UNiagaraEmitter::StaticClass(), TEXT("NE_")}
	};
}

void UQuickAssetAction::DuplicateAssets(int32 NumOfDuplicates)
{
	if(NumOfDuplicates <= 0)
	{
		FText Title = FText::FromString(TEXT("Invalid number of duplicates"));
		ShowMessageDialog((TEXT("Please enter a valid number of duplicates")), Title, EAppMsgType::Ok);
		return;
	}

	TArray<FAssetData> SelectedAssetsData = UEditorUtilityLibrary::GetSelectedAssetData();
	if(SelectedAssetsData.Num() == 0)
	{
		Print(TEXT("Please select at least one asset"), FColor::Red);
		return;
	}

	for(const FAssetData& SelectedAssetData : SelectedAssetsData)
	{
		for(size_t i=0; i< NumOfDuplicates; i++)
		{
			const FString SourceAssetPath = SelectedAssetData.ObjectPath.ToString();
			PrintLog(SourceAssetPath);
			const FString NewDuplicatedAssetName = SelectedAssetData.AssetName.ToString() + TEXT("_") + FString::FromInt(i+1);
			PrintLog(NewDuplicatedAssetName);
			const FString NewPathName = FPaths::Combine(SelectedAssetData.PackagePath.ToString(), NewDuplicatedAssetName);
			PrintLog(NewPathName);

			if(UEditorAssetLibrary::DuplicateAsset(SourceAssetPath, NewPathName))
			{
				UEditorAssetLibrary::SaveAsset(NewPathName,false);
			}
		}
	}
	
}

void UQuickAssetAction::AddPrefixesToSelectedAssets()
{
	TArray<UObject*> SelectedObjects = UEditorUtilityLibrary::GetSelectedAssets();
	uint32 Counter = 0;

	for(auto* SelectedObject : SelectedObjects)
	{
		if(!SelectedObject) continue;

		FString* PrefixFound = PrefixMap.Find(SelectedObject->GetClass());

		if(!PrefixFound || PrefixFound->IsEmpty())
		{
			Print(TEXT("Failed to find prefix for class")+ SelectedObject->GetClass()->GetName(), FColor::Red);
			continue;
		}

		FString OldName = SelectedObject->GetName();
		if(OldName.StartsWith(*PrefixFound))
		{
			Print(TEXT("Asset already has prefix: ") + OldName, FColor::Red);
			continue;
		}

		if(SelectedObject->IsA<UMaterialInstanceConstant>())
		{
			OldName.RemoveFromStart(TEXT("M_"));
			OldName.RemoveFromEnd(TEXT("_Inst"));
		}

		const FString NewNameWithPrefix = *PrefixFound + OldName;

		UEditorUtilityLibrary::RenameAsset(SelectedObject, NewNameWithPrefix);

		++Counter;
	}

	if(Counter > 0)
		ShowNotifyInfo(TEXT("Successfully renamed" + FString::FromInt(Counter) + TEXT(" assets")));
}

void UQuickAssetAction::RemoveUnusedAssets()
{
	TArray<FAssetData> Assets = UEditorUtilityLibrary::GetSelectedAssetData();
	TArray<FAssetData> UnusedAssets;

	for(auto& Asset : Assets)
	{
		TArray<FString> AssetReferences = UEditorAssetLibrary::FindPackageReferencersForAsset(Asset.GetSoftObjectPath().ToString());
		if(AssetReferences.Num() == 0)
		{
			UnusedAssets.Add(Asset);
		}
	}

	if(UnusedAssets.Num() == 0)
	{
		ShowMessageDialog(TEXT("No unused assets found"), FText::FromString(TEXT("Unused Assets")), EAppMsgType::Ok);
		return;
	}

	ObjectTools::DeleteAssets(UnusedAssets, true);
}
