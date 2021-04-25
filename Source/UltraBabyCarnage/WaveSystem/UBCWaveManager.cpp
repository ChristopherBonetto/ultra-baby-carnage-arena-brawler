
#include "UBCWaveManager.h"
#include <iostream>
#include <string>
#include "Kismet/KismetMathLibrary.h"
#include "UBCWeaponCost.h"

AUBCWaveManager::AUBCWaveManager()
{
	// Binds the delegates to the events.

	waveStart.AddDynamic(this, &AUBCWaveManager::OnWaveStart);
	roundStart.AddDynamic(this, &AUBCWaveManager::OnRoundStart);
	roundUpdate.AddDynamic(this, &AUBCWaveManager::OnRoundUpdate);
	roundDone.AddDynamic(this, &AUBCWaveManager::OnRoundDone);
	waveDone.AddDynamic(this, &AUBCWaveManager::OnWaveDone);
	enemySpawned.AddDynamic(this, &AUBCWaveManager::OnEnemySpawned);
	anyEnemyDeath.AddDynamic(this, &AUBCWaveManager::OnAnyEnemyDeath);
}

void AUBCWaveManager::BeginPlay()
{
	if (wave->IsValidLowLevel())
	{
		// Starts the wave.
		waveStart.Broadcast();
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(0, 5.f, FColor::Red, TEXT("The Wave Manager doesn't have a wave asset."));
	}
}

void AUBCWaveManager::UpdateRound()
{
	// Ticks the round.
	roundUpdate.Broadcast(GetWorld()->DeltaTimeSeconds);
}

void AUBCWaveManager::StartRound()
{
	// Starts the round.
	roundStart.Broadcast();
}

AUBCItemBase* AUBCWaveManager::GetItemToEquip()
{
	int itemCount = roundItems.Num();

	TSubclassOf<AUBCItemBase> itemClass;
	// If there are still items in the list, a random item is selected and its amount decreased.
	if (itemCount > 0)
	{
		int itemIndex = FMath::RandRange(0, itemCount - 1);

		itemClass = roundItems[itemIndex].Key;
		//roundItems[itemIndex].Value--;

		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, FString::FromInt(roundItems[itemIndex].Value - 1));

		// If the amount of the items is now less or equal to 0, it is removed from the list.
		if (--roundItems[itemIndex].Value <= 0)
		{
			roundItems.RemoveAt(itemIndex);
		}
	}
	// Else the default item is selected.
	else
	{
		itemClass = defaultItemClass;
	}

	if (itemClass)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, itemClass.Get()->GetName());

		FActorSpawnParameters spawnParams;
		spawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		// The item is spawned.
		return (AUBCItemBase*)GetWorld()->SpawnActor(itemClass);
	}

	return nullptr;
}

void AUBCWaveManager::SpawnEnemy()
{
	// Sorts the spawn points.
	SortSpawnPointsByDistance();

	// Finds the spawn location of the enemy.
	FTransform transform(FRotator::ZeroRotator, GetSpawnLocation());

	FActorSpawnParameters spawnParams;
	spawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
	
	// Spawns the enemy.
	AUBCCharacter* enemy = (AUBCCharacter*)GetWorld()->SpawnActor(*wave->GetEnemyClass(), &transform, spawnParams);

	if (enemy->IsValidLowLevelFast())
	{
		// Increase the counters.

		currentEnemyCount++;
		spawnedEnemyCount++;

		// Spawns and attaches the item to the actor.
		//AUBCItemBase* item = GetItemToEquip();
		//if (item->IsValidLowLevelFast())
		//{
		//	item->AttachToActor(enemy, FAttachmentTransformRules::KeepRelativeTransform, "LeftHandSocket");
		//}

		// Binds to the death event of the enemy.
		enemy->death.AddDynamic(this, &AUBCWaveManager::OnEnemyDeath);

		// Invokes the enemy spawned event.
		enemySpawned.Broadcast(enemy);
	}
}

void AUBCWaveManager::SpawnEnemies()
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, TEXT("Spawn Enemies."));
	for (int i = 1; i <= enemyBatchSize; i++)
	{
		// Spawns an enemy.
		SpawnEnemy();

		// If enough enemies have been spawned the spawning ends.
		if (spawnedEnemyCount >= roundEnemyCount)
		{
			GetWorldTimerManager().ClearTimer(enemySpawnTimer);
			break;
		}
		// Else if the current count of active enemies is greater than the maximum amount of active enemies, 
		// the spawning pauses until an enemy is killed.
		else if (currentEnemyCount >= maxActiveEnemiesCount)
		{
			spawnHalted = true;
			GetWorldTimerManager().ClearTimer(enemySpawnTimer);
			break;
		}
	}
}

