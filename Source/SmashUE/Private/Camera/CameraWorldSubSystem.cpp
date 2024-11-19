// Fill out your copyright notice in the Description page of Project Settings.


#include "Camera/CameraWorldSubSystem.h"
#include "EngineUtils.h"
#include "Camera/CameraFollowTarget.h"


void UCameraWorldSubSystem::PostInitialize()
{
	Super::PostInitialize();
}

void UCameraWorldSubSystem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	TickUpdateCameraPosition(DeltaTime);
}

TStatId UCameraWorldSubSystem::GetStatId() const
{
	RETURN_QUICK_DECLARE_CYCLE_STAT(UCameraWorldSubSystem, STATGROUP_Tickables);
}

void UCameraWorldSubSystem::AddFollowTarget(UObject* FollowTarget)
{
	FollowTargets.Add(FollowTarget);
}

void UCameraWorldSubSystem::RemoveFollowTarget(UObject* FollowTarget)
{
	FollowTargets.Remove(FollowTarget);
}

void UCameraWorldSubSystem::TickUpdateCameraPosition(float DeltaTime)
{
	if (CameraMain == nullptr) return;
	if (FollowTargets.Num() == 0) return;
	FVector AveragePosition = CalculateAveragePositionBetweenTargets();
	AveragePosition.Y = CameraMain->GetComponentLocation().Y;
	CameraMain->SetWorldLocation(AveragePosition);
}

FVector UCameraWorldSubSystem::CalculateAveragePositionBetweenTargets()
{
	FVector AveragePosition = FVector::ZeroVector;
	if (FollowTargets.Num() > 0)
	{
		int Index = 0;
		for (int32 i = 0; i < FollowTargets.Num(); i++)
		{
			UObject* FollowTarget = Cast<UObject>(FollowTargets[i]);
			if (FollowTarget == nullptr) continue;
			UCameraFollowTarget* CameraFollowTarget = Cast<UCameraFollowTarget>(FollowTarget);
			if (CameraFollowTarget == nullptr) continue;
			if (!CameraFollowTarget->IsFollowable()) continue;
			FVector FollowPosition = CameraFollowTarget->GetFollowPosition();
			AveragePosition += FollowPosition;
			Index++;
		}
		AveragePosition = FVector(AveragePosition.X / Index, CameraMain->GetComponentLocation().Y, AveragePosition.Z / Index);
	}
	return AveragePosition;
}

UCameraComponent* UCameraWorldSubSystem::FindCameraByTag(const FName& Tag) const
{
	for (TActorIterator<AActor> Iterator(GetWorld()); Iterator; ++Iterator)
	{
		AActor* Actor = *Iterator;
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

void UCameraWorldSubSystem::OnWorldBeginPlay(UWorld& InWorld)
{
	Super::OnWorldBeginPlay(InWorld);
	CameraMain = FindCameraByTag("CameraMain");
}
