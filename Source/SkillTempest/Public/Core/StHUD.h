// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"

#include "StHUD.generated.h"

class UMasterWidget;

UCLASS()
class SKILLTEMPEST_API AStHUD final : public AHUD
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<UMasterWidget> MasterWidgetClass;

	UPROPERTY(BlueprintReadWrite, Category = "UI")
	UMasterWidget* MasterWidget;

protected:
	virtual void BeginPlay() override;
};
