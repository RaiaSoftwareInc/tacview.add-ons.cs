/*
	Tacview.Wrapper.MEdia
	Tacview API wrapper
	Version 1.8.5 // 2020-09-29
	Copyright (C) 2018-2021 Raia Software. All rights reserved.

	NOTE: You need a licence of Tacview Enterprise to run C# addons.
*/

#include "Tacview.Wrapper.Headers.h"
#include "Tacview.Wrapper.h"

namespace TacviewSDK
{
	// Angle

	Wrapper::MediaClass::MediaClass(void * newAddonHandle, TacviewSDK::Interface187 * newTacviewInterface) :
		addonHandle(newAddonHandle),
		tacviewInterface(newTacviewInterface)
	{
	}

	bool Wrapper::MediaClass::Load(int playerId, System::String ^ _fileName)
	{
		pin_ptr<const wchar_t> fileName = PtrToStringChars(_fileName);
		return tacviewInterface->MediaLoad(addonHandle, playerId, fileName);
	}

	bool Wrapper::MediaClass::Load(int playerId, System::String ^ _fileName, double absoluteTime)
	{
		pin_ptr<const wchar_t> fileName = PtrToStringChars(_fileName);
		return tacviewInterface->MediaLoad2(addonHandle, playerId, fileName, absoluteTime);
	}

	bool Wrapper::MediaClass::Unload(int playerId)
	{
		return tacviewInterface->MediaUnload(addonHandle, playerId);
	}

	bool Wrapper::MediaClass::Close(int playerId)
	{
		return tacviewInterface->MediaClose(addonHandle, playerId);
	}
}
