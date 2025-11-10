// Louis Pougis All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "AdvancedUITypes/AdvancedUIEnumTypes.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "AdvancedUISubsystem.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnButtonDescriptionTextUpdatedDelegate, UAdvancedUICommonButtonBase*, InBroadCastingButton, FText, DescriptionText);

enum class EAsyncPushWidgetState : uint8
{
    OnCreatedBeforePush,
    AfterPush
};

/**
 * Subsystem in charge of storing the Primary layout and providing with methods to push widget
 */
UCLASS()
class UE5ADVANCEDUI_API UAdvancedUISubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:

    static UAdvancedUISubsystem* Get(const UObject* InWorldContextObject);

    // ~ Begin USubsystem interface
    virtual bool ShouldCreateSubsystem(UObject* Outer) const override;
    // ~ End USubsystem interface

    UFUNCTION(BlueprintCallable)
    void RegisterPrimaryLayoutWidget(class UPrimaryLayoutWidget* InPrimaryLayoutWidget);

    void PushSoftWidgetToStackAsync(const struct FGameplayTag& InWidgetStackTag, TSoftClassPtr<class UCommonActivatableWidgetBase> InSoftWidgetClass, TFunction<void (EAsyncPushWidgetState, class UCommonActivatableWidgetBase*)> AsyncPushStateCallback);

    void PushConfirmScreenToModalStackBasic(EConfirmScreenType InScreenType, const FText& InScreenTitle, const FText& InScreenMessage, TFunction<void(EConfirmationScreenButtonType)> ButtonClickedCallback);

// Variables
public:
    
    UPROPERTY(BlueprintAssignable)
    FOnButtonDescriptionTextUpdatedDelegate OnButtonDescriptionTextUpdatedDelegate;
    
private:

    UPROPERTY(Transient)
    class UPrimaryLayoutWidget* PrimaryLayoutWidget;
};
