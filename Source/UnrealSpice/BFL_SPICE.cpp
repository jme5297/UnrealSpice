// Fill out your copyright notice in the Description page of Project Settings.

#include "BFL_SPICE.h"

/*
 * Access and return the names of all available kernels in CSPICE's data folder.
 */
TArray<FString> UBFL_SPICE::GetAvailableKernels()
{
	TArray<FString>		AvailableKernels;
	FString				spicedir;
	FString				kernNameUE;
	FString				p;
	FString				f;
	FString				e;

	// Get the directory to the data folder
	spicedir = FPaths::Combine(FPaths::ProjectDir(), FString("Content/SPICE_data/*"));

	// Return list of files in the SPICE data folder
	IFileManager::Get().FindFiles(AvailableKernels, *spicedir, true, false);

	// Remove unnecessary kernels
	for (int32 i = 0; i < AvailableKernels.Num(); i++)
	{
		// Get the absolute path of the kernel name.
		kernNameUE = FPaths::Combine(FPaths::ProjectDir(), FString("Content/SPICE_data/"), AvailableKernels[i]);
		kernNameUE = IFileManager::Get().ConvertToAbsolutePathForExternalAppForRead(*kernNameUE);

		// Split directory, file, and extension
		FPaths::Split(kernNameUE, p, f, e);

		// If the file exists, then attempt to unload the kernel.
		if (e.Equals("txt", ESearchCase::IgnoreCase))
		{
			AvailableKernels.RemoveAt(i);
		}
	}

	return AvailableKernels;
}

/*
 * Access and return the names of all loaded kernels in the kernel pool.
 * NOTE: does not currently work with lists of kernel files (functionality to be
 * implemented at a later point).
 */
TArray<FString> UBFL_SPICE::GetLoadedKernels()
{
	SpiceInt			which;
	SpiceInt			handle;
	SpiceInt			count;
	SpiceChar			file[512];
	SpiceChar			filtyp[33];
	SpiceChar			source[512];
	SpiceBoolean		found;
	TArray<FString>		LoadedKernels;
	FString				fileloc;
	FString				p;
	FString				f;
	FString				e;

	// Determine the amount of kernels currently loaded
	ktotal_c("ALL", &count);
	for (which = 0; which < count; which++)
	{
		// Grab information about the specific kernel.
		kdata_c(which, "ALL", 512, 33, 512, file, filtyp, source, &handle, &found);
		UE_LOG(LogTemp, Display, TEXT("Found kernel: %s"), *FString(file));

		// Separate out the file from path and extension.
		fileloc = FString(file);
		
		FPaths::Split(fileloc, p, f, e);

		// Add the name of this specific kernel.
		LoadedKernels.Add(f.Append(".").Append(e));
	}

	return LoadedKernels;
}

/*
 * Load a specific kernel into the kernel pool. Must be a unique kernel name.
 */
int UBFL_SPICE::LoadKernel(FString kname)
{
	SpiceInt			count = 0;
	ConstSpiceChar *	kernName;
	FString				kernNameUE;
	TArray<FString>		LoadedKernels;

	// Get the absolute path of the kernel name.
	kernNameUE = FPaths::Combine(FPaths::ProjectDir(), FString("Content/SPICE_data/"), kname);
	kernNameUE = IFileManager::Get().ConvertToAbsolutePathForExternalAppForRead(*kernNameUE);

	// If file exists, check if it's loaded. If it's not, then we're good to add!
	if (IFileManager::Get().FileExists(*kernNameUE))
	{
		// Find the kernels already added to the system.
		LoadedKernels = GetLoadedKernels();
		if (LoadedKernels.Find(FString(kname)) != INDEX_NONE)
		{
			// If already loaded into the system, return.
			UE_LOG(LogTemp, Warning, TEXT("This kernel is already loaded!"));
			ktotal_c("ALL", &count);
			return count;
		}

		// Convert to type acceptable by SPICE and attempt to furnish the kernel.
		kernName = TCHAR_TO_UTF8(*kernNameUE);
		UE_LOG(LogTemp, Display, TEXT("Kernal Name: %s"), *FString(kernName));
		furnsh_c(kernName);
	}

	// Check total number of loaded kernels and return
	ktotal_c("ALL", &count);
	return count;
}

