// Louis Pougis All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "AdvancedUIFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class UE5ADVANCEDUI_API UAdvancedUIFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

    UFUNCTION(BlueprintPure, Category = "Advanced UI Function Library")
    static TSoftClassPtr<class UCommonActivatableWidgetBase> GetAdvancedUISoftWidgetClassByTag(UPARAM(meta = (Categories = "AdvancedUI.Widget")) FGameplayTag InWidgetTag);
};
