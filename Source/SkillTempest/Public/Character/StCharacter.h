// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/Character.h"

#include "StCharacter.generated.h"

class UStAbilitySystemComponent;

UCLASS()
class SKILLTEMPEST_API AStCharacter final : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	AStCharacter();

protected:
	UPROPERTY()
	TWeakObjectPtr<UStAbilitySystemComponent> AbilitySystemComponent;

public:
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
};
