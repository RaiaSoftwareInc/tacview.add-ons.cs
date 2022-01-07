/*
	Tacview.SDK.Interface
	Interface to create C++/C# addons for Tacview
	Version 1.8.0 // 2019-06-27
	Copyright (C) 2018-2020 Raia Software. All rights reserved.

	NOTE: You need a licence of Tacview Enterprise to run C++/C# addons.
*/

#pragma once

#ifndef TACVIEW_SDK_INTERFACE_H
#define	TACVIEW_SDK_INTERFACE_H

/*
	Here is the current C++ interface to develop addons for Tacview.

	Interfaces available in final builds of Tacview are stable and will be supported till Tacview 2.0.

	When you compile your code with the current SDK, your program will be linked against the latest available interface.
	Which means that your code may require a few changes if it has been written for an older API.

	Old addons which are using older interfaces will run properly with the latest versions of Tacview.

	NOTE ABOUT BETA VERSIONS OF TACVIEW: If you are currently using a beta version of Tacview to build your addon,
	it may not work with the corresponding final version of Tacview. Beta versions of Tacview should be used only for prototyping,
	not to compile and release public versions of addons.
*/

namespace TacviewSDK
{
	// Constants

	static constexpr double BeginningOfTime = -FLT_MAX;		// Typically used for timeless objects like waypoints or buildings
	static constexpr double EndOfTime = FLT_MAX;
	static constexpr int InvalidPropertyIndex = -1;

	// Tags

	namespace Tag
	{
		static constexpr wchar_t const * Separator = L"+";

		// Object class

		static constexpr wchar_t const * Air = L"Air";
		static constexpr wchar_t const * Ground = L"Ground";
		static constexpr wchar_t const * Sea = L"Sea";
		static constexpr wchar_t const * Space = L"Space";

		static constexpr wchar_t const * Weapon = L"Weapon";
		static constexpr wchar_t const * Sensor = L"Sensor";
		static constexpr wchar_t const * Navaid = L"Navaid";
		static constexpr wchar_t const * Abstract = L"Abstract";
		static constexpr wchar_t const * Misc = L"Misc";

		static constexpr wchar_t const * Static = L"Static";
		static constexpr wchar_t const * Heavy = L"Heavy";
		static constexpr wchar_t const * Medium = L"Medium";
		static constexpr wchar_t const * Light = L"Light";
		static constexpr wchar_t const * Minor = L"Minor";

		// Basic Types

		static constexpr wchar_t const * FixedWing = L"FixedWing";
		static constexpr wchar_t const * Rotorcraft = L"Rotorcraft";
		static constexpr wchar_t const * Spacecraft = L"Spacecraft";

		static constexpr wchar_t const * Armor = L"Armor";
		static constexpr wchar_t const * AntiAircraft = L"AntiAircraft";
		static constexpr wchar_t const * Vehicle = L"Vehicle";
		static constexpr wchar_t const * Watercraft = L"Watercraft";
		static constexpr wchar_t const * Human = L"Human";
		static constexpr wchar_t const * Biologic = L"Biologic";

		static constexpr wchar_t const * Missile = L"Missile";
		static constexpr wchar_t const * Rocket = L"Rocket";
		static constexpr wchar_t const * Bomb = L"Bomb";
		static constexpr wchar_t const * Torpedo = L"Torpedo";
		static constexpr wchar_t const * Projectile = L"Projectile";
		static constexpr wchar_t const * Beam = L"Beam";

		static constexpr wchar_t const * Decoy = L"Decoy";

		static constexpr wchar_t const * Building = L"Building";

		static constexpr wchar_t const * Bullseye = L"Bullseye";
		static constexpr wchar_t const * Waypoint = L"Waypoint";

		// Specific Types

		static constexpr wchar_t const * Tank = L"Tank";
		static constexpr wchar_t const * Warship = L"Warship";
		static constexpr wchar_t const * AircraftCarrier = L"AircraftCarrier";
		static constexpr wchar_t const * Submarine = L"Submarine";
		static constexpr wchar_t const * Infantry = L"Infantry";
		static constexpr wchar_t const * Parachutist = L"Parachutist";

		static constexpr wchar_t const * Shell = L"Shell";
		static constexpr wchar_t const * Bullet = L"Bullet";

		static constexpr wchar_t const * Flare = L"Flare";
		static constexpr wchar_t const * Chaff = L"Chaff";
		static constexpr wchar_t const * SmokeGrenade = L"SmokeGrenade";

		static constexpr wchar_t const * Aerodrome = L"Aerodrome";

		static constexpr wchar_t const * Container = L"Container";
		static constexpr wchar_t const * Shrapnel = L"Shrapnel";
		static constexpr wchar_t const * Explosion = L"Explosion";

		// Composite Tags

		static constexpr wchar_t const * CompositeFixedWing = L"Air+FixedWing";
		static constexpr wchar_t const * CompositeRotorcraft = L"Air+Rotorcraft";

		static constexpr wchar_t const * CompositeAntiAircraft = L"Ground+AntiAircraft";
		static constexpr wchar_t const * CompositeArmor = L"Ground+Heavy+Armor+Vehicle";
		static constexpr wchar_t const * CompositeTank = L"Ground+Heavy+Armor+Vehicle+Tank";
		static constexpr wchar_t const * CompositeGroundVehicle = L"Ground+Vehicle";

		static constexpr wchar_t const * CompositeWatercraft = L"Sea+Watercraft";
		static constexpr wchar_t const * CompositeWarship = L"Sea+Watercraft+Warship";
		static constexpr wchar_t const * CompositeAircraftCarrier = L"Sea+Watercraft+AircraftCarrier";
		static constexpr wchar_t const * CompositeSubmarine = L"Sea+Watercraft+Submarine";

		static constexpr wchar_t const * CompositeSonobuoy = L"Sea+Sensor";

		static constexpr wchar_t const * CompositeHuman = L"Ground+Light+Human";
		static constexpr wchar_t const * CompositeInfantry = L"Ground+Light+Human+Infantry";
		static constexpr wchar_t const * CompositeParachutist = L"Ground+Light+Human+Air+Parachutist";

		static constexpr wchar_t const * CompositeMissile = L"Weapon+Missile";
		static constexpr wchar_t const * CompositeRocket = L"Weapon+Rocket";
		static constexpr wchar_t const * CompositeBomb = L"Weapon+Bomb";
		static constexpr wchar_t const * CompositeProjectile = L"Weapon+Projectile";
		static constexpr wchar_t const * CompositeBeam = L"Weapon+Beam";
		static constexpr wchar_t const * CompositeShell = L"Projectile+Shell";
		static constexpr wchar_t const * CompositeBullet = L"Projectile+Bullet";
		static constexpr wchar_t const * CompositeBallisticShell = L"Projectile+Shell+Heavy";

		static constexpr wchar_t const * CompositeDecoy = L"Misc+Decoy";
		static constexpr wchar_t const * CompositeFlare = L"Misc+Decoy+Flare";
		static constexpr wchar_t const * CompositeChaff = L"Misc+Decoy+Chaff";
		static constexpr wchar_t const * CompositeSmokeGrenade = L"Misc+Decoy+SmokeGrenade";

		static constexpr wchar_t const * CompositeBuilding = L"Ground+Static+Building";
		static constexpr wchar_t const * CompositeAerodrome = L"Ground+Static+Aerodrome";

		static constexpr wchar_t const * CompositeBullseye = L"Navaid+Static+Bullseye";
		static constexpr wchar_t const * CompositeWaypoint = L"Navaid+Static+Waypoint";

		static constexpr wchar_t const * CompositeContainer = L"Misc+Container";
		static constexpr wchar_t const * CompositeShrapnel = L"Misc+Shrapnel";
		static constexpr wchar_t const * CompositeMinorObject = L"Misc+Minor";
		static constexpr wchar_t const * CompositeExplosion = L"Misc+Explosion";
	};

	// Properties

	namespace Property
	{
		namespace Text
		{
			static constexpr wchar_t const * CallSign = L"CallSign";
			static constexpr wchar_t const * Color = L"Color";
			static constexpr wchar_t const * Event = L"Event";
			static constexpr wchar_t const * FocusedTarget = L"FocusedTarget";
			static constexpr wchar_t const * LockedTarget = L"LockedTarget";
			static constexpr wchar_t const * Name = L"Name";
			static constexpr wchar_t const * Pilot = L"Pilot";
			static constexpr wchar_t const * Type = L"Type";
		};

		namespace Numeric
		{
			static constexpr wchar_t const * Disabled = L"Disabled";
			static constexpr wchar_t const * EngagementMode = L"EngagementMode";
			static constexpr wchar_t const * EngagementMode2 = L"EngagementMode2";
			static constexpr wchar_t const * EngagementRange = L"EngagementRange";
			static constexpr wchar_t const * EngagementRange2 = L"EngagementRange2";
			static constexpr wchar_t const * VerticalEngagementRange = L"VerticalEngagementRange";
			static constexpr wchar_t const * VerticalEngagementRange2 = L"VerticalEngagementRange2";
			static constexpr wchar_t const * IAS = L"IAS";
			static constexpr wchar_t const * Importance = L"Importance";

			static constexpr wchar_t const * MinRange = L"MinRange";
			static constexpr wchar_t const * MaxRange = L"MaxRange";
		};
	};

	// Types

	typedef void * ModelHandle;
	typedef void * ObjectHandle;
	typedef void * RecordHandle;
	typedef void * RenderStateHandle;
	typedef void * StaticObjectHandle;
	typedef void * TextureCoordinateArrayHandle;
	typedef void * TextureHandle;
	typedef void * VertexArrayHandle;

	typedef uint64_t ObjectId;
	typedef uint64_t ObjectTags;

	enum class MessageBoxResult
	{
		OK,
		Cancel,
	};

	enum class CameraMode
	{
		Cockpit,
		External,
		Satellite,
		Free,
	};

	enum class Unit
	{
		Meters,
		Feet,
	};

	struct CameraOffset
	{
		float lateral;
		float longitudinal;
		float vertical;
		float roll;
		float pitch;
		float yaw;
	};

	struct float2
	{
		float x;
		float y;
	};

	struct float3
	{
		float x;
		float y;
		float z;
	};

	struct double3
	{
		double x;
		double y;
		double z;
	};

	struct ObjectTransformOutput
	{
		// Sample time relative to 1970-01-01 in seconds

		double absoluteTime;

		// Cartesian coordinates in meters
		// (0,0,0) is the Earth center

		double x;
		double y;
		double z;

		// Spherical coordinates (radian)

		double longitude;
		double latitude;
		float altitude;

		// Object orientation (radian)

		float roll;
		float pitch;
		float yaw;