FVector AUBCWaveManager::GetSpawnLocation() const
{
	// Retrieves the minimum length of the array that respects the parameters.
	int size = FMath::Min(GetCutoffLength(), FMath::Min(maxActiveSpawnPoints, enemySpawnPoints.Num()));

	if(enemySpawnPoints.IsValidIndex(size - 1))
	{ 
		// Returns a random spawn point inside this pool.
		return enemySpawnPoints[FMath::RandRange(0, size - 1)];
	}

	// No available spawn point was found, a zero vector is returned.
	return FVector::ZeroVector;
}

void AUBCWaveManager::SortSpawnPointsByDistance()
{
	// Retrieves the position of the player in the world.
	FVector playerPosition = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation();

	// Bubble sorts the spawn points using the distance from the player as the comparator.
	for (int i = 0; i < enemySpawnPoints.Num(); i++)
	{
		for (int j = i; j < enemySpawnPoints.Num() - 1; j++)
		{
			FVector& a = enemySpawnPoints[j];
			FVector& b = enemySpawnPoints[j + 1];

			if (FVector::Distance(a, playerPosition) > FVector::Distance(b, playerPosition))
			{
				FVector tmp = a;
				a = b;
				b = tmp;
			}
		}
	}
}

int AUBCWaveManager::GetCutoffLength() const
{
	// Retrieves the position of the player in the world.
	FVector playerPosition = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation();

	// Retrieves the size of the array.
	int size = enemySpawnPoints.Num();

	for (int i = 0; i < size; i++)
	{
		// If the spawn point is further than the cutoff distance, the size of the array before this element is returned.
		if (FVector::Distance(enemySpawnPoints[i], playerPosition) > spawnCutoffDistance)
		{
			return i;
		}
	}

	// All the spawn points respect the cutoff distance.
	return size;
}

void AUBCWaveManager::OnWaveStart_Implementation() 
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, TEXT("Wave started"));
	// Retrieves the max active enemies count from the wave asset.
	maxActiveEnemiesCount = wave->GetMaxActiveEnemiesCount();

	//roundBudgetMultiplier = wave->GetMinBudgetMultiplier();

	// Starts the round.
	//roundStart.Broadcast();
	GetWorldTimerManager().SetTimer(roundStartTimer, this, &AUBCWaveManager::StartRound, wave->GetRoundDelay(), false);
}

void AUBCWaveManager::CreateRoundItemList()
{
	roundBudgetMultiplier = wave->GetRoundBudgetMultiplier(currentRound);

	// Calculates the budget of the round.
	roundBudget = wave->GetBaseBudget() * roundBudgetMultiplier;

	//UDataTable* itemTable = wave->GetItemCostTableOfTier();
	UDataTable* itemTable = wave->GetItemCostTableOfTier(wave->GetRoundTier(currentRound));

	if (itemTable->IsValidLowLevelFast())
	{
		FString contextString;

		// Finds all the names of the items in the table.
		TArray<FName> rowNames;
		rowNames = itemTable->GetRowNames();

		int itemCount = rowNames.Num();

		// Finds the first and last indeces of the iteration.
		//int last = FMath::Clamp(wave->GetRoundMaxItemIndex(currentRound), 0, itemCount - 1);
		//int first = FMath::Clamp(wave->GetRoundItemIndexOffset(currentRound), 0, last);	
		int last = itemCount - 1;
		int first = 0;

		// Retrieves the default item class of the round.
		int defaultIndex = wave->GetRoundDefaultItemIndex(currentRound);
		defaultItemClass = FMath::IsWithin(defaultIndex, 0, itemCount) ?
			itemTable->FindRow<FUBCWeaponCost>(rowNames[defaultIndex], contextString)->weaponClass :
			nullptr;

		for (int i = last; i >= first; i--)
		{
			FUBCWeaponCost* row = itemTable->FindRow<FUBCWeaponCost>(rowNames[i], contextString);
			if (row)
			{
				int cost = row->cost;

				// Adds to the item list the class and amount to buy.
				int amountToBuy = FMath::RandRange(0, roundBudget / cost);
				roundItems.Add(TPair<TSubclassOf<AUBCItemBase>, int>(row->weaponClass, amountToBuy));

				// Deducts the cost from the budget.
				roundBudget -= cost * amountToBuy;

				// If the budget is 0, no other items are bought.
				if (roundBudget <= 0)
				{
					break;
				}
			}
		}

		// If there's still budget left, it is all spent on copies of the first item.
		if (roundBudget > 0)
		{
			FUBCWeaponCost* row = itemTable->FindRow<FUBCWeaponCost>(rowNames[first], contextString);
			if (row->cost <= roundBudget)
			{
				int amount = roundBudget / row->cost;
				roundItems[last].Value += amount;
				roundBudget -= amount * row->cost;
			}
		}
	}
	else
	{
		defaultItemClass = nullptr;
	}

#if WITH_EDITOR

	for (auto i : roundItems)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, i.Key.Get()->GetName() + " : " + FString::FromInt(i.Value));
	}

#endif

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, FString::FromInt(roundBudget));
}

