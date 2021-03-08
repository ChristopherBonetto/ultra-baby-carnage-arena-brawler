// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Curves/CurveFloat.h"
#include "Engine/DataTable.h"
#include "../UBCCharacter.h"
#include "UBCWaveInfo.generated.h"

/**
 * Contains info regarding a wave of Ultra Baby Carnage.
 */

USTRUCT(Blueprintable)
struct ULTRABABYCARNAGE_API FUBCWaveInfo
{

	GENERATED_USTRUCT_BODY()

public:

	/**
	* The delay between rounds.
	*/

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float roundDelay = 5.f;

	/**
	* Value multiplied to the enemy spawn curve to decide how many enemies to spawn.
	*/

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int enemyMultiplier = 1;

	/**
	* Maximum amount of enemies that can be active at the same time.
	*/

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int maxActiveEnemiesCount = 10;

	/**
	* Curve that indicates how many enemies should be spawned per round.
	*/

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UCurveFloat* enemySpawnCurve;

	/**
	* Curve that indicates the delay between spawns of enemies.
	*/

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UCurveFloat* enemySpawnDelayCurve;

	/**
	* Curve that indicates how many enemies should be spawned at the same time per round.
	*/

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UCurveFloat* enemySpawnBatchCurve;

	/**
	* Curve that indicates how many enemies should be spawned at the same time per round.
	*/

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UCurveFloat* enemyHealthCurve;

	/**
	* Curve that indicates how many enemies should be spawned at the same time per round.
	*/

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UCurveFloat* enemyPowerCurve;

	/**
	* The base item budget of a round.
	*/

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int baseBudget = 1;

	/**
	* The minimum item budget multiplier of a round.
	*/

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int minBudgetMultiplier = 1;

	/**
	* The maximum item budget multiplier of a round.
	*/

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int maxBudgetMultiplier = 10;

	/**
	* Data table that contains the items that will be used and their cost.
	*/

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<UDataTable*> itemTierTables;

	/**
	* Curve that indicates the start index of the items that will be considered in the table.
	*/

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UCurveFloat* itemIndexOffsetCurve;

	/**
	* Curve that indicates the indeces in the item table that will be considered per round.
	*/

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UCurveFloat* maxItemIndexCurve;

	/**
	* Curve that indicates the index of the default item that will be used each round in the table.
	*/

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UCurveFloat* defaultItemIndexCurve;

	/**
	* Curve that indicates the tier table to use for each round.
	*/

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UCurveFloat* itemTierCurve;

	/**
	* Class of the enemy that will be spawned.
	*/

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AUBCCharacter> enemyToSpawn;

};