		// Native coordinates for Flight simulators such as DCS & BMS

		float u;				// Native x coordinate (meters)
		float v;				// Native y coordinate (meters)
		float heading;			// Native heading (radian)

		// These flags indicate which members are valid
		// Invalid members are set to 0.0

		bool rotationIsValid;
		bool nativeCoordinatesAreValid;
	};

	struct ObjectTransformInput
	{
		enum Flags
		{
			LongitudeIsSet	=	1<<0,
			LatitudeIsSet	=	1<<1,
			AltitudeIsSet	=	1<<2,

			RollIsSet		=	1<<3,
			PitchIsSet		=	1<<4,
			YawIsSet		=	1<<5,

			UIsSet			=	1<<6,
			VIsSet			=	1<<7,
			HeadingIsSet	=	1<<8,
		};

		// Injected angles (including longitude and latitude) MUST be normalized between ]-pi,+pi]
		// Failure to do so may produce undefined results with some formulas.

		double longitude;	// (radian) Spherical position (+ is towards east)
		double latitude;	// (radian) Spherical position (+ is towards north)
		float altitude;		// (meters) Spherical position

		float roll;			// (radian) roll axis rotation
		float pitch;		// (radian) pitch axis rotation
		float yaw;			// (radian) yaw axis rotation

		float u;			// (meters) Native x coordinate
		float v;			// (meters) Native y coordinate
		float heading;		// (radian) Heading in native coordinates system

		uint32_t flags;		// Indicate which fields are valid
	};

	struct ObjectSphericalTransform
	{
		// Spherical coordinates (radian)

		double longitude;
		double latitude;
		float altitude;

		// Object orientation (radian)

		float roll;
		float pitch;
		float yaw;
	};

	struct ObjectCartesianTransform
	{
		// Cartesian coordinates in meters
		// (0,0,0) is the Earth center

		double x;
		double y;
		double z;

		// Object orientation (radian)

		float roll;
		float pitch;
		float yaw;
	};

	struct RenderState
	{
		uint32_t color = 0xFFFFFFFF;
		TextureHandle textureHandle = nullptr;

		enum class BlendMode
		{
			Normal,
			Additive,
		};

		BlendMode blendMode = BlendMode::Normal;
	};

	struct ColorVertex
	{
		double x;
		double y;
		double z;
		uint32_t rgba;
	};

	struct ObjectRenderSphericalTransform
	{
		// Spherical coordinates (radian)

		double longitude;
		double latitude;
		float altitude;

		// Object orientation (radian)

		float roll;
		float pitch;
		float yaw;

		// Scale

		float scale;
	};

	struct ObjectRenderCartesianTransform
	{
		// Cartesian coordinates in meters
		// (0,0,0) is the Earth center

		double x;
		double y;
		double z;

		// Object orientation (radian)

		float roll;
		float pitch;
		float yaw;

		// Scale

		float scale;
	};

	struct UIRenderTransform
	{
		float x;
		float y;
		float z;

		float roll;
		float pitch;
		float yaw;

		float scale;
	};

	struct UIRenderTextTransform	// Tacview 1.8.0
	{
		float x;
		float y;
		float z;

		float scale;
	};

	struct UIRenderShapeTransform	// Tacview 1.8.0
	{
		float x;
		float y;
		float z;

		float roll;
		float pitch;
		float yaw;

		float scaleX;
		float scaleY;
	};

	struct OpenFileNameOptions
	{
		struct FileType
		{
			// Set extensions to nullptr to terminate the list

			const wchar_t * extensions;
			const wchar_t * description;
		};

		const wchar_t * defaultFileExtension;
		const wchar_t * fileName;
		const FileType * fileTypeList;
		bool multiSelection;
	};

	struct SaveFileNameOptions
	{
		struct FileType
		{
			// Set extensions to nullptr to terminate the list

			const wchar_t * extensions;
			const wchar_t * description;
		};

		const wchar_t * defaultFileExtension;
		const wchar_t * fileName;
		const FileType * fileTypeList;
	};

	struct FolderNameOptions
	{
		const wchar_t * folderName;
		bool canCreateNewFolder;
	};

	// Events handlers

	typedef void(_cdecl * TacviewEventsUpdateEventHandler172)(void * userData, float dt, double absoluteTime);
	typedef void(_cdecl * TacviewEventsDrawEventHandler172)(void * userData);
	typedef void(_cdecl * TacviewEventsMenuEventHandler172)(void * userData, int commandId);
	typedef void(_cdecl * TacviewEventsDocumentLoadedEventHandler182)(void * userData);
	typedef void(_cdecl * TacviewEventsDocumentLoadedEventHandler187)(void * userData, const wchar_t * fileNames);
	typedef void(_cdecl * TacviewEventsDocumentUnloadEventHandler184)(void * userData);
	typedef bool(_cdecl * TacviewEventsPowerSaveEventHandler185)(void * userData);

	typedef void(_cdecl * TacviewUIRendererContextMenuEventHandler176)(void * userData, int contextMenuId, ObjectHandle objectHandle);
	typedef void(_cdecl * TacviewUIRendererPick3DPointEventHandler186)(void * userData, double longitude, double latitude, double altitude);

	// Global functions

	typedef void(_cdecl * TacviewClose172)(void * addonHandle);

	// Tacview.AddOns

	typedef void(_cdecl * TacviewAddOnsCurrentGetPath174)(void * addonHandle, wchar_t * pathBuffer, size_t pathBufferSize);

	typedef void(_cdecl * TacviewAddOnsCurrentSetTitle172)(void * addonHandle, const wchar_t * title);
	typedef void(_cdecl * TacviewAddOnsCurrentSetVersion172)(void * addonHandle, const wchar_t * version);
	typedef void(_cdecl * TacviewAddOnsCurrentSetAuthor172)(void * addonHandle, const wchar_t * author);
	typedef void(_cdecl * TacviewAddOnsCurrentSetNotes172)(void * addonHandle, const wchar_t * notes);

	typedef bool(_cdecl * TacviewAddOnsCurrentSettingsGetBoolean172)(void * addonHandle, const wchar_t * settingName, bool defaultSettingValue);
	typedef void(_cdecl * TacviewAddOnsCurrentSettingsSetBoolean172)(void * addonHandle, const wchar_t * settingName, bool settingValue);

	typedef void(_cdecl * TacviewAddOnsCurrentSettingsGetString182)(void * addonHandle, const wchar_t * settingName, wchar_t * valueBuffer, size_t valueBufferSize, const wchar_t * defaultSettingValue);
	typedef void(_cdecl * TacviewAddOnsCurrentSettingsSetString182)(void * addonHandle, const wchar_t * settingName, const wchar_t * value);

	// Tacview.Context

	typedef double(_cdecl * TacviewContextGetAbsoluteTime175)(void * addonHandle);
	typedef void(_cdecl * TacviewContextSetAbsoluteTime176)(void * addonHandle, double absoluteTime);

	typedef ObjectHandle(_cdecl * TacviewContextGetSelectedObject172)(void * addonHandle, int objectIndex);
	typedef void(_cdecl * TacviewContextSetSelectedObject172)(void * addonHandle, int objectIndex, ObjectHandle objectHandle);

	typedef size_t(_cdecl * TacviewContextGetActiveObjectList173)(void * addonHandle, ObjectHandle * objectHandleListAddress, size_t objectHandleListMaxCount);

	typedef CameraMode(_cdecl * TacviewContextCameraGetMode172)(void * addonHandle);
	typedef void(_cdecl * TacviewContextCameraSetOffset172)(void * addonHandle, const CameraOffset * newCameraOffset);
	typedef void(_cdecl * TacviewContextCameraSetFieldOfView172)(void * addonHandle, float vecticalFieldOfViewInRadian);

	typedef void(_cdecl* TacviewContextCameraGetSphericalPosition185)(void* addonHandle, double & longitude, double & latitude, double & altitude);

	typedef void(_cdecl* TacviewContextCameraSetRotation180)(void* addonHandle, float roll, float pitch, float yaw);
	typedef void(_cdecl* TacviewContextCameraSetRangeToTarget180)(void* addonHandle, double range);

	typedef void(_cdecl * TacviewContextPlaybackPlay176)(void * addonHandle);
	typedef void(_cdecl * TacviewContextPlaybackPause176)(void * addonHandle);
	typedef bool(_cdecl * TacviewContextPlaybackIsPlaying176)(void * addonHandle);

	typedef void(_cdecl * TacviewContextGetDocumentPath187)(void * addonHandle, wchar_t * buffer, size_t bufferSize);

	// Tacview.Directory

	typedef bool(_cdecl * TacviewDirectoryCreateDirectory187)(void * addonHandle, const wchar_t * directoryName);
	typedef bool(_cdecl * TacviewDirectoryDelete187)(void * addonHandle, const wchar_t * directoryName, bool recursive);
	typedef bool(_cdecl * TacviewDirectoryGetFiles187)(void * addonHandle, const wchar_t * directoryName, bool recursive, wchar_t * buffer, size_t bufferSize);

	// Tacview.Events

	typedef void(_cdecl * TacviewEventsUpdateRegisterListener172)(void * addonHandle, TacviewEventsUpdateEventHandler172 eventHandler, void * userData);

	typedef void(_cdecl * TacviewEventsDrawOpaqueObjectsRegisterListener172)(void * addonHandle, TacviewEventsDrawEventHandler172 eventHandler, void * userData);
	typedef void(_cdecl * TacviewEventsDrawTransparentObjectsRegisterListener172)(void * addonHandle, TacviewEventsDrawEventHandler172 eventHandler, void * userData);
	typedef void(_cdecl * TacviewEventsDrawTransparentObjectsNearRegisterListener186)(void * addonHandle, TacviewEventsDrawEventHandler172 eventHandler, void * userData);
	typedef void(_cdecl * TacviewEventsDrawOpaqueUIRegisterListener172)(void * addonHandle, TacviewEventsDrawEventHandler172 eventHandler, void * userData);
	typedef void(_cdecl * TacviewEventsDrawTransparentUIRegisterListener172)(void * addonHandle, TacviewEventsDrawEventHandler172 eventHandler, void * userData);

	typedef void(_cdecl * TacviewEventsDocumentLoadedRegisterListener182)(void * addonHandle, TacviewEventsDocumentLoadedEventHandler182 eventHandler, void * userData);
	typedef void(_cdecl * TacviewEventsDocumentLoadedRegisterListener187)(void * addonHandle, TacviewEventsDocumentLoadedEventHandler187 eventHandler, void * userData);
	typedef void(_cdecl * TacviewEventsDocumentUnloadRegisterListener184)(void * addonHandle, TacviewEventsDocumentUnloadEventHandler184 eventHandler, void * userData);

