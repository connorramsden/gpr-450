// Fill out your copyright notice in the Description page of Project Settings.


#include "DataHandler.h"

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
	clipPoolFile = ReadFile("sprite_anim.txt");

	// Create an array to hold each line
	TArray<FString> lines;

	// Parse the original read-in file into individual lines
	clipPoolFile.ParseIntoArrayLines(lines, true);

	// Iterate over each line
	for (int i = 0; i < lines.Num(); ++i)
	{
		// Only read a line that starts with our DATA character
		if (lines[i].StartsWith("@"))
		{
			// Create a temporary array to hold a single line
			TArray<FString> line;

			// Parse the single line into an array, separated by tabs
			lines[i].ParseIntoArray(line, TEXT("\t"), true);

			// Create temporary instruction set
			FClipInstruction tempInstr;

			// Read in clip dat
			tempInstr.clipName = line[1];
			tempInstr.clipDuration = FCString::Atof(*line[2]);
			tempInstr.firstFrame = FCString::Atoi(*line[3]);
			tempInstr.lastFrame = FCString::Atoi(*line[4]);
			tempInstr.revTransition = line[5];
			tempInstr.fwdTransition = line[6];
			tempInstr.comments = line[7];

			instructions.Add(tempInstr);
		}
	}
}


// Called every frame
void UDataHandler::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction * ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

// Initial file IO borrowed from http://bocilmania.com/2017/03/12/reading-text-file-in-unreal-engine-4/
FString UDataHandler::ReadFile(FString fileName)
{
	// Read text file
	FString dir = FPaths::Combine(FPaths::ProjectContentDir(), TEXT("Data"));
	FString result;

	IPlatformFile & file = FPlatformFileManager::Get().GetPlatformFile();

	if (file.CreateDirectory(*dir))
	{
		FString dataFile = dir + "/" + fileName;
		FFileHelper::LoadFileToString(result, *dataFile);
	}

	return result;
}
