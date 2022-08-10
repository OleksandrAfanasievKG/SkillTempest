// Fill out your copyright notice in the Description page of Project Settings.

#include "Core/StGameMode.h"

#include "GameFramework/GameStateBase.h"
#include "GameFramework/PlayerState.h"

void AStGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	if (!GameState || !GEngine)
		return;
	
	const int32 NumberOfPlayers = GameState.Get()->PlayerArray.Num();
	GEngine->AddOnScreenDebugMessage(
		1,
		60.0f,
		FColor::Yellow,
		FString::Printf(TEXT("Players in game: %d."), NumberOfPlayers));

	APlayerState* PlayerState = NewPlayer->GetPlayerState<APlayerState>();
	if (PlayerState)
	{
		GEngine->AddOnScreenDebugMessage(
			-1,
			60.0f,
			FColor::Cyan,
			FString::Printf(TEXT("%s has join the game!"), *PlayerState->GetPlayerName()));
	}
}

void AStGameMode::Logout(AController* Exiting)
{
	Super::Logout(Exiting);

	if (!GEngine)
		return;
	
	const int32 NumberOfPlayers = GameState.Get()->PlayerArray.Num();
	GEngine->AddOnScreenDebugMessage(
		1,
		60.0f,
		FColor::Yellow,
		FString::Printf(TEXT("Players in game: %d."), NumberOfPlayers-1));
	
	APlayerState* PlayerState = Exiting->GetPlayerState<APlayerState>();
	if (!PlayerState)
		return;
	
	GEngine->AddOnScreenDebugMessage(
		-1,
		60.0f,
		FColor::Cyan,
		FString::Printf(TEXT("%s has left the game!"), *PlayerState->GetPlayerName()));
}
