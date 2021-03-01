
#include "UBCWaveAsset.h"

float UUBCWaveAsset::GetCurveValue(UCurveFloat* curve, int round)
{
	return curve->IsValidLowLevelFast() ?
		curve->GetFloatValue(round) :
		0.f;
}

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
	return (int)GetCurveValue(GetSpawnCurve(), round);
}

UCurveFloat* UUBCWaveAsset::GetSpawnDelayCurve() const
{
	return info.enemySpawnDelayCurve;
}

float UUBCWaveAsset::GetRoundSpawnDelay(int round) const
{
	return GetCurveValue(GetSpawnDelayCurve(), round);
}

UCurveFloat* UUBCWaveAsset::GetSpawnBatchCurve() const
{
	return info.enemySpawnBatchCurve;
}

int UUBCWaveAsset::GetRoundBatchSize(int round) const
{
	return GetCurveValue(GetSpawnBatchCurve(), round);
}

UCurveFloat* UUBCWaveAsset::GetHealthCurve() const
{
	return info.enemyHealthCurve;
}

int UUBCWaveAsset::GetRoundHealthValue(int round) const
{
	return GetCurveValue(GetHealthCurve(), round);
}

UCurveFloat* UUBCWaveAsset::GetPowerCurve() const
{
	return info.enemyPowerCurve;
}

int UUBCWaveAsset::GetRoundPowerValue(int round) const
{
	return GetCurveValue(GetPowerCurve(), round);
}

TSubclassOf<AUBCCharacter> UUBCWaveAsset::GetEnemyClass() const
{
	return info.enemyToSpawn;
}