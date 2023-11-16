// Copyright Epic Games, Inc. All Rights Reserved.

#include "mathcourseGameMode.h"
#include "mathcourseCharacter.h"
#include "UObject/ConstructorHelpers.h"

AmathcourseGameMode::AmathcourseGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
