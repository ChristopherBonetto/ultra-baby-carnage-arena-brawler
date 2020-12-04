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
}