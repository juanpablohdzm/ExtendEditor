#include "Misc/MessageDialog.h"
#include "Widgets/Notifications/SNotificationList.h"
#include "Framework/Notifications/NotificationManager.h"

static void Print(const FString& Message, const FColor& Color)
{
	if(GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, Color, Message);
	}
}

static void PrintLog(const FString& Message)
{
	UE_LOG(LogTemp,Warning,TEXT("%s"),*Message);
}

static EAppReturnType::Type ShowMessageDialog(const FString& Message, const FText& Title, EAppMsgType::Type MessageType)
{
	return FMessageDialog::Open(MessageType, FText::FromString(Message), &Title);
}

static void ShowNotifyInfo(const FString& Message)
{
	FNotificationInfo NotifyInfo(FText::FromString(Message));
	NotifyInfo.bUseLargeFont = true;
	NotifyInfo.FadeOutDuration = 7.0f;

	FSlateNotificationManager::Get().AddNotification(NotifyInfo);
}