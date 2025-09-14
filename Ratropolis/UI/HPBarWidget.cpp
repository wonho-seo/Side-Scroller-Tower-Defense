// Fill out your copyright notice in the Description page of Project Settings.


#include "HPBarWidget.h"

#include "Components/ProgressBar.h"

void UHPBarWidget::UpdateHealthPercent(float Health, float MaxHealth) const
{
	if (HPProgressBar)
	{
		const float Percentage = (MaxHealth > 0.f) ? (Health / MaxHealth) : 0.f;
		HPProgressBar->SetPercent(Percentage);
	}
}
