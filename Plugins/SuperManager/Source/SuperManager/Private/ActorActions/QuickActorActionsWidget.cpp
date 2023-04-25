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
