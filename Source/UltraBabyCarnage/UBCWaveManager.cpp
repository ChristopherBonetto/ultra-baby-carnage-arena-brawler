
#include "UBCWaveManager.h"

// Sets default values
AUBCWaveManager::AUBCWaveManager()
{
	waveStart.AddDynamic(this, &AUBCWaveManager::OnWaveStart);
	roundStart.AddDynamic(this, &AUBCWaveManager::OnRoundStart);
	roundUpdate.AddDynamic(this, &AUBCWaveManager::OnRoundUpdate);
	roundDone.AddDynamic(this, &AUBCWaveManager::OnRoundDone);
	waveDone.AddDynamic(this, &AUBCWaveManager::OnWaveDone);
	enemySpawn.AddDynamic(this, &AUBCWaveManager::OnEnemySpawn);
	enemySpawned.AddDynamic(this, &AUBCWaveManager::OnEnemySpawned);
	anyEnemyDeath.AddDynamic(this, &AUBCWaveManager::OnAnyEnemyDeath);
}

void AUBCWaveManager::BeginPlay()
{
	waveStart.Broadcast();
}

void AUBCWaveManager::UpdateRound()
{
	roundUpdate.Broadcast();
}

void AUBCWaveManager::StartRound()
{
	roundStart.Broadcast();
}

void AUBCWaveManager::SpawnEnemies()
{
	enemySpawn.Broadcast();
}

void AUBCWaveManager::SpawnEnemy()
{
	SortSpawnPointsByDistance();

	FTransform transform(FRotator::ZeroRotator, GetSpawnLocation());

	FActorSpawnParameters spawnParams;
	spawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
	
	AActor* enemy = GetWorld()->SpawnActor(*wave->GetEnemyClass(), &transform, spawnParams);

	currentEnemyCount++;
	spawnedEnemyCount++;
}

FVector AUBCWaveManager::GetSpawnLocation() const
{
	int size = FMath::Min(GetCutoffLength(), FMath::Min(maxActiveEnemySpawnersCount, enemySpawnPoints.Num()));
	return enemySpawnPoints[FMath::RandRange(0, size - 1)];
}

void AUBCWaveManager::SortSpawnPointsByDistance()
{
	FVector playerPosition = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation();

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
	FVector playerPosition = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation();

	int size = enemySpawnPoints.Num();

	for (int i = 0; i < size; i++)
	{
		if (FVector::Distance(enemySpawnPoints[i], playerPosition) > spawnCutoffDistance)
		{
			return i;
		}
	}

	return size;
}

void AUBCWaveManager::AddSpawnPoints(TArray<FVector>& newSpawnPoints)
{
	enemySpawnPoints.Append(newSpawnPoints);
}

void AUBCWaveManager::AddSpawnPoint(FVector newSpawnPoint)
{
	enemySpawnPoints.Add(newSpawnPoint);
}

void AUBCWaveManager::OnWaveStart_Implementation() 
{
	maxActiveEnemiesCount = wave->GetMaxActiveEnemiesCount();
	roundStart.Broadcast();
}

void AUBCWaveManager::OnRoundStart_Implementation() 
{
	isRoundDone = spawnHalted = false;

	roundEnemyCount = wave->GetRoundSpawnCount(currentRound) * wave->GetEnemyMultiplier();

	if (roundEnemyCount > 0)
	{
		currentEnemyCount = spawnedEnemyCount = 0;
		enemyBatchSize = wave->GetRoundBatchSize(currentRound);
		GetWorldTimerManager().SetTimer(enemySpawnTimer, this, &AUBCWaveManager::SpawnEnemies, wave->GetRoundSpawnDelay(currentRound), true);
		GetWorldTimerManager().SetTimer(roundUpdateTimer, this, &AUBCWaveManager::UpdateRound, 0.f, true);
	}
}

void AUBCWaveManager::OnRoundUpdate_Implementation()
{
}

void AUBCWaveManager::OnRoundDone_Implementation() 
{
	isRoundDone = true;
	currentRound++;
	GetWorldTimerManager().ClearTimer(roundUpdateTimer);
	GetWorldTimerManager().SetTimer(roundStartTimer, this, &AUBCWaveManager::StartRound, wave->GetRoundDelay(), false);
}

void AUBCWaveManager::OnWaveDone_Implementation() 
{
}

void AUBCWaveManager::OnEnemySpawn_Implementation() 
{
	for (int i = 1; i < enemyBatchSize; i++)
	{
		SpawnEnemy();

		if (spawnedEnemyCount >= roundEnemyCount)
		{
			if (currentEnemyCount >= maxActiveEnemiesCount)
			{
				spawnHalted = true;
			}
			
			GetWorldTimerManager().ClearTimer(enemySpawnTimer);
			break;
		}
	}
}

void AUBCWaveManager::OnEnemySpawned_Implementation(AActor* enemy) 
{
}

void AUBCWaveManager::OnAnyEnemyDeath_Implementation(AActor* enemy) 
{
	if (--currentEnemyCount <= 0 && spawnedEnemyCount >= roundEnemyCount)
	{
		roundDone.Broadcast();
	}
	else if (spawnHalted)
	{
		spawnHalted = false;
		GetWorldTimerManager().SetTimer(enemySpawnTimer, this, &AUBCWaveManager::SpawnEnemies, wave->GetRoundSpawnDelay(currentRound), true);
	}
}

bool AUBCWaveManager::IsRoundDone() const
{
	return isRoundDone;
}