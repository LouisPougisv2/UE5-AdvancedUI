// Louis Pougis All rights reserved


#include "Controllers/AUIPlayerController.h"
#include "Camera/CameraActor.h"
#include "Kismet/GameplayStatics.h"

void AAUIPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	TArray<AActor*> OutCameraActors;
	UGameplayStatics::GetAllActorsOfClassWithTag(this, ACameraActor::StaticClass(), FName("Default"), OutCameraActors);

	if(!OutCameraActors.IsEmpty())
	{
		// Setting the new camera
		SetViewTarget(OutCameraActors[0]);
	}
}
