/*
	Tacview.Wrapper.Settings
	Tacview API wrapper
	Version 1.7.3 // 2018-10-04
	Copyright (C) 2018 Raia Software. All rights reserved.

	NOTE: You need a licence of Tacview Enterprise to run C# addons.
*/

#include "Tacview.Wrapper.Headers.h"
#include "Tacview.Wrapper.h"

namespace TacviewSDK
{
	Wrapper::SettingsClass::SettingsClass(void * newAddonHandle, TacviewSDK::Interface187 * newTacviewInterface) :
		addonHandle(newAddonHandle),
		tacviewInterface(newTacviewInterface)
	{
	}

	bool Wrapper::SettingsClass::GetBoolean(System::String ^ _settingPath)
	{
		pin_ptr<const wchar_t> settingPath = PtrToStringChars(_settingPath);
		return tacviewInterface->SettingsGetBoolean(addonHandle, settingPath);
	}

	void Wrapper::SettingsClass::SetBoolean(System::String ^ _settingPath, bool value)
	{
		pin_ptr<const wchar_t> settingPath = PtrToStringChars(_settingPath);
		tacviewInterface->SettingsSetBoolean(addonHandle, settingPath, value);
	}

	double Wrapper::SettingsClass::GetNumber(System::String ^ _settingPath)
	{
		pin_ptr<const wchar_t> settingPath = PtrToStringChars(_settingPath);
		return tacviewInterface->SettingsGetNumber(addonHandle, settingPath);
	}

	void Wrapper::SettingsClass::SetNumber(System::String ^ _settingPath, double value)
	{
		pin_ptr<const wchar_t> settingPath = PtrToStringChars(_settingPath);
		tacviewInterface->SettingsSetNumber(addonHandle, settingPath, value);
	}

	String ^ Wrapper::SettingsClass::GetString(System::String ^ _settingPath)
	{
		pin_ptr<const wchar_t> settingPath = PtrToStringChars(_settingPath);

		wchar_t valueBuffer[4096];
		static constexpr size_t valueBufferSize = _countof(valueBuffer);

		tacviewInterface->SettingsGetString(addonHandle, settingPath, valueBuffer, valueBufferSize);

		return gcnew System::String(valueBuffer);
	}

	void Wrapper::SettingsClass::SetString(System::String ^ _settingPath, System::String ^ _value)
	{
		pin_ptr<const wchar_t> settingPath = PtrToStringChars(_settingPath);
		pin_ptr<const wchar_t> value = PtrToStringChars(_value);

		tacviewInterface->SettingsSetString(addonHandle, settingPath, value);
	}

	Unit Wrapper::SettingsClass::GetAltitudeUnit()
	{
		return tacviewInterface->SettingsGetAltitudeUnit(addonHandle);
	}
}
