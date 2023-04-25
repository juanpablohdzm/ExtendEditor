// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "SuperManager/Public/ActorActions/QuickActorActionsWidget.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeQuickActorActionsWidget() {}
// Cross Module References
	BLUTILITY_API UClass* Z_Construct_UClass_UEditorUtilityWidget();
	COREUOBJECT_API UEnum* Z_Construct_UEnum_CoreUObject_ESearchCase();
	SUPERMANAGER_API UClass* Z_Construct_UClass_UQuickActorActionsWidget();
	SUPERMANAGER_API UClass* Z_Construct_UClass_UQuickActorActionsWidget_NoRegister();
	UNREALED_API UClass* Z_Construct_UClass_UEditorActorSubsystem_NoRegister();
	UPackage* Z_Construct_UPackage__Script_SuperManager();
// End Cross Module References
	DEFINE_FUNCTION(UQuickActorActionsWidget::execSelectAllActorsWithSimilarName)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->SelectAllActorsWithSimilarName();
		P_NATIVE_END;
	}
	void UQuickActorActionsWidget::StaticRegisterNativesUQuickActorActionsWidget()
	{
		UClass* Class = UQuickActorActionsWidget::StaticClass();
		static const FNameNativePtrPair Funcs[] = {
			{ "SelectAllActorsWithSimilarName", &UQuickActorActionsWidget::execSelectAllActorsWithSimilarName },
		};
		FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
	}
	struct Z_Construct_UFunction_UQuickActorActionsWidget_SelectAllActorsWithSimilarName_Statics
	{
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UQuickActorActionsWidget_SelectAllActorsWithSimilarName_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/ActorActions/QuickActorActionsWidget.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UQuickActorActionsWidget_SelectAllActorsWithSimilarName_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UQuickActorActionsWidget, nullptr, "SelectAllActorsWithSimilarName", nullptr, nullptr, 0, nullptr, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UQuickActorActionsWidget_SelectAllActorsWithSimilarName_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickActorActionsWidget_SelectAllActorsWithSimilarName_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UQuickActorActionsWidget_SelectAllActorsWithSimilarName()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UQuickActorActionsWidget_SelectAllActorsWithSimilarName_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(UQuickActorActionsWidget);
	UClass* Z_Construct_UClass_UQuickActorActionsWidget_NoRegister()
	{
		return UQuickActorActionsWidget::StaticClass();
	}
	struct Z_Construct_UClass_UQuickActorActionsWidget_Statics
	{
		static UObject* (*const DependentSingletons[])();
		static const FClassFunctionLinkInfo FuncInfo[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_SearchCase_MetaData[];
#endif
		static const UECodeGen_Private::FBytePropertyParams NewProp_SearchCase;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_EditorActorSubsystem_MetaData[];
#endif
		static const UECodeGen_Private::FObjectPropertyParams NewProp_EditorActorSubsystem;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UQuickActorActionsWidget_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UEditorUtilityWidget,
		(UObject* (*)())Z_Construct_UPackage__Script_SuperManager,
	};
	const FClassFunctionLinkInfo Z_Construct_UClass_UQuickActorActionsWidget_Statics::FuncInfo[] = {
		{ &Z_Construct_UFunction_UQuickActorActionsWidget_SelectAllActorsWithSimilarName, "SelectAllActorsWithSimilarName" }, // 3176862571
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UQuickActorActionsWidget_Statics::Class_MetaDataParams[] = {
		{ "Comment", "/**\n * \n */" },
		{ "IncludePath", "ActorActions/QuickActorActionsWidget.h" },
		{ "ModuleRelativePath", "Public/ActorActions/QuickActorActionsWidget.h" },
	};
#endif
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UQuickActorActionsWidget_Statics::NewProp_SearchCase_MetaData[] = {
		{ "Category", "ActorBatchSelection" },
		{ "ModuleRelativePath", "Public/ActorActions/QuickActorActionsWidget.h" },
	};
#endif
	const UECodeGen_Private::FBytePropertyParams Z_Construct_UClass_UQuickActorActionsWidget_Statics::NewProp_SearchCase = { "SearchCase", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(UQuickActorActionsWidget, SearchCase), Z_Construct_UEnum_CoreUObject_ESearchCase, METADATA_PARAMS(Z_Construct_UClass_UQuickActorActionsWidget_Statics::NewProp_SearchCase_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UQuickActorActionsWidget_Statics::NewProp_SearchCase_MetaData)) }; // 1578437248
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UQuickActorActionsWidget_Statics::NewProp_EditorActorSubsystem_MetaData[] = {
		{ "ModuleRelativePath", "Public/ActorActions/QuickActorActionsWidget.h" },
	};
#endif
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UQuickActorActionsWidget_Statics::NewProp_EditorActorSubsystem = { "EditorActorSubsystem", nullptr, (EPropertyFlags)0x0040000000000000, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(UQuickActorActionsWidget, EditorActorSubsystem), Z_Construct_UClass_UEditorActorSubsystem_NoRegister, METADATA_PARAMS(Z_Construct_UClass_UQuickActorActionsWidget_Statics::NewProp_EditorActorSubsystem_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UQuickActorActionsWidget_Statics::NewProp_EditorActorSubsystem_MetaData)) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UQuickActorActionsWidget_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UQuickActorActionsWidget_Statics::NewProp_SearchCase,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UQuickActorActionsWidget_Statics::NewProp_EditorActorSubsystem,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_UQuickActorActionsWidget_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UQuickActorActionsWidget>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_UQuickActorActionsWidget_Statics::ClassParams = {
		&UQuickActorActionsWidget::StaticClass,
		"Editor",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		FuncInfo,
		Z_Construct_UClass_UQuickActorActionsWidget_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		UE_ARRAY_COUNT(FuncInfo),
		UE_ARRAY_COUNT(Z_Construct_UClass_UQuickActorActionsWidget_Statics::PropPointers),
		0,
		0x00B010A4u,
		METADATA_PARAMS(Z_Construct_UClass_UQuickActorActionsWidget_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_UQuickActorActionsWidget_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_UQuickActorActionsWidget()
	{
		if (!Z_Registration_Info_UClass_UQuickActorActionsWidget.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UQuickActorActionsWidget.OuterSingleton, Z_Construct_UClass_UQuickActorActionsWidget_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_UQuickActorActionsWidget.OuterSingleton;
	}
	template<> SUPERMANAGER_API UClass* StaticClass<UQuickActorActionsWidget>()
	{
		return UQuickActorActionsWidget::StaticClass();
	}
	DEFINE_VTABLE_PTR_HELPER_CTOR(UQuickActorActionsWidget);
	UQuickActorActionsWidget::~UQuickActorActionsWidget() {}
	struct Z_CompiledInDeferFile_FID_ExtendEditor_Plugins_SuperManager_Source_SuperManager_Public_ActorActions_QuickActorActionsWidget_h_Statics
	{
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_ExtendEditor_Plugins_SuperManager_Source_SuperManager_Public_ActorActions_QuickActorActionsWidget_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_UQuickActorActionsWidget, UQuickActorActionsWidget::StaticClass, TEXT("UQuickActorActionsWidget"), &Z_Registration_Info_UClass_UQuickActorActionsWidget, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UQuickActorActionsWidget), 2620651828U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_ExtendEditor_Plugins_SuperManager_Source_SuperManager_Public_ActorActions_QuickActorActionsWidget_h_1063328169(TEXT("/Script/SuperManager"),
		Z_CompiledInDeferFile_FID_ExtendEditor_Plugins_SuperManager_Source_SuperManager_Public_ActorActions_QuickActorActionsWidget_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_ExtendEditor_Plugins_SuperManager_Source_SuperManager_Public_ActorActions_QuickActorActionsWidget_h_Statics::ClassInfo),
		nullptr, 0,
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
