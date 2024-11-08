// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/SmashCharacterStateWalk.h"

#include "Character/SmashCharacter.h"
#include "Character/SmashCharacterStateID.h"

ESmashCharacterStateID USmashCharacterStateWalk::GetStateID()
{
	return ESmashCharacterStateID::Walk;
}

void USmashCharacterStateWalk::StateEnter(ESmashCharacterStateID PreviousStateID)
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

void USmashCharacterStateWalk::StateExit(ESmashCharacterStateID NextStateID)
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

void USmashCharacterStateWalk::StateTick(float DeltaTime)
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
