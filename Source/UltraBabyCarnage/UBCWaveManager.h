// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "UBCWaveAsset.h"
#include "UBCWaveManager.generated.h"

UCLASS()
class ULTRABABYCARNAGE_API AUBCWaveManager : 
	public AActor
{
	GENERATED_BODY()
	
#pragma region Delegates declarations

public:

	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FWaveStart);
	
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FRoundStart);
	
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FRoundUpdate);
	
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FRoundDone);
	
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FWaveDone);

	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FEnemySpawn);
	
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FEnemySpawned, AActor*, enemy);
	
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAnyEnemyDeath, AActor*, enemy);

#pragma endregion

#pragma region Attributes

protected:

#pragma region Protected attributes

#pragma region Wave: Round attributes

	UPROPERTY(BlueprintReadWrite, Category = "Wave: Round")
	bool isRoundDone;

	UPROPERTY(BlueprintReadWrite, Category = "Wave: Round")
	int currentRound = 1;

	UPROPERTY(BlueprintReadWrite, Category = "Wave: Round")
	FTimerHandle roundStartTimer;

	UPROPERTY(BlueprintReadWrite, Category = "Wave: Round")
	FTimerHandle roundUpdateTimer;

#pragma endregion

#pragma region Wave: Spawn attributes

	UPROPERTY(BlueprintReadWrite, Category = "Wave: Spawn")
	bool spawnHalted;

	UPROPERTY(BlueprintReadWrite, Category = "Wave: Spawn")
	int roundEnemyCount;

	UPROPERTY(BlueprintReadWrite, Category = "Wave: Spawn")
	int currentEnemyCount;

	UPROPERTY(BlueprintReadWrite, Category = "Wave: Spawn")
	int spawnedEnemyCount;

	UPROPERTY(BlueprintReadWrite, Category = "Wave: Spawn")
	int maxActiveEnemiesCount;

	UPROPERTY(BlueprintReadWrite, Category = "Wave: Spawn")
	int enemyBatchSize;

	UPROPERTY(BlueprintReadWrite, Category = "Wave: Spawn")
	FTimerHandle enemySpawnTimer;

#pragma endregion

#pragma endregion

public:

#pragma region Public attributes
	
#pragma region Wave: Spawn attributes

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Wave: Spawn")
	float spawnCutoffDistance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Wave: Spawn")
	int maxActiveEnemySpawnersCount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Wave: Spawn")
	TArray<FVector> enemySpawnPoints;

#pragma endregion

#pragma region Wave: Info attributes

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Wave: Info")
	UUBCWaveAsset* wave;

#pragma endregion

#pragma region Delegate definitions

	UPROPERTY(BlueprintAssignable)
	FWaveStart waveStart;
	
	UPROPERTY(BlueprintAssignable)
	FRoundStart roundStart;
	
	UPROPERTY(BlueprintAssignable)
	FRoundUpdate roundUpdate;
	
	UPROPERTY(BlueprintAssignable)
	FRoundDone roundDone;
	
	UPROPERTY(BlueprintAssignable)
	FWaveDone waveDone;
	
	UPROPERTY(BlueprintAssignable)
	FEnemySpawn enemySpawn;
	
	UPROPERTY(BlueprintAssignable)
	FEnemySpawned enemySpawned;
	
	UPROPERTY(BlueprintAssignable)
	FAnyEnemyDeath anyEnemyDeath;

#pragma endregion

#pragma endregion

#pragma endregion

#pragma region Constructors

public:	

	// Sets default values for this actor's properties
	AUBCWaveManager();

#pragma endregion

#pragma region Methods

protected:
	
#pragma region Protected methods

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	virtual void UpdateRound();

	UFUNCTION(BlueprintCallable)
	void StartRound();

	UFUNCTION(BlueprintCallable)
	void SpawnEnemies();
	
	UFUNCTION(BlueprintCallable)
	void SpawnEnemy();

	UFUNCTION(BlueprintCallable)
	FVector GetSpawnLocation() const;

	UFUNCTION(BlueprintCallable)
	void SortSpawnPointsByDistance();

	UFUNCTION(BlueprintCallable)
	int GetCutoffLength() const;

	UFUNCTION(BlueprintCallable)
	void AddSpawnPoints(TArray<FVector>& newSpawnPoints);
	
	UFUNCTION(BlueprintCallable)
	void AddSpawnPoint(FVector newSpawnPoint);

#pragma region Events implementations

	UFUNCTION(BlueprintNativeEvent)
	void OnWaveStart();

	UFUNCTION(BlueprintNativeEvent)
	void OnRoundStart();

	UFUNCTION(BlueprintNativeEvent)
	void OnRoundUpdate();

	UFUNCTION(BlueprintNativeEvent)
	void OnRoundDone();

	UFUNCTION(BlueprintNativeEvent)
	void OnWaveDone();

	UFUNCTION(BlueprintNativeEvent)
	void OnEnemySpawn();

	UFUNCTION(BlueprintNativeEvent)
	void OnEnemySpawned(AActor* enemy);

	UFUNCTION(BlueprintNativeEvent)
	void OnAnyEnemyDeath(AActor* enemy);

#pragma endregion

#pragma endregion

public:	

#pragma region Public methods

	/**
	* Returns whether the round should end.
	*/

	UFUNCTION(BlueprintCallable)
	bool IsRoundDone() const;

#pragma endregion

#pragma endregion

};
