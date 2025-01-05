#include "TriggerButton.h"
#include "Orb.h"

// Sets default values
ATriggerButton::ATriggerButton()
{
	PrimaryActorTick.bCanEverTick = true;

	// Creates, scales, and attaches the box to the root
	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	RootComponent = BoxComponent;
	BoxComponent->SetWorldScale3D(FVector(0.5f, 0.5f, 0.5f));

	// Creates the static part of the button and attaches it to the root
	StaticPartMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticPartMesh"));
	StaticPartMesh->SetupAttachment(BoxComponent);

	// Creates the pressable part of the button and attaches it to the root
	TriggerablePartMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TriggerablePartMesh"));
	TriggerablePartMesh->SetupAttachment(BoxComponent);

	// Load the mesh from the starter content
	static ConstructorHelpers::FObjectFinder<UStaticMesh> PlatformMesh (TEXT("/Game/StarterContent/Architecture/SM_AssetPlatform.SM_AssetPlatform"));

	if (PlatformMesh.Succeeded())
	{
		// Configure the static part of the button
		StaticPartMesh->SetStaticMesh(PlatformMesh.Object);
		FVector CurrentScale = StaticPartMesh->GetComponentScale();
		CurrentScale.Z = CurrentScale.Z * 3.0f;
		StaticPartMesh->SetWorldScale3D(CurrentScale);
		// Configure the dynamic part of the button
		TriggerablePartMesh->SetStaticMesh(PlatformMesh.Object);
		FVector CurrentPosition = TriggerablePartMesh->GetComponentScale();
		CurrentPosition.Z = CurrentPosition.Z + 25.0f;
		TriggerablePartMesh->SetRelativeLocation(CurrentPosition);
		TriggerablePartMesh->SetWorldScale3D(FVector(0.6f, 0.6f, 3.0f));
		
	} else
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to load cylinder shape"));
	}

	// Load the metal material
	static ConstructorHelpers::FObjectFinder<UMaterial> MetalMaterial (TEXT("/Game/StarterContent/Materials/M_Metal_Brushed_Nickel.M_Metal_Brushed_Nickel"));

	if (MetalMaterial.Succeeded())
	{
		// Set the material
		StaticPartMesh->SetMaterial(0, MetalMaterial.Object);
	}

	// Load the red plastic material
	static ConstructorHelpers::FObjectFinder<UMaterial> ButtonMaterial (TEXT("/Game/StarterContent/Materials/M_AssetPlatformRed.M_AssetPlatformRed"));

	if (MetalMaterial.Succeeded())
	{
		// Set the material to the mesh
		TriggerablePartMesh->SetMaterial(0, ButtonMaterial.Object);
	}

	// Adjust the scale of the box
	BoxComponent->SetBoxExtent(FVector(55.0f, 55.0f, 70.0f));

	
	// Handle overlap
	BoxComponent -> SetGenerateOverlapEvents(true);
	BoxComponent -> OnComponentBeginOverlap.AddDynamic(this, &ATriggerButton::OnBeginOverlap);
	
}

// Called when the game starts or when spawned
void ATriggerButton::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATriggerButton::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}


void ATriggerButton::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// Ensure that the button can't be pressed twice
	if (!hasBeenPressed)
	{
		// Simulate pressing the button by lowering the pressable part
		FVector CurrentPosition = TriggerablePartMesh->GetRelativeLocation();
		CurrentPosition.Z = CurrentPosition.Z - 15.0f;
		TriggerablePartMesh->SetRelativeLocation(CurrentPosition);
		
		// Spawn an orb at a chosen location 
		FVector Location(620.0f, 990.0f, 210.0f);
		FRotator Rotation(1.0f, 1.0f, 1.0f);
		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
		AOrb* newOrb = GetWorld()->SpawnActor<AOrb>(AOrb::StaticClass(), Location, Rotation, SpawnParams);


		// For debugging purposes
		if (newOrb)
		{
			UE_LOG(LogTemp, Warning, TEXT("Orb successfully spawned!"));
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("Failed to spawn!"));
		}
		// Mark the button as pressed to prevent further presses
		hasBeenPressed = true;
	}
}



