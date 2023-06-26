// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "UCPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class UEAPP_API AUCPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AUCPlayerController();
	
    UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="char")
	APawn* my_char;


	
	
};