void AUBCWaveManager::OnRoundStart_Implementation() 
{
	// Sets the round as not done and spawn halting as false.
	isRoundDone = spawnHalted = false;

	// Retrieves the amount of enemies to spawn this round from the asset.
	roundEnemyCount = wave->GetRoundSpawnCount(currentRound);
	
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, FString::FromInt(roundEnemyCount) + " enemies should spawn");

	// If the enemy count is greater than 0, the round is actually started, else it is ended.
	if (roundEnemyCount > 0)
	{
		// Updates the item list of the round.
		CreateRoundItemList();

		currentEnemyCount = spawnedEnemyCount = 0;
		enemyBatchSize = wave->GetRoundBatchSize(currentRound);

		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, "Spawn initial enemies");
		SpawnEnemies();

		GetWorldTimerManager().SetTimer(enemySpawnTimer, this, &AUBCWaveManager::SpawnEnemies, wave->GetRoundSpawnDelay(currentRound), true);
		GetWorldTimerManager().SetTimer(roundUpdateTimer, this, &AUBCWaveManager::UpdateRound, .1f, true);
	}
	else
	{
		roundDone.Broadcast();
	}

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, TEXT("Round " + FString::FromInt(currentRound) + " started"));
}

void AUBCWaveManager::OnRoundUpdate_Implementation(float deltaTime)
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, FString::SanitizeFloat(GetSpawnTimeRemaining()) + "s remain to next spawn.");
}

void AUBCWaveManager::OnRoundDone_Implementation() 
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, "Round " + FString::FromInt(currentRound) + " completed");

	// The round is set as done.
	isRoundDone = true;

	// The round count is increased.
	currentRound++;

	// The tick of the round is stopped.
	GetWorldTimerManager().ClearTimer(roundUpdateTimer);
	
	//roundBudgetMultiplier *= 2;

	// If the wave should end, it is ended.
	if (ShouldWaveEnd())
	{
		waveDone.Broadcast();
	}
	// Else the timer for the next round is started.
	else
	{
		GetWorldTimerManager().SetTimer(roundStartTimer, this, &AUBCWaveManager::StartRound, wave->GetRoundDelay(), false);
	}
}

void AUBCWaveManager::OnWaveDone_Implementation() 
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, TEXT("Wave completed"));

	// The wave is set as done.
	isWaveDone = true;
}

void AUBCWaveManager::OnEnemySpawned_Implementation(AUBCCharacter* enemy)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, TEXT("Enemy spawned."));
}

void AUBCWaveManager::OnEnemyDeath_Implementation(AUBCCharacter* enemy)
{
	anyEnemyDeath.Broadcast(enemy);
}

void AUBCWaveManager::OnAnyEnemyDeath_Implementation(AUBCCharacter* enemy)
{
	// The active enemy count is decreased.
	currentEnemyCount--;

	// If the round should end, it is ended.
	if (ShouldRoundEnd())
	{
		roundDone.Broadcast();
	}
	// Else if the spawnings were paused, they are resumed.
	else if (spawnHalted)
	{
		spawnHalted = false;
		GetWorldTimerManager().SetTimer(enemySpawnTimer, this, &AUBCWaveManager::SpawnEnemies, wave->GetRoundSpawnDelay(currentRound), true);
	}
}

bool AUBCWaveManager::ShouldRoundEnd() const
{
	// If the active enemy count is less or equal to 0 and enough enemies have been spawned.
	return currentEnemyCount <= 0 && 
		   spawnedEnemyCount >= roundEnemyCount;
}

bool AUBCWaveManager::ShouldWaveEnd() const
{
	// If the maximum amount of rounds have been reached and is not 0.
	return maxRoundCount != 0 && 
		   currentRound > maxRoundCount;
}

float AUBCWaveManager::GetRoundStartTimeRemaining() const
{
	return GetWorldTimerManager().GetTimerRemaining(roundStartTimer);
}

void AUBCWaveManager::ForceRoundDone()
{
	// The round is set as done an the timers are stopped.
	isRoundDone = true;
	GetWorldTimerManager().ClearTimer(roundUpdateTimer);
	GetWorldTimerManager().ClearTimer(enemySpawnTimer);
}

void AUBCWaveManager::ForceWaveDone()
{
	// If the round is not done, it is forced to end.
	if (!isRoundDone)
	{
		ForceRoundDone();
	}

	// The wave is ended.
	waveDone.Broadcast();
}

void AUBCWaveManager::AddSpawnPoint(FVector newSpawnPoint)
{
	enemySpawnPoints.Add(newSpawnPoint);
}

void AUBCWaveManager::AddSpawnPoints(TArray<FVector> newSpawnPoints)
{
	enemySpawnPoints.Append(newSpawnPoints);
}

float AUBCWaveManager::GetSpawnTimeRemaining() const
{
	return GetWorldTimerManager().GetTimerRemaining(enemySpawnTimer);
}

