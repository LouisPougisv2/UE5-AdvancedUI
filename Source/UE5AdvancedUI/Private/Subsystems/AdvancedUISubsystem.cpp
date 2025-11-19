// Louis Pougis All rights reserved


#include "Subsystems/AdvancedUISubsystem.h"
#include "AdvancedUIDebugHelper.h"
#include "AdvancedUIFunctionLibrary.h"
#include "AUIGameplayTags.h"
#include "Engine/AssetManager.h"
#include "Widgets/CommonActivatableWidgetBase.h"
#include "Widgets/CommonActivatableWidgetContainer.h"
#include "Widgets/ConfirmScreenWidget.h"
#include "Widgets/PrimaryLayoutWidget.h"

UAdvancedUISubsystem* UAdvancedUISubsystem::Get(const UObject* InWorldContextObject)
{
    if(GEngine)
    {
        if(const UWorld* World = GEngine->GetWorldFromContextObject(InWorldContextObject, EGetWorldErrorMode::Assert))
        {
            return UGameInstance::GetSubsystem<UAdvancedUISubsystem>(World->GetGameInstance());
        }
    }

    return nullptr;
}

bool UAdvancedUISubsystem::ShouldCreateSubsystem(UObject* Outer) const
{
    if(!CastChecked<UGameInstance>(Outer)->IsDedicatedServerInstance())
    {
        TArray<UClass*> OutFoundClasses;
        GetDerivedClasses(GetClass(),OutFoundClasses);

        return OutFoundClasses.IsEmpty();
    }

    return false;
}

void UAdvancedUISubsystem::RegisterPrimaryLayoutWidget(UPrimaryLayoutWidget* InPrimaryLayoutWidget)
{
    check(InPrimaryLayoutWidget);
    
    PrimaryLayoutWidget = InPrimaryLayoutWidget;

    AdvancedUIDebug::Print(TEXT("Primary Layout Widget correctly stored"));
}

void UAdvancedUISubsystem::PushSoftWidgetToStackAsync(const FGameplayTag& InWidgetStackTag, TSoftClassPtr<UCommonActivatableWidgetBase> InSoftWidgetClass, TFunction<void (EAsyncPushWidgetState, UCommonActivatableWidgetBase*)> AsyncPushStateCallback)
{
    ensureAlways(!InSoftWidgetClass.IsNull());

    UAssetManager::Get().GetStreamableManager().RequestAsyncLoad(
        InSoftWidgetClass.ToSoftObjectPath(),
        FStreamableDelegate::CreateLambda(
            [InSoftWidgetClass, this, InWidgetStackTag, AsyncPushStateCallback]()
            {
                UClass* LoadedWidgetClass = InSoftWidgetClass.Get();

                ensureAlways(IsValid(LoadedWidgetClass) && IsValid(PrimaryLayoutWidget));

                UCommonActivatableWidgetContainerBase* FoundWidgetStack = PrimaryLayoutWidget->FindWidgetStackByTag(InWidgetStackTag);
                ensure(IsValid(FoundWidgetStack));

                UCommonActivatableWidgetBase* CreatedWidget = FoundWidgetStack->AddWidget<UCommonActivatableWidgetBase>(
                    LoadedWidgetClass,
                    [AsyncPushStateCallback](UCommonActivatableWidgetBase& InCreatedWidgetInstance)
                    {
                        // Here is our chance to initialize the widget, so we're informing the caller of the current push state
                        AsyncPushStateCallback(EAsyncPushWidgetState::OnCreatedBeforePush, &InCreatedWidgetInstance);
                    });

                AsyncPushStateCallback(EAsyncPushWidgetState::AfterPush, CreatedWidget);
            }
        )
    );
}

void UAdvancedUISubsystem::PushConfirmScreenToModalStackBasic(EConfirmScreenType InScreenType, const FText& InScreenTitle, const FText& InScreenMessage, TFunction<void(EConfirmationScreenButtonType)> ButtonClickedCallback)
{
    UConfirmScreenInfoObject* CreatedInfoObject = nullptr;
    
    switch (InScreenType)
    {
    case EConfirmScreenType::Ok:
        CreatedInfoObject = UConfirmScreenInfoObject::CreateOKScreen(InScreenTitle, InScreenMessage);
        break;

    case EConfirmScreenType::YesNo:
        CreatedInfoObject = UConfirmScreenInfoObject::CreateYesNoScreen(InScreenTitle, InScreenMessage);
        break;
        
    case EConfirmScreenType::OkCancel:
        CreatedInfoObject = UConfirmScreenInfoObject::CreateOkCancelScreen(InScreenTitle, InScreenMessage);
        break;
        
    case EConfirmScreenType::Default:
        break;
    }

    ensureAlwaysMsgf(CreatedInfoObject, TEXT("%s : CreatedInfoObject is not valid before pushing to stack"), *FString(__FUNCTION__));

    PushSoftWidgetToStackAsync(
        FAdvancedUIGameplayTags::AdvancedUI_WidgetStack_Modal,
        UAdvancedUIFunctionLibrary::GetAdvancedUISoftWidgetClassByTag(FAdvancedUIGameplayTags::AdvancedUI_Widget_ConfirmScreen),
        [CreatedInfoObject,ButtonClickedCallback](EAsyncPushWidgetState InPushWidgetState, UCommonActivatableWidgetBase* InPushedWidget)
        {
            if(InPushWidgetState == EAsyncPushWidgetState::OnCreatedBeforePush)
            {
                UConfirmScreenWidget* PushedConfirmScreenWidget = CastChecked<UConfirmScreenWidget>(InPushedWidget);
                PushedConfirmScreenWidget->InitConfirmScreen(CreatedInfoObject, ButtonClickedCallback);
            }
        });
}
