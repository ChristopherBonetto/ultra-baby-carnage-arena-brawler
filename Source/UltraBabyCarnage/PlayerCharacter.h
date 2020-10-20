
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "IDamageable.h"
#include "UBCItem.h"
#include "UBCPunchItem.h"
#include "PlayerCharacter.generated.h"

UCLASS()
class ULTRABABYCARNAGE_API APlayerCharacter : 
	public ACharacter,
	public IDamageable
{
GENERATED_BODY()

public:

	// Sets default values for this character's properties
	APlayerCharacter();

protected:

	UPROPERTY(EditAnywhere)
	float maxHealth;

	UPROPERTY(EditAnywhere)
	float currentHealth;

	UBCItem* leftItem;

	UBCItem* rightItem;

	TArray<AActor*> overlappingActors;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void MoveForward(float value);

	UFUNCTION()
	void MoveRight(float value);

	UFUNCTION()
	void LeftAttack();	
	
	UFUNCTION()
	void RightAttack();

	UFUNCTION()
	void CameraLook();

public:	

	UPROPERTY(EditAnywhere)
	float attackRange;

	UPROPERTY(VisibleAnywhere)
	class USphereComponent* overlapSphere;

	UPROPERTY(EditAnywhere)
	FVector cameraOffset;

	UPROPERTY(VisibleAnywhere)
	class UCameraComponent* camera;	

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual bool TakeDamage(const int& damage) override;

};
