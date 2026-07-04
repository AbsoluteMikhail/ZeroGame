// Copyright (c) 2026 Absolute Mikhail

#include "ZeroGameInstance.h"

#include "Engine/Engine.h"
#include "GameFramework/GameUserSettings.h"


UZeroGameInstance::UZeroGameInstance(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{	

}

void UZeroGameInstance::Init()
{
	Super::Init();

	// Пример настройки и ограничение FPS через консольную команду
	if (UGameUserSettings* GameUserSettings = UGameUserSettings::GetGameUserSettings())
	{
		GameUserSettings->SetVSyncEnabled(true);
		//GameUserSettings->SetFullscreenMode(EWindowMode::WindowedFullscreen);
		GameUserSettings->ApplySettings(true);
		GameUserSettings->SaveSettings();
	}

	if (GEngine)
	{
		GEngine->Exec(GetWorld(), TEXT("t.MaxFPS 60"));
	}
}
