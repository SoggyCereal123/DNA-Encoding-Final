// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/ScrollBox.h"
#include "Gene.h"
#include "GenesWidget.h"

void UGenesWidget::PopulateGeneList(TArray<UGene*>& Genome)
{
	if (!GeneListPanel || !GeneEntryWidgetClass) return;

	GeneListPanel->ClearChildren();

	for (int32 i = 0; i < Genome.Num(); ++i)
	{
		UGene* Gene = Genome[i];
		if (!IsValid(Gene)) continue;

		UUserWidget* GeneWidget = CreateWidget<UUserWidget>(this, GeneEntryWidgetClass);
		if (!GeneWidget) continue;
		
		GeneListPanel->AddChild(GeneWidget);
	}
}
