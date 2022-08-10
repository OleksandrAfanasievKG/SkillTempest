// Fill out your copyright notice in the Description page of Project Settings.

#include "Core/StGameMode.h"

#include "Character/StCharacter.h"
#include "Core/SkillTempest.h"
#include "GameFramework/GameStateBase.h"
#include "GameFramework/PlayerStart.h"
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

void AStGameMode::BeginPlay()
{
	Super::BeginPlay();

	checkUClassInBp(this, CharacterClass);

	// bind some delegates here if needed
	// that's okay if gamemode know about other classes, because it's main class in gameplay logic
}

void AStGameMode::RespawnPlayer(AController* Controller)
{
	const APlayerStart* PlayerStart = PlayerStarts[FMath::RandHelper(PlayerStarts.Num())];

	FActorSpawnParameters SpawnParameters;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	AStCharacter* Character = GetWorld()->SpawnActor<AStCharacter>(
		CharacterClass, PlayerStart->GetActorLocation(), PlayerStart->GetActorRotation(), SpawnParameters);

	APawn* OldPawn = Controller->GetPawn();
	Controller->UnPossess();

	OldPawn->Destroy();
	Controller->Possess(Character);
}
