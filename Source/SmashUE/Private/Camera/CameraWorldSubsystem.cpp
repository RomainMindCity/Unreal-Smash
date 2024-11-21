// Fill out your copyright notice in the Description page of Project Settings.


#include "Camera/CameraWorldSubsystem.h"
#include "Engine/World.h"
#include "EngineUtils.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Character/SmashCharacter.h"
#include "Camera/UCameraSettings.h"


void UCameraWorldSubSystem::OnWorldBeginPlay(UWorld& InWorld)
{
	Super::OnWorldBeginPlay(InWorld);
	UUCameraSettings* CameraSettings = NewObject<UUCameraSettings>();
    CameraMain = FindCameraByTag(FName(*CameraSettings->CameraMainTag));
	AActor* CameraBoundsActor = FindCameraBoundsActor();
	if(CameraBoundsActor != nullptr)
	{
		InitCameraBounds(CameraBoundsActor);
	}
	InitCameraZoom();
}

void UCameraWorldSubSystem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	TickUpdateCameraZoom(DeltaTime);
	TickUpdateCameraPosition(DeltaTime);

}

void UCameraWorldSubSystem::AddFollowTarget(UObject* Target)
{
	if(Target == nullptr) return;
	FollowTargets.Add(Target);
}

void UCameraWorldSubSystem::RemoveFollowTarget(UObject* Target)
{
	if(Target == nullptr) return;
	FollowTargets.Remove(Target);
}

void UCameraWorldSubSystem::TickUpdateCameraPosition(float DeltaTime)
{
	if (CameraMain == nullptr) return;
	if (FollowTargets.Num() == 0) return;

	FVector AveragePosition = CalculateAveragePositionBetweenTargets();
	ClampPositionIntoCameraBounds(AveragePosition);
	AveragePosition.Y = CameraMain->GetComponentLocation().Y; 
	CameraMain->SetWorldLocation(AveragePosition);
}

FVector UCameraWorldSubSystem::CalculateAveragePositionBetweenTargets()
{
	FVector AveragePosition = FVector::ZeroVector;

	if (FollowTargets.Num() > 0)
	{
		for (UObject* Target : FollowTargets)
		{
			if (ICameraFollowTarget* FollowTarget = Cast<ICameraFollowTarget>(Target))
			{
				if (FollowTarget->IsFollowable())
					AveragePosition += FollowTarget->GetFollowPosition();
			}
		}
	}

	return AveragePosition / FollowTargets.Num();
}

UCameraComponent* UCameraWorldSubSystem::FindCameraByTag(const FName& Tag) const
{
	for (TActorIterator<AActor> It(GetWorld()); It; ++It)
	{
		AActor* Actor = *It;
		if (Actor->ActorHasTag(Tag))
		{
			UCameraComponent* CameraComponent = Actor->FindComponentByClass<UCameraComponent>();
			if (CameraComponent)
			{
				return CameraComponent;
			}
		}
	}
	return nullptr;
}

void UCameraWorldSubSystem::PostInitialize()
{
	Super::PostInitialize();
}

TStatId UCameraWorldSubSystem::GetStatId() const
{
	RETURN_QUICK_DECLARE_CYCLE_STAT(UCameraWorldSubsystem, STATGROUP_Tickables);
}

AActor* UCameraWorldSubSystem::FindCameraBoundsActor() const
{
	UUCameraSettings* CameraSettings = NewObject<UUCameraSettings>();
	for (TActorIterator<AActor> It(GetWorld()); It; ++It)
	{
		AActor* Actor = *It;
		if (Actor->ActorHasTag(FName(*CameraSettings->CameraBoundsTag)))
		{
			return Actor;
		}
	}
	return nullptr;
}

void UCameraWorldSubSystem::InitCameraBounds(AActor* CameraBoundsActor)
{
	FVector Origin;
	FVector BoxExtent;
	CameraBoundsActor->GetActorBounds(false, Origin, BoxExtent);
	CameraBoundsMin = FVector2D(Origin.X - BoxExtent.X, Origin.Z - BoxExtent.Z);
	CameraBoundsMax = FVector2D(Origin.X + BoxExtent.X, Origin.Z + BoxExtent.Z);
	UE_LOG(LogTemp, Warning, TEXT("CameraBoundsMin: %s"), *CameraBoundsMin.ToString());
	UE_LOG(LogTemp, Warning, TEXT("CameraBoundsMax: %s"), *CameraBoundsMax.ToString());
	CameraBoundsYProjectionCenter = Origin.Y;
}

