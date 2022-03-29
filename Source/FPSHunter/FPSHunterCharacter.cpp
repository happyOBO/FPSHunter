// Copyright Epic Games, Inc. All Rights Reserved.

#include "FPSHunterCharacter.h"
#include "FPSHunterProjectile.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/InputSettings.h"
#include "Kismet/GameplayStatics.h"
#include "FPSHunterWeapon.h"
#include "FPSHunterMammal.h"
#include "DrawDebugHelpers.h"
// #include "MotionControllerComponent.h"
// #include "XRMotionControllerBase.h" // for FXRMotionControllerBase::RightHandSourceId
//#include "HeadMountedDisplayFunctionLibrary.h"

DEFINE_LOG_CATEGORY_STATIC(LogFPChar, Warning, All);

//////////////////////////////////////////////////////////////////////////
// AFPSHunterCharacter

AFPSHunterCharacter::AFPSHunterCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->SetRelativeLocation(FVector(-39.56f, 1.75f, 64.f)); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	Mesh1P->SetOnlyOwnerSee(true);
	Mesh1P->SetupAttachment(FirstPersonCameraComponent);
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;
	Mesh1P->SetRelativeRotation(FRotator(1.9f, -19.19f, 5.2f));
	Mesh1P->SetRelativeLocation(FVector(-0.5f, -4.4f, -155.7f));

	// Create a gun mesh component
	FP_Gun = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FP_Gun"));
	FP_Gun->SetOnlyOwnerSee(false);			// otherwise won't be visible in the multiplayer
	FP_Gun->bCastDynamicShadow = false;
	FP_Gun->CastShadow = false;
	// FP_Gun->SetupAttachment(Mesh1P, TEXT("GripPoint"));
	FP_Gun->SetupAttachment(RootComponent);

	FP_MuzzleLocation = CreateDefaultSubobject<USceneComponent>(TEXT("MuzzleLocation"));
	FP_MuzzleLocation->SetupAttachment(FP_Gun);
	FP_MuzzleLocation->SetRelativeLocation(FVector(0.2f, 48.4f, -10.6f));

	// Default offset from the character location for projectiles to spawn
	GunOffset = FVector(100.0f, 0.0f, 10.0f);

	CurrentWeaponSlot = 0;
	
	WeaponInventory.SetNum(NUM_OF_WEAPONS);
}

void AFPSHunterCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	//Attach gun mesh component to Skeleton, doing it here because the skeleton is not yet created in the constructor
	FP_Gun->AttachToComponent(Mesh1P, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), TEXT("GripPoint"));

	// Show or hide the two versions of the gun based on whether or not we're using motion controllers.

	Mesh1P->SetHiddenInGame(false, true);

	// Weapon 생성
	UWorld* const World = GetWorld();
	if (World != nullptr)
	{
		int idx = 0;
		for (auto& weapon : WeaponsClass)
		{
			WeaponInventory[idx++] = World->SpawnActor<AFPSHunterWeapon>(weapon);
			UAnimInstance* AnimInstance = Mesh1P->GetAnimInstance();
			if (AnimInstance != nullptr)
			{
				AnimInstance->OnMontageEnded.AddDynamic(this, &AFPSHunterCharacter::LoadCurrentWeaponFinish);
			}
		}
	}

	WeaponUpdate();

}

//////////////////////////////////////////////////////////////////////////
// Input

void AFPSHunterCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// set up gameplay key bindings
	check(PlayerInputComponent);

	// Bind jump events
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	// Bind fire event
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &AFPSHunterCharacter::OnFire);

	// Enable touchscreen input
	EnableTouchscreenMovement(PlayerInputComponent);

	// Bind movement events
	PlayerInputComponent->BindAxis("MoveForward", this, &AFPSHunterCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AFPSHunterCharacter::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &AFPSHunterCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &AFPSHunterCharacter::LookUpAtRate);


	// Weapon Up Down
	InputComponent->BindAction("WeaponUp", IE_Pressed, this, &AFPSHunterCharacter::MoveUpWeaponInventorySlot);
	InputComponent->BindAction("WeaponDown", IE_Pressed, this, &AFPSHunterCharacter::MoveDownWeaponInventorySlot);

	InputComponent->BindAction("WeaponLoad", IE_Pressed, this, &AFPSHunterCharacter::LoadCurrentWeapon);
	InputComponent->BindAction("Carving", IE_Pressed, this, &AFPSHunterCharacter::Carving);
}

void AFPSHunterCharacter::OnFire()
{
	// try and fire a projectile
	if (GetCurrentlyWeapon() != nullptr)
	{
		UWorld* const World = GetWorld();
		if (World != nullptr)
		{

			const FRotator SpawnRotation = GetControlRotation();
			// MuzzleOffset is in camera space, so transform it to world space before offsetting from the character location to find the final muzzle position
			const FVector SpawnLocation = ((FP_MuzzleLocation != nullptr) ? FP_MuzzleLocation->GetComponentLocation() : GetActorLocation()) + SpawnRotation.RotateVector(GunOffset);

			// 사격
			GetCurrentlyWeapon()->Shoot(SpawnLocation, SpawnRotation);

		}
	}


	// try and play a firing animation if specified
	if (FireAnimation != nullptr)
	{
		// Get the animation object for the arms mesh
		UAnimInstance* AnimInstance = Mesh1P->GetAnimInstance();
		if (AnimInstance != nullptr)
		{
			AnimInstance->Montage_Play(FireAnimation, 1.f);
		}
	}
}


