/*
	Tacview.Wrapper.SoundPlayer
	Tacview API wrapper
	Version 1.8.4 // 2020-08-19
	Copyright (C) 2020 Raia Software. All rights reserved.

	NOTE: You need a licence of Tacview Enterprise to run C# addons.
*/

#include "Tacview.Wrapper.Headers.h"
#include "Tacview.Wrapper.h"

namespace TacviewSDK
{
	Wrapper::SoundPlayerClass::SoundPlayerClass(void * newAddonHandle, TacviewSDK::Interface187 * newTacviewInterface) :
		addonHandle(newAddonHandle),
		tacviewInterface(newTacviewInterface)
	{
	}

	void Wrapper::SoundPlayerClass::Play(System::String ^ _fileName)
	{
		pin_ptr<const wchar_t> fileName = PtrToStringChars(_fileName);
		tacviewInterface->SoundPlayerPlay(addonHandle, fileName);
	}

	void Wrapper::SoundPlayerClass::Stop()
	{
		tacviewInterface->SoundPlayerStop(addonHandle);
	}
}