	typedef void(_cdecl * TacviewEventsPowerSaveRegisterListener185)(void * addonHandle, TacviewEventsPowerSaveEventHandler185 eventHandler, void * userData);

	// Tacview.Log

	typedef void(_cdecl * TacviewLogDebug172)(void * addonHandle, const wchar_t * text);
	typedef void(_cdecl * TacviewLogInfo172)(void * addonHandle, const wchar_t * text);
	typedef void(_cdecl * TacviewLogWarning172)(void * addonHandle, const wchar_t * text);
	typedef void(_cdecl * TacviewLogError172)(void * addonHandle, const wchar_t * text);

	// Tacview.Math

	typedef float(_cdecl * TacviewMathAngleSubtract172)(void * addonHandle, float angle1, float angle2);
	typedef double(_cdecl * TacviewMathAngleSubtract174)(void * addonHandle, double angle1, double angle2);
	typedef float(_cdecl * TacviewMathAngleNormalizePiFloat185)(void * addonHandle, float angle);
	typedef double(_cdecl * TacviewMathAngleNormalizePiDouble185)(void * addonHandle, double angle);
	typedef float(_cdecl * TacviewMathAngleNormalize2PiFloat185)(void * addonHandle, float angle);
	typedef double(_cdecl * TacviewMathAngleNormalize2PiDouble185)(void * addonHandle, double angle);

	typedef void(_cdecl * TacviewMathVectorAdd172)(void * addonHandle, const double3 & vec1, const double3 & vec2, double3 & result);
	typedef void(_cdecl * TacviewMathVectorSubtract172)(void * addonHandle, const double3 & vec1, const double3 & vec2, double3 & result);
	typedef void(_cdecl * TacviewMathVectorMultiply175)(void * addonHandle, double factor, const double3 & vec, double3 & result);

	typedef void(_cdecl * TacviewMathVectorNormalize172)(void * addonHandle, const double3 & vec, double3 & result);
	typedef double(_cdecl * TacviewMathVectorGetLength180)(void * addonHandle, const double3 & vec);
	typedef double(_cdecl * TacviewMathVectorGetDistance180)(void * addonHandle, const double3 & pt1, const double3 & pt2);
	typedef double(_cdecl * TacviewMathVectorGetDistanceBetweenObjects184)(void * addonHandle, const ObjectTransformOutput * objectTransform1, const ObjectTransformOutput * objectTransform2);
	typedef double(_cdecl * TacviewMathVectorGetDistanceOnEarth180)(void * addonHandle, double longitude1, double latitude1, double longitude2, double latitude2, double altitude);

	typedef float(_cdecl * TacviewMathVectorAngleBetween172)(void * addonHandle, const double3 & vec1, const double3 & vec2);
	typedef float(_cdecl * TacviewMathVectorAngleBetween2172)(void * addonHandle, const double3 & vec, const double3 & referenceVec1, const double3 & referenceVec2);

	typedef void(_cdecl * TacviewMathVectorLocalToGlobal172)(void * addonHandle, const ObjectSphericalTransform * objectTransform, const double3 * localCoordinates, double3 * globalCoordinates);
	typedef void(_cdecl * TacviewMathVectorLocalToGlobal2172)(void * addonHandle, const ObjectCartesianTransform * objectTransform, const double3 * localCoordinates, double3 * globalCoordinates);
	typedef void(_cdecl * TacviewMathVectorLongitudeLatitudeToCartesian172)(void * addonHandle, const double3 & vec, double3 & result);
	typedef void(_cdecl * TacviewMathVectorCartesianToLongitudeLatitude175)(void * addonHandle, const double3 & vec, double3 & result);
	typedef void(_cdecl * TacviewMathVectorBearingRangeAltitudeToLongitudeLatitude180)(void * addonHandle, double referenceLongitude, double referenceLatitude, double bearing, double range, double altitude, double3 & result);
	typedef void(_cdecl * TacviewMathVectorLongitudeLatitudeToBearingRangeAltitude187)(void * addonHandle, double referenceLongitude, double referenceLatitude, double referenceAltitude, double targetLongitude, double targetLatitude, double targetAltitude, double3 & result);

	typedef double(_cdecl * TacviewMathUnitsFeetToMeters180)(void * addonHandle, double value);
	typedef double(_cdecl * TacviewMathUnitsMetersToFeet187)(void * addonHandle, double value);
	typedef double(_cdecl * TacviewMathUnitsNauticalMilesToMeters180)(void * addonHandle, double value);
	typedef double(_cdecl * TacviewMathUnitsMetersToNauticalMiles187)(void * addonHandle, double value);
	typedef double(_cdecl * TacviewMathUnitsKnotsToMetersPerSecond187)(void * addonHandle, double value);
	typedef double(_cdecl * TacviewMathUnitsMetersPerSecondToKnots187)(void * addonHandle, double value);

	// Tacview.Media

	typedef bool(_cdecl * TacviewMediaLoad185)(void * addonHandle, int playerId, const wchar_t * fileName);
	typedef bool(_cdecl * TacviewMediaLoad2185)(void * addonHandle, int playerId, const wchar_t * fileName, double absoluteTime);
	typedef bool(_cdecl * TacviewMediaUnload187)(void * addonHandle, int playerId);
	typedef bool(_cdecl * TacviewMediaClose187)(void * addonHandle, int playerId);

	// Tacview.Path

	typedef void(_cdecl * TacviewPathGetDirectoryName187)(void * addonHandle, const wchar_t * path, wchar_t * buffer, size_t bufferSize);
	typedef void(_cdecl * TacviewPathGetFileName187)(void * addonHandle, const wchar_t * path, wchar_t * buffer, size_t bufferSize);

	// Tacview.Settings

	typedef bool(_cdecl * TacviewSettingsGetBoolean172)(void * addonHandle, const wchar_t * settingPath);
	typedef void(_cdecl * TacviewSettingsSetBoolean172)(void * addonHandle, const wchar_t * settingPath, bool value);

	typedef double(_cdecl * TacviewSettingsGetNumber186)(void * addonHandle, const wchar_t * settingPath);
	typedef void(_cdecl * TacviewSettingsSetNumber186)(void * addonHandle, const wchar_t * settingPath, double value);

	typedef void(_cdecl * TacviewSettingsGetString172)(void * addonHandle, const wchar_t * settingPath, wchar_t * valueBuffer, size_t valueBufferSize);
	typedef void(_cdecl * TacviewSettingsSetString172)(void * addonHandle, const wchar_t * settingPath, const wchar_t * value);

	typedef Unit(_cdecl * TacviewSettingsGetAltitudeUnit185)(void * addonHandle);

	// Tacview.SoundPlayer

	typedef void(_cdecl * TacviewSoundPlayerPlay184)(void * addonHandle, const wchar_t * fileName);
	typedef void(_cdecl * TacviewSoundPlayerStop184)(void * addonHandle);

	// Tacview.StaticObjects

	typedef StaticObjectHandle(_cdecl * TacviewStaticObjectsGetObjectHandleByName180)(void * addonHandle, const wchar_t * objectName);
	typedef void(_cdecl * TacviewStaticObjectsSetVisible180)(void * addonHandle, StaticObjectHandle objectHandle, bool isVisible);

	// Tacview.String

	typedef unsigned(_cdecl * TacviewStringCrc32185)(void * addonHandle, const wchar_t * text);

	// Tacview.Telemetry

	typedef void(_cdecl * TacviewTelemetryClear172)(void * addonHandle);
	typedef bool(_cdecl * TacviewTelemetryLoad180)(void * addonHandle, const wchar_t * fileName);

	typedef ObjectHandle(_cdecl * TacviewTelemetryGetCurrentObjectHandle172)(void * addonHandle, ObjectId objectId);
	typedef ObjectHandle(_cdecl * TacviewTelemetryGetObjectHandle186)(void * addonHandle, ObjectId objectId, double absoluteTime);
	typedef ObjectHandle(_cdecl * TacviewTelemetryGetCurrentOrCreateObjectHandle175)(void * addonHandle, ObjectId objectId);
	typedef ObjectHandle(_cdecl * TacviewTelemetryGetOrCreateObjectHandle175)(void * addonHandle, ObjectId objectId, double absoluteTime);

	typedef void(_cdecl * TacviewTelemetryDeleteObject175)(void * addonHandle, ObjectHandle objectHandle);

	typedef ObjectTags(_cdecl * TacviewTelemetryGetCurrentTags173)(void * addonHandle, ObjectHandle objectHandle);
	typedef void(_cdecl * TacviewTelemetryGetCurrentShortName172)(void * addonHandle, ObjectHandle objectHandle, wchar_t * nameBuffer, size_t nameBufferSize);
	typedef bool(_cdecl * TacviewTelemetryGetCurrentTransform172)(void * addonHandle, ObjectHandle objectHandle, ObjectTransformOutput * objectTransform);
	typedef bool(_cdecl * TacviewTelemetryGetCurrentCalculatedTransform186)(void * addonHandle, ObjectHandle objectHandle, ObjectTransformOutput * transform);
	typedef bool(_cdecl * TacviewTelemetryGetCurrentAngleOfAttack173)(void * addonHandle, ObjectHandle objectHandle, double & sampleValue);
	typedef bool(_cdecl * TacviewTelemetryGetCurrentAngleOfSideslip186)(void * addonHandle, ObjectHandle objectHandle, double & sampleValue);

