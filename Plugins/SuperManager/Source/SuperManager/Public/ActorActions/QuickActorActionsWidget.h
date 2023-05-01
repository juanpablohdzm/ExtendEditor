// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EditorUtilityWidget.h"
#include "QuickActorActionsWidget.generated.h"

UENUM(BlueprintType)
enum class E_DuplicationAxis : uint8
{
	EDA_XAxis UMETA(DisplayName = "X Axis"),
	EDA_YAxis UMETA(DisplayName = "Y Axis"),
	EDA_ZAxis UMETA(DisplayName = "Z Axis"),
	EDA_MAX UMETA(DisplayName = "Default Max"),
};

USTRUCT(BlueprintType)
struct FRandomActorRotation
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bRandomizeRotYaw = false;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (EditCondition = "bRandomizeRotYaw"))
	float RotYawMin = -45.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (EditCondition = "bRandomizeRotYaw"))
	float RotYawMax = 45.f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bRandomizeRotPitch = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (EditCondition = "bRandomizeRotPitch"))
	float RotPitchMin = -45.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (EditCondition = "bRandomizeRotPitch"))
	float RotPitchMax = 45.f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bRandomizeRotRoll = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (EditCondition = "bRandomizeRotRoll"))
	float RotRollMin = -45.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (EditCondition = "bRandomizeRotRoll"))
	float RotRollMax = 45.f;
	
};

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

	UFUNCTION(BlueprintCallable)
	void DuplicateActors();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="ActorBatchSelection")
	TEnumAsByte<ESearchCase::Type> SearchCase = ESearchCase::IgnoreCase;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="ActorBatchSelection")
	E_DuplicationAxis AxisForDuplication  = E_DuplicationAxis::EDA_XAxis;
	

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="ActorBatchSelection")
	int32 NumberOfDuplicates = 5;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="ActorBatchSelection")
	float OffsetDiff = 300.0f;

	UFUNCTION(BlueprintCallable, Category="")
	void RandomizeActorTransform();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="ActorBatchDuplication")
	FRandomActorRotation RandomActorRotation;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="ActorBatchDuplication")
	bool bRandomizeScale = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="ActorBatchDuplication", meta = (EditCondition = "bRandomizeScale"))
	float ScaleMin = .8f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="ActorBatchDuplication", meta = (EditCondition = "bRandomizeScale"))
	float ScaleMax = .8f;
	
private:
	UPROPERTY()
	class UEditorActorSubsystem* EditorActorSubsystem;

	
};
