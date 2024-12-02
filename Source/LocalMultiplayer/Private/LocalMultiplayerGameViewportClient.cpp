#include "LocalMultiplayerGameViewportClient.h"
#include "LocalMultiplayerSettings.h"
#include "LocalMultiplayerSubsystem.h"
#include "InputCoreTypes.h"
#include "GameFramework/PlayerInput.h"


void ULocalMultiplayerGameViewportClient::PostInitProperties()
{
    Super::PostInitProperties();
    ULocalMultiplayerSettings* Settings = GetMutableDefault<ULocalMultiplayerSettings>();
    Settings->NbMaxGamepads = MaxSplitscreenPlayers;
}

bool ULocalMultiplayerGameViewportClient::InputKey(const FInputKeyEventArgs& EventArgs)
{
    if(GameInstance == nullptr) return false;
    
    const ULocalMultiplayerSettings* LocalMultiplayerSettings = GetDefault<ULocalMultiplayerSettings>();
    ULocalMultiplayerSubsystem* LocalMultiplayerSubsystem = GameInstance->GetSubsystem<ULocalMultiplayerSubsystem>();
    
    if (LocalMultiplayerSettings == nullptr || LocalMultiplayerSubsystem == nullptr) return false;
    
    int KeyboardProfileIndex = LocalMultiplayerSettings->FindKeyboardProfileIndexFromKey(EventArgs.Key, ELocalMultiplayerInputMappingType::InGame);
    
    int PlayerIndex = !EventArgs.IsGamepad() ?LocalMultiplayerSubsystem->GetAssignedPlayerIndexFromKeyboardProfileIndex(KeyboardProfileIndex) : LocalMultiplayerSubsystem->GetAssignedPlayerIndexFromGamepadDeviceID(EventArgs.InputDevice.GetId());

    if(PlayerIndex < 0) return false;
    
    ULocalPlayer* LocalPlayer = GameInstance->GetLocalPlayerByIndex(PlayerIndex);
    if (LocalPlayer == nullptr) return false;
    
    APlayerController* PlayerController = LocalPlayer->GetPlayerController(GameInstance->GetWorld());
    if (PlayerController == nullptr) return false;
    
    FInputKeyParams params = FInputKeyParams(EventArgs.Key,EventArgs.Event,EventArgs.AmountDepressed,EventArgs.IsGamepad(),EventArgs.InputDevice);
    return PlayerController->InputKey(params);
}

bool ULocalMultiplayerGameViewportClient::InputAxis(FViewport* InViewport, FInputDeviceId InputDevice, FKey Key,
    float Delta, float DeltaTime, int32 NumSamples, bool bGamepad)
{
    if(GameInstance == nullptr) return false;
    
    const ULocalMultiplayerSettings* LocalMultiplayerSettings = GetDefault<ULocalMultiplayerSettings>();
    ULocalMultiplayerSubsystem* LocalMultiplayerSubsystem = GameInstance->GetSubsystem<ULocalMultiplayerSubsystem>();
    
    if (LocalMultiplayerSettings == nullptr || LocalMultiplayerSubsystem == nullptr) return false;
    
    int PlayerIndex = LocalMultiplayerSubsystem->GetAssignedPlayerIndexFromGamepadDeviceID(InputDevice.GetId());

    if(PlayerIndex < 0) return false;
    
    ULocalPlayer* LocalPlayer = GameInstance->GetLocalPlayerByIndex(PlayerIndex);
    if (LocalPlayer == nullptr) return false;
    
    APlayerController* PlayerController = LocalPlayer->GetPlayerController(GameInstance->GetWorld());
    if (PlayerController == nullptr) return false;
    
    FInputKeyParams params=FInputKeyParams(Key,Delta,DeltaTime,NumSamples,bGamepad,InputDevice);
    return PlayerController->InputKey(params);
}