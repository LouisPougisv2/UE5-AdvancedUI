// Louis Pougis All rights reserved


#include "AdvancedUIFunctionLibrary.h"
#include "AdvancedUISettings/AdvancedUIDeveloperSettings.h"

TSoftClassPtr<UCommonActivatableWidgetBase> UAdvancedUIFunctionLibrary::GetAdvancedUISoftWidgetClassByTag(FGameplayTag InWidgetTag)
{
    if(const UAdvancedUIDeveloperSettings* AdvancedUISettings = GetDefault<UAdvancedUIDeveloperSettings>())
    {
        ensureAlwaysMsgf(AdvancedUISettings->AdvancedUIWidgetMap.Contains(InWidgetTag), TEXT("%s : Couldn't not find the corresponding widget with tag %s"), *FString(__FUNCTION__), *InWidgetTag.ToString());
        return AdvancedUISettings->AdvancedUIWidgetMap.FindRef(InWidgetTag);
    }

    return TSoftClassPtr<UCommonActivatableWidgetBase>();
}
