
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"

UCLASS()
class ULTRABABYCARNAGE_API APlayerCharacter : public ACharacter
{
GENERATED_BODY()

public:

	// Sets default values for this character's properties
	APlayerCharacter();

protected:

	//UPROPERTY(NoExport)
	TArray<AActor*> overlappingActors;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void MoveForward(float value);

	UFUNCTION()
	void MoveRight(float value);

	UFUNCTION()
	void Attack();

	UFUNCTION()
	void CameraLook();

public:	

	//UPROPERTY(VisibleAnywhere)
	UPROPERTY(EditAnywhere)
	float maxHealth;

	UPROPERTY(EditAnywhere)
	float health;

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

};
