// Louis Pougis All rights reserved


#include "AsyncActions/AsyncAction_PushConfirmScreen.h"

#include "Subsystems/AdvancedUISubsystem.h"

UAsyncAction_PushConfirmScreen* UAsyncAction_PushConfirmScreen::PushConfirmScreen(const UObject* WorldContextObject, EConfirmScreenType InScreenType, FText InScreenTitle, FText InScreenMessage)
{
    if(GEngine)
    {
        if(UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull))
        {
            UAsyncAction_PushConfirmScreen* NewConfirmScreen = NewObject<UAsyncAction_PushConfirmScreen>();
            NewConfirmScreen->CachedOwningWorld = World;
            NewConfirmScreen->CachedScreenType = InScreenType;
            NewConfirmScreen->CachedScreenTitle = InScreenTitle;
            NewConfirmScreen->CachedScreenMessage = InScreenMessage;

            NewConfirmScreen->RegisterWithGameInstance(World);

            return NewConfirmScreen;
        }
    }

    return nullptr;
}

void UAsyncAction_PushConfirmScreen::Activate()
{
    UAdvancedUISubsystem* AdvancedSubsystem = UAdvancedUISubsystem::Get(CachedOwningWorld.Get());
    ensure(IsValid(AdvancedSubsystem));

    AdvancedSubsystem->PushConfirmScreenToModalStackBasic(CachedScreenType, CachedScreenTitle, CachedScreenMessage,
        [&](EConfirmationScreenButtonType InConfirmationScreenButtonType)
        {
            OnButtonClickedDelegate.Broadcast(InConfirmationScreenButtonType);

            SetReadyToDestroy();
        });
}