	typedef bool(_cdecl * TacviewTelemetryGetVerticalGForce180)(void * addonHandle, ObjectHandle objectHandle, double absoluteTime, double & sampleValue);
	typedef bool(_cdecl * TacviewTelemetryGetCurrentVerticalGForce173)(void * addonHandle, ObjectHandle objectHandle, double & sampleValue);
	typedef bool(_cdecl * TacviewTelemetryGetLateralGForce186)(void * addonHandle, ObjectHandle objectHandle, double absoluteTime, double & sampleValue);
	typedef bool(_cdecl * TacviewTelemetryGetCurrentLateralGForce186)(void * addonHandle, ObjectHandle objectHandle, double & sampleValue);
	typedef bool(_cdecl * TacviewTelemetryGetLongitudinalGForce186)(void * addonHandle, ObjectHandle objectHandle, double absoluteTime, double & sampleValue);
	typedef bool(_cdecl * TacviewTelemetryGetCurrentLongitudinalGForce186)(void * addonHandle, ObjectHandle objectHandle, double & sampleValue);
	typedef bool(_cdecl * TacviewTelemetryGetAbsoluteGForce180)(void * addonHandle, ObjectHandle objectHandle, double absoluteTime, double & sampleValue);
	typedef bool(_cdecl * TacviewTelemetryGetCurrentAbsoluteGForce180)(void * addonHandle, ObjectHandle objectHandle, double & sampleValue);
	typedef bool(_cdecl * TacviewTelemetryGetInstantaneousTurnRadius184)(void * addonHandle, ObjectHandle objectHandle, double absoluteTime, double & sampleValue);
	typedef bool(_cdecl * TacviewTelemetryGetTurnRadius184)(void * addonHandle, ObjectHandle objectHandle, double absoluteTime, double dt, double & sampleValue);
	typedef bool(_cdecl * TacviewTelemetryGetCurrentInstantaneousTurnRadius184)(void * addonHandle, ObjectHandle objectHandle, double & sampleValue);
	typedef bool(_cdecl * TacviewTelemetryGetCurrentTurnRadius184)(void * addonHandle, ObjectHandle objectHandle, double dt, double & sampleValue);
	typedef bool(_cdecl * TacviewTelemetryGetInstantaneousTurnRate184)(void * addonHandle, ObjectHandle objectHandle, double absoluteTime, double & sampleValue);
	typedef bool(_cdecl * TacviewTelemetryGetTurnRate184)(void * addonHandle, ObjectHandle objectHandle, double absoluteTime, double dt, double & sampleValue);
	typedef bool(_cdecl * TacviewTelemetryGetCurrentInstantaneousTurnRate184)(void * addonHandle, ObjectHandle objectHandle, double & sampleValue);
	typedef bool(_cdecl * TacviewTelemetryGetCurrentTurnRate184)(void * addonHandle, ObjectHandle objectHandle, double dt, double & sampleValue);
	typedef bool(_cdecl * TacviewTelemetryGetMachNumber184)(void * addonHandle, ObjectHandle objectHandle, double absoluteTime, double & sampleValue);
	typedef bool(_cdecl * TacviewTelemetryGetCurrentMachNumber184)(void * addonHandle, ObjectHandle objectHandle, double & sampleValue);

	typedef int(_cdecl * TacviewTelemetryGetGlobalNumericPropertyIndex176)(void * addonHandle, const wchar_t * propertyName, bool autoCreate);
	typedef int(_cdecl * TacviewTelemetryGetGlobalTextPropertyIndex176)(void * addonHandle, const wchar_t * propertyName, bool autoCreate);

	typedef int(_cdecl * TacviewTelemetryGetObjectsNumericPropertyIndex175)(void * addonHandle, const wchar_t * propertyName, bool autoCreate);
	typedef int(_cdecl * TacviewTelemetryGetObjectsTextPropertyIndex175)(void * addonHandle, const wchar_t * propertyName, bool autoCreate);

	typedef size_t(_cdecl * TacviewTelemetryGetObjectCount176)(void * addonHandle);

	typedef ObjectHandle(_cdecl * TacviewTelemetryGetObjectHandleByIndex176)(void * addonHandle, size_t index);
	typedef ObjectId(_cdecl * TacviewTelemetryGetObjectId176)(void * addonHandle, ObjectHandle objectHandle);

	typedef bool(_cdecl * TacviewTelemetryIsEmpty176)(void * addonHandle);
	typedef bool(_cdecl * TacviewTelemetryIsLikeEmpty176)(void * addonHandle);
	typedef void(_cdecl * TacviewTelemetryGetDataTimeRange176)(void * addonHandle, double & lifeTimeBegin, double & lifeTimeEnd);
	typedef void(_cdecl * TacviewTelemetryGetLifeTime176)(void * addonHandle, ObjectHandle objectHandle, double & lifeTimeBegin, double & lifeTimeEnd);
	typedef void(_cdecl * TacviewTelemetrySetLifeTimeEnd175)(void * addonHandle, ObjectHandle objectHandle, double absoluteTime);
	typedef bool(_cdecl * TacviewTelemetryGetTransformTimeRange180)(void * addonHandle, ObjectHandle objectHandle, double & firstSampleTime, double & lastSampleTime);

	typedef bool(_cdecl * TacviewTelemetryGetNumericSample175)(void * addonHandle, ObjectHandle objectHandle, double absoluteTime, int propertyIndex, double & value);
	typedef size_t(_cdecl * TacviewTelemetryGetNumericSampleCount180)(void * addonHandle, ObjectHandle objectHandle, int propertyIndex);
	typedef bool(_cdecl * TacviewTelemetryGetNumericSampleFromIndex180)(void * addonHandle, ObjectHandle objectHandle, size_t sampleIndex, int propertyIndex, double & sampleTime, double & sampleValue);

	typedef bool(_cdecl * TacviewTelemetryGetTextSample175)(void * addonHandle, ObjectHandle objectHandle, double absoluteTime, int propertyIndex, wchar_t * valueBuffer, size_t valueBufferSize);
	typedef size_t(_cdecl * TacviewTelemetryGetTextSampleCount180)(void * addonHandle, ObjectHandle objectHandle, int propertyIndex);
	typedef bool(_cdecl * TacviewTelemetryGetTextSampleFromIndex180)(void * addonHandle, ObjectHandle objectHandle, size_t sampleIndex, int propertyIndex, double & sampleTime, wchar_t * valueBuffer, size_t valueBufferSize);

	typedef bool(_cdecl * TacviewTelemetryGetTransform175)(void * addonHandle, ObjectHandle objectHandle, double absoluteTime, ObjectTransformOutput * transform);
	typedef bool(_cdecl * TacviewTelemetryGetCalculatedTransform186)(void * addonHandle, ObjectHandle objectHandle, double absoluteTime, ObjectTransformOutput * transform);

	typedef size_t(_cdecl * TacviewTelemetryGetTransformCount186)(void * addonHandle, ObjectHandle objectHandle);
	typedef bool(_cdecl * TacviewTelemetryGetTransformFromIndex186)(void * addonHandle, ObjectHandle objectHandle, size_t sampleIndex, ObjectTransformOutput * transform);

	typedef void(_cdecl * TacviewTelemetrySetNumericSample175)(void * addonHandle, ObjectHandle objectHandle, double absoluteTime, int propertyIndex, double value);
	typedef void(_cdecl * TacviewTelemetrySetTextSample175)(void * addonHandle, ObjectHandle objectHandle, double absoluteTime, int propertyIndex, const wchar_t * value);
	typedef void(_cdecl * TacviewTelemetrySetTransform175)(void * addonHandle, ObjectHandle objectHandle, double absoluteTime, const ObjectTransformInput * transform);

	typedef bool(_cdecl * TacviewTelemetryRemoveTransformSample187)(void * addonHandle, ObjectHandle objectHandle, double absoluteTime);
	typedef bool(_cdecl * TacviewTelemetryRemoveTransformSampleFromIndex187)(void * addonHandle, ObjectHandle objectHandle, size_t sampleIndex);

	typedef bool(_cdecl * TacviewTelemetryRemoveNumericSample180)(void * addonHandle, ObjectHandle objectHandle, double absoluteTime, int propertyIndex);
	typedef bool(_cdecl * TacviewTelemetryRemoveNumericSampleFromIndex180)(void * addonHandle, ObjectHandle objectHandle, size_t sampleIndex, int propertyIndex);
	typedef bool(_cdecl * TacviewTelemetryRemoveTextSample180)(void * addonHandle, ObjectHandle objectHandle, double absoluteTime, int propertyIndex);
	typedef bool(_cdecl * TacviewTelemetryRemoveTextSampleFromIndex180)(void * addonHandle, ObjectHandle objectHandle, size_t sampleIndex, int propertyIndex);

	typedef bool(_cdecl * TacviewTelemetryAllGivenTagsActive180)(void * addonHandle, ObjectTags objectTags, ObjectTags activeTagsCombination);
	typedef bool(_cdecl * TacviewTelemetryAnyGivenTagActive180)(void * addonHandle, ObjectTags objectTags, ObjectTags activeTagsCombination);

	typedef bool(_cdecl * TacviewTelemetryOnLoadStart185)(void * addonHandle, bool mergeWithExistingData);
	typedef void(_cdecl * TacviewTelemetryOnLoadEnd185)(void * addonHandle, const wchar_t * documentName);

	// Tacview.Database

	typedef RecordHandle(_cdecl * TacviewDatabaseGetNextRecord182)(void * addonHandle, RecordHandle recordHandle, const wchar_t * tags);

	typedef bool(_cdecl * TacviewDatabaseGetRecordId182)(void * addonHandle, RecordHandle recordHandle, wchar_t * valueBuffer, size_t valueBufferSize);
	typedef float(_cdecl * TacviewDatabaseGetRecordPriority182)(void * addonHandle, RecordHandle recordHandle);

	typedef size_t(_cdecl * TacviewDatabaseGetTextPropertyIndex182)(void * addonHandle, const wchar_t * propertyName);
	typedef size_t(_cdecl * TacviewDatabaseGetNumericPropertyIndex182)(void * addonHandle, const wchar_t * propertyName);

	typedef bool(_cdecl * TacviewDatabaseGetRecordTextValue182)(void * addonHandle, RecordHandle recordHandle, size_t propertyIndex, wchar_t * valueBuffer, size_t valueBufferSize);
	typedef bool(_cdecl * TacviewDatabaseGetRecordNumericValue182)(void * addonHandle, RecordHandle recordHandle, size_t propertyIndex, double & value);

	typedef bool(_cdecl * TacviewDatabaseReload183)(void * addonHandle);

	// Tacview.Terrain

	typedef float(_cdecl * TacviewTerrainGetElevation175)(void * addonHandle, double longitude, double latitude);

	typedef void(_cdecl * TacviewTerrainAddCustomTexture187)(void * addonHandle, const wchar_t * textureId, const wchar_t * layerId, const wchar_t * fileName, const wchar_t * filter, double topLeftLongitude, double topLeftLatitude, double topRightLongitude, double topRightLatitude, double bottomRightLongitude, double bottomRightLatitude, double bottomLeftLongitude, double bottomLeftLatitude);
	typedef void(_cdecl * TacviewTerrainShowCustomTexture187)(void * addonHandle, const wchar_t * textureId);
	typedef void(_cdecl * TacviewTerrainHideCustomTexture187)(void * addonHandle, const wchar_t * textureId);

	// Tacview.UI

	typedef void(_cdecl * TacviewUIEnterFullScreen172)(void * addonHandle);
	typedef void(_cdecl * TacviewUIExitFullScreen172)(void * addonHandle);
	typedef void(_cdecl * TacviewUIEnterReadMode172)(void * addonHandle, bool borderless);
	typedef void(_cdecl * TacviewUIExitReadMode172)(void * addonHandle);

