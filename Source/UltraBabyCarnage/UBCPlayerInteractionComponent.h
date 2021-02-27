// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "UBCPlayerInteractionComponent.generated.h"

/**
* Allows an actor to interact with objects.
*/

UCLASS(Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ULTRABABYCARNAGE_API UUBCPlayerInteractionComponent : 
	public USceneComponent
{
	GENERATED_BODY()

public:

	// Delegate for when an interactable is detected.

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FInteractableFound, AActor*, interactable);
	
	// Delegate for when an interaction is made.

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FInteraction, AActor*, interactable);

	// Delegate for when an interactable is no longer detected.

	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FInteractableLost);

protected: 

	/**
	* Indicates whether an interaction is detected.
	*/

	UPROPERTY(BlueprintReadWrite, Category = "Player: Interaction")
	bool hasInteraction;

	/**
	* The array of detected interactables.
	*/

	UPROPERTY(BlueprintReadWrite, Category = "Player: Interaction")
	TArray<AActor*> interactables;

	/**
	* Invoked when an interactable is detected.
	*/

	UPROPERTY(BlueprintAssignable)
	FInteractableFound interactablesFound;

	/**
	* Invoked when an interaction is made.
	*/

	UPROPERTY(BlueprintAssignable)
	FInteraction interaction;

	/**
	* Invoked when an interactable is no longer detected.
	*/

	UPROPERTY(BlueprintAssignable)
	FInteractableLost interactableLost;

public:

	/**
	* The radius of interaction.
	*/

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player: Interaction")
	float interactionRadius;

	/**
	* The angle of interaction.
	*/

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player: Interaction")
	float interactionAngle;

	/**
	* The object types that can be detected by the interaction.
	*/

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player: Interaction")
	TArray<TEnumAsByte<EObjectTypeQuery>> interactionObjectTypes;

	/**
	* The class of actors that will be detected by the interaction.
	*/

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player: Interaction")
	TSubclassOf<AActor> interactableClass;

public:	
	
	/**
	* Default constructor.
	*/

	UUBCPlayerInteractionComponent();

protected:
	
	// Called when the game starts.

	virtual void BeginPlay() override;

	/**
	* Event called when an interaction is detected.
	*/

	UFUNCTION(BlueprintNativeEvent)
	void OnInteractableFound(AActor* interactable);

	/**
	* Event called when an interaction is made.
	*/

	UFUNCTION(BlueprintNativeEvent)
	void OnInteraction(AActor* interactable);

	/**
	* Event called when an interaction is no longer detected.
	*/

	UFUNCTION(BlueprintNativeEvent)
	void OnInteractableLost();

	/**
	* Checks for interactables at the specified position and direction.
	*/

	UFUNCTION(BlueprintCallable, Category = "Player: Interaction")
	virtual bool CheckInteractables(FVector position, FVector forward);

	/**
	* Updates the interaction component.
	*/

	UFUNCTION(BlueprintCallable, Category = "Player: Interaction")
	virtual void UpdateInteractables();

public:	
	
	// Checks for new interactables.

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	/**
	* Returns whether an interactable is detected.
	*/

	UFUNCTION(BlueprintCallable, Category = "Player: Interaction")
	bool HasInteraction() const;

	/**
	* Returns the currently detected interactable. If no interactables are detected, a nullptr is returned.
	*/

	UFUNCTION(BlueprintCallable, Category = "Player: Interaction")
	AActor* GetInteractable() const;

	/**
	* Tries to make the owner interact with the detected interactable and returns whether the operation was succesful.
	*/

	UFUNCTION(BlueprintCallable, Category = "Player: Interaction")
	bool Interact();

};
