// Copyright (c) 2026 Absolute Mikhail

#include "HealthComponent.h"

#include "Net/UnrealNetwork.h"


UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	SetIsReplicatedByDefault(true);
}

void UHealthComponent::ChangeHealthValue_OnServer_Implementation(float ChangeValue)
{
	ApplyHealthChange(ChangeValue);
}

void UHealthComponent::ApplyHealthChange(float ChangeValue)
{
	if (bAliveStatus)
	{
		Health = FMath::Clamp(Health + ChangeValue, 0.0f, 100.0f);

		// Логирование https://www.chrismccole.com/blog/logging-in-ue4-cpp
		//GEngine->AddOnScreenDebugMessage(INDEX_NONE, 999.f, FColor::Red, FString::Printf(TEXT("Health %f"), ChangeValue));
		
		OnHealthChange.Broadcast(Health, ChangeValue);

		if (Health <= 0.0f)
		{
			bAliveStatus = false;
			OnDead.Broadcast();
		}
	}
}

void UHealthComponent::OnRep_Health(float OldHealth)
{
	OnHealthChange.Broadcast(Health, Health - OldHealth);
}

void UHealthComponent::OnRep_AliveStatus(bool bOldAliveStatus)
{
	if (bOldAliveStatus && !bAliveStatus)
	{
		OnDead.Broadcast();
	}
}

void UHealthComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UHealthComponent, Health);
	DOREPLIFETIME(UHealthComponent, bAliveStatus);
}
