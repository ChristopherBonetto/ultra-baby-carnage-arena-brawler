
#include "Kismet/KismetMathLibrary.h"
#include "Components/CapsuleComponent.h"
#include "Components/SphereComponent.h"
#include "Camera/CameraComponent.h"
#include "EnemyController.h"
#include "PlayerCharacter.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	UCapsuleComponent* capsule = GetCapsuleComponent();

	overlapSphere = CreateDefaultSubobject<USphereComponent>(TEXT("OverlapSphere"));
	if (overlapSphere)
	{
		overlapSphere->SetupAttachment(capsule);
		overlapSphere->SetRelativeLocation(FVector(0, 0, 0));
		overlapSphere->SetSphereRadius(attackRange * 100);
	}

	// Create a first person camera component.
	camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	if (camera)
	{
		// Attach the camera component to our capsule component.
		camera->SetupAttachment(capsule);
		
		camera->SetRelativeLocation(cameraOffset);
		camera->SetUsingAbsoluteLocation(true);
		camera->SetUsingAbsoluteRotation(true);
	}
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	overlapSphere->SetSphereRadius(attackRange * 100);
}

void APlayerCharacter::MoveForward(float value)
{
	// Find out which way is "forward" and record that the player wants to move that way.
	FVector direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::X);
	AddMovementInput(direction, value);
}

void APlayerCharacter::MoveRight(float value)
{
	// Find out which way is "forward" and record that the player wants to move that way.
	FVector direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::Y);
	AddMovementInput(direction, value);
}

void APlayerCharacter::Attack()
{
	overlapSphere->GetOverlappingActors(overlappingActors);
	for (auto i : overlappingActors)
	{
		if (i->GetClass()->IsChildOf(AEnemyController::StaticClass()))
		{
			((AEnemyController*)i)->TakeDamage(1);
		}
	}
}

// Makes the camera look at the player.

void APlayerCharacter::CameraLook()
{
	FVector playerPos = GetActorLocation();
	FVector cameraPos = playerPos + cameraOffset;
	
	FRotator lookRot = UKismetMathLibrary::FindLookAtRotation(cameraPos, playerPos);
	
	camera->SetWorldLocationAndRotation(cameraPos, lookRot);
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	CameraLook();
}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	// Set up "movement" bindings.
	PlayerInputComponent->BindAxis("Vertical", this, &APlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("Horizontal", this, &APlayerCharacter::MoveRight);

	// Attack bindings.
	PlayerInputComponent->BindAction("Attack", IE_Pressed, this, &APlayerCharacter::Attack);
}

