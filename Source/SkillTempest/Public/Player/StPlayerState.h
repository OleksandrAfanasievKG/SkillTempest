// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/PlayerState.h"

#include "StPlayerState.generated.h"

class UStAbilitySystemComponent;

UCLASS()
class SKILLTEMPEST_API AStPlayerState final : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	AStPlayerState();

protected:
	virtual void BeginPlay() override;

	UPROPERTY()
	UStAbilitySystemComponent* AbilitySystemComponent;

public:
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
};