void UCameraWorldSubSystem::ClampPositionIntoCameraBounds(FVector& Position)
{
	FVector2d ViewportBoundsMin, ViewportBoundsMax;
	GetViewportBounds(ViewportBoundsMin, ViewportBoundsMax);
	FVector WorldBoundsMin = CalculateWorldPositionFromViewportPosition(ViewportBoundsMin);
	FVector WorldBoundsMax = CalculateWorldPositionFromViewportPosition(ViewportBoundsMax);

	if(Position.X+WorldBoundsMax.X/2>CameraBoundsMax.X)
	{
		Position.X=CameraBoundsMax.X-WorldBoundsMax.X/2;
	}
	else if(Position.X+WorldBoundsMin.X/2<CameraBoundsMin.X)
	{
		Position.X=CameraBoundsMin.X-WorldBoundsMin.X/2;
	}
	if(Position.Z+WorldBoundsMin.Z/2>CameraBoundsMax.Y)
	{
		Position.Z=CameraBoundsMax.Y-WorldBoundsMin.Z/2;
	}
	else if(Position.Z+WorldBoundsMax.Z/2<CameraBoundsMin.Y)
	{
		Position.Z=CameraBoundsMin.Y-WorldBoundsMax.Z/2;
	}

}

void UCameraWorldSubSystem::GetViewportBounds(FVector2D& OutViewportBoundsMin, FVector2D& OutViewportBoundsMax)
{
	UGameViewportClient* GameViewport = GetWorld()->GetGameViewport();
	if(GameViewport == nullptr) return;

	FViewport* Viewport = GameViewport->Viewport;
	if(Viewport == nullptr) return;

	FIntRect ViewRect(
		Viewport->GetInitialPositionXY(),
		Viewport->GetInitialPositionXY() + Viewport->GetSizeXY()
	);
	FIntRect ViewportRect = Viewport-> CalculateViewExtents(CameraMain->AspectRatio, ViewRect);

	OutViewportBoundsMin.X = ViewportRect.Min.X;
	OutViewportBoundsMin.Y = ViewportRect.Min.Y;

	OutViewportBoundsMax.X = ViewportRect.Max.X;
	OutViewportBoundsMax.Y = ViewportRect.Max.Y;
}

FVector UCameraWorldSubSystem::CalculateWorldPositionFromViewportPosition(const FVector2D& ViewportPosition)
{
	if(CameraMain == nullptr) return FVector::ZeroVector;

	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if(PlayerController == nullptr) return FVector::ZeroVector;

	float YDistanceToCenter = CameraMain->GetOwner()->GetActorLocation().Y - CameraBoundsYProjectionCenter;

	FVector CameraWorldProjectDir;
	FVector WorldPosition;
	UGameplayStatics::DeprojectScreenToWorld(
		PlayerController,
		ViewportPosition,
		WorldPosition,
		CameraWorldProjectDir
		);

	WorldPosition += CameraWorldProjectDir * YDistanceToCenter;
	return WorldPosition;
}

void UCameraWorldSubSystem::InitCameraZoom()
{
	UUCameraSettings* CameraSettings = NewObject<UUCameraSettings>();
	for (TActorIterator<AActor> It(GetWorld()); It; ++It)
	{
		AActor* Actor = *It;
		if (Actor->ActorHasTag(FName(*CameraSettings->CameraDistanceMinTag)))
		{
			CameraZoomYMin = Actor->GetActorLocation().Y;
			break;
		}
	}
	for (TActorIterator<AActor> It(GetWorld()); It; ++It)
	{
		AActor* Actor = *It;
		if (Actor->ActorHasTag(FName(*CameraSettings->CameraDistanceMaxTag)))
		{
			CameraZoomYMax = Actor->GetActorLocation().Y;
			break;
		}
	}
}

void UCameraWorldSubSystem::TickUpdateCameraZoom(float DeltaTime)
{
	UUCameraSettings* CameraSettings = NewObject<UUCameraSettings>();
	if (CameraMain == nullptr) return;

	float GreatestDistanceBetweenTargets = CalculateGreatestDistanceBetweenTargets();
	float Percent = (GreatestDistanceBetweenTargets - CameraSettings->DistanceBetweenTargetsMin) / (CameraSettings->DistanceBetweenTargetsMax - CameraSettings->DistanceBetweenTargetsMin);
	Percent = FMath::Clamp(Percent, 0.0f, 1.0f);

	float TargetCameraY = FMath::Lerp(CameraZoomYMin, CameraZoomYMax, Percent);
	FVector CurrentPosition = CameraMain->GetComponentLocation();
	FVector TargetPosition = CurrentPosition;
	TargetPosition.Y = TargetCameraY;

	FVector NewPosition = FMath::Lerp(CurrentPosition, TargetPosition, DeltaTime * CameraSettings->SizeDampingFactor);
	CameraMain->SetWorldLocation(NewPosition);
}

float UCameraWorldSubSystem::CalculateGreatestDistanceBetweenTargets() 
{
	float GreatestDistance = 0.0f;
	for(int i = 0; i < FollowTargets.Num(); i++)
    {
        for(int j = i+1; j < FollowTargets.Num(); j++)
        {
        	float Distance = FVector::Dist(Cast<AActor>(FollowTargets[i])->GetActorLocation(), Cast<AActor>(FollowTargets[j])->GetActorLocation());
            if(Distance > GreatestDistance)
            {
                GreatestDistance = Distance;
            }
        }
    }
	return GreatestDistance;
}



