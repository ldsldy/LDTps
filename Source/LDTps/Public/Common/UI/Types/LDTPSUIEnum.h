#pragma once

UENUM(BlueprintType)
enum class EConfirmScreenType : uint8
{
	Ok,					 // 확인 버튼만 있는 팝업
	YesNo,				 // 예/아니오 버튼이 있는 팝업
	OKCancel,			 // 확인/취소 버튼이 있는 팝업	
	Unkown UMETA(Hidden)
};

UENUM(BlueprintType)
enum class EConfirmScreenButtonType : uint8
{
	Confirmed,				// 확인 버튼
	Cancelled,				// 취소 버튼
	Closed,					// 닫기 버튼
	Unkown UMETA(Hidden)
};

UENUM(BlueprintType)
enum class EOptionsListDataModifyReason : uint8
{
	DirectlyModified,	// 그대로 수정
	DependencyModified, // 의존성으로 인해 수정
	ResetToDefault,     // 기본값으로 초기화
};