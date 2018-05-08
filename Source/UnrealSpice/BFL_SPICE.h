// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"

// Include SPICE
#include "SpiceUsr.h"

// Other useful functions
#include "Paths.h"
#include "FileManagerGeneric.h"
#include "FileManager.h"

#include "BFL_SPICE.generated.h"

/**
 * 
 */
UCLASS()
class UNREALSPICE_API UBFL_SPICE : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
	UFUNCTION(BlueprintCallable, Category = "SPICE")
	static TArray<FString> GetAvailableKernels();

	UFUNCTION(BlueprintCallable, Category = "SPICE")
	static TArray<FString> GetLoadedKernels();

	UFUNCTION(BlueprintCallable, Category = "SPICE")
	static int LoadKernel(FString kname);

	UFUNCTION(BlueprintCallable, Category = "SPICE")
	static int UnloadKernel(FString kname);

	UFUNCTION(BlueprintCallable, Category = "SPICE")
	static int UnloadAllKernels();

	UFUNCTION(BlueprintCallable, Category = "SPICE")
	static int GetNumberOfKernels();

	UFUNCTION(BlueprintCallable, Category = "SPICE")
	static FString GetKernelType(FString kname);

	UFUNCTION(BlueprintCallable, Category = "SPICE")
	static FString GetKernelArch(FString kname);
	
};