/*
* Unload a specific kernel from the kernel pool. Must already be in the kernel pool.
*/
int UBFL_SPICE::UnloadKernel(FString kname)
{
	SpiceInt		count;
	FString			kernNameUE;

	// Get the absolute path of the kernel name.
	kernNameUE = FPaths::Combine(FPaths::ProjectDir(), FString("Content/SPICE_data/"), kname);
	kernNameUE = IFileManager::Get().ConvertToAbsolutePathForExternalAppForRead(*kernNameUE);
	
	// If the file exists, then attempt to unload the kernel.
	if (IFileManager::Get().FileExists(*kernNameUE))
	{
		unload_c(TCHAR_TO_UTF8(*kernNameUE));
	}

	// Check total number of loaded kernels and return.
	ktotal_c("ALL", &count);
	return count;
}

/*
* Unload all kernels from the kernel pool.
*/
int UBFL_SPICE::UnloadAllKernels()
{
	SpiceInt			count;
	FString				kernNameUE;
	TArray<FString>		LoadedKernels;

	// Get all loaded kernels.
	LoadedKernels = GetLoadedKernels();

	for (int32 i = 0; i < LoadedKernels.Num(); i++)
	{
		// Get the absolute path of the kernel name.
		kernNameUE = FPaths::Combine(FPaths::ProjectDir(), FString("Content/SPICE_data/"), LoadedKernels[i]);
		kernNameUE = IFileManager::Get().ConvertToAbsolutePathForExternalAppForRead(*kernNameUE);

		// If the file exists, then attempt to unload the kernel.
		if (IFileManager::Get().FileExists(*kernNameUE))
		{
			unload_c(TCHAR_TO_UTF8(*kernNameUE));
		}
	}

	// Check total number of loaded kernels and return.
	ktotal_c("ALL", &count);
	return count;
}

/* 
 * Returns total number of kernels loaded. 
 */
int UBFL_SPICE::GetNumberOfKernels()
{
	SpiceInt count;

	ktotal_c("ALL", &count);
	return count;
}

/*
* Returns the type of a kernel.
*/
FString UBFL_SPICE::GetKernelType(FString kname)
{
	SpiceChar 		arch[128];
	SpiceChar 		type[128];
	FString			kernNameUE;

	// Get the absolute path of the kernel name.
	kernNameUE = FPaths::Combine(FPaths::ProjectDir(), FString("Content/SPICE_data/"), kname);
	kernNameUE = IFileManager::Get().ConvertToAbsolutePathForExternalAppForRead(*kernNameUE);

	// If the file exists, then attempt grab kernel information.
	if (IFileManager::Get().FileExists(*kernNameUE))
	{
		getfat_c(TCHAR_TO_UTF8(*kernNameUE), 128, 128, arch, type);
	}
	
	return FString(type);
}

/*
* Returns the architecture of a kernel.
*/
FString UBFL_SPICE::GetKernelArch(FString kname)
{
	SpiceChar 		arch[128];
	SpiceChar 		type[128];
	FString			kernNameUE;

	// Get the absolute path of the kernel name.
	kernNameUE = FPaths::Combine(FPaths::ProjectDir(), FString("Content/SPICE_data/"), kname);
	kernNameUE = IFileManager::Get().ConvertToAbsolutePathForExternalAppForRead(*kernNameUE);

	// If the file exists, then attempt grab kernel information.
	if (IFileManager::Get().FileExists(*kernNameUE))
	{
		getfat_c(TCHAR_TO_UTF8(*kernNameUE), 128, 128, arch, type);
	}

	return FString(arch);
}
