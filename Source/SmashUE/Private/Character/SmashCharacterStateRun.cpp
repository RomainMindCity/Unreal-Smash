// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/SmashCharacterStateRun.h"
#include "Character/SmashCharacter.h"
#include "Character/SmashCharacterStateID.h"

ESmashCharacterStateID USmashCharacterStateRun::GetStateID()
{
	return ESmashCharacterStateID::Run;
}

void USmashCharacterStateRun::StateEnter(ESmashCharacterStateID PreviousStateID)
{
	Super::StateEnter(PreviousStateID);

	GEngine->AddOnScreenDebugMessage
	(
		-1,
		3.f,
		FColor::Cyan,
		TEXT("Enter State : Walk")
	);
}

void USmashCharacterStateRun::StateExit(ESmashCharacterStateID NextStateID)
{
	Super::StateExit(NextStateID);

	GEngine->AddOnScreenDebugMessage
	(
		-1,
		3.f,
		FColor::Cyan,
		TEXT("Exit State : Walk")
	);
}

void USmashCharacterStateRun::StateTick(float DeltaTime)
{
	Super::StateTick(DeltaTime);

	if (Character->GetVelocity().X < MaxMoveSpeed)
		Character->AddMovementInput(FVector(MaxMoveSpeed, 0, 0));
	

	GEngine->AddOnScreenDebugMessage
	(
		-1,
		3.f,
		FColor::Green,
		TEXT("Tick State Walk")
	);
}