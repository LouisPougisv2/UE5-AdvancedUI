#pragma once
/*
 * Advanced UI enum types
 */


UENUM(BlueprintType)
enum class EConfirmScreenType : uint8
{
    Ok,
    YesNo,
    OkCancel,
    
    Default UMETA(Hidden)
};

UENUM(BlueprintType)
enum class EConfirmationScreenButtonType : uint8
{
    Confirmed,
    Cancelled,
    Closed,
    
    Default UMETA(Hidden)
};