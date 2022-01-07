/*
	Tacview.Wrapper.Context
	Tacview API wrapper
	Version 1.7.3 // 2018-10-04
	Copyright (C) 2018 Raia Software. All rights reserved.

	NOTE: You need a licence of Tacview Enterprise to run C# addons.
*/

#include "Tacview.Wrapper.Headers.h"
#include "Tacview.Wrapper.h"

namespace TacviewSDK
{
	// Tacview.Context.Camera

	Wrapper::ContextClass::CameraClass::CameraClass(void * newAddonHandle, TacviewSDK::Interface187 * newTacviewInterface) :
		addonHandle(newAddonHandle),
		tacviewInterface(newTacviewInterface)
	{
	}

	Wrapper::ContextClass::CameraClass::Mode Wrapper::ContextClass::CameraClass::GetMode()
	{
		return static_cast<Wrapper::ContextClass::CameraClass::Mode>(tacviewInterface->ContextCameraGetMode(addonHandle));
	}

	void Wrapper::ContextClass::CameraClass::SetOffset(CameraOffset ^ _newCameraOffset)
	{
		TacviewSDK::CameraOffset newCameraOffset = { 0 };

		newCameraOffset.lateral = _newCameraOffset->lateral;
		newCameraOffset.longitudinal = _newCameraOffset->longitudinal;
		newCameraOffset.vertical = _newCameraOffset->vertical;
		newCameraOffset.roll = _newCameraOffset->roll;
		newCameraOffset.pitch = _newCameraOffset->pitch;
		newCameraOffset.yaw = _newCameraOffset->yaw;

		tacviewInterface->ContextCameraSetOffset(addonHandle, &newCameraOffset);
	}

	void Wrapper::ContextClass::CameraClass::SetFieldOfView(float vecticalFieldOfViewInRadian)
	{
		tacviewInterface->ContextCameraSetFieldOfView(addonHandle, vecticalFieldOfViewInRadian);
	}

	// Tacview.Context.Camera.GetSphericalPosition

	void Wrapper::ContextClass::CameraClass::GetSphericalPosition([Out] double % _longitude, [Out] double % _latitude, [Out]  double % _altitude)
	{
		double longitude = 0.0;
		double latitude = 0.0;
		double altitude = 0.0;

		tacviewInterface->ContextCameraGetSphericalPosition(addonHandle, longitude, latitude, altitude);

		_longitude = longitude;
		_latitude = latitude;
		_altitude = altitude;
	}

	// Tacview.Context.Camera.SetRotation

	void Wrapper::ContextClass::CameraClass::SetRotation(float roll, float pitch, float yaw)
	{
		tacviewInterface->ContextCameraSetRotation(addonHandle, roll, pitch, yaw);
	}

	// Tacview.Context.Camera.SetRangeToTarget

	void Wrapper::ContextClass::CameraClass::SetRangeToTarget(double range)
	{
		tacviewInterface->ContextCameraSetRangeToTarget(addonHandle, range);
	}

	// Tacview.Context.Playback

	Wrapper::ContextClass::PlaybackClass::PlaybackClass(void * newAddonHandle, TacviewSDK::Interface187 * newTacviewInterface) :
		addonHandle(newAddonHandle),
		tacviewInterface(newTacviewInterface)
	{
	}

	void Wrapper::ContextClass::PlaybackClass::Play()
	{
		tacviewInterface->ContextPlaybackPlay(addonHandle);
	}

	void Wrapper::ContextClass::PlaybackClass::Pause()
	{
		tacviewInterface->ContextPlaybackPause(addonHandle);
	}

	bool Wrapper::ContextClass::PlaybackClass::IsPlaying()
	{
		return tacviewInterface->ContextPlaybackIsPlaying(addonHandle);
	}

	// Tacview.Context

	Wrapper::ContextClass::ContextClass(void * newAddonHandle, TacviewSDK::Interface187 * newTacviewInterface) :
		addonHandle(newAddonHandle),
		tacviewInterface(newTacviewInterface)
	{
		Camera = gcnew CameraClass(newAddonHandle, newTacviewInterface);
		Playback = gcnew PlaybackClass(newAddonHandle, newTacviewInterface);
	}

	double Wrapper::ContextClass::GetAbsoluteTime()
	{
		return tacviewInterface->ContextGetAbsoluteTime(addonHandle);
	}

	void Wrapper::ContextClass::SetAbsoluteTime(double absoluteTime)
	{
		tacviewInterface->ContextSetAbsoluteTime(addonHandle, absoluteTime);
	}

	Wrapper::ObjectHandle Wrapper::ContextClass::GetSelectedObject(int objectIndex)
	{
		return static_cast<Wrapper::ObjectHandle>(tacviewInterface->ContextGetSelectedObject(addonHandle, objectIndex));
	}

	void Wrapper::ContextClass::SetSelectedObject(int objectIndex, ObjectHandle objectHandle)
	{
		tacviewInterface->ContextSetSelectedObject(addonHandle, objectIndex, static_cast<TacviewSDK::ObjectHandle>(objectHandle));
	}

	List<Wrapper::ObjectHandle> ^ Wrapper::ContextClass::GetActiveObjectList()
	{
		TacviewSDK::ObjectHandle objectList[4096];
		static constexpr size_t objectListMaxCount = _countof(objectList);

		const size_t totalObjectCount = tacviewInterface->ContextGetActiveObjectList(addonHandle, objectList, objectListMaxCount);
		const size_t objectCount = std::min(totalObjectCount, objectListMaxCount);

		List<Wrapper::ObjectHandle> ^ gcList = gcnew List<Wrapper::ObjectHandle>(static_cast<int>(objectCount));

		for (size_t objectIndex = 0; objectIndex < objectCount; ++objectIndex)
		{
			gcList->Add(safe_cast<Wrapper::ObjectHandle>(objectList[objectIndex]));
		}

		return gcList;
	}

	String ^ Wrapper::ContextClass::GetDocumentPath()
	{
		wchar_t buffer[4096];
		static constexpr size_t bufferSize = _countof(buffer);

		tacviewInterface->ContextGetDocumentPath(addonHandle, buffer, bufferSize);

		return gcnew System::String(buffer);
	}
}
