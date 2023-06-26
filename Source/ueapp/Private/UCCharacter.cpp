// Fill out your copyright notice in the Description page of Project Settings.在项目设置的“说明”页中填写版权声明。


#include "UCCharacter.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"



// Sets default values设置默认值
AUCCharacter::AUCCharacter()
{
 	/* Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	设置此字符以每帧调用 Tick（）。如果不这样做，您可以关闭此功能以提高性能*/
	PrimaryActorTick.bCanEverTick = true;

	


	//构造函数中调用自定义构造
	this->UCgouzhao();
	this->UCdisanrenchen();

	AutoPossessPlayer=EAutoReceiveInput::Player0;
}



// Called when the game starts or when spawned 在游戏启动或生成时调用
void AUCCharacter::BeginPlay()
{
	Super::BeginPlay();

	//this->spwanaactor();
	
	//Add Input Mapping Context 添加输入映射上下文
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
}

// Called every frame 调用每一帧

void AUCCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


// Called to bind functionality to input  调用将功能绑定到输入
void AUCCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	// Set up action bindings 设置操作绑定
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent)) {

		//Jumping 开始跳跃
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ACharacter::Jump);
		//Jumping 停止跳跃
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		//Moving 移动
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AUCCharacter::Move);

		//Looking查看
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AUCCharacter::Look);

	}



}



//增强输入移动函数
void AUCCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D 申明移动输入变量并赋值 矢量2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr) //如果控制器有效
	{
		// find out which way is forward找出前进的方向
		const FRotator Rotation = Controller->GetControlRotation(); //定义旋转等于控制器旋转
		const FRotator YawRotation(0, Rotation.Yaw, 0);//定义Y旋转

		// get forward vector 获取向前向量 （根据给定的YawRotation（偏航旋转）创建一个旋转矩阵，并从中获取X轴的单位向量。）
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		// get right vector 向右向量 （根据给定的YawRotation（偏航旋转）创建一个旋转矩阵，并从中获取Y轴的单位向量。）
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 添加动作
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

//增强输入查看函数
void AUCCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D申明查看变量并赋值 矢量2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	
	if (Controller != nullptr)//如果控制器有效
	{
		// add yaw and pitch input to controller 将偏航和俯仰输入添加到控制器
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}



void AUCCharacter::UCdisanrenchen()
{
	// Set size for collision capsule 设置碰撞胶囊的大小
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	/* Don't rotate when the controller rotates. Let that just affect the camera.
	控制器旋转时不要旋转。让它影响相机。*/
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
	
	
	//附加2个组件
	SpringArmComponent->SetupAttachment(RootComponent);
	CameraComponent->SetupAttachment(SpringArmComponent);

	SpringArmComponent->bUsePawnControlRotation=true;
	CameraComponent->bUsePawnControlRotation=false;
	
	/* Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	注意：为了加快迭代速度，可以在角色蓝图中调整这些变量以及更多变量
	instead of recompiling to adjust them
	而不是重新编译以调整它们*/
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // 角色沿输入方向移动...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // 初始旋转速度


	
	
}


//赋值相关
void AUCCharacter::UCgouzhao()
{


	
	//设置弹簧臂和相机
	SpringArmComponent=CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	CameraComponent=CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	SkeletalMesh=LoadObject<USkeletalMesh>(NULL,TEXT(""));



	
}


//模型设置相关
void AUCCharacter::UCshezhimoxing()
{
	//设置骨骼网格体旋转
	GetMesh()->SetRelativeRotation(FRotator(0,-90,0));
	//设置位置
	GetMesh()->SetRelativeLocation(FVector(0,0,-80));
	//将之前申明的骨骼模型设置给默认网格体组件
	GetMesh()->SetSkeletalMesh(SkeletalMesh);
	//设置胶囊体尺寸
	GetCapsuleComponent()->InitCapsuleSize(42,100);
}


//测试生成对象
void AUCCharacter::spwanaactor()
{
	AUCCharacter*Myactor=GetWorld()->SpawnActor<AUCCharacter>(FVector((560,410,96)),FRotator(0,0,0));
	Myactor->Destroy();
	SetLifeSpan(10);

}

