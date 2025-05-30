// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GeneEntryWidget.generated.h"

/**
 * 
 */
class UTextBlock;
UCLASS()
class TERMATH_API UGeneEntryWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void SetGeneText(const FText& Text);

protected:
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* GeneInfoText;
	
};
