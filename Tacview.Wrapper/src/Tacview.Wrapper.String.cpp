/*
	Tacview.Wrapper.String
	Tacview API wrapper
	Version 1.8.5 // 2020-09-30
	Copyright (C) 2018-2021 Raia Software. All rights reserved.

	NOTE: You need a licence of Tacview Enterprise to run C# addons.
*/

#include "Tacview.Wrapper.Headers.h"
#include "Tacview.Wrapper.h"

namespace TacviewSDK
{
	// String

	Wrapper::StringClass::StringClass(void * newAddonHandle, TacviewSDK::Interface187 * newTacviewInterface) :
		addonHandle(newAddonHandle),
		tacviewInterface(newTacviewInterface)
	{
	}

	unsigned Wrapper::StringClass::Crc32(System::String ^ _text)
	{
		pin_ptr<const wchar_t> text = PtrToStringChars(_text);
		return tacviewInterface->StringCrc32(addonHandle, text);
	}
}
