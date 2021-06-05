
#include "UBCWaveAsset.h"

float UUBCWaveAsset::GetCurveValue(UCurveFloat* curve, int round)
{
	return curve->IsValidLowLevelFast() ?
		curve->GetFloatValue(round) :
		0.f;
}

UEvaluator* UUBCWaveAsset::GetEquation(UEvaluator*& eqInstance, const TSubclassOf<UEvaluator>& evalClass)
{
	UClass* eqClass = evalClass.Get();
	if (eqClass->IsValidLowLevelFast() && (!eqInstance || eqInstance->GetClass() != eqClass))
	{
		eqInstance = NewObject<UEvaluator>((UObject*)this, eqClass);
	}

	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, eqClass->GetName() + ": " + eqInstance->GetClass()->GetName());

	return eqInstance;
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

UEvaluator * UUBCWaveAsset::GetSpawnEquation()
{
	return GetEquation(enemySpawnEquation, info.enemySpawnEquation);
}

int UUBCWaveAsset::GetRoundSpawnCount(int round)
{
	return (int)(*GetSpawnEquation())(round);
}

UEvaluator * UUBCWaveAsset::GetMaxActiveEnemiesCountEquation()
{
	return GetEquation(maxActiveEnemyCountEquation, info.maxActiveEnemyCountEquation);
}

int UUBCWaveAsset::GetRoundMaxActiveEnemiesCount(int round)
{
	return FMath::Clamp((int)(*GetMaxActiveEnemiesCountEquation())(round), 0, info.maxActiveEnemiesCount);
}

UEvaluator * UUBCWaveAsset::GetSpawnDelayEquation()
{
	return GetEquation(enemySpawnDelayEquation, info.enemySpawnDelayEquation);
}

float UUBCWaveAsset::GetRoundSpawnDelay(int round)
{
	return (int)(*GetSpawnDelayEquation())(round);
}

UEvaluator * UUBCWaveAsset::GetSpawnBatchEquation()
{
	return GetEquation(enemySpawnBatchEquation, info.enemySpawnBatchEquation);
}

int UUBCWaveAsset::GetRoundBatchSize(int round)
{
	return (int)(*GetSpawnBatchEquation())(round);
}

UEvaluator * UUBCWaveAsset::GetHealthEquation()
{
	return GetEquation(enemyHealthEquation, info.enemyHealthEquation);
}

int UUBCWaveAsset::GetRoundHealthValue(int round)
{
	return (int)(*GetHealthEquation())(round);
}

UEvaluator * UUBCWaveAsset::GetPowerEquation()
{
	return GetEquation(enemyPowerEquation, info.enemyPowerEquation);
}

int UUBCWaveAsset::GetRoundPowerValue(int round)
{
	return (int)(*GetPowerEquation())(round);
}

UEvaluator * UUBCWaveAsset::GetSpeedEquation()
{
	return GetEquation(enemySpeedEquation, info.enemySpeedEquation);
}

int UUBCWaveAsset::GetRoundSpeedValue(int round)
{
	return (int)(*GetSpeedEquation())(round);
}

int UUBCWaveAsset::GetBaseBudget() const
{
	return info.baseBudget;
}

int UUBCWaveAsset::GetMinBudgetMultiplier() const
{
	return info.minBudgetMultiplier;
}

int UUBCWaveAsset::GetMaxBudgetMultiplier() const
{
	return info.maxBudgetMultiplier;
}

UEvaluator * UUBCWaveAsset::GetBudgetMultiplierEquation()
{
	return GetEquation(weaponBudgetMultiplierEquation, info.weaponBudgetMultiplierEquation);
}

int UUBCWaveAsset::GetRoundBudgetMultiplier(int round)
{
	return (int)(*GetBudgetMultiplierEquation())(round);
}

UCurveFloat * UUBCWaveAsset::GetTierCurve() const
{
	return info.itemTierCurve;
}

int UUBCWaveAsset::GetRoundTier(int round) const
{
	return (int)GetCurveValue(GetTierCurve(), round);
}

UDataTable * UUBCWaveAsset::GetItemCostTableOfTier(int tier) const
{
	int tierCount = info.itemTierTables.Num();
	return FMath::IsWithin(tier, 0, tierCount) ? 
		info.itemTierTables[tier] : 
		nullptr;
}

UCurveFloat * UUBCWaveAsset::GetItemIndexOffsetCurve() const
{
	return info.itemIndexOffsetCurve;
}

int UUBCWaveAsset::GetRoundItemIndexOffset(int round) const
{
	return (int)GetCurveValue(GetItemIndexOffsetCurve(), round);
}

UCurveFloat * UUBCWaveAsset::GetMaxItemIndexCurve() const
{
	return info.maxItemIndexCurve;
}

int UUBCWaveAsset::GetRoundMaxItemIndex(int round) const
{
	return (int)GetCurveValue(GetMaxItemIndexCurve(), round);
}

UCurveFloat * UUBCWaveAsset::GetDefaultItemIndexCurve() const
{
	return info.defaultItemIndexCurve;
}

int UUBCWaveAsset::GetRoundDefaultItemIndex(int round) const
{
	return GetCurveValue(GetDefaultItemIndexCurve(), round);
}

TSubclassOf<AUBCCharacter> UUBCWaveAsset::GetEnemyClass() const
{
	return info.enemyToSpawn;
}