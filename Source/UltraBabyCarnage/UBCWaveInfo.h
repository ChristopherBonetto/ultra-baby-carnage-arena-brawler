// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Curves/CurveFloat.h"
#include "UBCCharacter.h"
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
	float roundDelay;

	/**
	* Value multiplied to the enemy spawn curve to decide how many enemies to spawn.
	*/

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int enemyMultiplier;

	/**
	* Maximum amount of enemies that can be active at the same time.
	*/

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int maxActiveEnemiesCount;

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
	* Class of the enemy that will be spawned.
	*/

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AUBCCharacter> enemyToSpawn;

};
