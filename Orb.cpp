// MovingPlatform.cpp
// Implements the Orb actor class
// The Orb rotates and is destroyed when collected (overlaps with the player)

#include "Orb.h"

#include "Components/BoxComponent.h"
#include "Components/PointLightComponent.h"
#include "YourFirstHour/MyCharacter.h"

// Sets default values
AOrb::AOrb()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create the box collision component to detect overlaps and set it as the root.
	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBoxComponent"));
	RootComponent = BoxComponent;
	// Scale it
	BoxComponent->SetWorldScale3D(FVector(0.3f, 0.3f, 0.3f));

	// Create the mesh
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->SetupAttachment(GetRootComponent());

	// Create the light inside
	PointLightComponent = CreateDefaultSubobject<UPointLightComponent>(TEXT("PointLight"));
	PointLightComponent->SetupAttachment(GetRootComponent());

	// Adjust the light's properties
	PointLightComponent-> Intensity = 2000.0f;
	PointLightComponent-> AttenuationRadius = 80.0f;
	PointLightComponent-> LightColor = FColor::Purple;
	
	
	// Import the static mesh and material for the orb's visual representation
	static ConstructorHelpers::FObjectFinder<UStaticMesh> OrbMesh(TEXT("/Game/orb_sm.orb_sm")); // Source: https://www.thingiverse.com/thing:581605/files
	static ConstructorHelpers::FObjectFinder<UMaterial> MetalOrbMaterial(TEXT("/Game/StarterContent/Materials/M_Metal_Chrome.M_Metal_Chrome")); //From starter content

	// Set the orb's static mesh and material if the assets were loaded successfully
	if (OrbMesh.Succeeded())
	{
		StaticMesh->SetStaticMesh(OrbMesh.Object);
		// Scale the orb
		StaticMesh->SetWorldScale3D(FVector(0.5, 0.5, 0.5));
		if (MetalOrbMaterial.Succeeded())
		{
			StaticMesh->SetMaterial(0, MetalOrbMaterial.Object);
		}
	} else
	{
		UE_LOG(LogTemp, Error, TEXT("Orb Mesh could not be found"));
	}

	// Enable overlap events for the box component and bind the overlap event to a handler
	BoxComponent->SetGenerateOverlapEvents(true);
	// Add a response to overlapping
	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &AOrb::OnBeginOverlap);
	
	// Optionally adjust the scale of the box and orb
	BoxComponent->SetBoxExtent(FVector(60.0f, 60.0f, 60.0f)); // Adjust size of the box
	StaticMesh->SetWorldScale3D(FVector(1.0f, 1.0f, 1.0f)); // Adjust size of the orb
	StaticMesh->SetRelativeLocation(FVector(0.0f, 0.0f, -60.0f));

}

// Called when the game starts or when spawned
void AOrb::BeginPlay()
{
	Super::BeginPlay();
	
	
}

// Handle the rotation of the orb every frame based on DeltaTim
void AOrb::Tick(float DeltaTime)
{
	// Calculate the new yaw rotation based on speed and frame tim
	
	// Get the orb's location
	float CurrentRotation = GetActorRotation().Yaw;

	// Move one degree every 10 seconds
	CurrentRotation += (DeltaTime * 360) / Speed; // Assuming 360 degrees

	// Normalize rotation to stay within 0-360
	CurrentRotation = FMath::Fmod(CurrentRotation, 360.0f); 
	if (CurrentRotation < 0) {
		CurrentRotation += 360.0f; // Handle negative rotations
	}

	// Apply the new rotation to the orb
	SetActorRotation(FRotator(0, CurrentRotation, 0));

	
}

// Handle the overlap event when another actor interacts with the orb
void AOrb::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// Ensure the overlap is with a valid actor and not the orb itself
	if (!OtherActor || OtherActor == this)
		return;
	
	// Check if the overlapping actor is of the Character class
	if (OtherActor->IsA(ACharacter::StaticClass()))
	{
		UE_LOG(LogTemp, Display, TEXT("Player collected the orb"));
		Destroy(this);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Non-player actor overlapped with the orb"));
	}
}	


// Created by bb-EDU