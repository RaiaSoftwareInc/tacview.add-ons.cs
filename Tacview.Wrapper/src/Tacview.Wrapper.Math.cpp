/*
	Tacview.Wrapper.Math
	Tacview API wrapper
	Version 1.7.3 // 2018-10-04
	Copyright (C) 2018 Raia Software. All rights reserved.

	NOTE: You need a licence of Tacview Enterprise to run C# addons.
*/

#include "Tacview.Wrapper.Headers.h"
#include "Tacview.Wrapper.h"

namespace TacviewSDK
{
	// Angle

	Wrapper::MathClass::AngleClass::AngleClass(void * newAddonHandle, TacviewSDK::Interface187 * newTacviewInterface) :
		addonHandle(newAddonHandle),
		tacviewInterface(newTacviewInterface)
	{
	}

	float Wrapper::MathClass::AngleClass::Subtract(float angle1, float angle2)
	{
		return tacviewInterface->MathAngleSubtract(addonHandle, angle1, angle2);
	}

	double Wrapper::MathClass::AngleClass::Subtract(double angle1, double angle2)
	{
		return tacviewInterface->MathAngleSubtract2(addonHandle, angle1, angle2);
	}

	// Normalize

	float Wrapper::MathClass::AngleClass::NormalizePi(float angle)
	{
		return tacviewInterface->MathAngleNormalizePiFloat(addonHandle, angle);
	}

	double Wrapper::MathClass::AngleClass::NormalizePi(double angle)
	{
		return tacviewInterface->MathAngleNormalizePiDouble(addonHandle, angle);
	}

	float Wrapper::MathClass::AngleClass::Normalize2Pi(float angle)
	{
		return tacviewInterface->MathAngleNormalize2PiFloat(addonHandle, angle);
	}

	double Wrapper::MathClass::AngleClass::Normalize2Pi(double angle)
	{
		return tacviewInterface->MathAngleNormalize2PiDouble(addonHandle, angle);
	}

	// Vector

	Wrapper::MathClass::VectorClass::VectorClass(void * newAddonHandle, TacviewSDK::Interface187 * newTacviewInterface) :
		addonHandle(newAddonHandle),
		tacviewInterface(newTacviewInterface)
	{
	}

	Wrapper::double3 ^ Wrapper::MathClass::VectorClass::Add(double3 ^ _vec1, double3 ^ _vec2)
	{
		const TacviewSDK::double3 vec1 = { _vec1->x, _vec1->y, _vec1->z };
		const TacviewSDK::double3 vec2 = { _vec2->x, _vec2->y, _vec2->z };

		TacviewSDK::double3 result;

		tacviewInterface->MathVectorAdd(addonHandle, vec1, vec2, result);

		return gcnew Wrapper::double3(result.x, result.y, result.z);
	}

	Wrapper::double3 ^ Wrapper::MathClass::VectorClass::Subtract(double3 ^ _vec1, double3 ^ _vec2)
	{
		const TacviewSDK::double3 vec1 = { _vec1->x, _vec1->y, _vec1->z };
		const TacviewSDK::double3 vec2 = { _vec2->x, _vec2->y, _vec2->z };

		TacviewSDK::double3 result;

		tacviewInterface->MathVectorSubtract(addonHandle, vec1, vec2, result);

		return gcnew Wrapper::double3(result.x, result.y, result.z);
	}

	Wrapper::double3 ^ Wrapper::MathClass::VectorClass::Multiply(double factor, double3 ^ _vec)
	{
		const TacviewSDK::double3 vec = { _vec->x, _vec->y, _vec->z };

		TacviewSDK::double3 result;

		tacviewInterface->MathVectorMultiply(addonHandle, factor, vec, result);

		return gcnew Wrapper::double3(result.x, result.y, result.z);
	}

	Wrapper::double3 ^ Wrapper::MathClass::VectorClass::Normalize(double3 ^ _vec)
	{
		const TacviewSDK::double3 vec = { _vec->x, _vec->y, _vec->z };

		TacviewSDK::double3 result;

		tacviewInterface->MathVectorNormalize(addonHandle, vec, result);

		return gcnew Wrapper::double3(result.x, result.y, result.z);
	}

	double Wrapper::MathClass::VectorClass::GetLength(double3 ^ _vec)
	{
		const TacviewSDK::double3 vec = { _vec->x, _vec->y, _vec->z };
		return tacviewInterface->MathVectorGetLength(addonHandle, vec);
	}

	double Wrapper::MathClass::VectorClass::GetDistance(double3 ^ _pt1, double3 ^ _pt2)
	{
		const TacviewSDK::double3 pt1 = { _pt1->x, _pt1->y, _pt1->z };
		const TacviewSDK::double3 pt2 = { _pt2->x, _pt2->y, _pt2->z };
		return tacviewInterface->MathVectorGetDistance(addonHandle, pt1, pt2);
	}

