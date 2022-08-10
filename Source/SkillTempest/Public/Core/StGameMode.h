// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "StGameMode.generated.h"

class APlayerStart;
class AStCharacter;

UCLASS()
class SKILLTEMPEST_API AStGameMode final : public AGameMode
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<APlayerStart*> PlayerStarts;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<AStCharacter> CharacterClass;

	virtual void PostLogin(APlayerController* NewPlayer) override;
	virtual void Logout(AController* Exiting) override;

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void RespawnPlayer(AController* Controller);
};