	typedef void(_cdecl * TacviewUISetWindowParent172)(void * addonHandle, HWND parentWindow);
	typedef void(_cdecl * TacviewUISetWindowPosition172)(void * addonHandle, int x, int y);
	typedef void(_cdecl * TacviewUISetWindowPosition2172)(void * addonHandle, int x, int y, int width, int height);
	typedef void(_cdecl * TacviewUISetWindowSize172)(void * addonHandle, int width, int height);

	typedef HWND(_cdecl * TacviewUIGetWindowHandle175)(void * addonHandle);

	typedef void(_cdecl * TacviewUIUpdate183)(void * addonHandle);

	typedef void(_cdecl * TacviewUIMessageBoxInfo172)(void * addonHandle, const wchar_t * text);
	typedef void(_cdecl * TacviewUIMessageBoxWarning187)(void * addonHandle, const wchar_t * text);
	typedef void(_cdecl * TacviewUIMessageBoxError172)(void * addonHandle, const wchar_t * text);
	typedef MessageBoxResult(_cdecl * TacviewUIMessageBoxQuestion172)(void * addonHandle, const wchar_t * text);

	typedef bool(_cdecl * TacviewUIMessageBoxInputText185)(void * addonHandle, const wchar_t * title, wchar_t * textBuffer, size_t textBufferSize, const wchar_t * message);

	typedef bool(_cdecl * TacviewUIMessageBoxGetOpenFileName182)(void * addonHandle, wchar_t * namesBuffer, size_t namesBufferSize, const OpenFileNameOptions * options);
	typedef bool(_cdecl * TacviewUIMessageBoxGetSaveFileName180)(void * addonHandle, wchar_t * nameBuffer, size_t nameBufferSize, const SaveFileNameOptions * options);
	typedef bool(_cdecl * TacviewUIMessageBoxGetFolderName180)(void * addonHandle, wchar_t * nameBuffer, size_t nameBufferSize, const FolderNameOptions * options);

	typedef void(_cdecl * TacviewUIFormatAltitudeToText182)(void * addonHandle, double value, wchar_t * buffer, size_t bufferSize);
	typedef bool(_cdecl * TacviewUIFormatTextToAltitude182)(void * addonHandle, const wchar_t * text, double & value);
	typedef bool(_cdecl * TacviewUIFormatTextToAltitudeLocalized183)(void * addonHandle, const wchar_t * text, double & value);

	typedef void(_cdecl * TacviewUIFormatDistanceToText182)(void * addonHandle, double value, wchar_t * buffer, size_t bufferSize);
	typedef bool(_cdecl * TacviewUIFormatTextToDistance182)(void * addonHandle, const wchar_t * text, double & value);
	typedef bool(_cdecl * TacviewUIFormatTextToDistanceLocalized183)(void * addonHandle, const wchar_t * text, double & value);

	typedef void(_cdecl * TacviewUIFormatSpeedToText183)(void * addonHandle, double value, wchar_t * buffer, size_t bufferSize);
	typedef bool(_cdecl * TacviewUIFormatTextToSpeed183)(void * addonHandle, const wchar_t * text, double & value);
	typedef bool(_cdecl * TacviewUIFormatTextToSpeedLocalized183)(void * addonHandle, const wchar_t * text, double & value);

	typedef void(_cdecl * TacviewUIFormatLongitudeToText182)(void * addonHandle, double value, wchar_t * buffer, size_t bufferSize);
	typedef void(_cdecl * TacviewUIFormatLatitudeToText182)(void * addonHandle, double value, wchar_t * buffer, size_t bufferSize);
	typedef bool(_cdecl * TacviewUIFormatTextToSpherical182)(void * addonHandle, const wchar_t * text, double & value);

	typedef void(_cdecl * TacviewUIFormatAbsoluteTimeToISOText183)(void * addonHandle, double value, bool outputDecimals, wchar_t * buffer, size_t bufferSize);
	typedef bool(_cdecl * TacviewUIFormatTextToAbsoluteTime183)(void * addonHandle, const wchar_t * text, double & value);

	typedef int(_cdecl * TacviewUIMenusAddMenu172)(void * addonHandle, int parentMenuId, const wchar_t * menuLabel);
	typedef int(_cdecl * TacviewUIMenusAddSeparator180)(void * addonHandle, int parentMenuId);
	typedef int(_cdecl * TacviewUIMenusAddCommand172)(void * addonHandle, int parentMenuId, const wchar_t * menuLabel, TacviewEventsMenuEventHandler172 eventHandler, void * userData);
	typedef int(_cdecl * TacviewUIMenusAddOption172)(void * addonHandle, int parentMenuId, const wchar_t * menuLabel, bool optionValue, TacviewEventsMenuEventHandler172 eventHandler, void * userData);
	typedef int(_cdecl * TacviewUIMenusAddExclusiveOption184)(void * addonHandle, int parentMenuId, const wchar_t * menuLabel, bool optionValue, TacviewEventsMenuEventHandler172 eventHandler, void * userData);
	typedef void(_cdecl * TacviewUIMenusSetOption172)(void * addonHandle, int commandId, bool optionValue);

	// Tacview.UI.Renderer

	typedef void(_cdecl * TacviewUIRendererDrawLines184)(void * addonHandle, TacviewSDK::RenderStateHandle renderStateHandle, float thickness, const double3 * vertexList, size_t vertexCount);
	typedef void(_cdecl * TacviewUIRendererDrawColoredLines184)(void * addonHandle, TacviewSDK::RenderStateHandle renderStateHandle, float thickness, const TacviewSDK::ColorVertex * vertexList, size_t vertexCount);
	typedef void(_cdecl * TacviewUIRendererDrawLineStrip184)(void * addonHandle, TacviewSDK::RenderStateHandle renderStateHandle, float thickness, const double3 * vertexList, size_t vertexCount);
	typedef void(_cdecl * TacviewUIRendererDrawColoredLineStrip184)(void * addonHandle, TacviewSDK::RenderStateHandle renderStateHandle, float thickness, const TacviewSDK::ColorVertex * vertexList, size_t vertexCount);

	typedef int(_cdecl * TacviewUIRendererGetWidth172)(void * addonHandle);
	typedef int(_cdecl * TacviewUIRendererGetHeight172)(void * addonHandle);

	typedef TextureHandle(_cdecl * TacviewUIRendererLoadTexture173)(void * addonHandle, const wchar_t * texturePath, bool wrapRepeat, bool compressed);
	typedef void(_cdecl * TacviewUIRendererUnloadTexture173)(void * addonHandle, TextureHandle textureHandle);

	typedef VertexArrayHandle(_cdecl * TacviewUIRendererCreateVertexArray172)(void * addonHandle, const float3 * vertexList, size_t vertexCount);
	typedef void(_cdecl * TacviewUIRendererReleaseVertexArray172)(void * addonHandle, VertexArrayHandle vertexArrayHandle);

	typedef TextureCoordinateArrayHandle(_cdecl * TacviewUIRendererCreateTextureCoordinateArray173)(void * addonHandle, const float2 * uvList, size_t uvCount);
	typedef void(_cdecl * TacviewUIRendererReleaseTextureCoordinateArray173)(void * addonHandle, TextureCoordinateArrayHandle textureCoordinateArrayHandle);

	typedef RenderStateHandle(_cdecl * TacviewUIRendererCreateRenderState172)(void * addonHandle, const RenderState * renderState);
	typedef void(_cdecl * TacviewUIRendererReleaseRenderState172)(void * addonHandle, RenderStateHandle renderStateHandle);

	typedef void(_cdecl * TacviewUIRendererDrawObjectVertexArray172)(void * addonHandle, const ObjectRenderSphericalTransform * transform, RenderStateHandle renderStateHandle, VertexArrayHandle vertexArrayHandle, TextureCoordinateArrayHandle textureCoordinateArrayHandle);
	typedef void(_cdecl * TacviewUIRendererDrawObjectVertexArray2172)(void * addonHandle, const ObjectRenderCartesianTransform * transform, RenderStateHandle renderStateHandle, VertexArrayHandle vertexArrayHandle, TextureCoordinateArrayHandle textureCoordinateArrayHandle);
	typedef void(_cdecl * TacviewUIRendererDrawUIVertexArray172)(void * addonHandle, const UIRenderTransform * transform, RenderStateHandle renderStateHandle, VertexArrayHandle vertexArrayHandle, TextureCoordinateArrayHandle textureCoordinateArrayHandle);
	typedef void(_cdecl * TacviewUIRendererDrawUIVertexArray180)(void * addonHandle, const UIRenderShapeTransform * transform, RenderStateHandle renderStateHandle, VertexArrayHandle vertexArrayHandle, TextureCoordinateArrayHandle textureCoordinateArrayHandle);

	typedef void(_cdecl * TacviewUIRendererDrawOpaqueObject172)(void * addonHandle, ObjectHandle objectHandle, const ObjectRenderSphericalTransform * transform, float alpha);
	typedef void(_cdecl * TacviewUIRendererDrawOpaqueObject2172)(void * addonHandle, ObjectHandle objectHandle, const ObjectRenderCartesianTransform * transform, float alpha);
	typedef void(_cdecl * TacviewUIRendererDrawTransparentObject172)(void * addonHandle, ObjectHandle objectHandle, const ObjectRenderSphericalTransform * transform, float alpha);
	typedef void(_cdecl * TacviewUIRendererDrawTransparentObject2172)(void * addonHandle, ObjectHandle objectHandle, const ObjectRenderCartesianTransform * transform, float alpha);

	typedef void(_cdecl * TacviewUIRendererPrint173)(void * addonHandle, const UIRenderTransform * transform, RenderStateHandle renderStateHandle, const wchar_t * text);
	typedef void(_cdecl * TacviewUIRendererPrint180)(void * addonHandle, const UIRenderTextTransform * transform, RenderStateHandle renderStateHandle, const wchar_t * text);

	typedef void(_cdecl * TacviewUIRendererContextMenuRegisterListener176)(void * addonHandle, TacviewUIRendererContextMenuEventHandler176 eventHandler, void * userData);

	typedef void(_cdecl * TacviewUIRendererPick3DPointRegisterListener186)(void * addonHandle, TacviewUIRendererPick3DPointEventHandler186 eventHandler, void * userData);

	typedef ModelHandle(_cdecl * TacviewUIRendererLoad3DModel185)(void * addonHandle, const wchar_t * fileName);
	typedef void(_cdecl * TacviewUIRendererDraw3DModel185)(void * addonHandle, ModelHandle modelHandle, const ObjectRenderSphericalTransform * transform, uint32_t color);
	typedef void(_cdecl * TacviewUIRendererDraw3DModel2185)(void * addonHandle, ModelHandle modelHandle, const ObjectRenderCartesianTransform * transform, uint32_t color);
	typedef void(_cdecl * TacviewUIRendererDrawSemiTransparent3DModel185)(void * addonHandle, ModelHandle modelHandle, const ObjectRenderSphericalTransform * transform, uint32_t color);
	typedef void(_cdecl * TacviewUIRendererDrawSemiTransparent3DModel2185)(void * addonHandle, ModelHandle modelHandle, const ObjectRenderCartesianTransform * transform, uint32_t color);

