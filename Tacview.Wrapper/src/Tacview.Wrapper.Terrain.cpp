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
	Wrapper::TerrainClass::TerrainClass(void * newAddonHandle, TacviewSDK::Interface187 * newTacviewInterface) :
		addonHandle(newAddonHandle),
		tacviewInterface(newTacviewInterface)
	{
	}

	float Wrapper::TerrainClass::GetElevation(double longitude, double latitude)
	{
		return tacviewInterface->TerrainGetElevation(addonHandle, longitude, latitude);
	}

	void Wrapper::TerrainClass::AddCustomTexture(System::String ^ _textureId, System::String ^ _layerId, System::String ^ _fileName, System::String ^ _filter, double topLeftLongitude, double topLeftLatitude, double topRightLongitude, double topRightLatitude, double bottomRightLongitude, double bottomRightLatitude, double bottomLeftLongitude, double bottomLeftLatitude)
	{
		pin_ptr<const wchar_t> textureId = PtrToStringChars(_textureId);
		pin_ptr<const wchar_t> layerId = PtrToStringChars(_layerId);
		pin_ptr<const wchar_t> fileName = PtrToStringChars(_fileName);
		pin_ptr<const wchar_t> filter = PtrToStringChars(_filter);

		tacviewInterface->TerrainAddCustomTexture(addonHandle, textureId, layerId, fileName, filter, topLeftLongitude, topLeftLatitude, topRightLongitude, topRightLatitude, bottomRightLongitude, bottomRightLatitude, bottomLeftLongitude, bottomLeftLatitude);
	}

	void Wrapper::TerrainClass::ShowCustomTexture(System::String ^ _textureId)
	{
		pin_ptr<const wchar_t> textureId = PtrToStringChars(_textureId);
		tacviewInterface->TerrainShowCustomTexture(addonHandle, textureId);
	}

	void Wrapper::TerrainClass::HideCustomTexture(System::String ^ _textureId)
	{
		pin_ptr<const wchar_t> textureId = PtrToStringChars(_textureId);
		tacviewInterface->TerrainHideCustomTexture(addonHandle, textureId);
	}
}
