// Fill out your copyright notice in the Description page of Project Settings.

#include "Player/StPlayerState.h"

#include "AbilitySystem/StAbilitySystemComponent.h"

AStPlayerState::AStPlayerState()
{
}

void AStPlayerState::BeginPlay()
{
	Super::BeginPlay();
}

UAbilitySystemComponent* AStPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}
