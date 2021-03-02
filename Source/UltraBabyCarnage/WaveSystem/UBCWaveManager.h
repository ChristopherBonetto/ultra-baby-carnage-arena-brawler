
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../UBCCharacter.h"
#include "../Items/UBCItemBase.h"
#include "UBCWaveAsset.h"
#include "UBCWaveManager.generated.h"

/**
* Manages a wave of Ultra Baby Carnage.
*/

UCLASS()
class ULTRABABYCARNAGE_API AUBCWaveManager : 
	public AActor
{
	GENERATED_BODY()
	
#pragma region Delegates declarations

public:

	// Delegate used when the wave starts.

	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FWaveStart);

	// Delegate used when the round starts.
	
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FRoundStart);

	// Delegate used when the round updates.

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FRoundUpdate, float, deltaTime);

	// Delegate used when the round ends.

	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FRoundDone);

	// Delegate used when the wave ends.

	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FWaveDone);

	// Delegate used when the an enemy has been spawned.

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FEnemySpawned, AUBCCharacter*, enemy);

	// Delegate used when any one of the spawned enemies dies.

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAnyEnemyDeath, AUBCCharacter*, enemy);

#pragma endregion

#pragma region Attributes

protected:

#pragma region Protected attributes

#pragma region Wave: Round attributes

	/**
	* Indicates whether the round is finished.
	*/

	UPROPERTY(BlueprintReadWrite, Category = "Wave: Round")
	bool isRoundDone;

	/**
	* Indicates whether the wave is finished.
	*/

	UPROPERTY(BlueprintReadWrite, Category = "Wave: Round")
	bool isWaveDone;

	/**
	* The current round of the wave.
	*/

	UPROPERTY(BlueprintReadWrite, Category = "Wave: Round")
	int currentRound = 1;

	/**
	* The timer that handles the start of the next round.
	*/

	UPROPERTY(BlueprintReadWrite, Category = "Wave: Round")
	FTimerHandle roundStartTimer;

	/**
	* The timer that ticks the update of the round.
	*/

	UPROPERTY(BlueprintReadWrite, Category = "Wave: Round")
	FTimerHandle roundUpdateTimer;

#pragma endregion

#pragma region Wave: Spawn attributes

	/**
	* Indicates whether the spawning of enemies has been paused.
	*/

	UPROPERTY(BlueprintReadWrite, Category = "Wave: Spawn")
	bool spawnHalted;

	/**
	* The count of enemies that should be spawned this round.
	*/

	UPROPERTY(BlueprintReadWrite, Category = "Wave: Spawn")
	int roundEnemyCount;

	/**
	* The count of currently active spawned enemies.
	*/

	UPROPERTY(BlueprintReadWrite, Category = "Wave: Spawn")
	int currentEnemyCount;

	/**
	* The total count of enemies spawned this round.
	*/

	UPROPERTY(BlueprintReadWrite, Category = "Wave: Spawn")
	int spawnedEnemyCount;

	/**
	* The maximum number of enemies that can be active at the same time.
	*/

	UPROPERTY(BlueprintReadWrite, Category = "Wave: Spawn")
	int maxActiveEnemiesCount;

	/**
	* The number of enemies that will be spawned at the same time.
	*/

	UPROPERTY(BlueprintReadWrite, Category = "Wave: Spawn")
	int enemyBatchSize;

	/**
	* The item budget of the round.
	*/

	UPROPERTY(BlueprintReadWrite, Category = "Wave: Spawn")
	int roundBudget;

	/**
	* The current budget multiplier.
	*/

	UPROPERTY(BlueprintReadWrite, Category = "Wave: Spawn")
	int roundBudgetMultiplier;

	/**
	* Items that will be used this round.
	*/

	//UPROPERTY(BlueprintReadWrite, Category = "Wave: Spawn")
	TArray<TPair<TSubclassOf<AUBCItemBase>, int>> roundItems;

	UPROPERTY(BlueprintReadWrite, Category = "Wave: Spawn")
	TSubclassOf<AUBCItemBase> defaultItemClass;

	/**
	* The timer that handles spawnings.
	*/

	UPROPERTY(BlueprintReadWrite, Category = "Wave: Spawn")
	FTimerHandle enemySpawnTimer;

#pragma endregion

#pragma endregion

public:

#pragma region Public attributes
	
#pragma region Wave: Round attributes

	/**
	* Maximum number of rounds (0 = endless).
	*/

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Wave: Round")
	int maxRoundCount;

#pragma endregion

#pragma region Wave: Spawn attributes

	/**
	* The maximum distance at which a spawner can be before being forced disabled.
	*/

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Wave: Spawn")
	float spawnCutoffDistance;

	/**
	* The maximum number of spawners that can be active at the same time.
	*/

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Wave: Spawn")
	int maxActiveSpawnPoints;

	/**
	* The positions of the spawners.
	*/

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Wave: Spawn", Meta = (MakeEditWidget = true))
	TArray<FVector> enemySpawnPoints;

#pragma endregion

#pragma region Wave: Info attributes

	/**
	* The asset on which the manager will base to progress the wave.
	*/

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Wave: Info")
	UUBCWaveAsset* wave;

#pragma endregion

