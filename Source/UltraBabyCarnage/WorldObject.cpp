
#include "WorldObject.h"

UWorldObject::UWorldObject() :
	UObject()
{
	//FWorldDelegates::OnPostWorldCreation.AddUObject(this, &UWorldObject::Init);
	OnInit();
}

void UWorldObject::Init(UWorld* world)
{
	OnInit();
}

void UWorldObject::OnInit_Implementation()
{
}

class UWorld* UWorldObject::GetWorld() const
{
	//if (GetOuter()->IsA(UActorComponent::StaticClass()))
	if(!HasAnyFlags(RF_ClassDefaultObject))
	{
		return GetOuter()->GetWorld();
	}

	return nullptr;
}