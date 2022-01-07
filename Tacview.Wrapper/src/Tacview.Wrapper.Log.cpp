/*
	Tacview.Wrapper.Log
	Tacview API wrapper
	Version 1.7.3 // 2018-10-04
	Copyright (C) 2018 Raia Software. All rights reserved.

	NOTE: You need a licence of Tacview Enterprise to run C# addons.
*/

#include "Tacview.Wrapper.Headers.h"
#include "Tacview.Wrapper.h"

namespace TacviewSDK
{
	Wrapper::LogClass::LogClass(void * newAddonHandle, TacviewSDK::Interface187 * newTacviewInterface) :
		addonHandle(newAddonHandle),
		tacviewInterface(newTacviewInterface)
	{
	}

	void Wrapper::LogClass::Debug(System::String ^ _text)
	{
		pin_ptr<const wchar_t> text = PtrToStringChars(_text);
		tacviewInterface->LogDebug(addonHandle, text);
	}

	void Wrapper::LogClass::Info(System::String ^ _text)
	{
		pin_ptr<const wchar_t> text = PtrToStringChars(_text);
		tacviewInterface->LogInfo(addonHandle, text);
	}

	void Wrapper::LogClass::Warning(System::String ^ _text)
	{
		pin_ptr<const wchar_t> text = PtrToStringChars(_text);
		tacviewInterface->LogWarning(addonHandle, text);
	}

	void Wrapper::LogClass::Error(System::String ^ _text)
	{
		pin_ptr<const wchar_t> text = PtrToStringChars(_text);
		tacviewInterface->LogError(addonHandle, text);
	}
}
