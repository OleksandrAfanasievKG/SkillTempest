// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/Character.h"

#include "StCharacterBase.generated.h"

class UStAbilitySystemComponent;

UCLASS()
class SKILLTEMPEST_API AStCharacterBase final : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	AStCharacterBase();

protected:
	virtual void BeginPlay() override;

	UPROPERTY()
	TWeakObjectPtr<UStAbilitySystemComponent> AbilitySystemComponent;

public:
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
};
