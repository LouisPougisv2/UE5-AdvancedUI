// Louis Pougis All rights reserved

#include "Widgets/PrimaryLayoutWidget.h"
#include "AdvancedUIDebugHelper.h"

UCommonActivatableWidgetContainerBase* UPrimaryLayoutWidget::FindWidgetStackByTag(const FGameplayTag& InWidgetTag)
{
    checkf(RegisteredWidgetStackMap.Contains(InWidgetTag), TEXT("%s: Cannot retrieve the Widget stack with tag %s"), *FString(__FUNCTION__), *InWidgetTag.ToString());

    return RegisteredWidgetStackMap.FindRef(InWidgetTag);
}

void UPrimaryLayoutWidget::RegisterWidgetStack(FGameplayTag InStackTag, UCommonActivatableWidgetContainerBase* InWidgetStack)
{
    // If IsDesignTime is false, it means we're in runtime (not in editor anymore)
    if(!IsDesignTime())
    {
        if(!RegisteredWidgetStackMap.Contains(InStackTag))
        {
            RegisteredWidgetStackMap.Add(InStackTag, InWidgetStack);
        }
    }
}