	// Tacview.IO

	typedef uint64_t(_cdecl * TacviewIOStreamGetLength180)(void * addonHandle, void * stream);
	typedef uint64_t(_cdecl * TacviewIOStreamGetPosition180)(void * addonHandle, void * stream);
	typedef bool(_cdecl * TacviewIOStreamSetPosition180)(void * addonHandle, void * stream, uint64_t newAbsolutePosition);
	typedef bool(_cdecl * TacviewIOStreamReadData180)(void * addonHandle, void * stream, void * dataBuffer, uint64_t dataSize);

	typedef void(_cdecl * TacviewIOImportSetProgress180)(void * addonHandle, void * operationStatus, double progressionRatio);
	typedef bool(_cdecl * TacviewIOImportOperationHasBeenCanceled180)(void * addonHandle, void * operation);

	struct ImportMetaData
	{
		void * stream;
		void * operationStatus;
		const wchar_t * documentName;
		double documentAbsoluteTime;
		uint64_t uniqueIdOffset;
	};

	typedef bool(_cdecl * TacviewIOImportCallback180)(void * userData, const ImportMetaData * metaData);

	struct ImporterDeclaration
	{
		TacviewIOImportCallback180 importCallback;
		void * userData;

		float priority;						// 0.3

		const wchar_t * extensionList;		// "txt.acmi;csv;gpx"
		const wchar_t * fileDescription;	// "Tacview Text Telemetry Data"
	};

	typedef void(_cdecl * TacviewIOImportRegisterImporter180)(void * addonHandle, const ImporterDeclaration * declaration);

	// Interfaces

	struct Interface
	{
	};

	///////////////////////////////////////////////////////////////
	// WARNING
	// DO NOT CHANGE THE FOLLOWING STRUCTURE.
	// FAILURE TO DO SO WILL BREAK COMPATIBILITY WITH OLDER ADDONS.
	///////////////////////////////////////////////////////////////

	struct Interface173 : public Interface
	{
		// Glocal functions

		TacviewClose172 Close;

		// Tacview.AddOns

		TacviewAddOnsCurrentSetTitle172 AddOnsCurrentSetTitle;
		TacviewAddOnsCurrentSetVersion172 AddOnsCurrentSetVersion;
		TacviewAddOnsCurrentSetAuthor172 AddOnsCurrentSetAuthor;
		TacviewAddOnsCurrentSetNotes172 AddOnsCurrentSetNotes;

		TacviewAddOnsCurrentSettingsGetBoolean172 AddOnsCurrentSettingsGetBoolean;
		TacviewAddOnsCurrentSettingsSetBoolean172 AddOnsCurrentSettingsSetBoolean;

		// Tacview.Context

		TacviewContextGetSelectedObject172 ContextGetSelectedObject;
		TacviewContextSetSelectedObject172 ContextSetSelectedObject;

		TacviewContextGetActiveObjectList173 ContextGetActiveObjectList;

		TacviewContextCameraGetMode172 ContextCameraGetMode;
		TacviewContextCameraSetOffset172 ContextCameraSetOffset;
		TacviewContextCameraSetFieldOfView172 ContextCameraSetFieldOfView;

		// Tacview.Events

		TacviewEventsUpdateRegisterListener172 EventsUpdateRegisterListener;
		TacviewEventsDrawOpaqueObjectsRegisterListener172 EventsDrawOpaqueObjectsRegisterListener;
		TacviewEventsDrawTransparentObjectsRegisterListener172 EventsDrawTransparentObjectsRegisterListener;
		TacviewEventsDrawOpaqueUIRegisterListener172 EventsDrawOpaqueUIRegisterListener;
		TacviewEventsDrawTransparentUIRegisterListener172 EventsDrawTransparentUIRegisterListener;

		// Tacview.Log

		TacviewLogDebug172 LogDebug;
		TacviewLogInfo172 LogInfo;
		TacviewLogWarning172 LogWarning;
		TacviewLogError172 LogError;

		// Tacview.Math

		TacviewMathAngleSubtract172 MathAngleSubtract;

		TacviewMathVectorAdd172 MathVectorAdd;
		TacviewMathVectorSubtract172 MathVectorSubtract;
		TacviewMathVectorNormalize172 MathVectorNormalize;
		TacviewMathVectorAngleBetween172 MathVectorAngleBetween;
		TacviewMathVectorAngleBetween2172 MathVectorAngleBetween2;
		TacviewMathVectorLocalToGlobal172 MathVectorLocalToGlobal;
		TacviewMathVectorLocalToGlobal2172 MathVectorLocalToGlobal2;
		TacviewMathVectorLongitudeLatitudeToCartesian172 MathVectorLongitudeLatitudeToCartesian;

		// Tacview.Settings

		TacviewSettingsGetBoolean172 SettingsGetBoolean;
		TacviewSettingsSetBoolean172 SettingsSetBoolean;

		TacviewSettingsGetString172 SettingsGetString;
		TacviewSettingsSetString172 SettingsSetString;

		// Tacview.Telemetry

		TacviewTelemetryClear172 TelemetryClear;

		TacviewTelemetryGetCurrentObjectHandle172 TelemetryGetCurrentObjectHandle;

		TacviewTelemetryGetCurrentTags173 TelemetryGetCurrentTags;
		TacviewTelemetryGetCurrentShortName172 TelemetryGetCurrentShortName;

		TacviewTelemetryGetCurrentTransform172 TelemetryGetCurrentTransform;

		TacviewTelemetryGetCurrentAngleOfAttack173 TelemetryGetCurrentAngleOfAttack;
		TacviewTelemetryGetCurrentVerticalGForce173 TelemetryGetCurrentVerticalGForce;

		// Tacview.UI

		TacviewUIMessageBoxInfo172 UIMessageBoxInfo;
		TacviewUIMessageBoxError172 UIMessageBoxError;
		TacviewUIMessageBoxQuestion172 UIMessageBoxQuestion;

		TacviewUIEnterFullScreen172 UIEnterFullScreen;
		TacviewUIExitFullScreen172 UIExitFullScreen;
		TacviewUIEnterReadMode172 UIEnterReadMode;
		TacviewUIExitReadMode172 UIExitReadMode;
		TacviewUISetWindowParent172 UISetWindowParent;
		TacviewUISetWindowPosition172 UISetWindowPosition;
		TacviewUISetWindowPosition2172 UISetWindowPosition2;
		TacviewUISetWindowSize172 UISetWindowSize;

		TacviewUIMenusAddMenu172 UIMenusAddMenu;
		TacviewUIMenusAddCommand172 UIMenusAddCommand;
		TacviewUIMenusAddOption172 UIMenusAddOption;
		TacviewUIMenusSetOption172 UIMenusSetOption;

		TacviewUIRendererGetWidth172 UIRendererGetWidth;
		TacviewUIRendererGetHeight172 UIRendererGetHeight;

		TacviewUIRendererLoadTexture173 UIRendererLoadTexture;
		TacviewUIRendererUnloadTexture173 UIRendererUnloadTexture;

		TacviewUIRendererCreateVertexArray172 UIRendererCreateVertexArray;
		TacviewUIRendererReleaseVertexArray172 UIRendererReleaseVertexArray;
		TacviewUIRendererCreateTextureCoordinateArray173 UIRendererCreateTextureCoordinateArray;
		TacviewUIRendererReleaseTextureCoordinateArray173 UIRendererReleaseTextureCoordinateArray;
		TacviewUIRendererCreateRenderState172 UIRendererCreateRenderState;
		TacviewUIRendererReleaseRenderState172 UIRendererReleaseRenderState;

		TacviewUIRendererDrawObjectVertexArray172 UIRendererDrawObjectVertexArray;
		TacviewUIRendererDrawObjectVertexArray2172 UIRendererDrawObjectVertexArray2;
		TacviewUIRendererDrawUIVertexArray172 UIRendererDrawUIVertexArray;
		TacviewUIRendererDrawOpaqueObject172 UIRendererDrawOpaqueObject;
		TacviewUIRendererDrawOpaqueObject2172 UIRendererDrawOpaqueObject2;
		TacviewUIRendererDrawTransparentObject172 UIRendererDrawTransparentObject;
		TacviewUIRendererDrawTransparentObject2172 UIRendererDrawTransparentObject2;

		TacviewUIRendererPrint173 UIRendererPrint;

		// Constants

		// Tacview.Telemetry.Tags

		// WARNING: These are binary tags for performance, NOT storage.
		// The value of these tags can change from one version to another.
		// DO NOT save them in files.
		// If you need persistence, instead use the text object type which is fully portable.

		ObjectTags TelemetryTagsFixedWing;
		ObjectTags TelemetryTagsRotorcraft;

		ObjectTags TelemetryTagsArmor;
		ObjectTags TelemetryTagsAntiAircraft;
		ObjectTags TelemetryTagsVehicle;
		ObjectTags TelemetryTagsWatercraft;

		ObjectTags TelemetryTagsHuman;
		ObjectTags TelemetryTagsBiologic;

		ObjectTags TelemetryTagsMissile;
		ObjectTags TelemetryTagsRocket;
		ObjectTags TelemetryTagsBomb;
		ObjectTags TelemetryTagsTorpedo;
		ObjectTags TelemetryTagsProjectile;
		ObjectTags TelemetryTagsBeam;

		ObjectTags TelemetryTagsDecoy;

		ObjectTags TelemetryTagsBuilding;

		ObjectTags TelemetryTagsBullseye;
	};

	///////////////////////////////////////////////////////////////
	// WARNING
	// DO NOT CHANGE THE FOLLOWING STRUCTURE.
	// FAILURE TO DO SO WILL BREAK COMPATIBILITY WITH OLDER ADDONS.
	///////////////////////////////////////////////////////////////

	struct Interface174 : public Interface173
	{
		// Tacview.AddOns

		TacviewAddOnsCurrentGetPath174 AddOnsCurrentGetPath;

		// Tacview.Math

		TacviewMathAngleSubtract174 MathAngleSubtract2;
	};

	///////////////////////////////////////////////////////////////
	// WARNING
	// DO NOT CHANGE THE FOLLOWING STRUCTURE.
	// FAILURE TO DO SO WILL BREAK COMPATIBILITY WITH OLDER ADDONS.
	///////////////////////////////////////////////////////////////

