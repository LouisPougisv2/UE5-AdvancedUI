// Louis Pougis All rights reserved


#include "Widgets/CommonActivatableWidgetBase.h"
#include "Controllers/AUIPlayerController.h"

AAUIPlayerController* UCommonActivatableWidgetBase::GetCachedOwningPlayerController()
{
    if(!CachedOwningPlayerController.IsValid())
    {
        CachedOwningPlayerController = GetOwningPlayer<AAUIPlayerController>();
    }

    return CachedOwningPlayerController.IsValid() ? CachedOwningPlayerController.Get() : nullptr;
}