// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/SmashCharacterStateJump.h"
#include "Character/SmashCharacter.h"
#include "Character/SmashCharacterStateID.h"
#include "GameFramework/CharacterMovementComponent.h"

ESmashCharacterStateID USmashCharacterStateJump::GetStateID()
{
	return ESmashCharacterStateID::Jump;
}

void USmashCharacterStateJump::StateEnter(ESmashCharacterStateID PreviousStateID)
{
	Super::StateEnter(PreviousStateID);
	Character->GetCharacterMovement()->JumpZVelocity = (2*JumpMaxHeight)/JumpDuration;
	Character->Jump();
	Character->GetCharacterMovement()->AirControl = ((-(2*JumpMaxHeight)/JumpDuration) * JumpAirControl);
}

void USmashCharacterStateJump::StateExit(ESmashCharacterStateID NextStateID)
{
	Super::StateExit(NextStateID);
}

void USmashCharacterStateJump::StateTick(float DeltaTime)
{
	Super::StateTick(DeltaTime);
	if (Character->GetCharacterMovement()->IsFalling())
	{
		Character->ChangeState(ESmashCharacterStateID::Fall);
	}
}
