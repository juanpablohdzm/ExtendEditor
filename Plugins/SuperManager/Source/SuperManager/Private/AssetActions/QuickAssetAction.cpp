// Fill out your copyright notice in the Description page of Project Settings.


#include "AssetActions/QuickAssetAction.h"

void UQuickAssetAction::TestFunc()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("TestFunc"));
}
