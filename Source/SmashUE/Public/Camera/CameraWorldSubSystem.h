// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "Subsystems/WorldSubsystem.h"
#include "CameraWorldSubSystem.generated.h"

/**
 * 
 */
UCLASS()
class SMASHUE_API UCameraWorldSubSystem : public UTickableWorldSubsystem
{
	GENERATED_BODY()
	
public:
	virtual void PostInitialize() override;
	virtual void OnWorldBeginPlay(UWorld& InWorld) override;
	virtual void Tick(float DeltaTime) override;
	virtual TStatId GetStatId() const override;
	void AddFollowTarget(UObject* FollowTarget);
	void RemoveFollowTarget(UObject* FollowTarget);
	
protected:
	UPROPERTY()
	TObjectPtr<UCameraComponent> CameraMain;

	UPROPERTY()
	TArray<UObject*> FollowTargets;

	void TickUpdateCameraPosition(float DeltaTime);
	FVector CalculateAveragePositionBetweenTargets();
	UCameraComponent* FindCameraByTag(const FName& Tag) const;


};
