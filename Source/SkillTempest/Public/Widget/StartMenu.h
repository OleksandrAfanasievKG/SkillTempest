// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "StartMenu.generated.h"

class UButton;

UCLASS()
class SKILLTEMPEST_API UStartMenu : public UUserWidget
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable)
	void Setup(int32 NumOfPublicConnections = 4, FString TypeOfMatch = FString(TEXT("FreeForAll")), FString PathToLevel = FString(TEXT("/Game/Map/L_Level_01")));

protected:

	virtual bool Initialize() override;

	virtual void OnLevelRemovedFromWorld(ULevel* InLevel, UWorld* InWorld) override;

	UFUNCTION()
	void OnCreateSession(bool bWasSuccessful);

	void OnFindSessions(const TArray<FOnlineSessionSearchResult> & SessionResults, bool bWasSuccessful);

	void OnJoinSession(EOnJoinSessionCompleteResult::Type Result);
	
	UFUNCTION()
	void OnDestroySession(bool bWasSuccessful);
	
	UFUNCTION()
	void OnStartSession(bool bWasSuccessful);
	
private:

	UFUNCTION()
	void HostButtonClicked();
	
	UFUNCTION()
	void JoinButtonClicked();

	void Shutdown();
	
private:

	UPROPERTY(meta = (BindWidget))
	UButton * HostButton;

	UPROPERTY(meta = (BindWidget))
	UButton * JoinButton;

	UPROPERTY()
	class UMultiplayerSessionsSubsystem * MultiplayerSessionsSubsystem;

	int32   PublicConnectionsCount;
	FString MatchType;
	FString LevelPath;
};
