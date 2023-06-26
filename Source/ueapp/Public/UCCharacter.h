// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "UCCharacter.generated.h"


UCLASS()
class UEAPP_API AUCCharacter : public ACharacter
{
	GENERATED_BODY()		

public:
	// 默认构造函数
	AUCCharacter();


protected:

	//添加输入事件重载函数
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// 游戏启动时调用 事件开始函数
	virtual void BeginPlay() override;

public:	
	// TICK每帧执行函数
	virtual void Tick(float DeltaTime) override;


protected:

	/** MappingContext 增强输入映射上下文 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputMappingContext* DefaultMappingContext;

	/** Jump Input Action  增强输入跳跃申明*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* JumpAction;

	/** Move Input Action 增强输入移动申明*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* MoveAction;

	/** Look Input Action 增强输入跳跃申明*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* LookAction;

	/** Called for movement input 增强输入移动函数*/
	void Move(const FInputActionValue& Value);

	/** Called for looking input 增强输入查看函数*/
	void Look(const FInputActionValue& Value);

public:
	//声明相机和弹簧臂组件
	UPROPERTY(EditInstanceOnly,Category="camera")
	USpringArmComponent* SpringArmComponent;
	UPROPERTY(EditInstanceOnly,Category="camera")
	UCameraComponent* CameraComponent;
	

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USkeletalMesh*SkeletalMesh;

	//初始化第三人称函数
	//UFUNCTION(BlueprintImplementableEvent)
	void UCdisanrenchen();

	
private:

	
	//自定义构造函数
	void UCgouzhao();
	//自定义模型属性函数
	void UCshezhimoxing();



public:
	//测试
	UPROPERTY(EditAnywhere, BlueprintReadWrite,meta=(instanceeditable=ture,ExposeOnSpawn=ture,AllowPrivateAccess=ture),Category="wenben")
	int TEST_TEXT;



	UFUNCTION(BlueprintCallable)
	void spwanaactor();
};

