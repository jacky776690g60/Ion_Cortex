/* =================================================================
| IonCortexGameMode.cpp  --  Ion_Cortex
|
| Created by Jack on 10/10/2023
| Copyright © 2023 jacktogon. All rights reserved.
================================================================= */

#include "IonCortexGameMode.h"
#include "UObject/ConstructorHelpers.h"
#include "HAL/FileManager.h"

#include "PlasmaBallCharacter.h"


AIonCortexGameMode::AIonCortexGameMode()
{
    UE_LOG(LogTemp, Warning, TEXT("Successfully loaded scene"));
    // Set default pawn class to our PlasmaBallCharacter
    //DefaultPawnClass = APlasmaBallCharacter::StaticClass();

    PlayerControllerClass = APlayerController::StaticClass();


    //FString AssetPath = "/Game/Characters/BP_PlasmaBallCharacter";
    //FString FullPath = FPaths::ProjectContentDir() + AssetPath.RightChop(6) + ".uasset"; // Removing the '/Game/' part

    //if (IFileManager::Get().FileExists(*FullPath))
    //{
    //    UE_LOG(LogTemp, Warning, TEXT("The file exists at path: %s"), *FullPath);
    //} else
    //{
    //    UE_LOG(LogTemp, Error, TEXT("File does not exist at path: %s"), *FullPath);
    //}

    // Find the Blueprint class of the PlasmaBallCharacter
    static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Characters/BP_PlasmaBallCharacter.BP_PlasmaBallCharacter_C"));

    if (PlayerPawnBPClass.Class != nullptr)
    {
        DefaultPawnClass = PlayerPawnBPClass.Class;
        UE_LOG(LogTemp, Warning, TEXT("Successfully set BP_PlasmaBallCharacter as DefaultPawnClass"));
    } else
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to find BP_PlasmaBallCharacter Blueprint"));
    }
}