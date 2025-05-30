// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePair.h"

UBasePair::UBasePair()
{
	BasePairTypes = {TEXT("A"), TEXT("T"), TEXT("C"), TEXT("G")};
	Value = FMath::RandRange(0.3f, 0.9f);
	bMultiply = false;
	bDivide = false;
	bIsExempt = false;
}
