// Fill out your copyright notice in the Description page of Project Settings.


#include "SmashCharacterState.h"

#include "Character/SmashCharacter.h"
#include "Character/SmashCharacterStateID.h"
#include "Character/SmashCharacterStateMachine.h"



// Sets default values for this component's properties
USmashCharacterState::USmashCharacterState()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

ESmashCharacterStateID USmashCharacterState::GetStateID()
{
	return ESmashCharacterStateID::None;
}

void USmashCharacterState::StateInit(USmashCharacterStateMachine* InStateMachine)
{
	StateMachine = InStateMachine;
	Character = InStateMachine->GetCharacter();
}

void USmashCharacterState::StateEnter(ESmashCharacterStateID PreviousStateID)
{
	Character->PlayAnimMontage(AnimMontage);
}

void USmashCharacterState::StateExit(ESmashCharacterStateID NextStateID)
{
	
}

void USmashCharacterState::StateTick(float DeltaTime)
{
	
}





