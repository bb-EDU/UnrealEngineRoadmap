// Header file for the MovingPlatform actor class.
// Defines a platform that can move in the game world.

// Properties are declared here

#pragma once
// Core engine includes for Unreal Engine functionality.
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

// Include for the MovingPlatform class.
// NOTE: This must always be the last include due to Unreal's build tool requirements.
#include "MovingPlaform.generated.h"

// Unreal Engine macro to generate boilerplate code for the class.
UCLASS()
class YOURFIRSTHOUR_API AMovingPlaform : public AActor
{
	// This takes care of boilerplate code for UE
	// Explanation of what it actually does: https://liquidex.house/programming/technologies/unreal-engine/generated-body
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMovingPlaform();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Static mesh component representing the platform's visual appearance.
	UPROPERTY(EditAnywhere, Blueprintable) // Macro that allows the Unreal Editor to access it
	UStaticMeshComponent* StaticMesh;

	// Numerical properties
	
	// Speed at which the platform moves.
	UPROPERTY(EditAnywhere, BlueprintReadWrite) // Can be changed in the editor and blueprints
	float MovementSpeed = 1.0f;
	// Maximum amplitude of the platform's movement.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MovementAmplitude = 200.0f;
};

// Created by bb-EDU
// Adapted from Epic Games' Unreal Engine C++ tutorial.