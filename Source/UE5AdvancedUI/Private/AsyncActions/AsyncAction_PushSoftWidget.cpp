// Louis Pougis All rights reserved


#include "AsyncActions/AsyncAction_PushSoftWidget.h"

#include "GameplayTagContainer.h"
#include "Subsystems/AdvancedUISubsystem.h"
#include "Widgets/CommonActivatableWidgetBase.h"

UAsyncAction_PushSoftWidget* UAsyncAction_PushSoftWidget::PushSoftWidget(const UObject* InWorldContextObject, APlayerController* InOwningPlayerController, TSoftClassPtr<UCommonActivatableWidgetBase> InSoftWidgetClass, UPARAM(meta = (Categories = "AdvancedUI.WidgetStack")) FGameplayTag InWidgetStackTag, bool bFocusOnNewlyPushedWidget)
{
    checkf(!InSoftWidgetClass.IsNull(), TEXT("%s was passed a null soft widget class"), *FString(__FUNCTION__));

    if(GEngine)
    {
        if(UWorld* World = GEngine->GetWorldFromContextObject(InWorldContextObject, EGetWorldErrorMode::LogAndReturnNull))
        {
            UAsyncAction_PushSoftWidget* Node = NewObject<UAsyncAction_PushSoftWidget>();
            Node->CachedOwningWorld = World;
            Node->CachedOwningPlayerController = InOwningPlayerController;
            Node->CachedSoftWidgetClass = InSoftWidgetClass;
            Node->CachedWidgetStackTag = InWidgetStackTag;
            Node->bCachedFocusOnNewlyPushedWidget = bFocusOnNewlyPushedWidget;

            Node->RegisterWithGameInstance(World);
            return Node;
        }
    }
    
    return nullptr;
}

void UAsyncAction_PushSoftWidget::Activate()
{
    UAdvancedUISubsystem* AdvancedSubsystem = UAdvancedUISubsystem::Get(CachedOwningWorld.Get());
    ensure(IsValid(AdvancedSubsystem));

    AdvancedSubsystem->PushSoftWidgetToStackAsync(CachedWidgetStackTag, CachedSoftWidgetClass,
        [this](EAsyncPushWidgetState InPushWidgetState, UCommonActivatableWidgetBase* InPushedWidget)
        {
            switch (InPushWidgetState)
            {
                case EAsyncPushWidgetState::OnCreatedBeforePush:
                    
                    InPushedWidget->SetOwningPlayer(CachedOwningPlayerController.Get());
                    OnCreatedWidgetBeforePush.Broadcast(InPushedWidget);
                    break;
                
                case EAsyncPushWidgetState::AfterPush:
                    
                    OnCreatedWidgetAfterPush.Broadcast(InPushedWidget);

                    if(UWidget* WidgetToFocus = InPushedWidget->GetDesiredFocusTarget())
                    {
                        WidgetToFocus->SetFocus();
                    }
                
                    SetReadyToDestroy();
                    break;
                
                default:
                    
                    break;
            }
        });
}