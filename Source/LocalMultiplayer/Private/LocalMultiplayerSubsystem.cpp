
#include "LocalMultiplayerSubsystem.h"
#include "EnhancedInputSubsystems.h"
#include "LocalMultiplayerSettings.h"

void ULocalMultiplayerSubsystem::CreateAndInitPlayers(ELocalMultiplayerInputMappingType MappingType)
{
	const ULocalMultiplayerSettings* Settings = GetDefault<ULocalMultiplayerSettings>();
	int NumKeyboardProfiles = Settings->KeyboardProfilesData.Num();
	int NumGamepads = Settings->NbMaxGamepads;

	for (int i = 0; i < NumKeyboardProfiles; ++i)
	{
		int PlayerIndex = AssignNewPlayerToKeyboardProfile(i);
		AssignKeyboardMapping(PlayerIndex, i, MappingType);
	}

	for (int i = 0; i < NumGamepads; ++i)
	{
		LastAssignedPlayerIndex = 1;
		int PlayerIndex = AssignNewPlayerToGamepadDeviceID(i);
		AssignGamePadInputMapping(PlayerIndex, MappingType);
	}
}

int ULocalMultiplayerSubsystem::GetAssignedPlayerIndexFromKeyboardProfileIndex(int KeyboardProfileIndex)
{
	if (PlayerIndexFromKeyboardProfileIndex.Contains(KeyboardProfileIndex))
	{
		return PlayerIndexFromKeyboardProfileIndex[KeyboardProfileIndex];
	}
	return -1;
}

int ULocalMultiplayerSubsystem::AssignNewPlayerToKeyboardProfile(int KeyboardProfileIndex)
{
	int PlayerIndex = LastAssignedPlayerIndex++;
	PlayerIndexFromKeyboardProfileIndex.Add(KeyboardProfileIndex, PlayerIndex);
	return PlayerIndex;
}

void ULocalMultiplayerSubsystem::AssignKeyboardMapping(int PlayerIndex, int KeyboardProfileIndex,
	ELocalMultiplayerInputMappingType MappingType) const
{
	const ULocalMultiplayerSettings* Settings = GetDefault<ULocalMultiplayerSettings>();
	const FLocalMultiplayerProfileData& ProfileData = Settings->KeyboardProfilesData[KeyboardProfileIndex];
	UInputMappingContext* IMC = ProfileData.GetIMCFromType(MappingType);
	UGameInstance* GameInstance = GetGameInstance();
	ULocalPlayer* LocalPlayer = GameInstance->GetLocalPlayerByIndex(PlayerIndex);
	APlayerController* PlayerController = LocalPlayer->GetPlayerController(GameInstance->GetWorld());
	if (PlayerController != nullptr)
	{
		UEnhancedInputLocalPlayerSubsystem* InputSubsystem = PlayerController->GetLocalPlayer()->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
		if (InputSubsystem != nullptr)
		{
			InputSubsystem->AddMappingContext(IMC, 1);
		}
	}
}

int ULocalMultiplayerSubsystem::GetAssignedPlayerIndexFromGamepadDeviceID(int DeviceID)
{
	if (PlayerIndexFromGamepadProfileIndex.Contains(DeviceID))
	{
		return PlayerIndexFromGamepadProfileIndex[DeviceID];
	}
	return -1;
}

int ULocalMultiplayerSubsystem::AssignNewPlayerToGamepadDeviceID(int DeviceID)
{
	if (PlayerIndexFromGamepadProfileIndex.Contains(DeviceID))
	{
		return PlayerIndexFromGamepadProfileIndex[DeviceID];
	}
	int PlayerIndex = LastAssignedPlayerIndex++;
	PlayerIndexFromGamepadProfileIndex.Add(DeviceID, PlayerIndex);
	return PlayerIndex;
}

void ULocalMultiplayerSubsystem::AssignGamePadInputMapping(int PlayerIndex,
	ELocalMultiplayerInputMappingType MappingType) const
{
	const ULocalMultiplayerSettings* Settings = GetDefault<ULocalMultiplayerSettings>();
	const FLocalMultiplayerProfileData& ProfileData = Settings->KeyboardProfilesData[PlayerIndex];
	UInputMappingContext* IMC = ProfileData.GetIMCFromType(MappingType);
	UGameInstance* GameInstance = GetGameInstance();
	ULocalPlayer* LocalPlayer = GameInstance->GetLocalPlayerByIndex(PlayerIndex);
	APlayerController* PlayerController = LocalPlayer->GetPlayerController(GameInstance->GetWorld());
	if (PlayerController != nullptr)
	{
		UEnhancedInputLocalPlayerSubsystem* InputSubsystem = PlayerController->GetLocalPlayer()->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
		if (InputSubsystem != nullptr)
		{
			InputSubsystem->AddMappingContext(IMC, 1);
		}
	}	
}
