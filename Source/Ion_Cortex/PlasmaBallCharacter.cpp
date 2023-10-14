/* =================================================================
| PlasmaBallCharacter.cpp  --  Ion_Cortex
|
| Created by Jack on 10/10/2023
| Copyright © 2023 jacktogon. All rights reserved.
================================================================= */

#include "PlasmaBallCharacter.h"
#include "GameFramework/SpringArmComponent.h"  // Required for the CameraBoom
#include "Camera/CameraComponent.h"            // Required for the FollowCamera
#include "Components/StaticMeshComponent.h"  // Required for the SphereMesh
#include "Components/CapsuleComponent.h"



APlasmaBallCharacter::APlasmaBallCharacter()
{
    // Set this character to call Tick() every frame.
    PrimaryActorTick.bCanEverTick = true;

    // Create a camera boom (spring arm)
    CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
    CameraBoom->SetupAttachment(RootComponent);
    CameraBoom->TargetArmLength = 300.0f; // The distance away from the player
    CameraBoom->bUsePawnControlRotation = true; // Rotate arm based on controller

    // Create a follow camera
    FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
    FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom
    FollowCamera->bUsePawnControlRotation = false; // Let the arm control the camera rotation


    // Create a sphere mesh and attach it to the character's root
    SphereMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SphereMesh"));
    SphereMesh->SetupAttachment(RootComponent);

    // Load and set the sphere mesh from the starter content
    static ConstructorHelpers::FObjectFinder<UStaticMesh> SphereMeshAsset(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Sphere.Shape_Sphere'"));
    if (SphereMeshAsset.Succeeded())
    {
        SphereMesh->SetStaticMesh(SphereMeshAsset.Object);
    }

    if (SphereMesh && SphereMesh->GetStaticMesh())
    {
        FBoxSphereBounds Bounds = SphereMesh->GetStaticMesh()->GetBounds();
        float SphereRadius = Bounds.SphereRadius;
        GetCapsuleComponent()->InitCapsuleSize(SphereRadius, SphereRadius);
    }










    // Load the Niagara system from the specified path
    static ConstructorHelpers::FObjectFinder<UNiagaraSystem> PlasmaEmitterAsset(TEXT("NiagaraSystem'/Game/Ion_Cortex/Content/FX/plasma_emitter_turbulance_System.plasma_emitter_turbulance_System'"));
    if (PlasmaEmitterAsset.Succeeded())
    {
        PlasmaEmitter = PlasmaEmitterAsset.Object;
    }

}

void APlasmaBallCharacter::BeginPlay()
{
    Super::BeginPlay();

    if (PlasmaEmitter)
    {
        PlasmaEmitterComponent = UNiagaraFunctionLibrary::SpawnSystemAttached(PlasmaEmitter, SphereMesh, NAME_None, FVector::ZeroVector, FRotator::ZeroRotator, EAttachLocation::SnapToTarget, true, true, ENCPoolMethod::AutoRelease, true);
    }

    if (PlasmaEmitterComponent)
    {
        PlasmaEmitterComponent->Activate(true);  // The 'true' parameter forcefully resets and starts the system, even if it was previously running.
    }

    // if (PlasmaEmitterComponent)
    // {
    //     // Log the status of the Niagara system to the console.
    //     UE_LOG(LogTemp, Warning, TEXT("Plasma Emitter is attached and valid."));
        
    //     if (!PlasmaEmitterComponent->IsActive())
    //     {
    //         UE_LOG(LogTemp, Warning, TEXT("Plasma Emitter is NOT active!"));
    //     }
    // }
    // else
    // {
    //     UE_LOG(LogTemp, Warning, TEXT("Plasma Emitter failed to attach or is invalid."));
    // }
}

void APlasmaBallCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void APlasmaBallCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    // Bind movement functions to input
    PlayerInputComponent->BindAxis("MoveForward", this, &APlasmaBallCharacter::MoveForward);
    PlayerInputComponent->BindAxis("MoveRight", this, &APlasmaBallCharacter::MoveRight);

    // Bind camera controls
    PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
    PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
}

void APlasmaBallCharacter::MoveForward(float Value)
{
    AddMovementInput(GetActorForwardVector(), Value);
}

void APlasmaBallCharacter::MoveRight(float Value)
{
    AddMovementInput(GetActorRightVector(), Value);
}
