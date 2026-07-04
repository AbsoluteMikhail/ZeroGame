// Copyright (c) 2026 Absolute Mikhail

#pragma once

#include "CoreMinimal.h"
#include "AdvancedFriendsGameInstance.h"

#include "ZeroGameInstance.generated.h"



UCLASS()
class ZERO_API UZeroGameInstance : public UAdvancedFriendsGameInstance // Наследуюсь от GameInstance из плагина AdvancedSessions
{
	GENERATED_BODY()

public:
	UZeroGameInstance(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void Init() override;
};
