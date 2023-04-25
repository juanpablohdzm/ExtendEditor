// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EditorUtilityWidget.h"
#include "QuickActorActionsWidget.generated.h"

/**
 * 
 */
UCLASS()
class SUPERMANAGER_API UQuickActorActionsWidget : public UEditorUtilityWidget
{
	GENERATED_BODY()

public:
	class UEditorActorSubsystem* GetEditorActorSubsystem();

	UFUNCTION(BlueprintCallable)
	void SelectAllActorsWithSimilarName();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="ActorBatchSelection")
	TEnumAsByte<ESearchCase::Type> SearchCase = ESearchCase::IgnoreCase;

private:
	UPROPERTY()
	class UEditorActorSubsystem* EditorActorSubsystem;

	
};
