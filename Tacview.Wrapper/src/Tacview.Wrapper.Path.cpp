/*
	Tacview.Wrapper.Path
	Tools to manipulate files and directories path
	Version 1.8.7 // 2021-07-15
	Copyright (C) 2018-2021 Raia Software. All rights reserved.

	NOTE: You need a licence of Tacview Enterprise to run C# addons.
*/

#include "Tacview.Wrapper.Headers.h"
#include "Tacview.Wrapper.h"

namespace TacviewSDK
{
	// Tacview.Path

	Wrapper::PathClass::PathClass(void * newAddonHandle, TacviewSDK::Interface187 * newTacviewInterface) :
		addonHandle(newAddonHandle),
		tacviewInterface(newTacviewInterface)
	{
	}

	String ^ Wrapper::PathClass::GetDirectoryName(System::String ^ _path)
	{
		pin_ptr<const wchar_t> path = PtrToStringChars(_path);

		wchar_t buffer[4096];
		static constexpr size_t bufferSize = _countof(buffer);

		tacviewInterface->PathGetDirectoryName(addonHandle, path, buffer, bufferSize);

		return gcnew System::String(buffer);
	}

	String ^ Wrapper::PathClass::GetFileName(System::String ^ _path)
	{
		pin_ptr<const wchar_t> path = PtrToStringChars(_path);

		wchar_t buffer[4096];
		static constexpr size_t bufferSize = _countof(buffer);

		tacviewInterface->PathGetFileName(addonHandle, path, buffer, bufferSize);

		return gcnew System::String(buffer);
	}
}
