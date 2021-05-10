
#include "UBCGameInstance.h"
#include "Kismet/GameplayStatics.h"

UUBCGameInstance::UUBCGameInstance()
{
}

void UUBCGameInstance::Init()
{
	for (TPair<TSubclassOf<AActor>, AActor*> &pair : singletons)
	{
		// If the instance of the class is not valid, a new instance is made.
		if (!pair.Value->IsValidLowLevel())
		{
			pair.Value = CreateInstance(pair.Key);
			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, pair.Key->GetName() + " -> " + pair.Value->GetName());
		}
	}

	UGameInstance::Init();
}

void UUBCGameInstance::OnStart()
{
	GEngine->GameViewport->Viewport->ViewportResizedEvent.AddUObject(this, &UUBCGameInstance::OnViewportSizeChange);
	UGameInstance::OnStart();
}

AActor* UUBCGameInstance::CreateInstance(TSubclassOf<AActor> actorClass)
{
	UWorld* world = GetWorld();

	// If the actor can be found in the world, it is returned.
	if (AActor* instance = UGameplayStatics::GetActorOfClass(world, actorClass))
	{
		return instance;
	}
	else // Else it is spawned and then returned a new actor.
	{
		return world->SpawnActor(actorClass);
	}
}

void UUBCGameInstance::MakeSingleton(TSubclassOf<AActor> actorClass)
{
	if (!IsSingleton(actorClass))
	{
		singletons.Add(actorClass, CreateInstance(actorClass));
	}
}

bool UUBCGameInstance::IsSingleton(TSubclassOf<AActor> actorClass) const
{
	return singletons.Contains(actorClass);
}

AActor* UUBCGameInstance::GetInstanceOf(TSubclassOf<AActor> actorClass, bool& outInstanceFound)
{
	AActor* instance = nullptr;

	if (IsSingleton(actorClass))
	{
		instance = singletons[actorClass];
		if (!instance->IsValidLowLevelFast())
		{
			instance = CreateInstance(actorClass);
		}
	}
	else
	{
		singletons.Add(actorClass, instance = CreateInstance(actorClass));
		//MakeSingleton(actorClass);
	}

	outInstanceFound = instance->IsValidLowLevelFast();
	return instance;
}

bool UUBCGameInstance::RemoveInstance(TSubclassOf<AActor> actorClass, bool destroyActor)
{
	if (IsSingleton(actorClass))
	{
		if (destroyActor)
		{
			// Destroys the actor.
			GetWorld()->DestroyActor(singletons[actorClass]);
		}

		// Removes the class from the map.
		singletons.Remove(actorClass);
	}

	return false;
}

void UUBCGameInstance::OnViewportSizeChange(FViewport* viewport, uint32 value)
{
	viewportSizeChanged.Broadcast(viewport->GetSizeXY().X, viewport->GetSizeXY().Y);
}