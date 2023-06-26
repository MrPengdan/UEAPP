// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ueappGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class UEAPP_API AueappGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
public:
	
	AueappGameModeBase();//构造函数
	
	virtual void BeginPlay() override;  //重载事件开始函数







	
};
