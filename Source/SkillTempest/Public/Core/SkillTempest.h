// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

#define checkUClassInBp(Class, Var) \
	checkf(Var != nullptr, *(TEXT(#Var " was not provided: ") + Class->GetClass()->GetName()))

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName)           \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName)               \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName)               \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

UENUM(BlueprintType)
enum class EStAbilityInputID : uint8
{
	None UMETA(Hidden),
	Confirm,
	Cancel,

	Shoot,
	Invisibility,
	Freeze,
	Dash,

	Aim,
	Sprint,
	Jump,
};
