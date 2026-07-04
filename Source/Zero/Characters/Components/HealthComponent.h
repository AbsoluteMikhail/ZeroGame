// Copyright (c) 2026 Absolute Mikhail

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "HealthComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnHealthChange, float, Health, float, Damage);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDead);

/**
 *  Компонент здоровья, содержит жизни игрока.
 *  Сообщает о смерти игрока через диспатчер
 */
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class ZERO_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UHealthComponent();

	UPROPERTY(BlueprintAssignable, Category = "Health")
	FOnHealthChange OnHealthChange;
	UPROPERTY(BlueprintAssignable, Category = "Health")
	FOnDead OnDead;
	
protected:
	UPROPERTY(ReplicatedUsing = OnRep_Health)
	float Health = 100.0f;
	UPROPERTY(ReplicatedUsing = OnRep_AliveStatus)
	bool bAliveStatus = true;

	UFUNCTION()
	void OnRep_Health(float OldHealth);
	UFUNCTION()
	void OnRep_AliveStatus(bool bOldAliveStatus);

public:
	UFUNCTION(BlueprintCallable, Category = "Health")
	FORCEINLINE float GetCurrentHealth() const { return Health;}
	UFUNCTION(BlueprintCallable, Category = "Health")
	FORCEINLINE bool GetAliveStatus() const { return bAliveStatus;}

	UFUNCTION(Server, Reliable, BlueprintCallable, Category = "Health")
	virtual void ChangeHealthValue_OnServer(float ChangeValue);

	void ApplyHealthChange(float ChangeValue);
};
