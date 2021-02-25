
#include "UBCPlayerInteractionComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Interactable.h"

// Sets default values for this component's properties

UUBCPlayerInteractionComponent::UUBCPlayerInteractionComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	interactablesFound.AddDynamic(this, &UUBCPlayerInteractionComponent::OnInteractableFound_Event);
	interaction.AddDynamic(this, &UUBCPlayerInteractionComponent::OnInteraction_Event);
	interactableLost.AddDynamic(this, &UUBCPlayerInteractionComponent::OnInteractableLost_Event);
}

void UUBCPlayerInteractionComponent::OnInteractableFound_Event_Implementation(AActor* interactable)
{
}

void UUBCPlayerInteractionComponent::OnInteraction_Event_Implementation(AActor* interactable)
{
}

void UUBCPlayerInteractionComponent::OnInteractableLost_Event_Implementation()
{
}

// Called when the game starts

void UUBCPlayerInteractionComponent::BeginPlay()
{
	Super::BeginPlay();
}

bool UUBCPlayerInteractionComponent::CheckInteractables(FVector position, FVector forward)
{
	UWorld* world = GetWorld();

	// Detects all the actors of the specified type in a sphere and stores them into the interactables array.

	bool found = UKismetSystemLibrary::SphereOverlapActors(world, position, interactionRadius, interactionObjectTypes, interactableClass, TArray<AActor*>(), interactables);
	if (found)
	{
		float halfAngle = interactionAngle / 2.f;

		for (int i = 0; i < interactables.Num(); i++)
		{
			FVector a = (interactables[i]->GetActorLocation() - position);
			a.Normalize();
			FVector b = forward;
			b.Normalize();

			// If the actor is not inside the interaction angle, it is removed from the array.

			float angle = UKismetMathLibrary::DegAcos(FVector::DotProduct(a, b));
			if (angle > halfAngle)
			{
				interactables.RemoveAt(i--);
			}
		}

		// If the array is empty, no interactables have been found.
		return interactables.Num() > 0;
	}

	return false;
}

void UUBCPlayerInteractionComponent::UpdateInteractables()
{
	AActor* owner = GetOwner();
	if (CheckInteractables(owner->GetActorLocation(), owner->GetActorForwardVector()))
	{
		if (!hasInteraction)
		{
			hasInteraction = true;
			interactablesFound.Broadcast(GetInteractable());
		}
	}
	else if (hasInteraction)
	{
		hasInteraction = false;
		interactableLost.Broadcast();
	}
}

void UUBCPlayerInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	UpdateInteractables();
}

bool UUBCPlayerInteractionComponent::HasInteraction() const
{
	return hasInteraction;
}

AActor * UUBCPlayerInteractionComponent::GetInteractable() const
{
	return HasInteraction() ?
		interactables[0] :
		nullptr;
}

bool UUBCPlayerInteractionComponent::Interact()
{
	if (hasInteraction)
	{
		AActor* interactable = GetInteractable();

		if (interactable->GetClass()->ImplementsInterface(UInteractable::StaticClass()) && 
			IInteractable::Execute_Interact(interactable, GetOwner()))
		{
			interaction.Broadcast(interactable);
			return true;
		}
	}

	return false;
}

