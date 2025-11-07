// Louis Pougis All rights reserved


#include "Widgets/Components/AdvancedUICommonButtonBase.h"
#include "CommonTextBlock.h"
#include "Subsystems/AdvancedUISubsystem.h"

void UAdvancedUICommonButtonBase::SetButtonText(FText InText)
{
    if(CommonTextBlock_ButtonText!= nullptr && !InText.IsEmpty())
    {
        CommonTextBlock_ButtonText->SetText(bUseUppercaseForButtonText ? InText.ToUpper() : InText);
    }
}

void UAdvancedUICommonButtonBase::NativePreConstruct()
{
    Super::NativePreConstruct();

    SetButtonText(ButtonDisplayText);
}

void UAdvancedUICommonButtonBase::NativeOnHovered()
{
    Super::NativeOnHovered();

    if(!ButtonDescriptionText.IsEmpty())
    {
        if(UAdvancedUISubsystem* AdvancedUISubsystem = UAdvancedUISubsystem::Get(this))
        {
            AdvancedUISubsystem->OnButtonDescriptionTextUpdatedDelegate.Broadcast(this, ButtonDescriptionText);
        }
    }
}

void UAdvancedUICommonButtonBase::NativeOnUnhovered()
{
    Super::NativeOnUnhovered();

    if(UAdvancedUISubsystem* AdvancedUISubsystem = UAdvancedUISubsystem::Get(this))
    {
        AdvancedUISubsystem->OnButtonDescriptionTextUpdatedDelegate.Broadcast(this, FText());
    }
}

void UAdvancedUICommonButtonBase::NativeOnCurrentTextStyleChanged()
{
    Super::NativeOnCurrentTextStyleChanged();

    if(CommonTextBlock_ButtonText != nullptr && GetCurrentTextStyleClass() != nullptr)
    {
        CommonTextBlock_ButtonText->SetStyle(GetCurrentTextStyleClass());
    }
}
