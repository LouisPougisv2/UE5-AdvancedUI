// Louis Pougis All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "GameplayTagContainer.h"
#include "PrimaryLayoutWidget.generated.h"

/**
 * 
 */
UCLASS(Abstract, BlueprintType, meta = (DisableNativeTick))
class UE5ADVANCEDUI_API UPrimaryLayoutWidget : public UCommonUserWidget
{
	GENERATED_BODY()
public:

	UFUNCTION(BlueprintCallable)
	class UCommonActivatableWidgetContainerBase* FindWidgetStackByTag(const FGameplayTag& InWidgetTag);
protected:

	UFUNCTION(BlueprintCallable)
	void RegisterWidgetStack(UPARAM(meta = (Categories = "AdvancedUI.WidgetStack")) FGameplayTag InStackTag, class UCommonActivatableWidgetContainerBase* InWidgetStack);
private:

	UPROPERTY(Transient)
	TMap<FGameplayTag, class UCommonActivatableWidgetContainerBase*> RegisteredWidgetStackMap;
};
