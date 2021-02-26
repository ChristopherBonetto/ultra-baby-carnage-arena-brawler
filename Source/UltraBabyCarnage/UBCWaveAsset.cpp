// Fill out your copyright notice in the Description page of Project Settings.


#include "UBCWaveAsset.h"

float UUBCWaveAsset::GetRoundDelay() const
{
	return info.roundDelay;
}

int UUBCWaveAsset::GetEnemyMultiplier() const
{
	return info.enemyMultiplier;
}

int UUBCWaveAsset::GetMaxActiveEnemiesCount() const
{
	return info.maxActiveEnemiesCount;
}

UCurveFloat* UUBCWaveAsset::GetSpawnCurve() const
{
	return info.enemySpawnCurve;
}

int UUBCWaveAsset::GetRoundSpawnCount(int round) const
{
	return (int)GetSpawnCurve()->GetFloatValue(round);
}

UCurveFloat* UUBCWaveAsset::GetSpawnDelayCurve() const
{
	return info.enemySpawnDelayCurve;
}

float UUBCWaveAsset::GetRoundSpawnDelay(int round) const
{
	return (int)GetSpawnDelayCurve()->GetFloatValue(round);
}

UCurveFloat* UUBCWaveAsset::GetSpawnBatchCurve() const
{
	return info.enemySpawnBatchCurve;
}

int UUBCWaveAsset::GetRoundBatchSize(int round) const
{
	return (int)GetSpawnBatchCurve()->GetFloatValue(round);
}

TSubclassOf<AActor> UUBCWaveAsset::GetEnemyClass() const
{
	return info.enemyToSpawn;
}