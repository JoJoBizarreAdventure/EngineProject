// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "NiagaraCommon.h"
#include "NiagaraEmitter.h"
#include "ViewModels/Stack/NiagaraStackItem.h"
#include "ViewModels/Stack/NiagaraStackScriptItemGroup.h"
#include "NiagaraStackEventScriptItemGroup.generated.h"

class FNiagaraScriptViewModel;
class UNiagaraStackObject;
struct FNiagaraEventScriptProperties;
class IDetailTreeNode;

UCLASS()
class NIAGARAEDITOR_API UNiagaraStackEventHandlerPropertiesItem : public UNiagaraStackItem
{
	GENERATED_BODY()
		 
public:
	void Initialize(FRequiredEntryData InRequiredEntryData, FGuid InEventScriptUsageId);

	virtual FText GetDisplayName() const override;

	virtual bool SupportsResetToBase() const override { return true; }
	virtual bool TestCanResetToBaseWithMessage(FText& OutCanResetToBaseMessage) const override;
	virtual void ResetToBase() override;

	FGuid GetEventScriptUsageId() const { return EventScriptUsageId; };

protected:
	virtual void FinalizeInternal() override;

	virtual void RefreshChildrenInternal(const TArray<UNiagaraStackEntry*>& CurrentChildren, TArray<UNiagaraStackEntry*>& NewChildren, TArray<FStackIssue>& NewIssues) override;

private:
	void EventHandlerPropertiesChanged();

	void SelectEmitterStackObjectRootTreeNodes(TArray<TSharedRef<IDetailTreeNode>> Source, TArray<TSharedRef<IDetailTreeNode>>* Selected);

	bool HasBaseEventHandler() const;

private:
	FGuid EventScriptUsageId;

	mutable TOptional<bool> bHasBaseEventHandlerCache;

	mutable TOptional<bool> bCanResetToBaseCache;

	TWeakObjectPtr<UNiagaraEmitter> Emitter;

	UPROPERTY()
	UNiagaraStackObject* EmitterObject;
};

UCLASS()
/** Meant to contain a single binding of a Emitter::EventScriptProperties to the stack.*/
class NIAGARAEDITOR_API UNiagaraStackEventScriptItemGroup : public UNiagaraStackScriptItemGroup
{
	GENERATED_BODY()

public:
	DECLARE_DELEGATE(FOnModifiedEventHandlers);

public:
	void Initialize(
		FRequiredEntryData InRequiredEntryData,
		TSharedRef<FNiagaraScriptViewModel> InScriptViewModel,
		ENiagaraScriptUsage InScriptUsage,
		FGuid InScriptUsageId,
		FGuid InEventSourceEmitterId);

	void SetOnModifiedEventHandlers(FOnModifiedEventHandlers OnModifiedEventHandlers);

	virtual bool SupportsDelete() const override { return true; }
	virtual bool TestCanDeleteWithMessage(FText& OutCanDeleteMessage) const override;
	virtual void Delete() override;

	FGuid GetEventSourceEmitterId() const {return EventSourceEmitterId; };

protected:
	FOnModifiedEventHandlers OnModifiedEventHandlersDelegate;

	virtual void RefreshChildrenInternal(const TArray<UNiagaraStackEntry*>& CurrentChildren, TArray<UNiagaraStackEntry*>& NewChildren, TArray<FStackIssue>& NewIssues) override;

private:
	bool HasBaseEventHandler() const;
	
private:
	mutable TOptional<bool> bHasBaseEventHandlerCache;

	FGuid EventSourceEmitterId;

	UPROPERTY()
	UNiagaraStackEventHandlerPropertiesItem* EventHandlerProperties;
};
