// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/SmashCharacterState.h"
#include "SmashCharacterStateWalk.generated.h"


UCLASS(ClassGroup=(SmashCharacterState), meta=(BlueprintSpawnableComponent))
class SMASHUE_API USmashCharacterStateWalk : public USmashCharacterState
{
	GENERATED_BODY()

public:
	virtual ESmashCharacterStateID GetStateID() override;

	virtual void StateEnter(ESmashCharacterStateID PreviousStateID) override;
	virtual void StateExit(ESmashCharacterStateID NextStateID) override;
	virtual void StateTick(float DeltaTime) override;
	
	UFUNCTION()
	void OnInputMoveXFast(float InputMoveX);

	UPROPERTY(EditAnywhere)
	float MaxMoveSpeed;
};
