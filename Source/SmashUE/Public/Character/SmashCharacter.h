// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SmashCharacterSettings.h"
#include "SmashCharacterStateID.h"
#include "Camera/CameraFollowTarget.h"
#include "GameFramework/Character.h"
#include "SmashCharacter.generated.h"

class USmashCharacterStateMachine;

UCLASS()
class SMASHUE_API ASmashCharacter : public ACharacter, public ICameraFollowTarget
{
	GENERATED_BODY()
#pragma region Unreal Defaulf

public:
	// Sets default values for this character's properties
	ASmashCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
#pragma endregion

#pragma region Orient
	
public:
	float GetOrientX() const;
	
	void SetOrientX(float NewOrientX);
	
protected:
	UPROPERTY(BluePrintReadOnly)
	float OrientX = 1.f;

	void RotateMeshUsingOrientX() const;

#pragma endregion

#pragma region StateMachine
	
public:
	void CreateStateMachine();

	void InitStateMachine();

	void TickStateMachine(float DeltaTime) const;

	void ChangeState(ESmashCharacterStateID NewStateID);

protected:
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<USmashCharacterStateMachine> StateMachine;
	
#pragma endregion

#pragma region Input Data / Mapping Context

public:
	UPROPERTY()
	TObjectPtr<UInputMappingContext> InputMappingContext;

	UPROPERTY()
	TObjectPtr<USmashCharacterInputData> InputData;

	protected:
	void SetupMappingContextIntoController() const;

#pragma endregion

#pragma region Input Move X/Y

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FInputMoveXEvent, float, InputMoveX);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FInputMoveYEvent, float, InputMoveY);
	
public:
	float GetInputMoveX() const;
	float GetInputMoveY() const;
	
	UPROPERTY()
	FInputMoveXEvent InputMoveXFastEvent;

	UPROPERTY()
	FInputMoveYEvent InputMoveYEvent;

	float GetInputMoveXThreshold() const;
	float GetInputMoveYThreshold() const;

protected:
	UPROPERTY()
	float InputMoveX = 0.f;

	UPROPERTY()
	float InputMoveY= 0.f;

private:
	void BindInputMoveXAxisAndActions(UEnhancedInputComponent* EnhancedInputComponent);
	void BindInputMoveYAxisAndActions(UEnhancedInputComponent* EnhancedInputComponent);

	void OnInputMoveX(const FInputActionValue& InputActionValue);

	void OnInputMoveXFast(const FInputActionValue& InputActionValue);

	void OnInputMoveYJump(const FInputActionValue& InputActionValue);

#pragma endregion

#pragma region CameraTarget
	virtual bool IsFollowable() override;
	virtual FVector GetFollowPosition() override;
#pragma endregion
};
