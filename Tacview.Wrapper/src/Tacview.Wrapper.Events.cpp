/*
	Tacview.Wrapper.Log
	Tacview API wrapper
	Version 1.7.3 // 2018-09-13
	Copyright (C) 2018 Raia Software. All rights reserved.

	NOTE: You need a licence of Tacview Enterprise to run C# addons.
*/

#include "Tacview.Wrapper.Headers.h"
#include "Tacview.Wrapper.h"

namespace TacviewSDK
{
	// Events Interface

	Wrapper::EventsClass::EventsClass(void * newAddonHandle, TacviewSDK::Interface187 * newTacviewInterface)
	{
		Update = gcnew UpdateClass(newAddonHandle, newTacviewInterface);

		DrawOpaqueObjects = gcnew DrawOpaqueObjectsClass(newAddonHandle, newTacviewInterface);
		DrawTransparentObjects = gcnew DrawTransparentObjectsClass(newAddonHandle, newTacviewInterface);
		DrawTransparentObjectsNear = gcnew DrawTransparentObjectsNearClass(newAddonHandle, newTacviewInterface);
		DrawOpaqueUI = gcnew DrawOpaqueUIClass(newAddonHandle, newTacviewInterface);
		DrawTransparentUI = gcnew DrawTransparentUIClass(newAddonHandle, newTacviewInterface);

		DocumentLoaded = gcnew DocumentLoadedClass(newAddonHandle, newTacviewInterface);
		DocumentUnload = gcnew DocumentUnloadClass(newAddonHandle, newTacviewInterface);

		PowerSave = gcnew PowerSaveClass(newAddonHandle, newTacviewInterface);
	}

	// Update callback

	static void _cdecl UpdateEventHandler(void * userData, float dt, double absoluteTime)
	{
		Wrapper::EventsClass::UpdateClass ^ self = (Wrapper::EventsClass::UpdateClass^)GCHandle::FromIntPtr(IntPtr(userData)).Target;
		self->OnUpdate(dt, absoluteTime);
	}

	Wrapper::EventsClass::UpdateClass::UpdateClass(void * addonHandle, TacviewSDK::Interface187 * tacviewInterface)
	{
		selfHandle = GCHandle::Alloc(this);
		tacviewInterface->EventsUpdateRegisterListener(addonHandle, UpdateEventHandler, GCHandle::ToIntPtr(selfHandle).ToPointer());
	}

	Wrapper::EventsClass::UpdateClass::~UpdateClass()
	{
		selfHandle.Free();
	}

	// DrawOpaqueObjects callback

	static void _cdecl DrawOpaqueObjectsEventHandler(void * userData)
	{
		Wrapper::EventsClass::DrawOpaqueObjectsClass ^ self = (Wrapper::EventsClass::DrawOpaqueObjectsClass^)GCHandle::FromIntPtr(IntPtr(userData)).Target;
		self->OnDrawOpaqueObjects();
	}

	Wrapper::EventsClass::DrawOpaqueObjectsClass::DrawOpaqueObjectsClass(void * addonHandle, TacviewSDK::Interface187 * tacviewInterface)
	{
		selfHandle = GCHandle::Alloc(this);
		tacviewInterface->EventsDrawOpaqueObjectsRegisterListener(addonHandle, DrawOpaqueObjectsEventHandler, GCHandle::ToIntPtr(selfHandle).ToPointer());
	}

	Wrapper::EventsClass::DrawOpaqueObjectsClass::~DrawOpaqueObjectsClass()
	{
		selfHandle.Free();
	}

	// DrawTransparentObjects callback

	static void _cdecl DrawTransparentObjectsEventHandler(void * userData)
	{
		Wrapper::EventsClass::DrawTransparentObjectsClass ^ self = (Wrapper::EventsClass::DrawTransparentObjectsClass^)GCHandle::FromIntPtr(IntPtr(userData)).Target;
		self->OnDrawTransparentObjects();
	}

	Wrapper::EventsClass::DrawTransparentObjectsClass::DrawTransparentObjectsClass(void * addonHandle, TacviewSDK::Interface187 * tacviewInterface)
	{
		selfHandle = GCHandle::Alloc(this);
		tacviewInterface->EventsDrawTransparentObjectsRegisterListener(addonHandle, DrawTransparentObjectsEventHandler, GCHandle::ToIntPtr(selfHandle).ToPointer());
	}

	Wrapper::EventsClass::DrawTransparentObjectsClass::~DrawTransparentObjectsClass()
	{
		selfHandle.Free();
	}

	// DrawTransparentObjectsNear callback

	static void _cdecl DrawTransparentObjectsNearEventHandler(void * userData)
	{
		Wrapper::EventsClass::DrawTransparentObjectsNearClass ^ self = (Wrapper::EventsClass::DrawTransparentObjectsNearClass^)GCHandle::FromIntPtr(IntPtr(userData)).Target;
		self->OnDrawTransparentObjectsNear();
	}

