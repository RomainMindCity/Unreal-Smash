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
}

void USmashCharacterStateIdle::StateExit(ESmashCharacterStateID NextStateID)
{
	Super::StateExit(NextStateID);
	Character->InputMoveXFastEvent.RemoveDynamic(this, &USmashCharacterStateIdle::OnInputMoveXFast);
}

void USmashCharacterStateIdle::StateTick(float DeltaTime)
{
	Super::StateTick(DeltaTime);
	
	if (FMath::Abs(Character->GetInputMoveX()) > 0.1f)
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