#pragma region Delegate definitions

	/**
	* Invoked when the wave starts.
	*/

	UPROPERTY(BlueprintCallable, BlueprintAssignable, Category = "Wave: Round")
	FWaveStart waveStart;

	/**
	* Invoked when the round starts.
	*/

	UPROPERTY(BlueprintCallable, BlueprintAssignable, Category = "Wave: Round")
	FRoundStart roundStart;

	/**
	* Invoked when the round should be updated.
	*/

	UPROPERTY(BlueprintCallable, BlueprintAssignable, Category = "Wave: Round")
	FRoundUpdate roundUpdate;

	/**
	* Invoked when the round ends.
	*/

	UPROPERTY(BlueprintCallable, BlueprintAssignable, Category = "Wave: Round")
	FRoundDone roundDone;

	/**
	* Invoked when the wave ends.
	*/

	UPROPERTY(BlueprintCallable, BlueprintAssignable, Category = "Wave: Round")
	FWaveDone waveDone;

	/**
	* Invoked when an enemy has been spawned.
	*/

	UPROPERTY(BlueprintCallable, BlueprintAssignable, Category = "Wave: Spawn")
	FEnemySpawned enemySpawned;

	/**
	* Invoked when any of the spawned enemies dies.
	*/

	UPROPERTY(BlueprintCallable, BlueprintAssignable, Category = "Wave: Spawn")
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

	virtual void BeginPlay() override;

	/**
	* Updates the current round.
	*/

	UFUNCTION(BlueprintCallable, Category = "Wave: Round")
	virtual void UpdateRound();

	/**
	* Starts a round.
	*/

	UFUNCTION(BlueprintCallable, Category = "Wave: Round")
	void StartRound();
	
	/**
	* Returns the item that the newly spawned enemy should equip.
	*/

	UFUNCTION(BlueprintCallable, Category = "Wave: Spawn")
	AUBCItemBase* GetItemToEquip();
	
	/**
	* Spawns an enemy to any of the spawner.
	*/

	UFUNCTION(BlueprintCallable, Category = "Wave: Spawn")
	void SpawnEnemy();

	/**
	* Spawns a batch of enemies.
	*/

	UFUNCTION(BlueprintCallable, Category = "Wave: Spawn")
	void SpawnEnemies();

	/**
	* Retrieves a spawn location for an enemy. 
	* The location will be one of the n (n = maxActiveSpawnPoints) nearest to the player and that respects the cutoff distance.
	*/

	UFUNCTION(BlueprintCallable, Category = "Wave: Spawn")
	FVector GetSpawnLocation() const;

	/**
	* Sorts the spawn points by distance from the player.
	*/

	UFUNCTION(BlueprintCallable, Category = "Wave: Spawn")
	void SortSpawnPointsByDistance();

	/**
	* Returns the count of spawners that respect the cutoff distance (spawn points MUST be ordered).
	*/

	UFUNCTION(BlueprintCallable, Category = "Wave: Spawn")
	int GetCutoffLength() const;

	void CreateRoundItemList();

#pragma region Events implementations

	/**
	* Called when the wave starts.
	*/

	UFUNCTION(BlueprintNativeEvent, Category = "Wave: Round")
	void OnWaveStart();

	/**
	* Called when the round starts.
	*/

	UFUNCTION(BlueprintNativeEvent, Category = "Wave: Round")
	void OnRoundStart();

	/**
	* Called when the round updates.
	*/

	UFUNCTION(BlueprintNativeEvent, Category = "Wave: Round")
	void OnRoundUpdate(float deltaTime);

	/**
	* Called when the round ends.
	*/

	UFUNCTION(BlueprintNativeEvent, Category = "Wave: Round")
	void OnRoundDone();

	/**
	* Called when the wave ends.
	*/

	UFUNCTION(BlueprintNativeEvent, Category = "Wave: Round")
	void OnWaveDone();

	/**
	* Called when an enemy is spawned.
	*/

	UFUNCTION(BlueprintNativeEvent, Category = "Wave: Spawn")
	void OnEnemySpawned(AUBCCharacter* enemy);

	/**
	* Called when a spawned enemy dies.
	*/

	UFUNCTION(BlueprintNativeEvent, Category = "Wave: Spawn")
	void OnEnemyDeath(AUBCCharacter* enemy);

	/**
	* Called when any of the spawned enemies die.
	*/

	UFUNCTION(BlueprintNativeEvent, Category = "Wave: Spawn")
	void OnAnyEnemyDeath(AUBCCharacter* enemy);

#pragma endregion

#pragma endregion

public:	

#pragma region Public methods

	/**
	* Returns whether the round should end.
	*/

	UFUNCTION(BlueprintCallable, Category = "Wave: Round")
	bool ShouldRoundEnd() const;

	/**
	* Returns whether the wave should end.
	*/

	UFUNCTION(BlueprintCallable, Category = "Wave: Round")
	bool ShouldWaveEnd() const;

	/**
	* Returns the amount of time in seconds that remains before the next round is started.
	*/

	UFUNCTION(BlueprintCallable, Category = "Wave: Round")
	float GetRoundStartTimeRemaining() const;

	/**
	* Forces the round to end.
	*/

	UFUNCTION(BlueprintCallable, Category = "Wave: Round")
	void ForceRoundDone();

	/**
	* Forces the wave to end.
	*/

	UFUNCTION(BlueprintCallable, Category = "Wave: Round")
	void ForceWaveDone();

	/**
	* Adds a single spawn point to the spawn points of the wave.
	*/

	UFUNCTION(BlueprintCallable, Category = "Wave: Spawn")
	void AddSpawnPoint(FVector newSpawnPoint);

	/**
	* Adds an array of spawn points to the spawn points of the wave.
	*/

	UFUNCTION(BlueprintCallable, Category = "Wave: Spawn")
	void AddSpawnPoints(TArray<FVector> newSpawnPoints);

	/**
	* Returns the amount of time in seconds that remains before the next batch of enemies is spawned.
	*/

	UFUNCTION(BlueprintCallable, Category = "Wave: Spawn")
	float GetSpawnTimeRemaining() const;

#pragma endregion

#pragma endregion

};
