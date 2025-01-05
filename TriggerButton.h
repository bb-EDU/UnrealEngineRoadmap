// Header file for the TriggerButton actor class.
// Defines a platform that, when pressed, spawns an Orb object

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "TriggerButton.generated.h"

UCLASS()
class YOURFIRSTHOUR_API ATriggerButton : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATriggerButton();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Static mesh component representing the static part
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* StaticPartMesh;

	// Static mesh component representing the pressable part
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* TriggerablePartMesh;

	// Box component that detects the overlapping
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UBoxComponent* BoxComponent;

	// Keeps track of being pressed
	UPROPERTY()
	bool hasBeenPressed = false;

	// Function that handles overlap
	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
	const FHitResult& SweepResult);
};