	double Wrapper::MathClass::VectorClass::GetDistanceBetweenObjects(ObjectTransformOutput ^ _transform1, ObjectTransformOutput ^ _transform2)
	{
		TacviewSDK::ObjectTransformOutput transform1 = { 0 };

		// Object 1 transform

		transform1.absoluteTime = _transform1->absoluteTime;

		transform1.x = _transform1->x;
		transform1.y = _transform1->y;
		transform1.z = _transform1->z;

		transform1.longitude = _transform1->longitude;
		transform1.latitude = _transform1->latitude;
		transform1.altitude = _transform1->altitude;

		transform1.roll = _transform1->roll;
		transform1.pitch = _transform1->pitch;
		transform1.yaw = _transform1->yaw;

		transform1.u = _transform1->u;
		transform1.v = _transform1->v;
		transform1.heading = _transform1->heading;

		transform1.rotationIsValid = _transform1->rotationIsValid;
		transform1.nativeCoordinatesAreValid = _transform1->nativeCoordinatesAreValid;

		// Object 2 transform

		TacviewSDK::ObjectTransformOutput transform2 = { 0 };

		transform2.absoluteTime = _transform2->absoluteTime;

		transform2.x = _transform2->x;
		transform2.y = _transform2->y;
		transform2.z = _transform2->z;

		transform2.longitude = _transform2->longitude;
		transform2.latitude = _transform2->latitude;
		transform2.altitude = _transform2->altitude;

		transform2.roll = _transform2->roll;
		transform2.pitch = _transform2->pitch;
		transform2.yaw = _transform2->yaw;

		transform2.u = _transform2->u;
		transform2.v = _transform2->v;
		transform2.heading = _transform2->heading;

		transform2.rotationIsValid = _transform2->rotationIsValid;
		transform2.nativeCoordinatesAreValid = _transform2->nativeCoordinatesAreValid;

		return tacviewInterface->MathVectorGetDistanceBetweenObjects(addonHandle, &transform1, &transform2);
	}

	double Wrapper::MathClass::VectorClass::GetDistanceOnEarth(double longitude1, double latitude1, double longitude2, double latitude2, double altitude)
	{
		return tacviewInterface->MathVectorGetDistanceOnEarth(addonHandle, longitude1, latitude1, longitude2, latitude2, altitude);
	}

	float Wrapper::MathClass::VectorClass::AngleBetween(double3 ^ _vec1, double3 ^ _vec2)
	{
		const TacviewSDK::double3 vec1 = { _vec1->x, _vec1->y, _vec1->z };
		const TacviewSDK::double3 vec2 = { _vec2->x, _vec2->y, _vec2->z };

		return tacviewInterface->MathVectorAngleBetween(addonHandle, vec1, vec2);
	}

	float Wrapper::MathClass::VectorClass::AngleBetween(double3 ^ _vec, double3 ^ _referenceVec1, double3 ^ _referenceVec2)
	{
		const TacviewSDK::double3 vec = { _vec->x, _vec->y, _vec->z };
		const TacviewSDK::double3 referenceVec1 = { _referenceVec1->x, _referenceVec1->y, _referenceVec1->z };
		const TacviewSDK::double3 referenceVec2 = { _referenceVec2->x, _referenceVec2->y, _referenceVec2->z };

		return tacviewInterface->MathVectorAngleBetween2(addonHandle, vec, referenceVec1, referenceVec2);
	}

	Wrapper::double3 ^ Wrapper::MathClass::VectorClass::LocalToGlobal(ObjectSphericalTransform ^ _objectTransform, double3 ^ _localCoordinates)
	{
		TacviewSDK::ObjectSphericalTransform objectTransform = { 0 };

		objectTransform.longitude = _objectTransform->longitude;
		objectTransform.latitude = _objectTransform->latitude;
		objectTransform.altitude = _objectTransform->altitude;

		objectTransform.roll = _objectTransform->roll;
		objectTransform.pitch = _objectTransform->pitch;
		objectTransform.yaw = _objectTransform->yaw;

		const TacviewSDK::double3 localCoordinates = { _localCoordinates->x, _localCoordinates->y, _localCoordinates->z };

		TacviewSDK::double3 result;

		tacviewInterface->MathVectorLocalToGlobal(addonHandle, &objectTransform, &localCoordinates, &result);

		return gcnew Wrapper::double3(result.x, result.y, result.z);
	}

