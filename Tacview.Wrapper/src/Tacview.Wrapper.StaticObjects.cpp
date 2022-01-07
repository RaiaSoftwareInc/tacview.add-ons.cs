/*
	Tacview.Wrapper.StaticObjects
	Tacview API wrapper
	Version 1.8.0 // 2018-05-28
	Copyright (C) 2018-2019 Raia Software. All rights reserved.

	NOTE: You need a licence of Tacview Enterprise to run C# addons.
*/

#include "Tacview.Wrapper.Headers.h"
#include "Tacview.Wrapper.h"

namespace TacviewSDK
{
	Wrapper::StaticObjectsClass::StaticObjectsClass(void * newAddonHandle, TacviewSDK::Interface187 * newTacviewInterface) :
		addonHandle(newAddonHandle),
		tacviewInterface(newTacviewInterface)
	{
	}

	Wrapper::StaticObjectHandle Wrapper::StaticObjectsClass::GetObjectHandleByName(System::String ^ _objectName)
	{
		pin_ptr<const wchar_t> objectName = PtrToStringChars(_objectName);
		return (Wrapper::StaticObjectHandle)tacviewInterface->StaticObjectsGetObjectHandleByName(addonHandle, objectName);
	}

	void Wrapper::StaticObjectsClass::SetVisible(StaticObjectHandle objectHandle, bool isVisible)
	{
		tacviewInterface->StaticObjectsSetVisible(addonHandle, static_cast<TacviewSDK::StaticObjectHandle>(objectHandle), isVisible);
	}
}
