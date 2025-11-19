// Louis Pougis All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "AdvancedUITypes/AdvancedUIEnumTypes.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "AsyncAction_PushConfirmScreen.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnConfirmScreenButtonClickedDelegate, EConfirmationScreenButtonType, InConfirmScreenType);
/**
 * 
 */
UCLASS()
class UE5ADVANCEDUI_API UAsyncAction_PushConfirmScreen : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

// Functions
public:
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject", HidePin = "WorldContextObject"), BlueprintInternalUseOnly, DisplayName = "Show Confirmation Screen")
	static UAsyncAction_PushConfirmScreen* PushConfirmScreen(
		const UObject* WorldContextObject,
		EConfirmScreenType InScreenType,
		FText InScreenTitle,
		FText InScreenMessage);
	
	//~ Begin UBlueprintAsyncActionBase interface
	virtual void Activate() override;
	//~ End UBlueprintAsyncActionBase interface

	UPROPERTY(BlueprintAssignable)
	FOnConfirmScreenButtonClickedDelegate OnConfirmScreenButtonClickedDelegate;

// Variables:
private:

	TWeakObjectPtr<UWorld> CachedOwningWorld;
	EConfirmScreenType CachedScreenType;
	FText CachedScreenTitle;
	FText CachedScreenMessage;
};