void AFPSHunterCharacter::BeginTouch(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	if (TouchItem.bIsPressed == true)
	{
		return;
	}
	if ((FingerIndex == TouchItem.FingerIndex) && (TouchItem.bMoved == false))
	{
		OnFire();
	}
	TouchItem.bIsPressed = true;
	TouchItem.FingerIndex = FingerIndex;
	TouchItem.Location = Location;
	TouchItem.bMoved = false;
}

void AFPSHunterCharacter::EndTouch(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	if (TouchItem.bIsPressed == false)
	{
		return;
	}
	TouchItem.bIsPressed = false;
}

void AFPSHunterCharacter::MoveForward(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorForwardVector(), Value);
	}
}

void AFPSHunterCharacter::MoveRight(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorRightVector(), Value);
	}
}

void AFPSHunterCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void AFPSHunterCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

bool AFPSHunterCharacter::EnableTouchscreenMovement(class UInputComponent* PlayerInputComponent)
{
	if (FPlatformMisc::SupportsTouchInput() || GetDefault<UInputSettings>()->bUseMouseForTouch)
	{
		PlayerInputComponent->BindTouch(EInputEvent::IE_Pressed, this, &AFPSHunterCharacter::BeginTouch);
		PlayerInputComponent->BindTouch(EInputEvent::IE_Released, this, &AFPSHunterCharacter::EndTouch);

		return true;
	}
	
	return false;
}

UTexture2D* AFPSHunterCharacter::GetCurrentWeaponThumbnail()
{
	if (GetCurrentlyWeapon() == nullptr) return nullptr;

	auto Weapon = GetCurrentlyWeapon();
	return Weapon->WeaponThumbnail;

}

AFPSHunterWeapon* AFPSHunterCharacter::GetCurrentlyWeapon()
{
	return WeaponInventory[CurrentWeaponSlot] != NULL ? WeaponInventory[CurrentWeaponSlot] : nullptr;
}


void AFPSHunterCharacter::MoveUpWeaponInventorySlot()
{
	CurrentWeaponSlot = FMath::Abs((CurrentWeaponSlot + 1) % NUM_OF_WEAPONS);

	WeaponUpdate();
}

void AFPSHunterCharacter::MoveDownWeaponInventorySlot()
{
	if (CurrentWeaponSlot == 0)
		CurrentWeaponSlot = NUM_OF_WEAPONS - 1;
	else
		CurrentWeaponSlot = FMath::Abs((CurrentWeaponSlot - 1) % NUM_OF_WEAPONS);


	WeaponUpdate();
}


int32 AFPSHunterCharacter::GetCurrentWeaponRemainedBullets()
{
	auto Weapon = GetCurrentlyWeapon();
	if (Weapon != nullptr)
	{
		return Weapon->GetRemainedBullets();
	}
	return 0;
}

int32 AFPSHunterCharacter::GetCurrentWeaponTotalBullets()
{
	auto Weapon = GetCurrentlyWeapon();
	if (Weapon != nullptr)
	{
		return Weapon->GetTotalBullets();
	}
	return 0;
}

int32 AFPSHunterCharacter::GetTotalCoin()
{
	return TotalCoin;
}

void AFPSHunterCharacter::LoadCurrentWeaponFinish(UAnimMontage* Montage, bool bInterrupted)
{
	UE_LOG(LogTemp, Log, TEXT("LoadCurrentWeaponFinish"));
	auto Weapon = GetCurrentlyWeapon();
	if (Weapon != nullptr)
	{
		if (Montage == Weapon->LoadAnimation)
			Weapon->LoadFinish();
	}
}



void AFPSHunterCharacter::WeaponUpdate()
{
	auto Weapon = GetCurrentlyWeapon();
	if (Weapon != nullptr)
	{
		FP_Gun->SetSkeletalMesh(Weapon->WeaponMesh->SkeletalMesh);
	}
}

void AFPSHunterCharacter::LoadCurrentWeapon()
{
	auto Weapon = GetCurrentlyWeapon();
	if (Weapon != nullptr)
	{
		Weapon->Load(Mesh1P->GetAnimInstance());
	}
}

void AFPSHunterCharacter::Carving()
{

	UWorld* World = GetWorld();
	FVector Center = GetActorLocation();
	float SearchRadius = 100.f;

	if (World == nullptr)
		return;
	TArray<FOverlapResult> OverlapResults;
	FCollisionQueryParams QueryParams(NAME_None, false, this);
	bool bResult = World->OverlapMultiByChannel(
		OverlapResults,
		Center,
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel2,
		FCollisionShape::MakeSphere(SearchRadius),
		QueryParams
	);

	if (bResult)
	{
		for (auto& OverlapResult : OverlapResults)
		{
			AFPSHunterMammal* Mammal = Cast<AFPSHunterMammal>(OverlapResult.GetActor());
			if (Mammal)
			{
				Mammal->Carved(TotalCoin);
				DrawDebugSphere(World, Center, SearchRadius, 16, FColor::Green, false, 0.2f);
				return;
			}
		}
	}


}

