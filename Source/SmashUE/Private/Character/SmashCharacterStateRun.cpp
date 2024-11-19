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
}

void USmashCharacterStateRun::StateExit(ESmashCharacterStateID NextStateID)
{
	Super::StateExit(NextStateID);
}

void USmashCharacterStateRun::StateTick(float DeltaTime)
{
	Super::StateTick(DeltaTime);

	if (FMath::Abs(Character->GetInputMoveX()) < Character->GetInputMoveXThreshold())
	{
		Character->ChangeState(ESmashCharacterStateID::Idle);
	}
	else
	{
		Character->SetOrientX(Character->GetInputMoveX());
		Character->AddMovementInput(FVector::ForwardVector * MaxFastMoveSpeed, Character->GetOrientX());
	}

	if (FMath::Abs(Character->GetInputMoveY()) > Character->GetInputMoveYThreshold())
	{
		Character->ChangeState(ESmashCharacterStateID::Jump);
	}
}