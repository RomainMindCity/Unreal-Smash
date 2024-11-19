// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/SmashCharacterStateFall.h"

#include "Character/SmashCharacter.h"
#include "Character/SmashCharacterStateID.h"
#include "GameFramework/CharacterMovementComponent.h"


ESmashCharacterStateID USmashCharacterStateFall::GetStateID()
{
	return ESmashCharacterStateID::Fall;
}

void USmashCharacterStateFall::StateEnter(ESmashCharacterStateID PreviousStateID)
{
	Super::StateEnter(PreviousStateID);
	Character->GetCharacterMovement()->GravityScale = FallGravityScale;
	Character->Falling();
}

void USmashCharacterStateFall::StateExit(ESmashCharacterStateID NextStateID)
{
	Super::StateExit(NextStateID);
}

void USmashCharacterStateFall::StateTick(float DeltaTime)
{
	Super::StateTick(DeltaTime);
	if (!Character->GetCharacterMovement()->IsFalling())
	{
		Character->ChangeState(ESmashCharacterStateID::Idle);
	}

	if (Character->GetInputMoveX() == 1)
	{
		Character->GetCharacterMovement()->AirControl = FallAirControl;
		Character->AddMovementInput(FVector::ForwardVector, FallHorizontalSpeed);
	}
}