	struct Interface175 : public Interface174
	{
		// Tacview.Context

		TacviewContextGetAbsoluteTime175 ContextGetAbsoluteTime;

		// Tacview.Math

		TacviewMathVectorMultiply175 MathVectorMultiply;

		TacviewMathVectorCartesianToLongitudeLatitude175 MathVectorCartesianToLongitudeLatitude;

		// Tacview.Telemetry

		TacviewTelemetryGetCurrentOrCreateObjectHandle175 TelemetryGetCurrentOrCreateObjectHandle;
		TacviewTelemetryGetOrCreateObjectHandle175 TelemetryGetOrCreateObjectHandle;

		TacviewTelemetryDeleteObject175 TelemetryDeleteObject;

		TacviewTelemetryGetObjectsNumericPropertyIndex175 TelemetryGetObjectsNumericPropertyIndex;
		TacviewTelemetryGetObjectsTextPropertyIndex175 TelemetryGetObjectsTextPropertyIndex;

		TacviewTelemetrySetLifeTimeEnd175 TelemetrySetLifeTimeEnd;

		TacviewTelemetryGetNumericSample175 TelemetryGetNumericSample;
		TacviewTelemetryGetTextSample175 TelemetryGetTextSample;
		TacviewTelemetryGetTransform175 TelemetryGetTransform;

		TacviewTelemetrySetNumericSample175 TelemetrySetNumericSample;
		TacviewTelemetrySetTextSample175 TelemetrySetTextSample;
		TacviewTelemetrySetTransform175 TelemetrySetTransform;

		// Tacview.Telemetry.Tags

		ObjectTags TelemetryTagsWaypoint;

		// Tacview.Terrain

		TacviewTerrainGetElevation175 TerrainGetElevation;

		// Tacview.UI

		TacviewUIGetWindowHandle175 UIGetWindowHandle;
	};

	///////////////////////////////////////////////////////////////
	// WARNING
	// DO NOT CHANGE THE FOLLOWING STRUCTURE.
	// FAILURE TO DO SO WILL BREAK COMPATIBILITY WITH OLDER ADDONS.
	///////////////////////////////////////////////////////////////

	struct Interface176 : public Interface175
	{
		// Tacview.Context

		TacviewContextSetAbsoluteTime176 ContextSetAbsoluteTime;

		// Tacview.Context.Playback

		TacviewContextPlaybackPlay176 ContextPlaybackPlay;
		TacviewContextPlaybackPause176 ContextPlaybackPause;
		TacviewContextPlaybackIsPlaying176 ContextPlaybackIsPlaying;

		// Tacview.Telemetry

		TacviewTelemetryGetObjectCount176 TelemetryGetObjectCount;

		TacviewTelemetryGetObjectHandleByIndex176 TelemetryGetObjectHandleByIndex;
		TacviewTelemetryGetObjectId176 TelemetryGetObjectId;

		TacviewTelemetryIsEmpty176 TelemetryIsEmpty;
		TacviewTelemetryIsLikeEmpty176 TelemetryIsLikeEmpty;
		TacviewTelemetryGetDataTimeRange176 TelemetryGetDataTimeRange;
		TacviewTelemetryGetLifeTime176 TelemetryGetLifeTime;

		TacviewTelemetryGetGlobalNumericPropertyIndex176 TelemetryGetGlobalNumericPropertyIndex;
		TacviewTelemetryGetGlobalTextPropertyIndex176 TelemetryGetGlobalTextPropertyIndex;

		// Tacview.UI.Renderer.ContextMenu

		TacviewUIRendererContextMenuRegisterListener176 UIRendererContextMenuRegisterListerner;
	};

	///////////////////////////////////////////////////////////////
	// WARNING
	// DO NOT CHANGE THE FOLLOWING STRUCTURE.
	// FAILURE TO DO SO WILL BREAK COMPATIBILITY WITH OLDER ADDONS.
	///////////////////////////////////////////////////////////////

	struct Interface180 : public Interface176
	{
		// Constants

		// Tacview.Telemetry.Tags

		// WARNING: These are binary tags for performance, NOT storage.
		// The value of these tags can change from one version to another.
		// DO NOT save them in files.
		// If you need persistence, instead use the text object type which is fully portable.

		// Domain

		ObjectTags TelemetryTagsAir;
		ObjectTags TelemetryTagsGround;
		ObjectTags TelemetryTagsSea;		// Includes under water objects

		ObjectTags TelemetryTagsWeapon;
		ObjectTags TelemetryTagsSensor;
		ObjectTags TelemetryTagsNavaid;
		ObjectTags TelemetryTagsAbstract;
		ObjectTags TelemetryTagsMisc;

		// Attributes

		ObjectTags TelemetryTagsStatic;
		ObjectTags TelemetryTagsHeavy;
		ObjectTags TelemetryTagsMedium;
		ObjectTags TelemetryTagsLight;
		ObjectTags TelemetryTagsMinor;

		// Specific Type

		ObjectTags TelemetryTagsTank;
		ObjectTags TelemetryTagsWarship;
		ObjectTags TelemetryTagsAircraftCarrier;
		ObjectTags TelemetryTagsSubmarine;
		ObjectTags TelemetryTagsInfantry;
		ObjectTags TelemetryTagsParachutist;

		ObjectTags TelemetryTagsShell;
		ObjectTags TelemetryTagsBullet;

		ObjectTags TelemetryTagsFlare;
		ObjectTags TelemetryTagsChaff;
		ObjectTags TelemetryTagsSmokeGrenade;

		ObjectTags TelemetryTagsAerodrome;

		ObjectTags TelemetryTagsContainer;
		ObjectTags TelemetryTagsShrapnel;
		ObjectTags TelemetryTagsExplosion;

		// Tacview.Context

		TacviewContextCameraSetRotation180 ContextCameraSetRotation;
		TacviewContextCameraSetRangeToTarget180 ContextCameraSetRangeToTarget;

		// Tacview.IO

		TacviewIOStreamGetLength180 IOStreamGetLength;
		TacviewIOStreamGetPosition180 IOStreamGetPosition;
		TacviewIOStreamSetPosition180 IOStreamSetPosition;
		TacviewIOStreamReadData180 IOStreamReadData;

		TacviewIOImportSetProgress180 IOImportSetProgress;
		TacviewIOImportOperationHasBeenCanceled180 IOImportOperationHasBeenCanceled;

		TacviewIOImportRegisterImporter180 IOImportRegisterImporter;

		// Tacview.Math

		TacviewMathUnitsFeetToMeters180 MathUnitsFeetToMeters;
		TacviewMathUnitsNauticalMilesToMeters180 MathUnitsNauticalMilesToMeters;

		TacviewMathVectorGetLength180 MathVectorGetLength;
		TacviewMathVectorGetDistance180 MathVectorGetDistance;
		TacviewMathVectorGetDistanceOnEarth180 MathVectorGetDistanceOnEarth;
		TacviewMathVectorBearingRangeAltitudeToLongitudeLatitude180 MathVectorBearingRangeAltitudeToLongitudeLatitude;

		// Tacview.StaticObjects

		TacviewStaticObjectsGetObjectHandleByName180 StaticObjectsGetObjectHandleByName;
		TacviewStaticObjectsSetVisible180 StaticObjectsSetVisible;

		// Tacview.Telemetry

		TacviewTelemetryLoad180 TelemetryLoad;

		TacviewTelemetryAllGivenTagsActive180 TelemetryAllGivenTagsActive;
		TacviewTelemetryAnyGivenTagActive180 TelemetryAnyGivenTagActive;

		TacviewTelemetryGetNumericSampleCount180 TelemetryGetNumericSampleCount;
		TacviewTelemetryGetNumericSampleFromIndex180 TelemetryGetNumericSampleFromIndex;
		TacviewTelemetryGetTextSampleCount180 TelemetryGetTextSampleCount;
		TacviewTelemetryGetTextSampleFromIndex180 TelemetryGetTextSampleFromIndex;

		TacviewTelemetryRemoveNumericSample180 TelemetryRemoveNumericSample;
		TacviewTelemetryRemoveNumericSampleFromIndex180 TelemetryRemoveNumericSampleFromIndex;
		TacviewTelemetryRemoveTextSample180 TelemetryRemoveTextSample;
		TacviewTelemetryRemoveTextSampleFromIndex180 TelemetryRemoveTextSampleFromIndex;

		TacviewTelemetryGetTransformTimeRange180 TelemetryGetTransformTimeRange;

		TacviewTelemetryGetVerticalGForce180 TelemetryGetVerticalGForce;
		TacviewTelemetryGetAbsoluteGForce180 TelemetryGetAbsoluteGForce;
		TacviewTelemetryGetCurrentAbsoluteGForce180 TelemetryGetCurrentAbsoluteGForce;

		// Tacview.UI.Renderer

		TacviewUIRendererDrawUIVertexArray180 UIRendererDrawUIVertexArray2;
		TacviewUIRendererPrint180 UIRendererPrint2;

		// Tacview.UI.Menu

		TacviewUIMenusAddSeparator180 UIMenusAddSeparator;

		// Tacview.UI.MessageBox

		TacviewUIMessageBoxGetSaveFileName180 UIMessageBoxGetSaveFileName;
		TacviewUIMessageBoxGetFolderName180 UIMessageBoxGetFolderName;
	};

	///////////////////////////////////////////////////////////////
	// WARNING
	// DO NOT CHANGE THE FOLLOWING STRUCTURE.
	// FAILURE TO DO SO WILL BREAK COMPATIBILITY WITH OLDER ADDONS.
	///////////////////////////////////////////////////////////////

	struct Interface182 : public Interface180
	{
		// AddOns.Current.Settings

		TacviewAddOnsCurrentSettingsGetString182 AddOnsCurrentSettingsGetString;
		TacviewAddOnsCurrentSettingsSetString182 AddOnsCurrentSettingsSetString;

		// Database

		TacviewDatabaseGetNextRecord182 DatabaseGetNextRecord;

		TacviewDatabaseGetRecordId182 DatabaseGetRecordId;
		TacviewDatabaseGetRecordPriority182 DatabaseGetRecordPriority;

		TacviewDatabaseGetTextPropertyIndex182 DatabaseGetTextPropertyIndex;
		TacviewDatabaseGetNumericPropertyIndex182 DatabaseGetNumericPropertyIndex;

		TacviewDatabaseGetRecordTextValue182 DatabaseGetRecordTextValue;
		TacviewDatabaseGetRecordNumericValue182 DatabaseGetRecordNumericValue;

		// UI.Format

		TacviewUIFormatAltitudeToText182 UIFormatAltitudeToText;
		TacviewUIFormatTextToAltitude182 UIFormatTextToAltitude;

