// Louis Pougis All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "AUIPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class UE5ADVANCEDUI_API AAUIPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:

	//~ Begin APlayerController Interface
	virtual void OnPossess(APawn* InPawn) override;
	//~ End APlayerController Interface
	
};
