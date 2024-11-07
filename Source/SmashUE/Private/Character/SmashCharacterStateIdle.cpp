// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/SmashCharacterStateIdle.h"

#include "Character/SmashCharacterStateID.h"

ESmashCharacterStateID USmashCharacterStateIdle::GetStateID()
{
	return ESmashCharacterStateID::Idle;
}

void USmashCharacterStateIdle::StateEnter(ESmashCharacterStateID PreviousStateID)
{
	Super::StateEnter(PreviousStateID);

	GEngine->AddOnScreenDebugMessage
	(
		-1,
		3.f,
		FColor::Cyan,
		TEXT("Enter State : Idle")
	);
}

void USmashCharacterStateIdle::StateExit(ESmashCharacterStateID NextStateID)
{
	Super::StateExit(NextStateID);

	GEngine->AddOnScreenDebugMessage
	(
		-1,
		3.f,
		FColor::Cyan,
		TEXT("Exit State : Idle")
	);
}

void USmashCharacterStateIdle::StateTick(float DeltaTime)
{
	Super::StateTick(DeltaTime);

	GEngine->AddOnScreenDebugMessage
	(
		-1,
		3.f,
		FColor::Green,
		TEXT("Tick StateWalk")
	);
}






