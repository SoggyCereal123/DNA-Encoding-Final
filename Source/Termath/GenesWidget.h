// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GenesWidget.generated.h"

/**
 * 
 */
class UGene;
class UScrollBox;
UCLASS()
class TERMATH_API UGenesWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(meta = (BindWidget))
	UScrollBox* GeneListPanel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
	TSubclassOf<UUserWidget> GeneEntryWidgetClass;

	void PopulateGeneList(TArray<UGene*>& Genome);
	
};
