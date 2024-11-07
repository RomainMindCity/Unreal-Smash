// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/SmashCharacter.h"
#include "Engine/DeveloperSettings.h"
#include "ArenaSettings.generated.h"

/**
 * 
 */
UCLASS(Config = Game, DefaultConfig, meta = (DisplayName = "Smash Arena Settings"))
class SMASHUE_API UArenaSettings : public UDeveloperSettings
{
	GENERATED_BODY()

public:
	UPROPERTY(config, EditAnywhere, Category = "Characters")
	TSubclassOf<ASmashCharacter> SmashCharacterClassP0;
	UPROPERTY(config, EditAnywhere, Category = "Characters")
	TSubclassOf<ASmashCharacter> SmashCharacterClassP1;
	UPROPERTY(config, EditAnywhere, Category = "Characters")
	TSubclassOf<ASmashCharacter> SmashCharacterClassP2;
	UPROPERTY(config, EditAnywhere, Category = "Characters")
	TSubclassOf<ASmashCharacter> SmashCharacterClassP3;
};
