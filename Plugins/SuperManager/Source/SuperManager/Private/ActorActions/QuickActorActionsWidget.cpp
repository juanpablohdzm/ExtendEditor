// Fill out your copyright notice in the Description page of Project Settings.


#include "ActorActions/QuickActorActionsWidget.h"
#include "DebugHeader.h"
#include "Subsystems/EditorActorSubsystem.h"

UEditorActorSubsystem* UQuickActorActionsWidget::GetEditorActorSubsystem()
{
	if(!EditorActorSubsystem)
	{
		EditorActorSubsystem = GEditor->GetEditorSubsystem<UEditorActorSubsystem>();
	}

	return EditorActorSubsystem;
	
}

void UQuickActorActionsWidget::SelectAllActorsWithSimilarName()
{
	auto* ActorSubsystem  = GetEditorActorSubsystem();
	if(!ActorSubsystem)
	{
		return;
	}

	auto SelectedActors = ActorSubsystem->GetSelectedLevelActors();
	uint32 SelectionCounter = 0;

	if(SelectedActors.Num() == 0)
	{
		ShowNotifyInfo("No actor selected");
		return;
	}

	if(SelectedActors.Num() > 1)
	{
		ShowNotifyInfo("You can only select one actor");
		return;
	}

	auto SelectedActorName = SelectedActors[0]->GetActorLabel();
	const auto NameToSearch  = SelectedActorName.LeftChop(4);

	auto AllLevelActors =  EditorActorSubsystem->GetAllLevelActors();
	for(AActor* ActorInLevel : AllLevelActors)
	{
		if(!ActorInLevel) continue;

		if(ActorInLevel->GetActorLabel().Contains(NameToSearch, SearchCase))
		{
			EditorActorSubsystem->SetActorSelectionState(ActorInLevel, true);
			SelectionCounter++;
		}
	}

	if(SelectionCounter)
	{
		ShowNotifyInfo("Success");
	}
	
}

void UQuickActorActionsWidget::DuplicateActors()
{
	auto ActorSubsystem = GetEditorActorSubsystem();
	if(!ActorSubsystem)
	{
		return;
	}

	auto SelectedActors = ActorSubsystem->GetSelectedLevelActors();
	uint32 Counter = 0;
	if(SelectedActors.Num() == 0)
	{
		ShowNotifyInfo("No actor selected");
		return;
	}

	if(NumberOfDuplicates <= 0)
	{
		ShowNotifyInfo("Did not specify number of duplications or an offset distance");
		return;
	}

	for(AActor* SelectedActor: SelectedActors)
	{
		if(!SelectedActor) continue;

		for(int32 i = 0; i < NumberOfDuplicates; i++)
		{
			auto DuplicatedActor = ActorSubsystem->DuplicateActor(SelectedActor,SelectedActor->GetWorld());
			if(!DuplicatedActor) continue;

			const float DuplicationOffsetDist = (i+1)* OffsetDiff;
			switch (AxisForDuplication)
			{
				case E_DuplicationAxis::EDA_XAxis:
					DuplicatedActor->AddActorWorldOffset(FVector(DuplicationOffsetDist,0,0));
					break;
				case E_DuplicationAxis::EDA_YAxis:
					DuplicatedActor->AddActorWorldOffset(FVector(0,DuplicationOffsetDist,0));
					break;
				case E_DuplicationAxis::EDA_ZAxis:
					DuplicatedActor->AddActorWorldOffset(FVector(0,0,DuplicationOffsetDist));
					break;
				case E_DuplicationAxis::EDA_MAX:
					break;
				default: ;
			}
			EditorActorSubsystem->SetActorSelectionState(DuplicatedActor,true);
			Counter++;
		}
		
	}

	if(Counter)
	{
		ShowNotifyInfo("Success");
	}
	
}
