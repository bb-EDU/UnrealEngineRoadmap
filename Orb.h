// Header file for the Orb actor class.
// Defines an Orb that rotates and can be collected by the player

#pragma once

// Included headers
#include "CoreMinimal.h"
#include "Components/BoxComponent.h" // Import the Box component 
#include "Components/PointLightComponent.h" // Imports the Point Light component
#include "GameFramework/Actor.h"
#include "Orb.generated.h"

UCLASS()
class YOURFIRSTHOUR_API AOrb : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AOrb();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Static mesh component representing the platform's visual appearance.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* StaticMesh;

	// Box component that detects the overlapping
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UBoxComponent* BoxComponent;

	// Point light component that creates the light in the orb
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UPointLightComponent* PointLightComponent;

	// Speed at which the Orb rotates
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Speed = 10.0;
	
	
	UFUNCTION()
	// Function triggered when another actor overlaps with the Orb's box component.
	// Used to handle player interaction when the Orb is collected
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
	const FHitResult& SweepResult); // Arguments are boilerplate

};

// Created by bb-EDU
