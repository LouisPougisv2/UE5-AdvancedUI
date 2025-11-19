// Louis Pougis All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "AdvancedUITypes/AdvancedUIEnumTypes.h"
#include "Widgets/CommonActivatableWidgetBase.h"
#include "ConfirmScreenWidget.generated.h"

USTRUCT(BlueprintType)
struct FConfirmScreenButtonInfo
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EConfirmationScreenButtonType ConfirmationScreenButtonType = EConfirmationScreenButtonType::Default;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FText ButtonTextDisplay = FText();
};

/**
 * Class describing a Confirm Screen pop up Info object
 */

UCLASS()
class UE5ADVANCEDUI_API UConfirmScreenInfoObject : public UObject
{
    
    GENERATED_BODY()

// Functions
public:

    static UConfirmScreenInfoObject* CreateOKScreen(const FText& InScreenTitle, const FText& InScreenMessage);
    static UConfirmScreenInfoObject* CreateYesNoScreen(const FText& InScreenTitle, const FText& InScreenMessage);
    static UConfirmScreenInfoObject* CreateOkCancelScreen(const FText& InScreenTitle, const FText& InScreenMessage);
    
// Variables
public:

    UPROPERTY(Transient)
    FText ScreenTitle = FText();
    
    UPROPERTY(Transient)
    FText ScreenMessage = FText();

    UPROPERTY(Transient)
    TArray<struct FConfirmScreenButtonInfo> ButtonsArray;
};

/**
 * Class describing a Confirm Screen pop up widget
 */
UCLASS(Abstract, BlueprintType, meta = (DisableNativeTick))
class UE5ADVANCEDUI_API UConfirmScreenWidget : public UCommonActivatableWidgetBase
{
	GENERATED_BODY()

// Function
public:

    /** This function gets called outside the class when this widget is constructed & before it's pushed to a stack */
    void InitConfirmScreen(UConfirmScreenInfoObject* InScreenInfoObject, TFunction<void(EConfirmationScreenButtonType)> ClickedButtonCallback);

protected:

    //~ Begin UCommonActivatableWidget override
    virtual UWidget* NativeGetDesiredFocusTarget() const override;
    //~ End UCommonActivatableWidget override
    
// Variables
private:

    UPROPERTY(meta = (BindWidget))
    class UCommonTextBlock* CommonTextBlock_Title;

    UPROPERTY(meta = (BindWidget))
    class UCommonTextBlock* CommonTextBlock_Message;

    UPROPERTY(meta = (BindWidget))
    class UDynamicEntryBox* DynamicEntryBox_Buttons;;
};
