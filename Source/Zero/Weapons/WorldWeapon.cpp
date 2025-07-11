﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "WorldWeapon.h"

#include "Components/BoxComponent.h"
#include "GameFramework/RotatingMovementComponent.h"
#include "Characters/ZeroCharacter.h"
#include "Characters/Components/InventoryComponent.h"



AWorldWeapon::AWorldWeapon()
{
	PrimaryActorTick.bCanEverTick = false;
	bReplicates = true;
	
	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("My Scene"));

	RootComponent = SceneComponent;
	
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("My Static Mesh"));
	StaticMesh->SetupAttachment(RootComponent);
	StaticMesh->SetRelativeLocation(FVector(0, -10, 50));

	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("My Collision Box"));
	CollisionBox->SetupAttachment(StaticMesh);
	CollisionBox->SetRelativeLocation(FVector(0, 10, 0));
	CollisionBox->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
	CollisionBox->CanCharacterStepUpOn = ECB_No;
	CollisionBox->SetCollisionResponseToChannels(ECR_Ignore);
	CollisionBox->SetCollisionResponseToChannel(ECC_Pawn, ECollisionResponse::ECR_Overlap);
	
	MovementComponent = CreateDefaultSubobject<URotatingMovementComponent>(TEXT("My Movement Component"));
}

void AWorldWeapon::BeginPlay()
{
	Super::BeginPlay();

	if (!SpawnWeaponClass)
	{
		this->Destroy();
	}
}

void AWorldWeapon::NotifyActorBeginOverlap(AActor* OtherActor)
{
	if (HasAuthority() && bActive)
	{
		SetNewWeapon_OnServer(OtherActor);
	}
	
	Super::NotifyActorBeginOverlap(OtherActor);
}

void AWorldWeapon::NotifyActorEndOverlap(AActor* OtherActor)
{
	Super::NotifyActorEndOverlap(OtherActor);
}

void AWorldWeapon::SetNewWeapon_OnServer_Implementation(AActor* OtherActor)
{
	if (const auto OtherChar = Cast<AZeroCharacter>(OtherActor))
	{
		if (const auto Inventory = Cast<UInventoryComponent>(OtherChar->GetComponentByClass(UInventoryComponent::StaticClass())))
		{
			Inventory->SetNewWeapon_OnServer(SpawnWeaponClass);

			bActive = false;
			Hide_Multicast();

			GetWorld()->GetTimerManager().SetTimer(ReloadTimer, this, &AWorldWeapon::Reload_Multicast, 60.0f, false);
		}
	}
}

void AWorldWeapon::Hide_Multicast_Implementation()
{
	if (StaticMesh)
	{
		StaticMesh->SetHiddenInGame(true);	
	}
}

void AWorldWeapon::Reload_Multicast_Implementation()
{
	bActive = true;
	if (StaticMesh)
	{
		StaticMesh->SetHiddenInGame(false);	
	}
}
