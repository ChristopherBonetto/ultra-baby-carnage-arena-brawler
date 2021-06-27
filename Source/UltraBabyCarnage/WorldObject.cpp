
#include "WorldObject.h"

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