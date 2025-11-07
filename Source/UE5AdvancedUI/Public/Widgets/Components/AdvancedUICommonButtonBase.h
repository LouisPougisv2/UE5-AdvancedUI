// Louis Pougis All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "CommonButtonBase.h"
#include "AdvancedUICommonButtonBase.generated.h"

/**
 * Customized Common Button Base class
 */
UCLASS(Abstract, BlueprintType, meta = (DisableNativeTick))
class UE5ADVANCEDUI_API UAdvancedUICommonButtonBase : public UCommonButtonBase
{
	GENERATED_BODY()

// Function
public:

    UFUNCTION(BlueprintCallable)
    void SetButtonText(FText InText);
    
private:

    //~ Begin UUserWidget Interface
    virtual void NativePreConstruct() override;
    virtual void NativeOnHovered() override;
    virtual void NativeOnUnhovered() override;

    //~ End UUserWidget Interface
    
    //~ Begin UCommonButtonBase Interface
    virtual void NativeOnCurrentTextStyleChanged() override;
    //~ End UCommonButtonBase Interface
    
// Variables
private:

    //~ Begin Widget Bindings
    UPROPERTY(meta = (BindWidgetOptional))
    class UCommonTextBlock* CommonTextBlock_ButtonText;
    //~ End Widget Bindings

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Advanced UI Button", meta = (AllowPrivateAccess = "true"))
    FText ButtonDisplayText;
    
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Advanced UI Button", meta = (AllowPrivateAccess = "true"))
    bool bUseUppercaseForButtonText = false;
    
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Advanced UI Button", meta = (AllowPrivateAccess = "true"))
    FText ButtonDescriptionText;
};