	Wrapper::EventsClass::DrawTransparentObjectsNearClass::DrawTransparentObjectsNearClass(void * addonHandle, TacviewSDK::Interface187 * tacviewInterface)
	{
		selfHandle = GCHandle::Alloc(this);
		tacviewInterface->EventsDrawTransparentObjectsNearRegisterListener(addonHandle, DrawTransparentObjectsNearEventHandler, GCHandle::ToIntPtr(selfHandle).ToPointer());
	}

	Wrapper::EventsClass::DrawTransparentObjectsNearClass::~DrawTransparentObjectsNearClass()
	{
		selfHandle.Free();
	}

	// DrawOpaqueUI callback

	static void _cdecl DrawOpaqueUIEventHandler(void * userData)
	{
		Wrapper::EventsClass::DrawOpaqueUIClass ^ self = (Wrapper::EventsClass::DrawOpaqueUIClass^)GCHandle::FromIntPtr(IntPtr(userData)).Target;
		self->OnDrawOpaqueUI();
	}

	Wrapper::EventsClass::DrawOpaqueUIClass::DrawOpaqueUIClass(void * addonHandle, TacviewSDK::Interface187 * tacviewInterface)
	{
		selfHandle = GCHandle::Alloc(this);
		tacviewInterface->EventsDrawOpaqueUIRegisterListener(addonHandle, DrawOpaqueUIEventHandler, GCHandle::ToIntPtr(selfHandle).ToPointer());
	}

	Wrapper::EventsClass::DrawOpaqueUIClass::~DrawOpaqueUIClass()
	{
		selfHandle.Free();
	}

	// DrawTransparentUI callback

	static void _cdecl DrawTransparentUIEventHandler(void * userData)
	{
		Wrapper::EventsClass::DrawTransparentUIClass ^ self = (Wrapper::EventsClass::DrawTransparentUIClass^)GCHandle::FromIntPtr(IntPtr(userData)).Target;
		self->OnDrawTransparentUI();
	}

	Wrapper::EventsClass::DrawTransparentUIClass::DrawTransparentUIClass(void * addonHandle, TacviewSDK::Interface187 * tacviewInterface)
	{
		selfHandle = GCHandle::Alloc(this);
		tacviewInterface->EventsDrawTransparentUIRegisterListener(addonHandle, DrawTransparentUIEventHandler, GCHandle::ToIntPtr(selfHandle).ToPointer());
	}

	Wrapper::EventsClass::DrawTransparentUIClass::~DrawTransparentUIClass()
	{
		selfHandle.Free();
	}

	// DocumentLoaded callback

	static void _cdecl DocumentLoadedEventHandler(void * userData, const wchar_t * fileNames)
	{
		Wrapper::EventsClass::DocumentLoadedClass ^ self = (Wrapper::EventsClass::DocumentLoadedClass^)GCHandle::FromIntPtr(IntPtr(userData)).Target;
		self->OnDocumentLoaded(gcnew System::String(fileNames));
	}

	Wrapper::EventsClass::DocumentLoadedClass::DocumentLoadedClass(void * addonHandle, TacviewSDK::Interface187 * tacviewInterface)
	{
		selfHandle = GCHandle::Alloc(this);
		tacviewInterface->EventsDocumentLoadedRegisterListener2(addonHandle, DocumentLoadedEventHandler, GCHandle::ToIntPtr(selfHandle).ToPointer());
	}

	Wrapper::EventsClass::DocumentLoadedClass::~DocumentLoadedClass()
	{
		selfHandle.Free();
	}

	// DocumentUnload callback

	static void _cdecl DocumentUnloadEventHandler(void * userData)
	{
		Wrapper::EventsClass::DocumentUnloadClass ^ self = (Wrapper::EventsClass::DocumentUnloadClass^)GCHandle::FromIntPtr(IntPtr(userData)).Target;
		self->OnDocumentUnload();
	}

	Wrapper::EventsClass::DocumentUnloadClass::DocumentUnloadClass(void * addonHandle, TacviewSDK::Interface187 * tacviewInterface)
	{
		selfHandle = GCHandle::Alloc(this);
		tacviewInterface->EventsDocumentUnloadRegisterListener(addonHandle, DocumentUnloadEventHandler, GCHandle::ToIntPtr(selfHandle).ToPointer());
	}

	Wrapper::EventsClass::DocumentUnloadClass::~DocumentUnloadClass()
	{
		selfHandle.Free();
	}

	// PowerSave callback

	static bool _cdecl PowerSaveEventHandler(void * userData)
	{
		Wrapper::EventsClass::PowerSaveClass ^ self = (Wrapper::EventsClass::PowerSaveClass^)GCHandle::FromIntPtr(IntPtr(userData)).Target;
		return self->OnPowerSave();
	}

	Wrapper::EventsClass::PowerSaveClass::PowerSaveClass(void * addonHandle, TacviewSDK::Interface187 * tacviewInterface)
	{
		selfHandle = GCHandle::Alloc(this);
		tacviewInterface->EventsPowerSaveRegisterListener(addonHandle, PowerSaveEventHandler, GCHandle::ToIntPtr(selfHandle).ToPointer());
	}

	Wrapper::EventsClass::PowerSaveClass::~PowerSaveClass()
	{
		selfHandle.Free();
	}
}
