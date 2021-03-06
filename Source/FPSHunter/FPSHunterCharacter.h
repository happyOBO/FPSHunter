// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "FPSHunterCharacter.generated.h"

class UInputComponent;
class USkeletalMeshComponent;
class USceneComponent;
class UCameraComponent;
class UAnimMontage;
class USoundBase;
// class UMotionControllerComponent;

UCLASS(config=Game)
class AFPSHunterCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Pawn mesh: 1st person view (arms; seen only by self) */
	UPROPERTY(VisibleDefaultsOnly, Category=Mesh)
	USkeletalMeshComponent* Mesh1P;

	/** Gun mesh: 1st person view (seen only by self) */
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	USkeletalMeshComponent* FP_Gun;

	/** Location on gun mesh where projectiles should spawn. */
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	USceneComponent* FP_MuzzleLocation;

	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FirstPersonCameraComponent;

public:
	AFPSHunterCharacter();

protected:
	virtual void BeginPlay();

public:
	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseLookUpRate;

	/** Gun muzzle's offset from the characters location */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Gameplay)
	FVector GunOffset;

	///** Projectile class to spawn */
	//UPROPERTY(EditDefaultsOnly, Category=Projectile)
	//TSubclassOf<class AFPSHunterProjectile> ProjectileClass;

	/** AnimMontage to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	UAnimMontage* FireAnimation;

protected:
	
	/** Fires a projectile. */
	void OnFire();

	/** Handles moving forward/backward */
	void MoveForward(float Val);

	/** Handles stafing movement, left and right */
	void MoveRight(float Val);

	/**
	 * Called via input to turn at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	/**
	 * Called via input to turn look up/down at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);

	struct TouchData
	{
		TouchData() { bIsPressed = false;Location=FVector::ZeroVector;}
		bool bIsPressed;
		ETouchIndex::Type FingerIndex;
		FVector Location;
		bool bMoved;
	};
	void BeginTouch(const ETouchIndex::Type FingerIndex, const FVector Location);
	void EndTouch(const ETouchIndex::Type FingerIndex, const FVector Location);
	void TouchUpdate(const ETouchIndex::Type FingerIndex, const FVector Location);
	TouchData	TouchItem;
	
protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;
	// End of APawn interface
	bool EnableTouchscreenMovement(UInputComponent* InputComponent);

public:
	/** Returns Mesh1P subobject **/
	USkeletalMeshComponent* GetMesh1P() const { return Mesh1P; }
	/** Returns FirstPersonCameraComponent subobject **/
	UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Weapon)
	TArray<TSubclassOf<class AFPSHunterWeapon>> WeaponsClass;

	TArray<AFPSHunterWeapon*> WeaponInventory;

	/* ???? Weapon ?????? ???????? */
	UFUNCTION(BlueprintPure, Category = Weapon)
	UTexture2D* GetCurrentWeaponThumbnail();

	/* ???? Weapon ???? ???? ?? ???????? */
	UFUNCTION(BlueprintPure, Category = Weapon)
	int32 GetCurrentWeaponRemainedBullets();

	/* ???? Weapon ?? ???? ?? ???????? */
	UFUNCTION(BlueprintPure, Category = Weapon)
	int32 GetCurrentWeaponTotalBullets();
	
	/* ???? Coin ???? ???????? */
	UFUNCTION(BlueprintPure, Category = Weapon)
	int32 GetTotalCoin();

	UFUNCTION()
	void LoadCurrentWeaponFinish(UAnimMontage* Montage, bool bInterrupted);

private:
	/* Weapon ???? */
	const int32 NUM_OF_WEAPONS = 2;

	/* ???? weapon idx */
	int32 CurrentWeaponSlot;

	int32 TotalCoin = 0;

	/* ???? weapon */
	AFPSHunterWeapon* GetCurrentlyWeapon();

	/* Weapon ????(??)*/
	void MoveUpWeaponInventorySlot();

	/* Weapon ????(????)*/
	void MoveDownWeaponInventorySlot();

	void WeaponUpdate();

	void WeaponLoad();

	void LoadCurrentWeapon();

	void Carving();

};

