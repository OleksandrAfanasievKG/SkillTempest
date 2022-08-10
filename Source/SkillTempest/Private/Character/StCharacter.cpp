// Fill out your copyright notice in the Description page of Project Settings.

#include "Character/StCharacter.h"

#include "AbilitySystem/StAbilitySystemComponent.h"

AStCharacter::AStCharacter()
{
}

UAbilitySystemComponent* AStCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent.Get();
}
