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
	SUPERMANAGER_API UEnum* Z_Construct_UEnum_SuperManager_E_DuplicationAxis();
	UNREALED_API UClass* Z_Construct_UClass_UEditorActorSubsystem_NoRegister();
	UPackage* Z_Construct_UPackage__Script_SuperManager();
// End Cross Module References
	static FEnumRegistrationInfo Z_Registration_Info_UEnum_E_DuplicationAxis;
	static UEnum* E_DuplicationAxis_StaticEnum()
	{
		if (!Z_Registration_Info_UEnum_E_DuplicationAxis.OuterSingleton)
		{
			Z_Registration_Info_UEnum_E_DuplicationAxis.OuterSingleton = GetStaticEnum(Z_Construct_UEnum_SuperManager_E_DuplicationAxis, Z_Construct_UPackage__Script_SuperManager(), TEXT("E_DuplicationAxis"));
		}
		return Z_Registration_Info_UEnum_E_DuplicationAxis.OuterSingleton;
	}
	template<> SUPERMANAGER_API UEnum* StaticEnum<E_DuplicationAxis>()
	{
		return E_DuplicationAxis_StaticEnum();
	}
	struct Z_Construct_UEnum_SuperManager_E_DuplicationAxis_Statics
	{
		static const UECodeGen_Private::FEnumeratorParam Enumerators[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Enum_MetaDataParams[];
#endif
		static const UECodeGen_Private::FEnumParams EnumParams;
	};
	const UECodeGen_Private::FEnumeratorParam Z_Construct_UEnum_SuperManager_E_DuplicationAxis_Statics::Enumerators[] = {
		{ "E_DuplicationAxis::EDA_XAxis", (int64)E_DuplicationAxis::EDA_XAxis },
		{ "E_DuplicationAxis::EDA_YAxis", (int64)E_DuplicationAxis::EDA_YAxis },
		{ "E_DuplicationAxis::EDA_ZAxis", (int64)E_DuplicationAxis::EDA_ZAxis },
		{ "E_DuplicationAxis::EDA_MAX", (int64)E_DuplicationAxis::EDA_MAX },
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UEnum_SuperManager_E_DuplicationAxis_Statics::Enum_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "EDA_MAX.DisplayName", "Default Max" },
		{ "EDA_MAX.Name", "E_DuplicationAxis::EDA_MAX" },
		{ "EDA_XAxis.DisplayName", "X Axis" },
		{ "EDA_XAxis.Name", "E_DuplicationAxis::EDA_XAxis" },
		{ "EDA_YAxis.DisplayName", "Y Axis" },
		{ "EDA_YAxis.Name", "E_DuplicationAxis::EDA_YAxis" },
		{ "EDA_ZAxis.DisplayName", "Z Axis" },
		{ "EDA_ZAxis.Name", "E_DuplicationAxis::EDA_ZAxis" },
		{ "ModuleRelativePath", "Public/ActorActions/QuickActorActionsWidget.h" },
	};
