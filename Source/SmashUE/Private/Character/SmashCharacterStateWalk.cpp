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

	Character->InputMoveXFastEvent.AddDynamic(this, &USmashCharacterStateWalk::OnInputMoveXFast);
}

void USmashCharacterStateWalk::StateExit(ESmashCharacterStateID NextStateID)
{
	Super::StateExit(NextStateID);

	Character->InputMoveXFastEvent.RemoveDynamic(this, &USmashCharacterStateWalk::OnInputMoveXFast);
}

void USmashCharacterStateWalk::StateTick(float DeltaTime)
{
	Super::StateTick(DeltaTime);
	
	if (FMath::Abs(Character->GetInputMoveX()) < 0.1f)
	{
		Character->ChangeState(ESmashCharacterStateID::Idle);
	}
	else
	{
		Character->SetOrientX(Character->GetInputMoveX());
		Character->AddMovementInput(FVector::ForwardVector, Character->GetOrientX());
	}

	if (FMath::Abs(Character->GetInputMoveY()) > Character->GetInputMoveYThreshold())
	{
		Character->ChangeState(ESmashCharacterStateID::Jump);
	}
}

void USmashCharacterStateWalk::OnInputMoveXFast(float InputMoveX)
{
    Character->ChangeState(ESmashCharacterStateID::Run);
}

void USmashCharacterStateWalk::OnInputMoveYJump(float InputMoveY)
{
	Character->ChangeState(ESmashCharacterStateID::Jump);
}
