// Fill out your copyright notice in the Description page of Project Settings.


#include "CJR_DataHandler.h"

#include "CJR_KeyframeAnimation.h"

// Sets default values for this component's properties
UDataHandler::UDataHandler()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

// Default deconstructor
UDataHandler::~UDataHandler()
{
}

// Called when the game starts
void UDataHandler::BeginPlay()
{
	Super::BeginPlay();

	// Read in a file from /Data/
	ClipPoolFile = ReadFile("sprite_anim.txt");

	// Create an array to hold each line
	TArray<FString> Lines;

	// Parse the original read-in file into individual lines
	ClipPoolFile.ParseIntoArrayLines(Lines, true);

	// Iterate over each line
	for (int i = 0; i < Lines.Num(); ++i)
	{
		// Only read a line that starts with our DATA character
		if (Lines[i].StartsWith("@"))
		{
			// Create a temporary array to hold a single line
			TArray<FString> Line;

			// Parse the single line into an array, separated by tabs
			Lines[i].ParseIntoArray(Line, TEXT("\t"), true);

			// Create temporary instruction set
			UFClipInstruction* TempInstr = NewObject<UFClipInstruction>();

			// Read in clip dat
			TempInstr->ClipName = Line[1];
			TempInstr->ClipDuration = FCString::Atof(*Line[2]);
			TempInstr->FirstFrame = FCString::Atoi(*Line[3]);
			TempInstr->LastFrame = FCString::Atoi(*Line[4]);
			TempInstr->RevTransition = Line[5];
			TempInstr->FwdTransition = Line[6];
			TempInstr->Comments = Line[7];

			Instructions.Add(TempInstr);
		}
	}
}

// Initial file IO borrowed from http://bocilmania.com/2017/03/12/reading-text-file-in-unreal-engine-4/
FString UDataHandler::ReadFile(const FString FileName) const
{
	// Read text file
	const FString Dir = FPaths::Combine(FPaths::ProjectContentDir(), TEXT("Data"));
	FString Result;

	IPlatformFile& File = FPlatformFileManager::Get().GetPlatformFile();

	if (File.CreateDirectory(*Dir))
	{
		const FString DataFile = Dir + "/" + FileName;
		FFileHelper::LoadFileToString(Result, *DataFile);
	}

	return Result;
}
