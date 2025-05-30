// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/TextBlock.h"
#include "GeneEntryWidget.h"

void UGeneEntryWidget::SetGeneText(const FText& Text)
{
	if (GeneInfoText)
	{
		GeneInfoText->SetText(Text);
	}
}
