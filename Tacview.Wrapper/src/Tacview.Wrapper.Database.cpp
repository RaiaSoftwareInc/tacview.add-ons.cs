/*
	Tacview.Wrapper.Database
	Tacview API wrapper
	Version 1.8.2 // 2019-12-10
	Copyright (C) 2019 Raia Software. All rights reserved.

	NOTE: You need a licence of Tacview Enterprise to run C# addons.
*/

#include "Tacview.Wrapper.Headers.h"
#include "Tacview.Wrapper.h"

namespace TacviewSDK
{
	static constexpr size_t maxTextBufferSize = 4 * 1024;

	// Constructor

	Wrapper::DatabaseClass::DatabaseClass(void * newAddonHandle, TacviewSDK::Interface187 * newTacviewInterface) :
		addonHandle(newAddonHandle),
		tacviewInterface(newTacviewInterface)
	{
	}

	// Tacview.Database.GetNextRecord()

	Wrapper::RecordHandle Wrapper::DatabaseClass::GetNextRecord(RecordHandle currentRecordHandle, System::String ^ _tags)
	{
		pin_ptr<const wchar_t> tags = PtrToStringChars(_tags);
		return (Wrapper::RecordHandle)tacviewInterface->DatabaseGetNextRecord(addonHandle, static_cast<TacviewSDK::RecordHandle>(currentRecordHandle), tags);
	}

	// Tacview.Database.GetRecordId()

	bool Wrapper::DatabaseClass::GetRecordId(RecordHandle recordHandle, [Out] System::String ^% _id)
	{
		wchar_t buffer[maxTextBufferSize];

		bool result = tacviewInterface->DatabaseGetRecordId(addonHandle, static_cast<TacviewSDK::RecordHandle>(recordHandle), buffer, _countof(buffer));

		_id = gcnew System::String(buffer);

		return result;
	}

	// Tacview.Database.GetRecordPriority()

	float Wrapper::DatabaseClass::GetRecordPriority(RecordHandle recordHandle)
	{
		return tacviewInterface->DatabaseGetRecordPriority(addonHandle, static_cast<TacviewSDK::RecordHandle>(recordHandle));
	}

	// Tacview.Database.GetTextPropertyIndex()

	int Wrapper::DatabaseClass::GetTextPropertyIndex(System::String ^ _propertyName)
	{
		pin_ptr<const wchar_t> propertyName = PtrToStringChars(_propertyName);
		return static_cast<int>(tacviewInterface->DatabaseGetTextPropertyIndex(addonHandle, propertyName));
	}

	// Tacview.Database.GetRecordTextValue()

	bool Wrapper::DatabaseClass::GetRecordTextValue(RecordHandle recordHandle, int propertyIndex, [Out] System::String ^% _value)
	{
		wchar_t buffer[maxTextBufferSize];

		bool result = tacviewInterface->DatabaseGetRecordTextValue(addonHandle, static_cast<TacviewSDK::RecordHandle>(recordHandle), propertyIndex, buffer, _countof(buffer));

		_value = gcnew System::String(buffer);

		return result;
	}

	// Tacview.Database.GetNumericPropertyIndex()

	int Wrapper::DatabaseClass::GetNumericPropertyIndex(System::String ^ _propertyName)
	{
		pin_ptr<const wchar_t> propertyName = PtrToStringChars(_propertyName);
		return static_cast<int>(tacviewInterface->DatabaseGetNumericPropertyIndex(addonHandle, propertyName));
	}

	// Tacview.Database.GetRecordNumericValue()

	bool Wrapper::DatabaseClass::GetRecordNumericValue(RecordHandle recordHandle, int propertyIndex, [Out] double % _value)
	{
		double value;

		bool result = tacviewInterface->DatabaseGetRecordNumericValue(addonHandle, static_cast<TacviewSDK::RecordHandle>(recordHandle), propertyIndex, value);

		_value = value;

		return result;
	}

	// Tacview.Database.Reload()

	bool Wrapper::DatabaseClass::Reload()
	{
		return tacviewInterface->DatabaseReload(addonHandle);
	}
}
