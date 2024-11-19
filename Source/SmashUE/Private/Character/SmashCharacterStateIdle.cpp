// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/SmashCharacterStateIdle.h"

#include "Character/SmashCharacter.h"
#include "Character/SmashCharacterStateID.h"

ESmashCharacterStateID USmashCharacterStateIdle::GetStateID()
{
	return ESmashCharacterStateID::Idle;
}

void USmashCharacterStateIdle::StateEnter(ESmashCharacterStateID PreviousStateID)
{
	Super::StateEnter(PreviousStateID);

	Character->InputMoveXFastEvent.AddDynamic(this, &USmashCharacterStateIdle::OnInputMoveXFast);
	Character->InputMoveYEvent.AddDynamic(this, &USmashCharacterStateIdle::OnInputMoveYJump);
}

void USmashCharacterStateIdle::StateExit(ESmashCharacterStateID NextStateID)
{
	Super::StateExit(NextStateID);
	Character->InputMoveXFastEvent.RemoveDynamic(this, &USmashCharacterStateIdle::OnInputMoveXFast);
	Character->InputMoveYEvent.RemoveDynamic(this, &USmashCharacterStateIdle::OnInputMoveYJump);
}

void USmashCharacterStateIdle::StateTick(float DeltaTime)
{
	Super::StateTick(DeltaTime);
	
	if (FMath::Abs(Character->GetInputMoveX()) > Character->GetInputMoveXThreshold())
	{
		Character->ChangeState(ESmashCharacterStateID::Walk);
	}

	if (FMath::Abs(Character->GetInputMoveY()) > Character->GetInputMoveYThreshold())
	{
		Character->ChangeState(ESmashCharacterStateID::Jump);
	}

	
}

void USmashCharacterStateIdle::OnInputMoveXFast(float InputMoveX)
{
    Character->ChangeState(ESmashCharacterStateID::Run);
}

void USmashCharacterStateIdle::OnInputMoveYJump(float InputMoveY)
{
	Character->ChangeState(ESmashCharacterStateID::Jump);
}
