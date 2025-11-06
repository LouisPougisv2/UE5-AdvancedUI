// Louis Pougis All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DeveloperSettings.h"
#include "Widgets/CommonActivatableWidgetBase.h"
#include "AdvancedUIDeveloperSettings.generated.h"

/**
 * Customized Developer settings to centralize Widget references 
 */
UCLASS(Config = Game, DefaultConfig, DisplayName = "Advanced UI Settings")
class UE5ADVANCEDUI_API UAdvancedUIDeveloperSettings : public UDeveloperSettings
{
	GENERATED_BODY()

public:

	UPROPERTY(Config, EditAnywhere, Category = "Widget Reference", meta = (ForceInlineRow, Categories = "AdvancedUI.Widget"))
	TMap<FGameplayTag, TSoftClassPtr<UCommonActivatableWidgetBase>> AdvancedUIWidgetMap;
	
};
