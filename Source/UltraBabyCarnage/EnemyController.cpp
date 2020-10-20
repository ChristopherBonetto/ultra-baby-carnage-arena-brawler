// Fill out your copyright notice in the Description page of Project Settings.

#include <cstdlib>
#include <string>
#include "Components/SkeletalMeshComponent.h"
#include "EnemyController.h"

// Sets default values
AEnemyController::AEnemyController()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	
	currentHealth = maxHealth;

	mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Skeletal Mesh"));
	if (mesh)
	{
		mesh->SetSimulatePhysics(false);
	}
}

// Called when the game starts or when spawned
void AEnemyController::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AEnemyController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

unsigned int AEnemyController::GetHealth() const
{
	return currentHealth;
}

bool AEnemyController::TakeDamage(const int& damage)
{
	currentHealth = std::max(0, (int)currentHealth - damage);

	if (GEngine)
	{
		std::string s = std::to_string(currentHealth);
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, s.c_str());
	}

	if (currentHealth == 0u)
	{
		mesh->SetSimulatePhysics(true);
		return true;
	}

	return false;
}

