// Fill out your copyright notice in the Description page of Project Settings.


#include "UBCEnemyCharacter.h"

// Sets default values
AUBCEnemyCharacter::AUBCEnemyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AUBCEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AUBCEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AUBCEnemyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