	Wrapper::double3 ^ Wrapper::MathClass::VectorClass::LocalToGlobal(ObjectCartesianTransform ^ _objectTransform, double3 ^ _localCoordinates)
	{
		TacviewSDK::ObjectCartesianTransform objectTransform = { 0 };

		objectTransform.x = _objectTransform->x;
		objectTransform.y = _objectTransform->y;
		objectTransform.z = _objectTransform->z;

		objectTransform.roll = _objectTransform->roll;
		objectTransform.pitch = _objectTransform->pitch;
		objectTransform.yaw = _objectTransform->yaw;

		const TacviewSDK::double3 localCoordinates = { _localCoordinates->x, _localCoordinates->y, _localCoordinates->z };

		TacviewSDK::double3 result;

		tacviewInterface->MathVectorLocalToGlobal2(addonHandle, &objectTransform, &localCoordinates, &result);

		return gcnew Wrapper::double3(result.x, result.y, result.z);
	}

	Wrapper::double3 ^ Wrapper::MathClass::VectorClass::LongitudeLatitudeToCartesian(double3 ^ _vec)
	{
		const TacviewSDK::double3 vec = { _vec->x, _vec->y, _vec->z };

		TacviewSDK::double3 result;

		tacviewInterface->MathVectorLongitudeLatitudeToCartesian(addonHandle, vec, result);

		return gcnew Wrapper::double3(result.x, result.y, result.z);
	}

	Wrapper::double3 ^ Wrapper::MathClass::VectorClass::CartesianToLongitudeLatitude(double3 ^ _vec)
	{
		const TacviewSDK::double3 vec = { _vec->x, _vec->y, _vec->z };

		TacviewSDK::double3 result;

		tacviewInterface->MathVectorCartesianToLongitudeLatitude(addonHandle, vec, result);

		return gcnew Wrapper::double3(result.x, result.y, result.z);
	}

	Wrapper::double3 ^ Wrapper::MathClass::VectorClass::BearingRangeAltitudeToLongitudeLatitude(double referenceLongitude, double referenceLatitude, double bearing, double range, double altitude)
	{
		TacviewSDK::double3 result;

		tacviewInterface->MathVectorBearingRangeAltitudeToLongitudeLatitude(addonHandle, referenceLongitude, referenceLatitude, bearing, range, altitude, result);

		return gcnew Wrapper::double3(result.x, result.y, result.z);
	}

	Wrapper::double3 ^ Wrapper::MathClass::VectorClass::LongitudeLatitudeToBearingRangeAltitude(double referenceLongitude, double referenceLatitude, double referenceAltitude, double targetLongitude, double targetLatitude, double targetAltitude)
	{
		TacviewSDK::double3 result;

		tacviewInterface->MathVectorLongitudeLatitudeToBearingRangeAltitude(addonHandle, referenceLongitude, referenceLatitude, referenceAltitude, targetLongitude, targetLatitude, targetAltitude, result);

		return gcnew Wrapper::double3(result.x, result.y, result.z);
	}

	// Units

	Wrapper::MathClass::UnitsClass::UnitsClass(void * newAddonHandle, TacviewSDK::Interface187 * newTacviewInterface) :
		addonHandle(newAddonHandle),
		tacviewInterface(newTacviewInterface)
	{
	}

	double Wrapper::MathClass::UnitsClass::NauticalMilesToMeters(double value)
	{
		return tacviewInterface->MathUnitsNauticalMilesToMeters(addonHandle, value);
	}

	double Wrapper::MathClass::UnitsClass::MetersToNauticalMiles(double value)
	{
		return tacviewInterface->MathUnitsMetersToNauticalMiles(addonHandle, value);
	}

	double Wrapper::MathClass::UnitsClass::FeetToMeters(double value)
	{
		return tacviewInterface->MathUnitsFeetToMeters(addonHandle, value);
	}

	double Wrapper::MathClass::UnitsClass::MetersToFeet(double value)
	{
		return tacviewInterface->MathUnitsMetersToFeet(addonHandle, value);
	}

	double Wrapper::MathClass::UnitsClass::MetersPerSecondToKnots(double value)
	{
		return tacviewInterface->MathUnitsMetersPerSecondToKnots(addonHandle, value);
	}

	double Wrapper::MathClass::UnitsClass::KnotsToMetersPerSecond(double value)
	{
		return tacviewInterface->MathUnitsKnotsToMetersPerSecond(addonHandle, value);
	}

	// Math

	Wrapper::MathClass::MathClass(void * newAddonHandle, TacviewSDK::Interface187 * newTacviewInterface) :
		addonHandle(newAddonHandle),
		tacviewInterface(newTacviewInterface)
	{
		Angle = gcnew AngleClass(newAddonHandle, newTacviewInterface);
		Vector = gcnew VectorClass(newAddonHandle, newTacviewInterface);
		Units = gcnew UnitsClass(newAddonHandle, newTacviewInterface);
	}
}
