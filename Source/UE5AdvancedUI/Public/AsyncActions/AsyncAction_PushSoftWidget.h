// Louis Pougis All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "AsyncAction_PushSoftWidget.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPushSoftWidgetDelegate, UCommonActivatableWidgetBase*, PushedWidget);

/**
 * 
 */
UCLASS()
class UE5ADVANCEDUI_API UAsyncAction_PushSoftWidget : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()
// Functions
public:

    UFUNCTION(BlueprintCallable, meta = (WorldContext = "InWorldContextObject", HidePin = "WorldContextObject"), BlueprintInternalUseOnly, DisplayName = "Push Soft Widget To Widget Stack")
    static UAsyncAction_PushSoftWidget* PushSoftWidget(const UObject* InWorldContextObject, APlayerController* InOwningPlayerController, TSoftClassPtr<class UCommonActivatableWidgetBase> InSoftWidgetClass, UPARAM(meta = (Categories = "AdvancedUI.WidgetStack")) struct FGameplayTag InWidgetStackTag, bool bFocusOnNewlyPushedWidget = true);

    //~ Begin UBlueprintAsyncActionBase interface
    virtual void Activate() override;
    //~ End UBlueprintAsyncActionBase interface
    
// Variables

    UPROPERTY(BlueprintAssignable)
    FOnPushSoftWidgetDelegate OnCreatedWidgetBeforePush;

    UPROPERTY(BlueprintAssignable)
    FOnPushSoftWidgetDelegate OnCreatedWidgetAfterPush;

private:

    TWeakObjectPtr<UWorld> CachedOwningWorld;
    TWeakObjectPtr<APlayerController> CachedOwningPlayerController;
    TSoftClassPtr<class UCommonActivatableWidgetBase> CachedSoftWidgetClass;
    FGameplayTag CachedWidgetStackTag;
    bool bCachedFocusOnNewlyPushedWidget = false;
    
};
