// Copyright (c) 2026 Absolute Mikhail


#include "ExplosionActor.h"

#include "Components/SphereComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"
#include "PhysicsEngine/RadialForceComponent.h"



AExplosionActor::AExplosionActor()
{
	PrimaryActorTick.bCanEverTick = false;
	bReplicates = true;
	
	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("My Scene"));

	RootComponent = SceneComponent;
	
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("My Static Mesh"));
	StaticMesh->SetupAttachment(RootComponent);
	StaticMesh->SetRelativeLocation(FVector(0, 0, 50));

	CollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("My Collision Sphere"));
	CollisionSphere->SetupAttachment(StaticMesh);
	CollisionSphere->SetSphereRadius(Radius);
	CollisionSphere->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
	CollisionSphere->CanCharacterStepUpOn = ECB_No;
	CollisionSphere->SetCollisionResponseToChannels(ECR_Ignore);
	CollisionSphere->SetCollisionResponseToChannel(ECC_Pawn, ECollisionResponse::ECR_Overlap);
	
	RadialForce = CreateDefaultSubobject<URadialForceComponent>(TEXT("My Radial Force"));
	RadialForce->SetupAttachment(StaticMesh);
	RadialForce->Radius = Radius;

	// в блюпринте
	//RadialForce->bImpulseVelChange(true);
	//RadialForce->ImpulseStrength(Damage * 10);
}

float AExplosionActor::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator,
	AActor* DamageCauser)
{
	if (HasAuthority() && bActive)
	{
		TArray<AActor*> OverlappingActors;
		CollisionSphere->GetOverlappingActors(OverlappingActors, ACharacter::StaticClass());

		if (OverlappingActors.Num() > 0)
		{
			for (AActor* CurrentActor : OverlappingActors) // for each
			{
				UGameplayStatics::ApplyDamage(CurrentActor, Damage, EventInstigator, DamageCauser, NULL);
			}
		}
		
		Explode();
	}
	
	return Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
}

void AExplosionActor::Explode()
{
	SetActive(false);
	GetWorld()->GetTimerManager().SetTimer(ReloadTimer, this, &AExplosionActor::Reload, 10.0f, false);
	
	ExplosionEffect_Multicast();
}

void AExplosionActor::ExplosionEffect_Multicast_Implementation()
{
	if (FxFire)
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), FxFire, GetTransform());
	}
	
	if (SoundFire)
	{
		UGameplayStatics::SpawnSoundAtLocation(GetWorld(), SoundFire, GetActorLocation());
	}

	if (RadialForce)
	{
		RadialForce->FireImpulse();
	}
}

void AExplosionActor::OnRep_Active()
{
	UpdateActiveState();
}

void AExplosionActor::Reload()
{
	SetActive(true);
}

void AExplosionActor::SetActive(bool bNewActive)
{
	bActive = bNewActive;
	UpdateActiveState();
}

void AExplosionActor::UpdateActiveState()
{
	if (StaticMesh)
	{
		StaticMesh->SetCollisionProfileName(bActive ? TEXT("BlockAllDynamic") : TEXT("NoCollision"));
		StaticMesh->SetHiddenInGame(!bActive);
	}
}

void AExplosionActor::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AExplosionActor, bActive);
}
