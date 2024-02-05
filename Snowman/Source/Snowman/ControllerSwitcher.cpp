// Fill out your copyright notice in the Description page of Project Settings.

#include "Camera/CameraActor.h"
#include "ControllerSwitcher.h"

// Sets default values for this component's properties
UControllerSwitcher::UControllerSwitcher()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

// Called when the game starts
void UControllerSwitcher::BeginPlay()
{
	Super::BeginPlay();

	for (auto &snowman : snowmen)
	{
		if (!snowman)
		{
			UE_LOG(LogTemp, Display, TEXT("snowman is null!"));
			if (GEngine)
				GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("snowman is null!")));
			return;
		}

		if (!snowman->InputComponent)
		{
			UE_LOG(LogTemp, Display, TEXT("snowman has no input component!"));
			if (GEngine)
				GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("snowman has no input component!")));
		}
		else
			snowman->InputComponent->BindAction(SWITCH, EInputEvent::IE_Pressed, this, &UControllerSwitcher::SwitchSnowman);
	}

	controller = snowmen[currentSnowman]->GetController();

	if (!controller)
	{
		if (GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("no controller!")));
	}
}

void UControllerSwitcher::SwitchSnowman()
{
	if (!controller)
	{
		if (GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("no controller!")));

		return;
	}

	if (currentSnowman + 1 >= snowmen.Num())
		currentSnowman = 0;
	else
		currentSnowman++;

	controller->UnPossess();
	controller->Possess(snowmen[currentSnowman]);
	controller = snowmen[currentSnowman]->GetController();
	snowmen[currentSnowman]->InputComponent->ClearActionBindings();
	snowmen[currentSnowman]->InputComponent->BindAction(SWITCH, EInputEvent::IE_Pressed, this, &UControllerSwitcher::SwitchSnowman);

	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("Possessing: %d"), currentSnowman));
}
