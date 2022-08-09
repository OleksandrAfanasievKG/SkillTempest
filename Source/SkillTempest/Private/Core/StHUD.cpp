// Fill out your copyright notice in the Description page of Project Settings.

#include "Core/StHUD.h"

#include "Core/SkillTempest.h"
#include "Widget/MasterWidget.h"

void AStHUD::BeginPlay()
{
	Super::BeginPlay();

	checkUClassInBp(this, MasterWidgetClass);

	MasterWidget = CreateWidget<UMasterWidget>(GetOwningPlayerController(), MasterWidgetClass);
	MasterWidget->AddToViewport();
}