#endif
	const UECodeGen_Private::FEnumParams Z_Construct_UEnum_SuperManager_E_DuplicationAxis_Statics::EnumParams = {
		(UObject*(*)())Z_Construct_UPackage__Script_SuperManager,
		nullptr,
		"E_DuplicationAxis",
		"E_DuplicationAxis",
		Z_Construct_UEnum_SuperManager_E_DuplicationAxis_Statics::Enumerators,
		UE_ARRAY_COUNT(Z_Construct_UEnum_SuperManager_E_DuplicationAxis_Statics::Enumerators),
		RF_Public|RF_Transient|RF_MarkAsNative,
		EEnumFlags::None,
		(uint8)UEnum::ECppForm::EnumClass,
		METADATA_PARAMS(Z_Construct_UEnum_SuperManager_E_DuplicationAxis_Statics::Enum_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UEnum_SuperManager_E_DuplicationAxis_Statics::Enum_MetaDataParams))
	};
	UEnum* Z_Construct_UEnum_SuperManager_E_DuplicationAxis()
	{
		if (!Z_Registration_Info_UEnum_E_DuplicationAxis.InnerSingleton)
		{
			UECodeGen_Private::ConstructUEnum(Z_Registration_Info_UEnum_E_DuplicationAxis.InnerSingleton, Z_Construct_UEnum_SuperManager_E_DuplicationAxis_Statics::EnumParams);
		}
		return Z_Registration_Info_UEnum_E_DuplicationAxis.InnerSingleton;
	}
	DEFINE_FUNCTION(UQuickActorActionsWidget::execDuplicateActors)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->DuplicateActors();
		P_NATIVE_END;
	}
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
			{ "DuplicateActors", &UQuickActorActionsWidget::execDuplicateActors },
			{ "SelectAllActorsWithSimilarName", &UQuickActorActionsWidget::execSelectAllActorsWithSimilarName },
		};
		FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
	}
	struct Z_Construct_UFunction_UQuickActorActionsWidget_DuplicateActors_Statics
	{
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UQuickActorActionsWidget_DuplicateActors_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/ActorActions/QuickActorActionsWidget.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UQuickActorActionsWidget_DuplicateActors_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UQuickActorActionsWidget, nullptr, "DuplicateActors", nullptr, nullptr, 0, nullptr, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UQuickActorActionsWidget_DuplicateActors_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickActorActionsWidget_DuplicateActors_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UQuickActorActionsWidget_DuplicateActors()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UQuickActorActionsWidget_DuplicateActors_Statics::FuncParams);
		}
		return ReturnFunction;
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
		static const UECodeGen_Private::FBytePropertyParams NewProp_AxisForDuplication_Underlying;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_AxisForDuplication_MetaData[];
#endif
		static const UECodeGen_Private::FEnumPropertyParams NewProp_AxisForDuplication;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_NumberOfDuplicates_MetaData[];
#endif
		static const UECodeGen_Private::FIntPropertyParams NewProp_NumberOfDuplicates;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_OffsetDiff_MetaData[];
#endif
		static const UECodeGen_Private::FFloatPropertyParams NewProp_OffsetDiff;
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
		{ &Z_Construct_UFunction_UQuickActorActionsWidget_DuplicateActors, "DuplicateActors" }, // 2118726316
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
	const UECodeGen_Private::FBytePropertyParams Z_Construct_UClass_UQuickActorActionsWidget_Statics::NewProp_SearchCase = { "SearchCase", nullptr, (EPropertyFlags)0x0020080000000005, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(UQuickActorActionsWidget, SearchCase), Z_Construct_UEnum_CoreUObject_ESearchCase, METADATA_PARAMS(Z_Construct_UClass_UQuickActorActionsWidget_Statics::NewProp_SearchCase_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UQuickActorActionsWidget_Statics::NewProp_SearchCase_MetaData)) }; // 1578437248
	const UECodeGen_Private::FBytePropertyParams Z_Construct_UClass_UQuickActorActionsWidget_Statics::NewProp_AxisForDuplication_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, 0, nullptr, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UQuickActorActionsWidget_Statics::NewProp_AxisForDuplication_MetaData[] = {
		{ "Category", "ActorBatchSelection" },
		{ "ModuleRelativePath", "Public/ActorActions/QuickActorActionsWidget.h" },
	};
#endif
	const UECodeGen_Private::FEnumPropertyParams Z_Construct_UClass_UQuickActorActionsWidget_Statics::NewProp_AxisForDuplication = { "AxisForDuplication", nullptr, (EPropertyFlags)0x0020080000000005, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(UQuickActorActionsWidget, AxisForDuplication), Z_Construct_UEnum_SuperManager_E_DuplicationAxis, METADATA_PARAMS(Z_Construct_UClass_UQuickActorActionsWidget_Statics::NewProp_AxisForDuplication_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UQuickActorActionsWidget_Statics::NewProp_AxisForDuplication_MetaData)) }; // 2179350869
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UQuickActorActionsWidget_Statics::NewProp_NumberOfDuplicates_MetaData[] = {
		{ "Category", "ActorBatchSelection" },
		{ "ModuleRelativePath", "Public/ActorActions/QuickActorActionsWidget.h" },
	};
