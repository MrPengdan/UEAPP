// Copyright Epic Games, Inc. All Rights Reserved.


#include "ueappGameModeBase.h"

#include "UCCharacter.h"
#include "UCPlayerController.h"

AueappGameModeBase::AueappGameModeBase()
{
	//设置游戏模式默认控制器
	PlayerControllerClass=AUCPlayerController::StaticClass();
	//设置游戏模式默认控制角色
	DefaultPawnClass=AUCCharacter::StaticClass();

	
}


void AueappGameModeBase::BeginPlay()  //重载事件开始函数
{
	Super::BeginPlay();
	
	
}