		TacviewUIFormatDistanceToText182 UIFormatDistanceToText;
		TacviewUIFormatTextToDistance182 UIFormatTextToDistance;

		TacviewUIFormatLongitudeToText182 UIFormatLongitudeToText;
		TacviewUIFormatLatitudeToText182 UIFormatLatitudeToText;
		TacviewUIFormatTextToSpherical182 UIFormatTextToSpherical;

		// UI.MessageBox

		TacviewUIMessageBoxGetOpenFileName182 UIMessageBoxGetOpenFileName;

		// Events.DocumentLoaded.RegisterListener

		TacviewEventsDocumentLoadedRegisterListener182 EventsDocumentLoadedRegisterListener;
	};

	///////////////////////////////////////////////////////////////
	// WARNING
	// DO NOT CHANGE THE FOLLOWING STRUCTURE.
	// FAILURE TO DO SO WILL BREAK COMPATIBILITY WITH OLDER ADDONS.
	///////////////////////////////////////////////////////////////

	struct Interface183 : public Interface182
	{
		// Database

		TacviewDatabaseReload183 DatabaseReload;

		// UI

		TacviewUIUpdate183 UIUpdate;

		// UI.Format

		TacviewUIFormatTextToAltitudeLocalized183 UIFormatTextToAltitudeLocalized;
		TacviewUIFormatTextToDistanceLocalized183 UIFormatTextToDistanceLocalized;

		TacviewUIFormatSpeedToText183 UIFormatSpeedToText;
		TacviewUIFormatTextToSpeed183 UIFormatTextToSpeed;
		TacviewUIFormatTextToSpeedLocalized183 UIFormatTextToSpeedLocalized;

		TacviewUIFormatAbsoluteTimeToISOText183 UIFormatAbsoluteTimeToISOText;
		TacviewUIFormatTextToAbsoluteTime183 UIFormatTextToAbsoluteTime;
	};

	///////////////////////////////////////////////////////////////
	// WARNING
	// DO NOT CHANGE THE FOLLOWING STRUCTURE.
	// FAILURE TO DO SO WILL BREAK COMPATIBILITY WITH OLDER ADDONS.
	///////////////////////////////////////////////////////////////

	struct Interface184 : public Interface183
	{
		// Events.DocumentUnload.RegisterListener

		TacviewEventsDocumentUnloadRegisterListener184 EventsDocumentUnloadRegisterListener;

		// Math.Vector.GetDistance

		TacviewMathVectorGetDistanceBetweenObjects184 MathVectorGetDistanceBetweenObjects;

		// SoundPlayer

		TacviewSoundPlayerPlay184 SoundPlayerPlay;
		TacviewSoundPlayerStop184 SoundPlayerStop;

		// UI.Telemetry

		TacviewTelemetryGetInstantaneousTurnRadius184 TelemetryGetInstantaneousTurnRadius;
		TacviewTelemetryGetTurnRadius184 TelemetryGetTurnRadius;
		TacviewTelemetryGetCurrentInstantaneousTurnRadius184 TelemetryGetCurrentInstantaneousTurnRadius;
		TacviewTelemetryGetCurrentTurnRadius184 TelemetryGetCurrentTurnRadius;

		TacviewTelemetryGetInstantaneousTurnRate184 TelemetryGetInstantaneousTurnRate;
		TacviewTelemetryGetTurnRate184 TelemetryGetTurnRate;
		TacviewTelemetryGetCurrentInstantaneousTurnRate184 TelemetryGetCurrentInstantaneousTurnRate;
		TacviewTelemetryGetCurrentTurnRate184 TelemetryGetCurrentTurnRate;

		TacviewTelemetryGetMachNumber184 TelemetryGetMachNumber;
		TacviewTelemetryGetCurrentMachNumber184 TelemetryGetCurrentMachNumber;

		// UI.Menu

		TacviewUIMenusAddExclusiveOption184 UIMenusAddExclusiveOption;

		// UI.Renderer

		TacviewUIRendererDrawLines184 UIRendererDrawLines;
		TacviewUIRendererDrawColoredLines184 UIRendererDrawColoredLines;
		TacviewUIRendererDrawLineStrip184 UIRendererDrawLineStrip;
		TacviewUIRendererDrawColoredLineStrip184 UIRendererDrawColoredLineStrip;
	};

	///////////////////////////////////////////////////////////////
	// WARNING
	// DO NOT CHANGE THE FOLLOWING STRUCTURE.
	// FAILURE TO DO SO WILL BREAK COMPATIBILITY WITH OLDER ADDONS.
	///////////////////////////////////////////////////////////////

	struct Interface185 : public Interface184
	{
		// Context

		TacviewContextCameraGetSphericalPosition185 ContextCameraGetSphericalPosition;

		// Events

		TacviewEventsPowerSaveRegisterListener185 EventsPowerSaveRegisterListener;

		// Math

		TacviewMathAngleNormalizePiFloat185 MathAngleNormalizePiFloat;
		TacviewMathAngleNormalizePiDouble185 MathAngleNormalizePiDouble;
		TacviewMathAngleNormalize2PiFloat185 MathAngleNormalize2PiFloat;
		TacviewMathAngleNormalize2PiDouble185 MathAngleNormalize2PiDouble;

		// Media

		TacviewMediaLoad185 MediaLoad;
		TacviewMediaLoad2185 MediaLoad2;

		// MessageBox

		TacviewUIMessageBoxInputText185 UIMessageBoxInputText;

		// Renderer

		TacviewUIRendererLoad3DModel185 UIRendererLoad3DModel;
		TacviewUIRendererDraw3DModel185 UIRendererDraw3DModel;
		TacviewUIRendererDraw3DModel2185 UIRendererDraw3DModel2;

		// Settings

		TacviewSettingsGetAltitudeUnit185 SettingsGetAltitudeUnit;

		// String

		TacviewStringCrc32185 StringCrc32;

		// Telemetry

		TacviewTelemetryOnLoadStart185 TelemetryOnLoadStart;
		TacviewTelemetryOnLoadEnd185 TelemetryOnLoadEnd;
	};

	///////////////////////////////////////////////////////////////
	// WARNING
	// DO NOT CHANGE THE FOLLOWING STRUCTURE.
	// FAILURE TO DO SO WILL BREAK COMPATIBILITY WITH OLDER ADDONS.
	///////////////////////////////////////////////////////////////

	struct Interface186 : public Interface185
	{
		// Addons

		TacviewSettingsGetNumber186 SettingsGetNumber;
		TacviewSettingsSetNumber186 SettingsSetNumber;

		// Events

		TacviewEventsDrawTransparentObjectsNearRegisterListener186 EventsDrawTransparentObjectsNearRegisterListener;

		// Renderer

		TacviewUIRendererDrawSemiTransparent3DModel185 UIRendererDrawSemiTransparent3DModel;
		TacviewUIRendererDrawSemiTransparent3DModel2185 UIRendererDrawSemiTransparent3DModel2;

		TacviewUIRendererPick3DPointRegisterListener186 UIRendererPick3DPointRegisterListener;

		// Telemetry

		TacviewTelemetryGetObjectHandle186 TelemetryGetObjectHandle;

		TacviewTelemetryGetTransformCount186 TelemetryGetTransformCount;
		TacviewTelemetryGetTransformFromIndex186 TelemetryGetTransformFromIndex;

		TacviewTelemetryGetLateralGForce186 TelemetryGetLateralGForce;
		TacviewTelemetryGetCurrentLateralGForce186 TelemetryGetCurrentLateralGForce;
		TacviewTelemetryGetLongitudinalGForce186 TelemetryGetLongitudinalGForce;
		TacviewTelemetryGetCurrentLongitudinalGForce186 TelemetryGetCurrentLongitudinalGForce;
		TacviewTelemetryGetCurrentAngleOfSideslip186 TelemetryGetCurrentAngleOfSideslip;
		TacviewTelemetryGetCalculatedTransform186 TelemetryGetCalculatedTransform;
		TacviewTelemetryGetCurrentCalculatedTransform186 TelemetryGetCurrentCalculatedTransform;
	};

	///////////////////////////////////////////////////////////////
	// WARNING
	// DO NOT CHANGE THE FOLLOWING STRUCTURE.
	// FAILURE TO DO SO WILL BREAK COMPATIBILITY WITH OLDER ADDONS.
	///////////////////////////////////////////////////////////////

	struct Interface187 : public Interface186
	{
		// Tacview.Context

		TacviewContextGetDocumentPath187 ContextGetDocumentPath;

		// Tacview.Directory

		TacviewDirectoryCreateDirectory187 DirectoryCreateDirectory;
		TacviewDirectoryDelete187 DirectoryDelete;
		TacviewDirectoryGetFiles187 DirectoryGetFiles;

		// Tacview.Events.DocumentLoaded.RegisterListener

		TacviewEventsDocumentLoadedRegisterListener187 EventsDocumentLoadedRegisterListener2;

		// Tacview.Math

		TacviewMathUnitsMetersToFeet187 MathUnitsMetersToFeet;
		TacviewMathUnitsMetersToNauticalMiles187 MathUnitsMetersToNauticalMiles;
		TacviewMathUnitsKnotsToMetersPerSecond187 MathUnitsKnotsToMetersPerSecond;
		TacviewMathUnitsMetersPerSecondToKnots187 MathUnitsMetersPerSecondToKnots;

		TacviewMathVectorLongitudeLatitudeToBearingRangeAltitude187 MathVectorLongitudeLatitudeToBearingRangeAltitude;

		// Tacview.Media

		TacviewMediaUnload187 MediaUnload;
		TacviewMediaClose187 MediaClose;

		// Tacview.Path

		TacviewPathGetDirectoryName187 PathGetDirectoryName;
		TacviewPathGetFileName187 PathGetFileName;

		// Tacview.Telemetry

		TacviewTelemetryRemoveTransformSample187 TelemetryRemoveTransformSample;
		TacviewTelemetryRemoveTransformSampleFromIndex187 TelemetryRemoveTransformSampleFromIndex;

		// Tacview.Terrain

		TacviewTerrainAddCustomTexture187 TerrainAddCustomTexture;
		TacviewTerrainShowCustomTexture187 TerrainShowCustomTexture;
		TacviewTerrainHideCustomTexture187 TerrainHideCustomTexture;

		// Tacview.UI

		TacviewUIMessageBoxWarning187 UIMessageBoxWarning;
	};

	// Call this function to retrieve one of the available Tacview interface:
	// interface = GetInterface(addonHandle, "Tacview180")

	typedef Interface * (_cdecl * GetInterface)(void * addonHandle, const char * interfaceName);
}

#endif // TACVIEW_SDK_INTERFACE_H