#endif
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UClass_UQuickActorActionsWidget_Statics::NewProp_NumberOfDuplicates = { "NumberOfDuplicates", nullptr, (EPropertyFlags)0x0020080000000005, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(UQuickActorActionsWidget, NumberOfDuplicates), METADATA_PARAMS(Z_Construct_UClass_UQuickActorActionsWidget_Statics::NewProp_NumberOfDuplicates_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UQuickActorActionsWidget_Statics::NewProp_NumberOfDuplicates_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UQuickActorActionsWidget_Statics::NewProp_OffsetDiff_MetaData[] = {
		{ "Category", "ActorBatchSelection" },
		{ "ModuleRelativePath", "Public/ActorActions/QuickActorActionsWidget.h" },
	};
#endif
	const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UQuickActorActionsWidget_Statics::NewProp_OffsetDiff = { "OffsetDiff", nullptr, (EPropertyFlags)0x0020080000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(UQuickActorActionsWidget, OffsetDiff), METADATA_PARAMS(Z_Construct_UClass_UQuickActorActionsWidget_Statics::NewProp_OffsetDiff_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UQuickActorActionsWidget_Statics::NewProp_OffsetDiff_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UQuickActorActionsWidget_Statics::NewProp_EditorActorSubsystem_MetaData[] = {
		{ "ModuleRelativePath", "Public/ActorActions/QuickActorActionsWidget.h" },
	};
#endif
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UQuickActorActionsWidget_Statics::NewProp_EditorActorSubsystem = { "EditorActorSubsystem", nullptr, (EPropertyFlags)0x0040000000000000, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(UQuickActorActionsWidget, EditorActorSubsystem), Z_Construct_UClass_UEditorActorSubsystem_NoRegister, METADATA_PARAMS(Z_Construct_UClass_UQuickActorActionsWidget_Statics::NewProp_EditorActorSubsystem_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UQuickActorActionsWidget_Statics::NewProp_EditorActorSubsystem_MetaData)) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UQuickActorActionsWidget_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UQuickActorActionsWidget_Statics::NewProp_SearchCase,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UQuickActorActionsWidget_Statics::NewProp_AxisForDuplication_Underlying,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UQuickActorActionsWidget_Statics::NewProp_AxisForDuplication,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UQuickActorActionsWidget_Statics::NewProp_NumberOfDuplicates,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UQuickActorActionsWidget_Statics::NewProp_OffsetDiff,
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
		static const FEnumRegisterCompiledInInfo EnumInfo[];
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FEnumRegisterCompiledInInfo Z_CompiledInDeferFile_FID_ExtendEditor_Plugins_SuperManager_Source_SuperManager_Public_ActorActions_QuickActorActionsWidget_h_Statics::EnumInfo[] = {
		{ E_DuplicationAxis_StaticEnum, TEXT("E_DuplicationAxis"), &Z_Registration_Info_UEnum_E_DuplicationAxis, CONSTRUCT_RELOAD_VERSION_INFO(FEnumReloadVersionInfo, 2179350869U) },
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_ExtendEditor_Plugins_SuperManager_Source_SuperManager_Public_ActorActions_QuickActorActionsWidget_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_UQuickActorActionsWidget, UQuickActorActionsWidget::StaticClass, TEXT("UQuickActorActionsWidget"), &Z_Registration_Info_UClass_UQuickActorActionsWidget, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UQuickActorActionsWidget), 101777620U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_ExtendEditor_Plugins_SuperManager_Source_SuperManager_Public_ActorActions_QuickActorActionsWidget_h_1251111554(TEXT("/Script/SuperManager"),
		Z_CompiledInDeferFile_FID_ExtendEditor_Plugins_SuperManager_Source_SuperManager_Public_ActorActions_QuickActorActionsWidget_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_ExtendEditor_Plugins_SuperManager_Source_SuperManager_Public_ActorActions_QuickActorActionsWidget_h_Statics::ClassInfo),
		nullptr, 0,
		Z_CompiledInDeferFile_FID_ExtendEditor_Plugins_SuperManager_Source_SuperManager_Public_ActorActions_QuickActorActionsWidget_h_Statics::EnumInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_ExtendEditor_Plugins_SuperManager_Source_SuperManager_Public_ActorActions_QuickActorActionsWidget_h_Statics::EnumInfo));
PRAGMA_ENABLE_DEPRECATION_WARNINGS
