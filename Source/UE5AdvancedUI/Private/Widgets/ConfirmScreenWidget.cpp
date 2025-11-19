// Louis Pougis All rights reserved


#include "Widgets/ConfirmScreenWidget.h"
#include "CommonTextBlock.h"
#include "ICommonInputModule.h"
#include "Components/DynamicEntryBox.h"
#include "Widgets/Components/AdvancedUICommonButtonBase.h"

UConfirmScreenInfoObject* UConfirmScreenInfoObject::CreateOKScreen(const FText& InScreenTitle, const FText& InScreenMessage)
{
    UConfirmScreenInfoObject* InfoObject = NewObject<UConfirmScreenInfoObject>();
    InfoObject->ScreenTitle = InScreenTitle;
    InfoObject->ScreenMessage = InScreenMessage;

    FConfirmScreenButtonInfo OKButtonInfo;
    OKButtonInfo.ConfirmationScreenButtonType = EConfirmationScreenButtonType::Closed;
    OKButtonInfo.ButtonTextDisplay = FText::FromString(TEXT("Confirm"));
    
    InfoObject->ButtonsArray.Add(OKButtonInfo);

    return InfoObject;
}

UConfirmScreenInfoObject* UConfirmScreenInfoObject::CreateYesNoScreen(const FText& InScreenTitle, const FText& InScreenMessage)
{
    UConfirmScreenInfoObject* InfoObject = NewObject<UConfirmScreenInfoObject>();
    InfoObject->ScreenTitle = InScreenTitle;
    InfoObject->ScreenMessage = InScreenMessage;

    FConfirmScreenButtonInfo YesButtonInfo;
    YesButtonInfo.ConfirmationScreenButtonType = EConfirmationScreenButtonType::Confirmed;
    YesButtonInfo.ButtonTextDisplay = FText::FromString(TEXT("Yes"));

    FConfirmScreenButtonInfo NoButtonInfo;
    NoButtonInfo.ConfirmationScreenButtonType = EConfirmationScreenButtonType::Cancelled;
    NoButtonInfo.ButtonTextDisplay = FText::FromString(TEXT("No"));
    
    InfoObject->ButtonsArray.Add(YesButtonInfo);
    InfoObject->ButtonsArray.Add(NoButtonInfo);

    return InfoObject;
}

UConfirmScreenInfoObject* UConfirmScreenInfoObject::CreateOkCancelScreen(const FText& InScreenTitle, const FText& InScreenMessage)
{
    UConfirmScreenInfoObject* InfoObject = NewObject<UConfirmScreenInfoObject>();
    InfoObject->ScreenTitle = InScreenTitle;
    InfoObject->ScreenMessage = InScreenMessage;

    FConfirmScreenButtonInfo ConfirmButtonInfo;
    ConfirmButtonInfo.ConfirmationScreenButtonType = EConfirmationScreenButtonType::Confirmed;
    ConfirmButtonInfo.ButtonTextDisplay = FText::FromString(TEXT("Confirm"));

    FConfirmScreenButtonInfo CancelButtonInfo;
    CancelButtonInfo.ConfirmationScreenButtonType = EConfirmationScreenButtonType::Cancelled;
    CancelButtonInfo.ButtonTextDisplay = FText::FromString(TEXT("Cancel"));
    
    InfoObject->ButtonsArray.Add(ConfirmButtonInfo);
    InfoObject->ButtonsArray.Add(CancelButtonInfo);

    return InfoObject;
}

void UConfirmScreenWidget::InitConfirmScreen(UConfirmScreenInfoObject* InScreenInfoObject, TFunction<void(EConfirmationScreenButtonType)> ClickedButtonCallback)
{
    ensureAlwaysMsgf(IsValid(InScreenInfoObject), TEXT("InScreenForObject parameter is not valid"));

    check(CommonTextBlock_Title != nullptr && CommonTextBlock_Message != nullptr)

    CommonTextBlock_Title->SetText(InScreenInfoObject->ScreenTitle);
    CommonTextBlock_Message->SetText(InScreenInfoObject->ScreenMessage);

    // Checking if Dynamic entry box has old buttons previously created
    if(DynamicEntryBox_Buttons->GetNumEntries() != 0)
    {
        // Clearing the old buttons entries. The widget type for the entry box is specified in the child widget BP
        DynamicEntryBox_Buttons->Reset<UAdvancedUICommonButtonBase>(
            [](UAdvancedUICommonButtonBase& ExistingWidgetToBeDeleted)
            {
                ExistingWidgetToBeDeleted.OnClicked().Clear();
            });
    }

    ensureMsgf(!InScreenInfoObject->ButtonsArray.IsEmpty(), TEXT("InScreenInfoObject buttons array is empty"));

    for (const FConfirmScreenButtonInfo& ButtonInfo : InScreenInfoObject->ButtonsArray)
    {
        // Setting corresponding Action based of ConfirmationScreenButtonType
        FDataTableRowHandle InputActionRowHandle;
        InputActionRowHandle = ButtonInfo.ConfirmationScreenButtonType == EConfirmationScreenButtonType::Confirmed ?
            ICommonInputModule::GetSettings().GetDefaultClickAction() :
            ICommonInputModule::GetSettings().GetDefaultBackAction();

        // Creating buttons from corresponding ButtonInfo
        UAdvancedUICommonButtonBase* AddedButton = DynamicEntryBox_Buttons->CreateEntry<UAdvancedUICommonButtonBase>();
        AddedButton->SetButtonText(ButtonInfo.ButtonTextDisplay);
        AddedButton->SetTriggeredInputAction(InputActionRowHandle);
        AddedButton->OnClicked().AddLambda(
            [&]()
            {
                // Next line is how the caller knows which button was clicked
                ClickedButtonCallback(ButtonInfo.ConfirmationScreenButtonType);

                DeactivateWidget();
            });
    }

    if(DynamicEntryBox_Buttons->GetNumEntries() != 0)
    {
        // Set focus on the last button (so if we have 2 buttons (Confirm & cancel), the focus goes on the safest options -> Cancel)
        DynamicEntryBox_Buttons->GetAllEntries().Last()->SetFocus();
    }
}
