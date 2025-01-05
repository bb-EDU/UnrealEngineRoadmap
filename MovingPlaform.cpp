// MovingPlatform.cpp
// Implements the MovingPlatform actor class, which includes logic for creating and configuring 
// the platform's visual appearance and periodic movement.

// Include the header file for the MovingPlatform class.
#include "MovingPlaform.h"

// Sets default values for this actor's properties and initializes the static mesh component.
AMovingPlaform::AMovingPlaform()
{
	// Enable ticking every frame.
	PrimaryActorTick.bCanEverTick = true;

	// Create the static mesh component and attach it to the root.
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->SetupAttachment(GetRootComponent());

	// Load the platform's mesh from the starter content.
	static ConstructorHelpers::FObjectFinder<UStaticMesh> PlatformMeshVisualAsset(TEXT("/Game/StarterContent/Architecture/Floor_400x400.Floor_400x400"));

	// Load the platform's material from the starter content
	static ConstructorHelpers::FObjectFinder<UMaterial> FloorWoodenTexture (TEXT("/Game/StarterContent/Materials/M_Wood_Oak.M_Wood_Oak"));

	// If the Mesh successfully loaded
	if (PlatformMeshVisualAsset.Object != nullptr)
	{
		// Assign the mesh to the static mesh component
		StaticMesh->SetStaticMesh(PlatformMeshVisualAsset.Object);
		// Set its relative location
		StaticMesh->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
		
		// If the Material successfully loaded
		if (FloorWoodenTexture.Object != nullptr)
		{
			// Get the material itself
			UMaterial* FloorWoodenTextureObject = FloorWoodenTexture.Object;
			// Apply the material to the static mesh
			StaticMesh->SetMaterial(0, FloorWoodenTextureObject);
		} else
		{
			// Log the error
			UE_LOG(LogTemp, Error, TEXT("FloorWoodenTexture is NULL"));
		}
	} else
	{
		// Log the error
		UE_LOG(LogTemp, Error, TEXT("Failed to load platform mesh assets"));
	}

}

// Called when the game starts or when spawned
void AMovingPlaform::BeginPlay()
{
	Super::BeginPlay();
	
}


// Called every frame
void AMovingPlaform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	// Get the location of the actor
	FVector NewLocation = GetActorLocation();
	// Get how much time (in seconds) passed since game started
	float RunningTime = GetGameTimeSinceCreation();
	// Account for frame time
	float CurrentTime = RunningTime + DeltaTime;
	// Calculate the height with the sine function
	float DeltaHeight = FMath::Sin(CurrentTime * MovementSpeed) - FMath::Sin(RunningTime * MovementSpeed);
	// Change the height
	NewLocation.Z += DeltaHeight * MovementAmplitude;
	// Set the location of the actor
	SetActorLocation(NewLocation);

}

// Created by bb-EDU
// Adapted from Epic Games' Unreal Engine C++ tutorial.