// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/StartMenu.h"

#include <fstream>

#include "OnlineSubsystem.h"
#include "Components/Button.h"
#include "MultiplayerSystem/MultiplayerSessionsSubsystem.h"

void UStartMenu::Setup(int32 NumOfPublicConnections, FString TypeOfMatch, FString PathToLevel)
{
	PublicConnectionsCount = NumOfPublicConnections;
	MatchType              = TypeOfMatch;
	LevelPath              = FString::Printf(TEXT("%s?listen"), *PathToLevel);

	AddToViewport();

	SetVisibility(ESlateVisibility::Visible);

	bIsFocusable = true;

	UWorld * World = GetWorld();

	if (!World)
		return;

	APlayerController * PlayerController = World->GetFirstPlayerController();

	if (!PlayerController)
		return;

	FInputModeUIOnly InputModeData;
	InputModeData.SetWidgetToFocus(TakeWidget());
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	PlayerController->SetInputMode(InputModeData);
	PlayerController->SetShowMouseCursor(true);

	UGameInstance * GameInstance = GetGameInstance();
	if (!GameInstance)
		return;
	
	MultiplayerSessionsSubsystem = GameInstance->GetSubsystem<UMultiplayerSessionsSubsystem>();

	if (!MultiplayerSessionsSubsystem)
		return;

	MultiplayerSessionsSubsystem->MultiplayerOnCreateSessionComplete.AddDynamic(this,  &ThisClass::UStartMenu::OnCreateSession);
	MultiplayerSessionsSubsystem->MultiplayerOnFindSessionComplete.AddUObject(this,    &ThisClass::OnFindSessions);
	MultiplayerSessionsSubsystem->MultiplayerOnJoinSessionComplete.AddUObject(this,    &ThisClass::OnJoinSession);
	MultiplayerSessionsSubsystem->MultiplayerOnDestroySessionComplete.AddDynamic(this, &ThisClass::OnDestroySession);
	MultiplayerSessionsSubsystem->MultiplayerOnStartSessionComplete.AddDynamic(this,   &ThisClass::OnStartSession);
}

bool UStartMenu::Initialize()
{
	if (!Super::Initialize())
		return false;

	HostButton->OnClicked.AddDynamic(this, &ThisClass::HostButtonClicked);
	JoinButton->OnClicked.AddDynamic(this, &ThisClass::JoinButtonClicked);

	return true;
}

void UStartMenu::OnLevelRemovedFromWorld(ULevel* InLevel, UWorld* InWorld)
{
	Shutdown();

	Super::OnLevelRemovedFromWorld(InLevel, InWorld);
}

void UStartMenu::OnCreateSession(bool bWasSuccessful)
{
	if(!bWasSuccessful)
	{
		HostButton->SetIsEnabled(true);

		GEngine->AddOnScreenDebugMessage(
				-1,
				15.f,
				FColor::Red,
				FString(TEXT("Failied to create session!")));
		
		return;
	}
	
	UWorld * World = GetWorld();

	if (World)
		World->ServerTravel(LevelPath);
}

void UStartMenu::OnFindSessions(const TArray<FOnlineSessionSearchResult> & SessionResults, bool bWasSuccessful)
{
	if (!bWasSuccessful)
		JoinButton->SetIsEnabled(true);
	
	if (!MultiplayerSessionsSubsystem)
		return;
	
	for (auto Result : SessionResults)
	{
		FString SettingsValue;
		Result.Session.SessionSettings.Get(FName("MatchType"), SettingsValue);
		
		if (SettingsValue != MatchType)
			continue;

		MultiplayerSessionsSubsystem->JoinSession(Result);
		return;
	}
}

void UStartMenu::OnJoinSession(EOnJoinSessionCompleteResult::Type Result)
{
	if (Result != EOnJoinSessionCompleteResult::Success)
		JoinButton->SetIsEnabled(true);
	
	IOnlineSubsystem * OnlineSubsystem = IOnlineSubsystem::Get();

	if (!OnlineSubsystem)
		return;
	
	IOnlineSessionPtr SessionInterface = OnlineSubsystem->GetSessionInterface();

	if (!SessionInterface.IsValid())
		return;

	FString Address;
	if (SessionInterface->GetResolvedConnectString(NAME_GameSession, Address))
	{
		APlayerController * PlayerController = GetGameInstance()->GetFirstLocalPlayerController();
		if (PlayerController)
			PlayerController->ClientTravel(Address, ETravelType::TRAVEL_Absolute);
	}
}

void UStartMenu::OnDestroySession(bool bWasSuccessful)
{
}

void UStartMenu::OnStartSession(bool bWasSuccessful)
{
}

void UStartMenu::HostButtonClicked()
{
	HostButton->SetIsEnabled(false);
	
	if (!MultiplayerSessionsSubsystem)
		return;

	MultiplayerSessionsSubsystem->CreateSession(PublicConnectionsCount, MatchType);
}

void UStartMenu::JoinButtonClicked()
{
	JoinButton->SetIsEnabled(false);

	if (!MultiplayerSessionsSubsystem)
		return;

	MultiplayerSessionsSubsystem->FindSessions(10000);
}

void UStartMenu::Shutdown()
{
	RemoveFromParent();
	
	UWorld * World = GetWorld();

	if (!World)
		return;

	APlayerController * PlayerController = World->GetFirstPlayerController();

	if (!PlayerController)
		return;
	
	FInputModeGameOnly InputModeData;
	PlayerController->SetInputMode(InputModeData);
	PlayerController->SetShowMouseCursor(false); 
}
