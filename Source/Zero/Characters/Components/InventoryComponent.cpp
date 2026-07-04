// Copyright (c) 2026 Absolute Mikhail

#include "InventoryComponent.h"

#include "Components/SceneComponent.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "Net/UnrealNetwork.h"


UInventoryComponent::UInventoryComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	SetIsReplicatedByDefault(true);
}

void UInventoryComponent::InitWeapon_OnServer_Implementation(USkeletalMeshComponent* FP_Mesh, USkeletalMeshComponent* TP_Mesh)
{
	AActor* OwnerActor = GetOwner();
	UWorld* World = GetWorld();
	if (!OwnerActor || !World)
	{
		return;
	}

	if (CurrentWeapon)
	{
		CurrentWeapon->Destroy();
		CurrentWeapon = nullptr;
	}
	
	if (SpawnWeaponClass)
	{
		PlayerFP_Mesh = FP_Mesh;
		PlayerTP_Mesh = TP_Mesh;
			
		CurrentWeapon = World->SpawnActor<AWeaponBase>(SpawnWeaponClass, FTransform::Identity);
		if (!CurrentWeapon)
		{
			return;
		}

		CurrentWeapon->SetOwner(OwnerActor);
		if (USceneComponent* OwnerRoot = OwnerActor->GetRootComponent())
		{
			CurrentWeapon->AttachToComponent(OwnerRoot, FAttachmentTransformRules::KeepRelativeTransform, NAME_None);
		}
		CurrentWeapon->AttachMeshes_OnServer(PlayerFP_Mesh, PlayerTP_Mesh);
	}
}

void UInventoryComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (CurrentWeapon)
	{
		CurrentWeapon->Destroy();
		CurrentWeapon = nullptr;
	}

	Super::EndPlay(EndPlayReason);
}

void UInventoryComponent::SetNewWeapon_OnServer_Implementation(TSubclassOf<AWeaponBase> NewWeapon)
{
	SpawnWeaponClass = NewWeapon;
	InitWeapon_OnServer(PlayerFP_Mesh, PlayerTP_Mesh);
}

void UInventoryComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UInventoryComponent, CurrentWeapon);
}
