/* =================================================================
| PlasmaBallCharacter.h  --  Ion_Cortex
|
| Created by Jack on 10/10/2023
| Copyright © 2023 jacktogon. All rights reserved.
================================================================= */

#pragma once

#include "CoreMinimal.h"             // includes a minimal set of core classes required by most source files in Unreal
#include "GameFramework/Character.h" // related to the basic character class in Unreal, allowing movement, animation, etc.

/* Additional includes for Niagara */
#include "NiagaraComponent.h"       // represents an instance of a particle system in the game world
#include "NiagaraSystem.h"          // represents the broader set of rules and behaviors that define how that particle system should behave.
#include "NiagaraFunctionLibrary.h" // This is a collection of helper functions related to the Niagara system. 

/* Characters */
#include "PlasmaBallCharacter.generated.h" // a file generated by the Unreal Header Tool (UHT) when compiling. It handles things like reflection, which allows C++ code to be exposed to and interact with the Unreal Editor


UCLASS() // unreal macro
class ION_CORTEX_API APlasmaBallCharacter : public ACharacter
{
    GENERATED_BODY()

public:
    // Sets default values for this character's properties
    APlasmaBallCharacter();

    /*
    * can be seen but not modified in the editor;
    * can be accessed in Blueprints (Unreal's visual scripting language) but can't be modified
    * will be sorted under the "Mesh" category
    * meta = (AllowPrivateAccess = "true"): This property, although private, can be edited in derived Blueprint classes.
    */ 
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Mesh, meta = (AllowPrivateAccess = "true"))
    class UStaticMeshComponent* SphereMesh;



    // Variable to hold the Niagara system asset
    UPROPERTY(EditDefaultsOnly, Category = "FX")
    UNiagaraSystem* PlasmaEmitter;

    // Variable to hold the Niagara component at runtime
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "FX", meta = (AllowPrivateAccess = "true"))
    UNiagaraComponent* PlasmaEmitterComponent;

protected: /* not accessible outside of the class, but can be accessed by derived classes */
    virtual void BeginPlay() override; // Called when game starts or when spawned

    /* Camera boom positioning the camera behind the character */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
    class USpringArmComponent* CameraBoom;
    /* main camera component */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
    class UCameraComponent* FollowCamera;

    


public:
    /* Called every frame. it's used to frequently update or check something in the game */
    virtual void Tick(float DeltaTime) override;

    /* Binds input functions (like pressing a key) to actions. */
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

    UFUNCTION(BlueprintNativeEvent, Category = "MyCustomCategory")
    float MyFunction();

    /* Lightning Properties */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Lightning", meta=(ToolTip="Controls how often the lightning line happens."))
	double TraceCooldown = .5;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Lightning", meta=(ToolTip="Record when is the last lightning line generated."))
	double LastTrace = 0.;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Lightning", meta=(ToolTip="min radius where the lightning can reach away from the surface."))
	double MinRadius = 13.;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Lightning", meta=(ToolTip="max radius where the lightning can reach away from the surface."))
	double MaxRadius = 200.;


    void MoveForward(float Value);
    void MoveRight(float Value);
};
