// Louis Pougis All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "CommonActivatableWidget.h"
#include "CommonActivatableWidgetBase.generated.h"

/**
 * 
 */
UCLASS(Abstract, BlueprintType, meta = (DisableNativeTick))
class UE5ADVANCEDUI_API UCommonActivatableWidgetBase : public UCommonActivatableWidget
{
	GENERATED_BODY()

protected:

    UFUNCTION(BlueprintPure)
    class AAUIPlayerController* GetCachedOwningPlayerController();
    
private:

    TWeakObjectPtr<class AAUIPlayerController> CachedOwningPlayerController;
};
