// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "UCameraSettings.generated.h"

/**
 * 
 */
UCLASS(Config=Game, DefaultConfig, meta = (DisplayName = "Smash Camera Settings"))
class SMASHUE_API UUCameraSettings : public UDeveloperSettings
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category = "Camera")
	FString CameraMainTag = TEXT("CameraMain");

	UPROPERTY(EditAnywhere, Category = "Camera")
	FString CameraDistanceMinTag = TEXT("CameraDistanceMin");

	UPROPERTY(EditAnywhere, Category = "Camera")
	FString CameraDistanceMaxTag = TEXT("CameraDistanceMax");

	UPROPERTY(EditAnywhere, Category = "Camera")
	FString CameraBoundsTag = TEXT("CameraBounds");

	UPROPERTY(EditAnywhere, Category = "Camera")
	float DistanceBetweenTargetsMin = 300.0f; 

	UPROPERTY(EditAnywhere, Category = "Camera")
	float DistanceBetweenTargetsMax = 1500.0f;

	UPROPERTY(EditAnywhere, Category = "Camera")
	float SizeDampingFactor = 5.0f;

	UPROPERTY(EditAnywhere, Category = "Camera")
	float PositionDampingFactor = 5.0f;
	
};
