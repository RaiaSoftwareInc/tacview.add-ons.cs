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
	static constexpr size_t maxTextBufferSize = 4 * 1024;

	Wrapper::TelemetryClass::PropertyClass::PropertyClass()
	{
		Text = gcnew TextClass;
		Numeric = gcnew NumericClass;
	}

	Wrapper::TelemetryClass::TelemetryClass(void * newAddonHandle, TacviewSDK::Interface187 * newTacviewInterface) :
		addonHandle(newAddonHandle),
		tacviewInterface(newTacviewInterface)
	{
		Tags = gcnew TagsClass();
		TypeNames = gcnew TypeNamesClass();
		Property = gcnew PropertyClass();
	}

	// Telemetry.Clear

	void Wrapper::TelemetryClass::Clear()
	{
		tacviewInterface->TelemetryClear(addonHandle);
	}

	// Telemetry.Load

	bool Wrapper::TelemetryClass::Load(System::String ^ _fileName)
	{
		pin_ptr<const wchar_t> fileName = PtrToStringChars(_fileName);
		return tacviewInterface->TelemetryLoad(addonHandle, fileName);
	}

	bool Wrapper::TelemetryClass::IsEmpty()
	{
		return tacviewInterface->TelemetryIsEmpty(addonHandle);
	}

	bool Wrapper::TelemetryClass::IsLikeEmpty()
	{
		return tacviewInterface->TelemetryIsLikeEmpty(addonHandle);
	}

	void Wrapper::TelemetryClass::GetDataTimeRange([Out] double % _beginTime, [Out] double % _endTime)
	{
		double beginTime;
		double endTime;

		tacviewInterface->TelemetryGetDataTimeRange(addonHandle, beginTime, endTime);

		_beginTime = beginTime;
		_endTime = endTime;
	}

	void Wrapper::TelemetryClass::GetTransformTimeRange(ObjectHandle objectHandle, [Out] double % _beginTime, [Out] double % _endTime)
	{
		double beginTime;
		double endTime;

		tacviewInterface->TelemetryGetTransformTimeRange(addonHandle, static_cast<TacviewSDK::ObjectHandle>(objectHandle), beginTime, endTime);

		_beginTime = beginTime;
		_endTime = endTime;
	}

	Wrapper::ObjectHandle Wrapper::TelemetryClass::GetCurrentObjectHandle(ObjectId objectId)
	{
		return (Wrapper::ObjectHandle)tacviewInterface->TelemetryGetCurrentObjectHandle(addonHandle, objectId);
	}

	Wrapper::ObjectHandle Wrapper::TelemetryClass::GetObjectHandle(ObjectId objectId, double absoluteTime)
	{
		return (Wrapper::ObjectHandle)tacviewInterface->TelemetryGetObjectHandle(addonHandle, objectId, absoluteTime);
	}

	Wrapper::ObjectHandle Wrapper::TelemetryClass::GetCurrentOrCreateObjectHandle(ObjectId objectId)
	{
		return (Wrapper::ObjectHandle)tacviewInterface->TelemetryGetCurrentOrCreateObjectHandle(addonHandle, objectId);
	}

	Wrapper::ObjectHandle Wrapper::TelemetryClass::GetOrCreateObjectHandle(ObjectId objectId, double absoluteTime)
	{
		return (Wrapper::ObjectHandle)tacviewInterface->TelemetryGetOrCreateObjectHandle(addonHandle, objectId, absoluteTime);
	}

	int Wrapper::TelemetryClass::GetObjectCount()
	{
		return static_cast<int>(tacviewInterface->TelemetryGetObjectCount(addonHandle));
	}

	Wrapper::ObjectHandle Wrapper::TelemetryClass::GetObjectHandleByIndex(int objectIndex)
	{
		return (Wrapper::ObjectHandle)tacviewInterface->TelemetryGetObjectHandleByIndex(addonHandle, objectIndex);
	}

	Wrapper::ObjectId Wrapper::TelemetryClass::GetObjectId(ObjectHandle objectHandle)
	{
		return tacviewInterface->TelemetryGetObjectId(addonHandle, static_cast<TacviewSDK::ObjectHandle>(objectHandle));
	}

	void Wrapper::TelemetryClass::DeleteObject(ObjectHandle objectHandle)
	{
		tacviewInterface->TelemetryDeleteObject(addonHandle, static_cast<TacviewSDK::ObjectHandle>(objectHandle));
	}

	Wrapper::ObjectTags Wrapper::TelemetryClass::GetCurrentTags(ObjectHandle objectHandle)
	{
		return tacviewInterface->TelemetryGetCurrentTags(addonHandle, static_cast<TacviewSDK::ObjectHandle>(objectHandle));
	}

	bool Wrapper::TelemetryClass::AllGivenTagsActive(ObjectTags objectTags, ObjectTags activeTagsCombination)
	{
		return tacviewInterface->TelemetryAllGivenTagsActive(addonHandle, objectTags, activeTagsCombination);
	}

	bool Wrapper::TelemetryClass::AnyGivenTagActive(ObjectTags objectTags, ObjectTags activeTagsCombination)
	{
		return tacviewInterface->TelemetryAnyGivenTagActive(addonHandle, objectTags, activeTagsCombination);
	}

	void Wrapper::TelemetryClass::GetCurrentShortName(ObjectHandle objectHandle, [Out] System::String ^% _name)
	{
		wchar_t buffer[maxTextBufferSize];

		tacviewInterface->TelemetryGetCurrentShortName(addonHandle, static_cast<TacviewSDK::ObjectHandle>(objectHandle), buffer, _countof(buffer));

		_name = gcnew System::String(buffer);
	}

	bool Wrapper::TelemetryClass::GetCurrentTransform(ObjectHandle objectHandle, [Out] ObjectTransformOutput ^% _objectTransform)
	{
		TacviewSDK::ObjectTransformOutput sample = { 0 };

		bool result = tacviewInterface->TelemetryGetCurrentTransform(addonHandle, static_cast<TacviewSDK::ObjectHandle>(objectHandle), &sample);

		_objectTransform = gcnew ObjectTransformOutput;

		_objectTransform->absoluteTime = sample.absoluteTime;

		_objectTransform->x = sample.x;
		_objectTransform->y = sample.y;
		_objectTransform->z = sample.z;

		_objectTransform->longitude = sample.longitude;
		_objectTransform->latitude = sample.latitude;
		_objectTransform->altitude = sample.altitude;

		_objectTransform->roll = sample.roll;
		_objectTransform->pitch = sample.pitch;
		_objectTransform->yaw = sample.yaw;

		_objectTransform->u = sample.u;
		_objectTransform->v = sample.v;
		_objectTransform->heading = sample.heading;

		_objectTransform->rotationIsValid = sample.rotationIsValid;
		_objectTransform->nativeCoordinatesAreValid = sample.nativeCoordinatesAreValid;

		return result;
	}

	bool Wrapper::TelemetryClass::GetCurrentCalculatedTransform(ObjectHandle objectHandle, [Out] ObjectTransformOutput ^% _objectTransform)
	{
		TacviewSDK::ObjectTransformOutput sample = { 0 };

		bool result = tacviewInterface->TelemetryGetCurrentCalculatedTransform(addonHandle, static_cast<TacviewSDK::ObjectHandle>(objectHandle), &sample);

		_objectTransform = gcnew ObjectTransformOutput;

		_objectTransform->absoluteTime = sample.absoluteTime;

		_objectTransform->x = sample.x;
		_objectTransform->y = sample.y;
		_objectTransform->z = sample.z;

		_objectTransform->longitude = sample.longitude;
		_objectTransform->latitude = sample.latitude;
		_objectTransform->altitude = sample.altitude;

		_objectTransform->roll = sample.roll;
		_objectTransform->pitch = sample.pitch;
		_objectTransform->yaw = sample.yaw;

		_objectTransform->u = sample.u;
		_objectTransform->v = sample.v;
		_objectTransform->heading = sample.heading;

		_objectTransform->rotationIsValid = sample.rotationIsValid;
		_objectTransform->nativeCoordinatesAreValid = sample.nativeCoordinatesAreValid;

		return result;
	}

	bool Wrapper::TelemetryClass::GetCurrentAngleOfAttack(ObjectHandle objectHandle, [Out] double % _sampleValue)
	{
		double sampleValue;

		const bool result = tacviewInterface->TelemetryGetCurrentAngleOfAttack(addonHandle, static_cast<TacviewSDK::ObjectHandle>(objectHandle), sampleValue);
		_sampleValue = sampleValue;

		return result;
	}

	bool Wrapper::TelemetryClass::GetCurrentAngleOfSideslip(ObjectHandle objectHandle, [Out] double % _sampleValue)
	{
		double sampleValue;

		const bool result = tacviewInterface->TelemetryGetCurrentAngleOfSideslip(addonHandle, static_cast<TacviewSDK::ObjectHandle>(objectHandle), sampleValue);
		_sampleValue = sampleValue;

		return result;
	}

	bool Wrapper::TelemetryClass::GetVerticalGForce(ObjectHandle objectHandle, double absoluteTime, [Out] double % _sampleValue)
	{
		double sampleValue;

		const bool result = tacviewInterface->TelemetryGetVerticalGForce(addonHandle, static_cast<TacviewSDK::ObjectHandle>(objectHandle), absoluteTime, sampleValue);
		_sampleValue = sampleValue;

		return result;
	}

	bool Wrapper::TelemetryClass::GetCurrentVerticalGForce(ObjectHandle objectHandle, [Out] double % _sampleValue)
	{
		double sampleValue;

		const bool result = tacviewInterface->TelemetryGetCurrentVerticalGForce(addonHandle, static_cast<TacviewSDK::ObjectHandle>(objectHandle), sampleValue);
		_sampleValue = sampleValue;

		return result;
	}

	bool Wrapper::TelemetryClass::GetLateralForce(ObjectHandle objectHandle, double absoluteTime, [Out] double % _sampleValue)
	{
		double sampleValue;

		const bool result = tacviewInterface->TelemetryGetLateralGForce(addonHandle, static_cast<TacviewSDK::ObjectHandle>(objectHandle), absoluteTime, sampleValue);
		_sampleValue = sampleValue;

		return result;
	}

	bool Wrapper::TelemetryClass::GetCurrentLateralForce(ObjectHandle objectHandle, [Out] double % _sampleValue)
	{
		double sampleValue;

		const bool result = tacviewInterface->TelemetryGetCurrentLateralGForce(addonHandle, static_cast<TacviewSDK::ObjectHandle>(objectHandle), sampleValue);
		_sampleValue = sampleValue;

		return result;
	}

	bool Wrapper::TelemetryClass::GetLongitudinalForce(ObjectHandle objectHandle, double absoluteTime, [Out] double % _sampleValue)
	{
		double sampleValue;

		const bool result = tacviewInterface->TelemetryGetLongitudinalGForce(addonHandle, static_cast<TacviewSDK::ObjectHandle>(objectHandle), absoluteTime, sampleValue);
		_sampleValue = sampleValue;

		return result;
	}

	bool Wrapper::TelemetryClass::GetCurrentLongitudinalForce(ObjectHandle objectHandle, [Out] double % _sampleValue)
	{
		double sampleValue;

		const bool result = tacviewInterface->TelemetryGetCurrentLongitudinalGForce(addonHandle, static_cast<TacviewSDK::ObjectHandle>(objectHandle), sampleValue);
		_sampleValue = sampleValue;

		return result;
	}

	bool Wrapper::TelemetryClass::GetAbsoluteGForce(ObjectHandle objectHandle, double absoluteTime, [Out] double % _sampleValue)
	{
		double sampleValue;

		const bool result = tacviewInterface->TelemetryGetAbsoluteGForce(addonHandle, static_cast<TacviewSDK::ObjectHandle>(objectHandle), absoluteTime, sampleValue);
		_sampleValue = sampleValue;

		return result;
	}

	bool Wrapper::TelemetryClass::GetCurrentAbsoluteGForce(ObjectHandle objectHandle, [Out] double % _sampleValue)
	{
		double sampleValue;

		const bool result = tacviewInterface->TelemetryGetCurrentAbsoluteGForce(addonHandle, static_cast<TacviewSDK::ObjectHandle>(objectHandle), sampleValue);
		_sampleValue = sampleValue;

		return result;
	}

	bool Wrapper::TelemetryClass::GetInstantaneousTurnRadius(ObjectHandle objectHandle, double absoluteTime, [Out] double % _sampleValue)
	{
		double sampleValue;

		const bool result = tacviewInterface->TelemetryGetInstantaneousTurnRadius(addonHandle, static_cast<TacviewSDK::ObjectHandle>(objectHandle), absoluteTime, sampleValue);
		_sampleValue = sampleValue;

		return result;
	}

	bool Wrapper::TelemetryClass::GetTurnRadius(ObjectHandle objectHandle, double absoluteTime, double dt, [Out] double % _sampleValue)
	{
		double sampleValue;

		const bool result = tacviewInterface->TelemetryGetTurnRadius(addonHandle, static_cast<TacviewSDK::ObjectHandle>(objectHandle), absoluteTime, dt, sampleValue);
		_sampleValue = sampleValue;

		return result;
	}

	bool Wrapper::TelemetryClass::GetCurrentInstantaneousTurnRadius(ObjectHandle objectHandle, [Out] double % _sampleValue)
	{
		double sampleValue;

		const bool result = tacviewInterface->TelemetryGetCurrentInstantaneousTurnRadius(addonHandle, static_cast<TacviewSDK::ObjectHandle>(objectHandle), sampleValue);
		_sampleValue = sampleValue;

		return result;
	}

	bool Wrapper::TelemetryClass::GetCurrentTurnRadius(ObjectHandle objectHandle, double dt, [Out] double % _sampleValue)
	{
		double sampleValue;

		const bool result = tacviewInterface->TelemetryGetCurrentTurnRadius(addonHandle, static_cast<TacviewSDK::ObjectHandle>(objectHandle), dt, sampleValue);
		_sampleValue = sampleValue;

		return result;
	}

	bool Wrapper::TelemetryClass::GetInstantaneousTurnRate(ObjectHandle objectHandle, double absoluteTime, [Out] double % _sampleValue)
	{
		double sampleValue;

		const bool result = tacviewInterface->TelemetryGetInstantaneousTurnRate(addonHandle, static_cast<TacviewSDK::ObjectHandle>(objectHandle), absoluteTime, sampleValue);
		_sampleValue = sampleValue;

		return result;
	}

	bool Wrapper::TelemetryClass::GetTurnRate(ObjectHandle objectHandle, double absoluteTime, double dt, [Out] double % _sampleValue)
	{
		double sampleValue;

		const bool result = tacviewInterface->TelemetryGetTurnRate(addonHandle, static_cast<TacviewSDK::ObjectHandle>(objectHandle), absoluteTime, dt, sampleValue);
		_sampleValue = sampleValue;

		return result;
	}

	bool Wrapper::TelemetryClass::GetCurrentInstantaneousTurnRate(ObjectHandle objectHandle, [Out] double % _sampleValue)
	{
		double sampleValue;

		const bool result = tacviewInterface->TelemetryGetCurrentInstantaneousTurnRate(addonHandle, static_cast<TacviewSDK::ObjectHandle>(objectHandle), sampleValue);
		_sampleValue = sampleValue;

		return result;
	}

	bool Wrapper::TelemetryClass::GetCurrentTurnRate(ObjectHandle objectHandle, double dt, [Out] double % _sampleValue)
	{
		double sampleValue;

		const bool result = tacviewInterface->TelemetryGetCurrentTurnRate(addonHandle, static_cast<TacviewSDK::ObjectHandle>(objectHandle), dt, sampleValue);
		_sampleValue = sampleValue;

		return result;
	}

	bool Wrapper::TelemetryClass::GetMachNumber(ObjectHandle objectHandle, double absoluteTime, [Out] double % _sampleValue)
	{
		double sampleValue;

		const bool result = tacviewInterface->TelemetryGetMachNumber(addonHandle, static_cast<TacviewSDK::ObjectHandle>(objectHandle), absoluteTime, sampleValue);
		_sampleValue = sampleValue;

		return result;
	}

	bool Wrapper::TelemetryClass::GetCurrentMachNumber(ObjectHandle objectHandle, [Out] double % _sampleValue)
	{
		double sampleValue;

		const bool result = tacviewInterface->TelemetryGetCurrentMachNumber(addonHandle, static_cast<TacviewSDK::ObjectHandle>(objectHandle), sampleValue);
		_sampleValue = sampleValue;

		return result;
	}

	int Wrapper::TelemetryClass::GetGlobalNumericPropertyIndex(System::String ^ _propertyName, bool autoCreate)
	{
		pin_ptr<const wchar_t> propertyName = PtrToStringChars(_propertyName);
		return tacviewInterface->TelemetryGetGlobalNumericPropertyIndex(addonHandle, propertyName, autoCreate);
	}

	int Wrapper::TelemetryClass::GetGlobalTextPropertyIndex(System::String ^ _propertyName, bool autoCreate)
	{
		pin_ptr<const wchar_t> propertyName = PtrToStringChars(_propertyName);
		return tacviewInterface->TelemetryGetGlobalTextPropertyIndex(addonHandle, propertyName, autoCreate);
	}

	int Wrapper::TelemetryClass::GetObjectsNumericPropertyIndex(System::String ^ _propertyName, bool autoCreate)
	{
		pin_ptr<const wchar_t> propertyName = PtrToStringChars(_propertyName);
		return tacviewInterface->TelemetryGetObjectsNumericPropertyIndex(addonHandle, propertyName, autoCreate);
	}

	int Wrapper::TelemetryClass::GetObjectsTextPropertyIndex(System::String ^ _propertyName, bool autoCreate)
	{
		pin_ptr<const wchar_t> propertyName = PtrToStringChars(_propertyName);
		return tacviewInterface->TelemetryGetObjectsTextPropertyIndex(addonHandle, propertyName, autoCreate);
	}

	void Wrapper::TelemetryClass::GetLifeTime(ObjectHandle objectHandle, [Out] double % lifeTimeBegin, [Out] double % lifeTimeEnd)
	{
		double beginTime;
		double endTime;

		tacviewInterface->TelemetryGetLifeTime(addonHandle, static_cast<TacviewSDK::ObjectHandle>(objectHandle), beginTime, endTime);

		lifeTimeBegin = beginTime;
		lifeTimeEnd = endTime;
	}

	void Wrapper::TelemetryClass::SetLifeTimeEnd(ObjectHandle objectHandle, double absoluteTime)
	{
		tacviewInterface->TelemetrySetLifeTimeEnd(addonHandle, static_cast<TacviewSDK::ObjectHandle>(objectHandle), absoluteTime);
	}

	void Wrapper::TelemetryClass::SetNumericSample(ObjectHandle objectHandle, double absoluteTime, int propertyIndex, double value)
	{
		tacviewInterface->TelemetrySetNumericSample(addonHandle, static_cast<TacviewSDK::ObjectHandle>(objectHandle), absoluteTime, propertyIndex, value);
	}

	int Wrapper::TelemetryClass::GetNumericSampleCount(ObjectHandle objectHandle, int propertyIndex)
	{
		return (int)tacviewInterface->TelemetryGetNumericSampleCount(addonHandle, static_cast<TacviewSDK::ObjectHandle>(objectHandle), propertyIndex);
	}

	bool Wrapper::TelemetryClass::GetNumericSample(ObjectHandle objectHandle, double absoluteTime, int propertyIndex, [Out] double % value)
	{
		double sampleValue;

		bool result = tacviewInterface->TelemetryGetNumericSample(addonHandle, static_cast<TacviewSDK::ObjectHandle>(objectHandle), absoluteTime, propertyIndex, sampleValue);

		value = sampleValue;

		return result;
	}

	bool Wrapper::TelemetryClass::GetNumericSampleFromIndex(ObjectHandle objectHandle, int sampleIndex, int propertyIndex, [Out] double % _sampleTime, [Out] double % _sampleValue)
	{
		double sampleTime;
		double sampleValue;

		bool result = tacviewInterface->TelemetryGetNumericSampleFromIndex(addonHandle, static_cast<TacviewSDK::ObjectHandle>(objectHandle), sampleIndex, propertyIndex, sampleTime, sampleValue);

		_sampleTime = sampleTime;
		_sampleValue = sampleValue;

		return result;
	}

	bool Wrapper::TelemetryClass::RemoveNumericSample(ObjectHandle objectHandle, double absoluteTime, int propertyIndex)
	{
		return tacviewInterface->TelemetryRemoveNumericSample(addonHandle, static_cast<TacviewSDK::ObjectHandle>(objectHandle), absoluteTime, propertyIndex);
	}

	bool Wrapper::TelemetryClass::RemoveNumericSampleFromIndex(ObjectHandle objectHandle, int sampleIndex, int propertyIndex)
	{
		return tacviewInterface->TelemetryRemoveNumericSampleFromIndex(addonHandle, static_cast<TacviewSDK::ObjectHandle>(objectHandle), sampleIndex, propertyIndex);
	}

	void Wrapper::TelemetryClass::SetTextSample(ObjectHandle objectHandle, double absoluteTime, int propertyIndex, System::String ^ _value)
	{
		pin_ptr<const wchar_t> value = PtrToStringChars(_value);
		tacviewInterface->TelemetrySetTextSample(addonHandle, static_cast<TacviewSDK::ObjectHandle>(objectHandle), absoluteTime, propertyIndex, value);
	}

	int Wrapper::TelemetryClass::GetTextSampleCount(ObjectHandle objectHandle, int propertyIndex)
	{
		return (int)tacviewInterface->TelemetryGetTextSampleCount(addonHandle, static_cast<TacviewSDK::ObjectHandle>(objectHandle), propertyIndex);
	}

	bool Wrapper::TelemetryClass::GetTextSample(ObjectHandle objectHandle, double absoluteTime, int propertyIndex, [Out] System::String ^% _sampleValue)
	{
		wchar_t buffer[maxTextBufferSize];

		bool result = tacviewInterface->TelemetryGetTextSample(addonHandle, static_cast<TacviewSDK::ObjectHandle>(objectHandle), absoluteTime, propertyIndex, buffer, _countof(buffer));

		_sampleValue = gcnew System::String(buffer);

		return result;
	}

	bool Wrapper::TelemetryClass::GetTextSampleFromIndex(ObjectHandle objectHandle, int sampleIndex, int propertyIndex, [Out] double % _sampleTime, [Out] System::String ^% _sampleValue)
	{
		double sampleTime;
		wchar_t buffer[maxTextBufferSize];

		bool result = tacviewInterface->TelemetryGetTextSampleFromIndex(addonHandle, static_cast<TacviewSDK::ObjectHandle>(objectHandle), sampleIndex, propertyIndex, sampleTime, buffer, _countof(buffer));

		_sampleTime = sampleTime;
		_sampleValue = gcnew System::String(buffer);

		return result;
	}

	bool Wrapper::TelemetryClass::RemoveTextSample(ObjectHandle objectHandle, double absoluteTime, int propertyIndex)
	{
		return tacviewInterface->TelemetryRemoveTextSample(addonHandle, static_cast<TacviewSDK::ObjectHandle>(objectHandle), absoluteTime, propertyIndex);
	}

	bool Wrapper::TelemetryClass::RemoveTextSampleFromIndex(ObjectHandle objectHandle, int sampleIndex, int propertyIndex)
	{
		return tacviewInterface->TelemetryRemoveTextSampleFromIndex(addonHandle, static_cast<TacviewSDK::ObjectHandle>(objectHandle), sampleIndex, propertyIndex);
	}

	void Wrapper::TelemetryClass::SetTransform(ObjectHandle objectHandle, double absoluteTime, ObjectTransformInput ^ _transform)
	{
		TacviewSDK::ObjectTransformInput transform;

		transform.longitude = _transform->longitude;
		transform.latitude = _transform->latitude;
		transform.altitude = _transform->altitude;

		transform.roll = _transform->roll;
		transform.pitch = _transform->pitch;
		transform.yaw = _transform->yaw;

		transform.u = _transform->u;
		transform.v = _transform->v;
		transform.heading = _transform->heading;

		transform.flags = _transform->flags;

		tacviewInterface->TelemetrySetTransform(addonHandle, static_cast<TacviewSDK::ObjectHandle>(objectHandle), absoluteTime, &transform);
	}

	bool Wrapper::TelemetryClass::GetTransform(ObjectHandle objectHandle, double absoluteTime, [Out] ObjectTransformOutput ^% _objectTransform)
	{
		TacviewSDK::ObjectTransformOutput sample = { 0 };

		bool result = tacviewInterface->TelemetryGetTransform(addonHandle, static_cast<TacviewSDK::ObjectHandle>(objectHandle), absoluteTime, &sample);

		_objectTransform = gcnew ObjectTransformOutput;

		_objectTransform->absoluteTime = sample.absoluteTime;

		_objectTransform->x = sample.x;
		_objectTransform->y = sample.y;
		_objectTransform->z = sample.z;

		_objectTransform->longitude = sample.longitude;
		_objectTransform->latitude = sample.latitude;
		_objectTransform->altitude = sample.altitude;

		_objectTransform->roll = sample.roll;
		_objectTransform->pitch = sample.pitch;
		_objectTransform->yaw = sample.yaw;

		_objectTransform->u = sample.u;
		_objectTransform->v = sample.v;
		_objectTransform->heading = sample.heading;

		_objectTransform->rotationIsValid = sample.rotationIsValid;
		_objectTransform->nativeCoordinatesAreValid = sample.nativeCoordinatesAreValid;

		return result;
	}

	bool Wrapper::TelemetryClass::GetCalculatedTransform(ObjectHandle objectHandle, double absoluteTime, [Out] ObjectTransformOutput ^% _objectTransform)
	{
		TacviewSDK::ObjectTransformOutput sample = { 0 };

		bool result = tacviewInterface->TelemetryGetCalculatedTransform(addonHandle, static_cast<TacviewSDK::ObjectHandle>(objectHandle), absoluteTime, &sample);

		_objectTransform = gcnew ObjectTransformOutput;

		_objectTransform->absoluteTime = sample.absoluteTime;

		_objectTransform->x = sample.x;
		_objectTransform->y = sample.y;
		_objectTransform->z = sample.z;

		_objectTransform->longitude = sample.longitude;
		_objectTransform->latitude = sample.latitude;
		_objectTransform->altitude = sample.altitude;

		_objectTransform->roll = sample.roll;
		_objectTransform->pitch = sample.pitch;
		_objectTransform->yaw = sample.yaw;

		_objectTransform->u = sample.u;
		_objectTransform->v = sample.v;
		_objectTransform->heading = sample.heading;

		_objectTransform->rotationIsValid = sample.rotationIsValid;
		_objectTransform->nativeCoordinatesAreValid = sample.nativeCoordinatesAreValid;

		return result;
	}

	int Wrapper::TelemetryClass::GetTransformCount(ObjectHandle objectHandle)
	{
		return (int)tacviewInterface->TelemetryGetTransformCount(addonHandle, static_cast<TacviewSDK::ObjectHandle>(objectHandle));
	}

	bool Wrapper::TelemetryClass::GetTransformFromIndex(ObjectHandle objectHandle, int sampleIndex, [Out] ObjectTransformOutput ^% _objectTransform)
	{
		TacviewSDK::ObjectTransformOutput sample = { 0 };

		bool result = tacviewInterface->TelemetryGetTransformFromIndex(addonHandle, static_cast<TacviewSDK::ObjectHandle>(objectHandle), sampleIndex, &sample);

		_objectTransform = gcnew ObjectTransformOutput;

		_objectTransform->absoluteTime = sample.absoluteTime;

		_objectTransform->x = sample.x;
		_objectTransform->y = sample.y;
		_objectTransform->z = sample.z;

		_objectTransform->longitude = sample.longitude;
		_objectTransform->latitude = sample.latitude;
		_objectTransform->altitude = sample.altitude;

		_objectTransform->roll = sample.roll;
		_objectTransform->pitch = sample.pitch;
		_objectTransform->yaw = sample.yaw;

		_objectTransform->u = sample.u;
		_objectTransform->v = sample.v;
		_objectTransform->heading = sample.heading;

		_objectTransform->rotationIsValid = sample.rotationIsValid;
		_objectTransform->nativeCoordinatesAreValid = sample.nativeCoordinatesAreValid;

		return result;
	}

	bool Wrapper::TelemetryClass::RemoveTransformSample(ObjectHandle objectHandle, double absoluteTime)
	{
		return tacviewInterface->TelemetryRemoveTransformSample(addonHandle, static_cast<TacviewSDK::ObjectHandle>(objectHandle), absoluteTime);
	}

	bool Wrapper::TelemetryClass::RemoveTransformSampleFromIndex(ObjectHandle objectHandle, int sampleIndex)
	{
		return tacviewInterface->TelemetryRemoveTransformSampleFromIndex(addonHandle, static_cast<TacviewSDK::ObjectHandle>(objectHandle), sampleIndex);
	}

	// Adhoc loading

	bool Wrapper::TelemetryClass::OnLoadStart(bool mergeWithExistingData)
	{
		return tacviewInterface->TelemetryOnLoadStart(addonHandle, mergeWithExistingData);

	}

	void Wrapper::TelemetryClass::OnLoadEnd(System::String ^ _documentName)
	{
		pin_ptr<const wchar_t> documentName = PtrToStringChars(_documentName);
		tacviewInterface->TelemetryOnLoadEnd(addonHandle, documentName);
	}
}
