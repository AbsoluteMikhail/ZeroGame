// Copyright (c) 2026 Absolute Mikhail

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "ExplosionActor.generated.h"

class USceneComponent;
class UStaticMeshComponent;
class USphereComponent;
class URadialForceComponent;


UCLASS()
class ZERO_API AExplosionActor : public AActor
{
	GENERATED_BODY()
	
private:
	UPROPERTY(EditDefaultsOnly, Category = Components, meta = (AllowPrivateAccess = "true"))
	USceneComponent* SceneComponent = nullptr;
	UPROPERTY(EditDefaultsOnly, Category = Components, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* StaticMesh = nullptr;
	UPROPERTY(EditDefaultsOnly, Category = Components, meta = (AllowPrivateAccess = "true"))
	USphereComponent* CollisionSphere = nullptr;
	UPROPERTY(EditDefaultsOnly, Category = Components, meta = (AllowPrivateAccess = "true"))
	URadialForceComponent* RadialForce = nullptr;

	FTimerHandle ReloadTimer;
	UPROPERTY(ReplicatedUsing = OnRep_Active)
	bool bActive = true;
	
public:
	// Sets default values for this actor's properties
	AExplosionActor();

protected:
	virtual void OnConstruction(const FTransform& Transform) override;
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
	UFUNCTION(NetMulticast, Unreliable)
	void ExplosionEffect_Multicast();
	UFUNCTION()
	void OnRep_Active();

	void Explode();
	void Reload();
	void SetActive(bool bNewActive);
	void UpdateRadiusSettings();
	void UpdateActiveState();
	
public:
	UPROPERTY(EditInstanceOnly, Category = "Settings")
	float Radius = 250.0f;
	UPROPERTY(EditInstanceOnly, Category = "Settings")
	float Damage = 100.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Settings")
	UParticleSystem* FxFire = nullptr;
	UPROPERTY(EditDefaultsOnly, Category = "Settings")
	USoundBase* SoundFire = nullptr;
};
