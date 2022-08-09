// Fill out your copyright notice in the Description page of Project Settings.

#include "Character/StCharacterBase.h"

#include "AbilitySystem/StAbilitySystemComponent.h"

AStCharacterBase::AStCharacterBase()
{
}

void AStCharacterBase::BeginPlay()
{
	Super::BeginPlay();
}

void AStCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AStCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

UAbilitySystemComponent* AStCharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent.Get();
}
