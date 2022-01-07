/*
	Tacview.Wrapper.AddOns
	Tacview API wrapper
	Version 1.7.3 // 2018-10-04
	Copyright (C) 2018 Raia Software. All rights reserved.

	NOTE: You need a licence of Tacview Enterprise to run C# addons.
*/

#include "Tacview.Wrapper.Headers.h"
#include "Tacview.Wrapper.h"

namespace TacviewSDK
{
	Wrapper::AddOnsClass::CurrentClass::SettingsClass::SettingsClass(void * newAddonHandle, TacviewSDK::Interface187 * newTacviewInterface) :
		addonHandle(newAddonHandle),
		tacviewInterface(newTacviewInterface)
	{
	}

	// AddOns.Current.Settings.GetBoolean

	bool Wrapper::AddOnsClass::CurrentClass::SettingsClass::GetBoolean(System::String ^ _settingName, bool defaultSettingValue)
	{
		pin_ptr<const wchar_t> settingName = PtrToStringChars(_settingName);
		return tacviewInterface->AddOnsCurrentSettingsGetBoolean(addonHandle, settingName, defaultSettingValue);
	}

	// AddOns.Current.Settings.SetBoolean

	void Wrapper::AddOnsClass::CurrentClass::SettingsClass::SetBoolean(System::String ^ _settingName, bool settingValue)
	{
		pin_ptr<const wchar_t> settingName = PtrToStringChars(_settingName);
		tacviewInterface->AddOnsCurrentSettingsSetBoolean(addonHandle, settingName, settingValue);
	}

	// AddOns.Current.Settings.GetString

	String ^ Wrapper::AddOnsClass::CurrentClass::SettingsClass::GetString(System::String ^ _settingName, System::String ^ _defaultSettingValue)
	{
		pin_ptr<const wchar_t> settingPath = PtrToStringChars(_settingName);
		pin_ptr<const wchar_t> defaultSettingValue = PtrToStringChars(_defaultSettingValue);

		wchar_t valueBuffer[4096];
		static constexpr size_t valueBufferSize = _countof(valueBuffer);

		tacviewInterface->AddOnsCurrentSettingsGetString(addonHandle, settingPath, valueBuffer, valueBufferSize, defaultSettingValue);

		return gcnew System::String(valueBuffer);
	}

	// AddOns.Current.Settings.SetString

	void Wrapper::AddOnsClass::CurrentClass::SettingsClass::SetString(System::String ^ _settingName, System::String ^ _settingValue)
	{
		pin_ptr<const wchar_t> settingName = PtrToStringChars(_settingName);
		pin_ptr<const wchar_t> settingValue = PtrToStringChars(_settingValue);

		tacviewInterface->AddOnsCurrentSettingsSetString(addonHandle, settingName, settingValue);
	}

	Wrapper::AddOnsClass::CurrentClass::CurrentClass(void * newAddonHandle, TacviewSDK::Interface187 * newTacviewInterface) :
		addonHandle(newAddonHandle),
		tacviewInterface(newTacviewInterface)
	{
		Settings = gcnew SettingsClass(newAddonHandle, newTacviewInterface);
	}

	String ^ Wrapper::AddOnsClass::CurrentClass::GetPath()
	{
		wchar_t valueBuffer[4096];
		static constexpr size_t valueBufferSize = _countof(valueBuffer);

		tacviewInterface->AddOnsCurrentGetPath(addonHandle, valueBuffer, valueBufferSize);

		return gcnew System::String(valueBuffer);
	}

	void Wrapper::AddOnsClass::CurrentClass::SetTitle(System::String ^ _addonTitle)
	{
		pin_ptr<const wchar_t> addonTitle = PtrToStringChars(_addonTitle);
		tacviewInterface->AddOnsCurrentSetTitle(addonHandle, addonTitle);
	}

	void Wrapper::AddOnsClass::CurrentClass::SetVersion(System::String ^ _addonVersion)
	{
		pin_ptr<const wchar_t> addonVersion = PtrToStringChars(_addonVersion);
		tacviewInterface->AddOnsCurrentSetVersion(addonHandle, addonVersion);
	}

	void Wrapper::AddOnsClass::CurrentClass::SetAuthor(System::String ^ _addonAuthor)
	{
		pin_ptr<const wchar_t> addonAuthor = PtrToStringChars(_addonAuthor);
		tacviewInterface->AddOnsCurrentSetAuthor(addonHandle, addonAuthor);
	}

	void Wrapper::AddOnsClass::CurrentClass::SetNotes(System::String ^ _addonNotes)
	{
		pin_ptr<const wchar_t> addonNotes = PtrToStringChars(_addonNotes);
		tacviewInterface->AddOnsCurrentSetNotes(addonHandle, addonNotes);
	}

	Wrapper::AddOnsClass::AddOnsClass(void * newAddonHandle, TacviewSDK::Interface187 * newTacviewInterface)
	{
		Current = gcnew CurrentClass(newAddonHandle, newTacviewInterface);
	}
}
