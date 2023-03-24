// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AssetActionUtility.h"
#include "QuickAssetAction.generated.h"

/**
 * 
 */
UCLASS()
class SUPERMANAGER_API UQuickAssetAction : public UAssetActionUtility
{
	GENERATED_BODY()

	UQuickAssetAction();

public:
	UFUNCTION(CallInEditor)
	void DuplicateAssets(int32 NumOfDuplicates);

	UFUNCTION(CallInEditor)
	void AddPrefixesToSelectedAssets();

	UFUNCTION(CallInEditor)
	void RemoveUnusedAssets();

private:
	TMap<UClass*, FString> PrefixMap;

	void FixUpRedirectors();
	
};
