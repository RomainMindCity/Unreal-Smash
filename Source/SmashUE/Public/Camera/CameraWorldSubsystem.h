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
	void TickUpdateCameraZoom(float DeltaTime);
	void TickUpdateCameraPosition(float DeltaTime);
	FVector CalculateAveragePositionBetweenTargets();
	UCameraComponent* FindCameraByTag(const FName& Tag) const;



#pragma region Bounds

protected:
	UPROPERTY()
	FVector2D CameraBoundsMin;

	UPROPERTY()
	FVector2D CameraBoundsMax;

	UPROPERTY()
	float CameraBoundsYProjectionCenter;
	
	AActor* FindCameraBoundsActor() const;

	void InitCameraBounds(AActor*CameraBoundsActor);
	void ClampPositionIntoCameraBounds(FVector& Position);
	void GetViewportBounds(FVector2D& OutViewportBoundsMin, FVector2D& OutViewportBoundsMax);
	FVector CalculateWorldPositionFromViewportPosition(const FVector2D& ViewportPosition);
	float CalculateGreatestDistanceBetweenTargets();

	
	
#pragma endregion

#pragma region Zoom
public:
	float CameraZoomYMin;
	float CameraZoomYMax;

	void InitCameraZoom();
	

	
#pragma endregion

};
