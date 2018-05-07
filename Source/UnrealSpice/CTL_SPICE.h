// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

// Include SPICE
#include "SpiceUsr.h"

#include "Paths.h"
#include "PlatformFilemanager.h"

#include "CTL_SPICE.generated.h"

UCLASS()
class UNREALSPICE_API ACTL_SPICE : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACTL_SPICE();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	
};
