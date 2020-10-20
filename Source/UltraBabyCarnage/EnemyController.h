// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "IDamageable.h"
#include "EnemyController.generated.h"

UCLASS()
class ULTRABABYCARNAGE_API AEnemyController : 
	public AActor,
	public IDamageable
{
	GENERATED_BODY()
	
public:	

	// Sets default values for this actor's properties
	AEnemyController();

protected:

	UPROPERTY(EditAnywhere)
	unsigned int maxHealth;

	UPROPERTY(EditAnywhere)
	unsigned int currentHealth;

	UPROPERTY(VisibleAnywhere)
	USkeletalMeshComponent* mesh;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	unsigned int GetHealth() const;

	UFUNCTION()
	virtual bool TakeDamage(const int& damage) override;

};
