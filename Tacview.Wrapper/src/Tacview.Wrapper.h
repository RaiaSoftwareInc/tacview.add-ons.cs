/*
	Tacview.Wrapper.Main
	C# DLL add-on wrapper
	Version 1.7.3 // 2018-10-04
	Copyright (C) 2018 Raia Software. All rights reserved.

	NOTE: You need a licence of Tacview Enterprise to run C# addons.
*/

#pragma once

#ifndef TACVIEW_WRAPPER_H
#define	TACVIEW_WRAPPER_H

using namespace System;
using namespace System::Collections::Generic;
using namespace System::Runtime::InteropServices;

namespace TacviewSDK
{
	public ref class Wrapper
	{
	public:

		// **************************************************************** //
		// Aliases
		// **************************************************************** //

		typedef IntPtr RecordHandle;
		typedef IntPtr ObjectHandle;
		typedef IntPtr StaticObjectHandle;
		typedef TacviewSDK::ObjectId ObjectId;
		typedef TacviewSDK::ObjectTags ObjectTags;

		typedef IntPtr TextureHandle;
		typedef IntPtr VertexArrayHandle;
		typedef IntPtr TextureCoordinateArrayHandle;
		typedef IntPtr RenderStateHandle;

		// **************************************************************** //
		// PODs
		// **************************************************************** //

		ref struct CameraOffset
		{
			float lateral;
			float longitudinal;
			float vertical;
			float roll;
			float pitch;
			float yaw;
		};

		ref struct float2
		{
			float x;
			float y;
		};

		ref struct float3
		{
			float x;
			float y;
			float z;
		};

		ref struct double3
		{
			double3(double _x, double _y, double _z)
			{
				x = _x;
				y = _y;
				z = _z;
			}

			double x;
			double y;
			double z;
		};

		ref struct ObjectTransformInput
		{
			enum class Flags
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

		ref struct ObjectTransformOutput
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

		ref struct ObjectSphericalTransform
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

		ref struct ObjectCartesianTransform
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

		ref struct RenderState
		{
			uint32_t color = 0xFFFFFFFF;
			TextureHandle textureHandle = (TextureHandle)nullptr;

			enum class BlendMode
			{
				Normal,
				Additive,
			};

			BlendMode blendMode = BlendMode::Normal;
		};

		ref struct ColorVertex
		{
			double x;
			double y;
			double z;
			uint32_t rgba;
		};

		ref struct ObjectRenderSphericalTransform
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

		ref struct ObjectRenderCartesianTransform
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

		ref struct UIRenderTransform
		{
			float x;
			float y;
			float z;

			float roll;
			float pitch;
			float yaw;

			float scale;
		};

		ref struct UIRenderTextTransform
		{
			float x;
			float y;
			float z;

			float scale;
		};

		ref struct UIRenderShapeTransform
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

		// **************************************************************** //
		// Functions called by the C# dll to initialize this wrapper
		// **************************************************************** //

		bool InitializeWrapper(System::IntPtr addonHandle, System::IntPtr TacviewGetInterface);
		void ShutdownWrapper();

		// **************************************************************** //
		// Tacview global functions
		// **************************************************************** //

		void Close();

		// **************************************************************** //
		// Tacview.Addons
		// **************************************************************** //

		ref class AddOnsClass
		{
		public:

			ref class CurrentClass
			{
			public:

				ref class SettingsClass
				{
				public:

					SettingsClass(void * newAddonHandle, TacviewSDK::Interface187 * newTacviewInterface);

					bool GetBoolean(String ^ settingName, bool defaultSettingValue);
					void SetBoolean(String ^ settingName, bool settingValue);

					String ^ GetString(String ^ settingName, String ^ defaultSettingValue);
					void SetString(String ^ settingName, String ^ settingValue);

				private:

					void * addonHandle;
					TacviewSDK::Interface187 * tacviewInterface;
				};

				SettingsClass ^ Settings;

				CurrentClass(void * newAddonHandle, TacviewSDK::Interface187 * newTacviewInterface);

				String ^ GetPath();

				void SetTitle(String ^ addonTitle);
				void SetVersion(String ^ addonVersionNumber);
				void SetAuthor(String ^ addonAuthorName);
				void SetNotes(String ^ addonNotes);

			private:

				void * addonHandle;
				TacviewSDK::Interface187 * tacviewInterface;
			};

			AddOnsClass(void * newAddonHandle, TacviewSDK::Interface187 * newTacviewInterface);

			CurrentClass ^ Current;
		};

		AddOnsClass ^ AddOns;

		// **************************************************************** //
		// Tacview.Context
		// **************************************************************** //

		ref class ContextClass
		{
		public:

			ref class CameraClass
			{
			public:

				enum class Mode
				{
					Cockpit = (int)TacviewSDK::CameraMode::Cockpit,
					External = (int)TacviewSDK::CameraMode::External,
					Satellite = (int)TacviewSDK::CameraMode::Satellite,
					Free = (int)TacviewSDK::CameraMode::Free,
				};

				CameraClass(void * newAddonHandle, TacviewSDK::Interface187 * newTacviewInterface);

				Mode GetMode();
				void SetOffset(CameraOffset ^ newCameraOffset);
				void SetFieldOfView(float vecticalFieldOfViewInRadian);
				void GetSphericalPosition([Out] double % longitude, [Out]  double % latitude, [Out]  double % altitude);
				void SetRotation(float roll, float pitch, float yaw);
				void SetRangeToTarget(double range);

			private:

				void * addonHandle;
				TacviewSDK::Interface187 * tacviewInterface;
			};

			CameraClass ^ Camera;

			ref class PlaybackClass
			{
			public:

				PlaybackClass(void * newAddonHandle, TacviewSDK::Interface187 * newTacviewInterface);

				void Play();
				void Pause();
				bool IsPlaying();

			private:

				void * addonHandle;
				TacviewSDK::Interface187 * tacviewInterface;
			};

			PlaybackClass ^ Playback;

			ContextClass(void * newAddonHandle, TacviewSDK::Interface187 * newTacviewInterface);

			double GetAbsoluteTime();
			void SetAbsoluteTime(double absoluteTime);

			ObjectHandle GetSelectedObject(int objectIndex);
			void SetSelectedObject(int objectIndex, ObjectHandle objectHandle);

			List<ObjectHandle> ^ GetActiveObjectList();

			String ^ GetDocumentPath();

		private:

			void * addonHandle;
			TacviewSDK::Interface187 * tacviewInterface;
		};

		ContextClass ^ Context;

		// **************************************************************** //
		// Tacview.Directory
		// **************************************************************** //

		ref class DirectoryClass
		{
		public:

			DirectoryClass(void * newAddonHandle, TacviewSDK::Interface187 * newTacviewInterface);

			bool CreateDirectory(String ^ directoryName);
			bool Delete(String ^directoryName, bool recursive);
			List<String^> ^ GetFiles(String ^ directoryName, bool recursive);

		private:

			void * addonHandle;
			TacviewSDK::Interface187 * tacviewInterface;
		};

		DirectoryClass ^ Directory;

		// **************************************************************** //
		// Tacview.Events
		// **************************************************************** //

		ref class EventsClass
		{
		public:

			ref class UpdateClass
			{
			public:

				delegate void UpdateHandler(float dt, double absoluteTime);
				event UpdateHandler ^ Listeners;

				UpdateClass(void * newAddonHandle, TacviewSDK::Interface187 * newTacviewInterface);
				virtual ~UpdateClass();

				void OnUpdate(float dt, double absoluteTime)
				{
					Listeners(dt, absoluteTime);
				}

			private:

				GCHandle selfHandle;
			};

			ref class DrawOpaqueObjectsClass
			{
			public:

				delegate void DrawOpaqueObjectsHandler();
				event DrawOpaqueObjectsHandler ^ Listeners;

				DrawOpaqueObjectsClass(void * newAddonHandle, TacviewSDK::Interface187 * newTacviewInterface);
				virtual ~DrawOpaqueObjectsClass();

				void OnDrawOpaqueObjects()
				{
					Listeners();
				}

			private:

				GCHandle selfHandle;
			};

			ref class DrawTransparentObjectsClass
			{
			public:

				delegate void DrawTransparentObjectsHandler();
				event DrawTransparentObjectsHandler ^ Listeners;

				DrawTransparentObjectsClass(void * newAddonHandle, TacviewSDK::Interface187 * newTacviewInterface);
				virtual ~DrawTransparentObjectsClass();

				void OnDrawTransparentObjects()
				{
					Listeners();
				}

			private:

				GCHandle selfHandle;
			};

			ref class DrawTransparentObjectsNearClass
			{
			public:

				delegate void DrawTransparentObjectsNearHandler();
				event DrawTransparentObjectsNearHandler ^ Listeners;

				DrawTransparentObjectsNearClass(void * newAddonHandle, TacviewSDK::Interface187 * newTacviewInterface);
				virtual ~DrawTransparentObjectsNearClass();

				void OnDrawTransparentObjectsNear()
				{
					Listeners();
				}

			private:

				GCHandle selfHandle;
			};

			ref class DrawOpaqueUIClass
			{
			public:

				delegate void DrawOpaqueUIHandler();
				event DrawOpaqueUIHandler ^ Listeners;

				DrawOpaqueUIClass(void * newAddonHandle, TacviewSDK::Interface187 * newTacviewInterface);
				virtual ~DrawOpaqueUIClass();

				void OnDrawOpaqueUI()
				{
					Listeners();
				}

			private:

				GCHandle selfHandle;
			};

			ref class DrawTransparentUIClass
			{
			public:

				delegate void DrawTransparentUIHandler();
				event DrawTransparentUIHandler ^ Listeners;

				DrawTransparentUIClass(void * newAddonHandle, TacviewSDK::Interface187 * newTacviewInterface);
				virtual ~DrawTransparentUIClass();

				void OnDrawTransparentUI()
				{
					Listeners();
				}

			private:

				GCHandle selfHandle;
			};

			ref class DocumentLoadedClass
			{
			public:

				delegate void DocumentLoadedHandler(System::String ^ fileNames);
				event DocumentLoadedHandler ^ Listeners;

				DocumentLoadedClass(void * newAddonHandle, TacviewSDK::Interface187 * newTacviewInterface);
				virtual ~DocumentLoadedClass();

				void OnDocumentLoaded(System::String ^ fileNames)
				{
					Listeners(fileNames);
				}

			private:

				GCHandle selfHandle;
			};

			ref class DocumentUnloadClass
			{
			public:

				delegate void DocumentUnloadHandler();
				event DocumentUnloadHandler ^ Listeners;

				DocumentUnloadClass(void * newAddonHandle, TacviewSDK::Interface187 * newTacviewInterface);
				virtual ~DocumentUnloadClass();

				void OnDocumentUnload()
				{
					Listeners();
				}

			private:

				GCHandle selfHandle;
			};

			ref class PowerSaveClass
			{
			public:

				delegate void PowerSaveHandler(bool & isIdle);
				event PowerSaveHandler ^ Listeners;

				PowerSaveClass(void * newAddonHandle, TacviewSDK::Interface187 * newTacviewInterface);
				virtual ~PowerSaveClass();

				bool OnPowerSave()
				{
					bool isIdle = true;
					Listeners(isIdle);
					return isIdle;
				}

			private:

				GCHandle selfHandle;
			};

			EventsClass(void * newAddonHandle, TacviewSDK::Interface187 * newTacviewInterface);

			UpdateClass ^ Update;

			DrawOpaqueObjectsClass ^ DrawOpaqueObjects;
			DrawTransparentObjectsClass ^ DrawTransparentObjects;
			DrawTransparentObjectsNearClass ^ DrawTransparentObjectsNear;
			DrawOpaqueUIClass ^ DrawOpaqueUI;
			DrawTransparentUIClass ^ DrawTransparentUI;

			DocumentLoadedClass ^ DocumentLoaded;
			DocumentUnloadClass ^ DocumentUnload;

			PowerSaveClass ^ PowerSave;
		};

		EventsClass ^ Events;

		// **************************************************************** //
		// Tacview.Log
		// **************************************************************** //

		ref class LogClass
		{
		public:

			LogClass(void * newAddonHandle, TacviewSDK::Interface187 * newTacviewInterface);

			void Debug(String ^ text);
			void Info(String ^ text);
			void Warning(String ^ text);
			void Error(String ^ text);

		private:

			void * addonHandle;
			TacviewSDK::Interface187 * tacviewInterface;
		};

		LogClass ^ Log;

		// **************************************************************** //
		// Tacview.Math
		// **************************************************************** //

		ref class MathClass
		{
		public:

			ref class AngleClass
			{
			public:

				AngleClass(void * newAddonHandle, TacviewSDK::Interface187 * newTacviewInterface);

				float Subtract(float angle1, float angle2);
				double Subtract(double angle1, double angle2);

				float NormalizePi(float angle);
				double NormalizePi(double angle);
				float Normalize2Pi(float angle);
				double Normalize2Pi(double angle);

			private:

				void * addonHandle;
				TacviewSDK::Interface187 * tacviewInterface;
			};

			ref class VectorClass
			{
			public:

				VectorClass(void * newAddonHandle, TacviewSDK::Interface187 * newTacviewInterface);

				double3 ^ Add(double3 ^ vec1, double3 ^ vec2);
				double3 ^ Subtract(double3 ^ vec1, double3 ^ vec2);
				double3 ^ Multiply(double factor, double3 ^ vec);

				double3 ^ Normalize(double3 ^ vec);
				double GetLength(double3 ^ vec);
				double GetDistance(double3 ^ pt1, double3 ^ pt2);
				double GetDistanceBetweenObjects(ObjectTransformOutput ^ transform1, ObjectTransformOutput ^ transform2);
				double GetDistanceOnEarth(double longitude1, double latitude1, double longitude2, double latitude2, double altitude);

				float AngleBetween(double3 ^ vec1, double3 ^ vec2);
				float AngleBetween(double3 ^ vec, double3 ^ referenceVec1, double3 ^ referenceVec2);

				double3 ^ LocalToGlobal(ObjectSphericalTransform ^ objectTransform, double3 ^ localCoordinates);
				double3 ^ LocalToGlobal(ObjectCartesianTransform ^ objectTransform, double3 ^ localCoordinates);
				double3 ^ LongitudeLatitudeToCartesian(double3 ^ vec);
				double3 ^ CartesianToLongitudeLatitude(double3 ^ vec);

				double3 ^ BearingRangeAltitudeToLongitudeLatitude(double referenceLongitude, double referenceLatitude, double bearing, double range, double altitude);
				double3 ^ LongitudeLatitudeToBearingRangeAltitude(double referenceLongitude, double referenceLatitude, double referenceAltitude, double targetLongitude, double targetLatitude, double targetAltitude);

			private:

				void * addonHandle;
				TacviewSDK::Interface187 * tacviewInterface;
			};

			ref class UnitsClass
			{
			public:

				UnitsClass(void * newAddonHandle, TacviewSDK::Interface187 * newTacviewInterface);

				double NauticalMilesToMeters(double value);
				double MetersToNauticalMiles(double value);
				double FeetToMeters(double value);
				double MetersToFeet(double value);
				double MetersPerSecondToKnots(double value);
				double KnotsToMetersPerSecond(double value);

				void * addonHandle;
				TacviewSDK::Interface187 * tacviewInterface;
			};

			AngleClass ^ Angle;
			VectorClass ^ Vector;
			UnitsClass ^ Units;

			MathClass(void * newAddonHandle, TacviewSDK::Interface187 * newTacviewInterface);

		private:

			void * addonHandle;
			TacviewSDK::Interface187 * tacviewInterface;
		};

		MathClass ^ Math;

		// **************************************************************** //
		// Tacview.Media
		// **************************************************************** //

		ref class MediaClass
		{
		public:
				MediaClass(void * newAddonHandle, TacviewSDK::Interface187 * newTacviewInterface);

				bool Load(int playerId, String ^ fileName);
				bool Load(int playerId, String ^ fileName, double absoluteTime);
				bool Unload(int playerId);
				bool Close(int playerId);

		private:

			void * addonHandle;
			TacviewSDK::Interface187 * tacviewInterface;
		};

		MediaClass ^ Media;

		// **************************************************************** //
		// Tacview.Path
		// **************************************************************** //

		ref class PathClass
		{
		public:

			PathClass(void * newAddonHandle, TacviewSDK::Interface187 * newTacviewInterface);

			String ^ GetDirectoryName(String ^ path);
			String ^ GetFileName(String ^ path);

		private:

			void * addonHandle;
			TacviewSDK::Interface187 * tacviewInterface;
		};

		PathClass ^ Path;

		// **************************************************************** //
		// Tacview.Settings
		// **************************************************************** //

		ref class SettingsClass
		{
		public:

			SettingsClass(void * newAddonHandle, TacviewSDK::Interface187 * newTacviewInterface);

			bool GetBoolean(String ^ settingPath);
			void SetBoolean(String ^ settingPath, bool value);

			double GetNumber(String ^ settingPath);
			void SetNumber(String ^ settingPath, double value);

			String ^ GetString(String ^ settingPath);
			void SetString(String ^ settingPath, String ^ value);

			Unit GetAltitudeUnit();

		private:

			void * addonHandle;
			TacviewSDK::Interface187 * tacviewInterface;
		};

		SettingsClass ^ Settings;

		// **************************************************************** //
		// Tacview.SoundPlayer
		// **************************************************************** //

		ref class SoundPlayerClass
		{
		public:

			SoundPlayerClass(void * newAddonHandle, TacviewSDK::Interface187 * newTacviewInterface);

			void Play(String ^ fileName);
			void Stop();

		private:

			void * addonHandle;
			TacviewSDK::Interface187 * tacviewInterface;
		};

		SoundPlayerClass ^ SoundPlayer;

		// **************************************************************** //
		// Tacview.StaticObjects
		// **************************************************************** //

		ref class StaticObjectsClass
		{
		public:

			StaticObjectsClass(void * newAddonHandle, TacviewSDK::Interface187 * newTacviewInterface);

			StaticObjectHandle GetObjectHandleByName(String ^ objectName);
			void SetVisible(StaticObjectHandle objectHandle, bool isVisible);

		private:

			void * addonHandle;
			TacviewSDK::Interface187 * tacviewInterface;
		};

		StaticObjectsClass ^ StaticObjects;

		// **************************************************************** //
		// Tacview.String
		// **************************************************************** //

		ref class StringClass
		{
		public:

			StringClass(void * newAddonHandle, TacviewSDK::Interface187 * newTacviewInterface);

			unsigned Crc32(String ^ text);

		private:

			void * addonHandle;
			TacviewSDK::Interface187 * tacviewInterface;
		};

		StringClass ^ String;

		// **************************************************************** //
		// Tacview.Telemetry
		// **************************************************************** //

		ref class TelemetryClass
		{
		public:

			ref class TagsClass
			{
			public:

				// Class

				ObjectTags Air;
				ObjectTags Ground;
				ObjectTags Sea;

				ObjectTags Weapon;
				ObjectTags Sensor;
				ObjectTags Navaid;
				ObjectTags Abstract;
				ObjectTags Misc;

				// Basic Types

				ObjectTags FixedWing;
				ObjectTags Rotorcraft;

				ObjectTags Armor;
				ObjectTags AntiAircraft;
				ObjectTags Vehicle;
				ObjectTags Watercraft;

				ObjectTags Human;
				ObjectTags Biologic;

				ObjectTags Missile;
				ObjectTags Rocket;
				ObjectTags Bomb;
				ObjectTags Torpedo;
				ObjectTags Projectile;
				ObjectTags Beam;

				ObjectTags Decoy;

				ObjectTags Building;

				ObjectTags Bullseye;
				ObjectTags Waypoint;
			};

			ref class TypeNamesClass
			{
			public:

				// Object class

				System::String ^ Air;
				System::String ^ Ground;
				System::String ^ Sea;

				System::String ^ Weapon;
				System::String ^ Sensor;
				System::String ^ Navaid;
				System::String ^ Abstract;
				System::String ^ Misc;

				System::String ^ Static;
				System::String ^ Heavy;
				System::String ^ Medium;
				System::String ^ Light;
				System::String ^ Minor;

				// Basic Types

				System::String ^ FixedWing;
				System::String ^ Rotorcraft;

				System::String ^ Armor;
				System::String ^ AntiAircraft;
				System::String ^ Vehicle;
				System::String ^ Watercraft;
				System::String ^ Human;
				System::String ^ Biologic;

				System::String ^ Missile;
				System::String ^ Rocket;
				System::String ^ Bomb;
				System::String ^ Torpedo;
				System::String ^ Projectile;
				System::String ^ Beam;

				System::String ^ Decoy;

				System::String ^ Building;

				System::String ^ Bullseye;
				System::String ^ Waypoint;

				// Specific Types

				System::String ^ Tank;
				System::String ^ Warship;
				System::String ^ AircraftCarrier;
				System::String ^ Submarine;
				System::String ^ Infantry;
				System::String ^ Parachutist;

				System::String ^ Shell;
				System::String ^ Bullet;

				System::String ^ Flare;
				System::String ^ Chaff;
				System::String ^ SmokeGrenade;

				System::String ^ Aerodrome;

				System::String ^ Container;
				System::String ^ Shrapnel;
				System::String ^ Explosion;

				// Composite Tags

				System::String ^ CompositeFixedWing;
				System::String ^ CompositeRotorcraft;

				System::String ^ CompositeAntiAircraft;
				System::String ^ CompositeArmor;
				System::String ^ CompositeTank;
				System::String ^ CompositeGroundVehicle;

				System::String ^ CompositeWatercraft;
				System::String ^ CompositeWarship;
				System::String ^ CompositeAircraftCarrier;
				System::String ^ CompositeSubmarine;

				System::String ^ CompositeSonobuoy;

				System::String ^ CompositeHuman;
				System::String ^ CompositeInfantry;
				System::String ^ CompositeParachutist;

				System::String ^ CompositeMissile;
				System::String ^ CompositeRocket;
				System::String ^ CompositeBomb;
				System::String ^ CompositeProjectile;
				System::String ^ CompositeBeam;
				System::String ^ CompositeShell;
				System::String ^ CompositeBullet;
				System::String ^ CompositeBallisticShell;

				System::String ^ CompositeDecoy;
				System::String ^ CompositeFlare;
				System::String ^ CompositeChaff;
				System::String ^ CompositeSmokeGrenade;

				System::String ^ CompositeBuilding;
				System::String ^ CompositeAerodrome;

				System::String ^ CompositeBullseye;
				System::String ^ CompositeWaypoint;

				System::String ^ CompositeContainer;
				System::String ^ CompositeShrapnel;
				System::String ^ CompositeMinorObject;
				System::String ^ CompositeExplosion;
			};

			ref class PropertyClass
			{
			public:

				ref class TextClass
				{
				public:

					System::String ^ CallSign;
					System::String ^ Color;
					System::String ^ Event;
					System::String ^ FocusedTarget;
					System::String ^ LockedTarget;
					System::String ^ Name;
					System::String ^ Pilot;
					System::String ^ Type;
				};

				ref class NumericClass
				{
				public:

					System::String ^ Disabled;
					System::String ^ EngagementMode;
					System::String ^ EngagementMode2;
					System::String ^ EngagementRange;
					System::String ^ EngagementRange2;
					System::String ^ VerticalEngagementRange;
					System::String ^ VerticalEngagementRange2;
					System::String ^ IAS;

					System::String ^ Importance;
					System::String ^ MinRange;
					System::String ^ MaxRange;
				};

				PropertyClass();

				TextClass ^ Text;
				NumericClass ^ Numeric;
			};

			const double BeginingOfTime = TacviewSDK::BeginningOfTime;
			const double EndOfTime = TacviewSDK::EndOfTime;
			const int InvalidPropertyIndex = TacviewSDK::InvalidPropertyIndex;

			TagsClass ^ Tags;
			TypeNamesClass ^ TypeNames;
			PropertyClass ^ Property;

			TelemetryClass(void * newAddonHandle, TacviewSDK::Interface187 * newTacviewInterface);

			void Clear();
			bool Load(System::String ^ fileName);

			bool IsEmpty();
			bool IsLikeEmpty();
			void GetDataTimeRange([Out] double % beginTime, [Out] double % endTime);
			void GetTransformTimeRange(ObjectHandle objectHandle, [Out] double % beginTime, [Out] double % endTime);

			ObjectHandle GetCurrentObjectHandle(ObjectId objectId);
			ObjectHandle GetObjectHandle(ObjectId objectId, double absoluteTime);
			ObjectHandle GetCurrentOrCreateObjectHandle(ObjectId objectId);
			ObjectHandle GetOrCreateObjectHandle(ObjectId objectId, double absoluteTime);

			int GetObjectCount();
			ObjectHandle GetObjectHandleByIndex(int objectIndex);
			ObjectId GetObjectId(ObjectHandle objectHandle);
			void DeleteObject(ObjectHandle objectHandle);

			ObjectTags GetCurrentTags(ObjectHandle objectHandle);
			bool AllGivenTagsActive(ObjectTags objectTags, ObjectTags activeTagsCombination);
			bool AnyGivenTagActive(ObjectTags objectTags, ObjectTags activeTagsCombination);

			void GetCurrentShortName(ObjectHandle objectHandle, [Out] System::String ^% name);
			bool GetCurrentTransform(ObjectHandle objectHandle, [Out] ObjectTransformOutput ^% objectTransform);
			bool GetCurrentCalculatedTransform(ObjectHandle objectHandle, [Out] ObjectTransformOutput ^% objectTransform);

			bool GetCurrentAngleOfAttack(ObjectHandle objectHandle, [Out] double % sampleValue);
			bool GetCurrentAngleOfSideslip(ObjectHandle objectHandle, [Out] double % sampleValue);
			bool GetVerticalGForce(ObjectHandle objectHandle, double absoluteTime, [Out] double % sampleValue);
			bool GetCurrentVerticalGForce(ObjectHandle objectHandle, [Out] double % sampleValue);
			bool GetLateralForce(ObjectHandle objectHandle, double absoluteTime, [Out] double % sampleValue);
			bool GetCurrentLateralForce(ObjectHandle objectHandle, [Out] double % sampleValue);
			bool GetLongitudinalForce(ObjectHandle objectHandle, double absoluteTime, [Out] double % sampleValue);
			bool GetCurrentLongitudinalForce(ObjectHandle objectHandle, [Out] double % sampleValue);
			bool GetAbsoluteGForce(ObjectHandle objectHandle, double absoluteTime, [Out] double % sampleValue);
			bool GetCurrentAbsoluteGForce(ObjectHandle objectHandle, [Out] double % sampleValue);
			bool GetInstantaneousTurnRadius(ObjectHandle objectHandle, double absoluteTime, [Out] double % sampleValue);
			bool GetTurnRadius(ObjectHandle objectHandle, double absoluteTime, double dt, [Out] double % sampleValue);
			bool GetCurrentInstantaneousTurnRadius(ObjectHandle objectHandle, [Out] double % sampleValue);
			bool GetCurrentTurnRadius(ObjectHandle objectHandle, double dt, [Out] double % sampleValue);
			bool GetInstantaneousTurnRate(ObjectHandle objectHandle, double absoluteTime, [Out] double % sampleValue);
			bool GetTurnRate(ObjectHandle objectHandle, double absoluteTime, double dt, [Out] double % sampleValue);
			bool GetCurrentInstantaneousTurnRate(ObjectHandle objectHandle, [Out] double % sampleValue);
			bool GetCurrentTurnRate(ObjectHandle objectHandle, double dt, [Out] double % sampleValue);
			bool GetMachNumber(ObjectHandle objectHandle, double absoluteTime, [Out] double % sampleValue);
			bool GetCurrentMachNumber(ObjectHandle objectHandle, [Out] double % sampleValue);

			int GetGlobalNumericPropertyIndex(System::String ^ propertyName, bool autoCreate);
			int GetGlobalTextPropertyIndex(System::String ^ propertyName, bool autoCreate);

			int GetObjectsNumericPropertyIndex(System::String ^ propertyName, bool autoCreate);
			int GetObjectsTextPropertyIndex(System::String ^ propertyName, bool autoCreate);

			void GetLifeTime(ObjectHandle objectHandle, [Out] double % lifeTimeBegin, [Out] double % lifeTimeEnd);
			void SetLifeTimeEnd(ObjectHandle objectHandle, double absoluteTime);

			int GetNumericSampleCount(ObjectHandle objectHandle, int propertyIndex);
			bool GetNumericSample(ObjectHandle objectHandle, double absoluteTime, int propertyIndex, [Out] double % value);
			bool GetNumericSampleFromIndex(ObjectHandle objectHandle, int sampleIndex, int propertyIndex, [Out] double % sampleTime, [Out] double % sampleValue);

			void SetNumericSample(ObjectHandle objectHandle, double absoluteTime, int propertyIndex, double value);

			bool RemoveNumericSample(ObjectHandle objectHandle, double absoluteTime, int propertyIndex);
			bool RemoveNumericSampleFromIndex(ObjectHandle objectHandle, int sampleIndex, int propertyIndex);

			int GetTextSampleCount(ObjectHandle objectHandle, int propertyIndex);
			bool GetTextSample(ObjectHandle objectHandle, double absoluteTime, int propertyIndex, [Out] System::String ^% value);
			bool GetTextSampleFromIndex(ObjectHandle objectHandle, int sampleIndex, int propertyIndex, [Out] double % sampleTime, [Out] System::String ^% sampleValue);

			void SetTextSample(ObjectHandle objectHandle, double absoluteTime, int propertyIndex, System::String ^ value);

			bool RemoveTextSample(ObjectHandle objectHandle, double absoluteTime, int propertyIndex);
			bool RemoveTextSampleFromIndex(ObjectHandle objectHandle, int sampleIndex, int propertyIndex);

			void SetTransform(ObjectHandle objectHandle, double absoluteTime, ObjectTransformInput ^ transform);
			bool GetTransform(ObjectHandle objectHandle, double absoluteTime, [Out] ObjectTransformOutput ^% objectTransform);
			bool GetCalculatedTransform(ObjectHandle objectHandle, double absoluteTime, [Out] ObjectTransformOutput ^% objectTransform);

			int GetTransformCount(ObjectHandle objectHandle);
			bool GetTransformFromIndex(ObjectHandle objectHandle, int sampleIndex, [Out] ObjectTransformOutput ^% objectTransform);

			bool RemoveTransformSample(ObjectHandle objectHandle, double absoluteTime);
			bool RemoveTransformSampleFromIndex(ObjectHandle objectHandle, int sampleIndex);

			bool OnLoadStart(bool mergeWithExistingData);
			void OnLoadEnd(System::String ^ documentName);

		private:

			void * addonHandle;
			TacviewSDK::Interface187 * tacviewInterface;
		};

		TelemetryClass ^ Telemetry;

		// **************************************************************** //
		// Tacview.Telemetry
		// **************************************************************** //

		ref class DatabaseClass
		{
		public:

			const int InvalidPropertyIndex = TacviewSDK::InvalidPropertyIndex;

			DatabaseClass(void * newAddonHandle, TacviewSDK::Interface187 * newTacviewInterface);

			RecordHandle GetNextRecord(RecordHandle currentRecordHandle, System::String ^ tags);

			bool GetRecordId(RecordHandle recordHandle, [Out] System::String ^% _id);
			float GetRecordPriority(RecordHandle recordHandle);

			int GetTextPropertyIndex(System::String ^ propertyName);
			bool GetRecordTextValue(RecordHandle recordHandle, int propertyIndex, [Out] System::String ^% value);

			int GetNumericPropertyIndex(System::String ^ propertyName);
			bool GetRecordNumericValue(RecordHandle recordHandle, int propertyIndex, [Out] double % value);

			bool Reload();

		private:

			void * addonHandle;
			TacviewSDK::Interface187 * tacviewInterface;
		};

		DatabaseClass ^ Database;

		// **************************************************************** //
		// Tacview.Terrain
		// **************************************************************** //

		ref class TerrainClass
		{
		public:

			TerrainClass(void * newAddonHandle, TacviewSDK::Interface187 * newTacviewInterface);

			float GetElevation(double longitude, double latitude);

			void AddCustomTexture(System::String ^ textureId, System::String ^ layerId, System::String ^ fileName, System::String ^ _filter, double topLeftLongitude, double topLeftLatitude, double topRightLongitude, double topRightLatitude, double bottomRightLongitude, double bottomRightLatitude, double bottomLeftLongitude, double bottomLeftLatitude);
			void ShowCustomTexture(System::String ^ textureId);
			void HideCustomTexture(System::String ^ textureId);

		private:

			void * addonHandle;
			TacviewSDK::Interface187 * tacviewInterface;
		};

		TerrainClass ^ Terrain;

		// **************************************************************** //
		// Tacview.UI
		// **************************************************************** //

		ref class UIClass
		{
		public:

			ref class MessageBoxClass
			{
			public:

				enum class Result
				{
					OK = (int)TacviewSDK::MessageBoxResult::OK,
					Cancel = (int)TacviewSDK::MessageBoxResult::Cancel,
				};

				MessageBoxClass(void * newAddonHandle, TacviewSDK::Interface187 * newTacviewInterface);

				void Info(System::String ^ text);
				void Warning(System::String ^ text);
				void Error(System::String ^ text);
				Result Question(System::String ^ text);

				bool InputText(System::String ^ title, System::String ^ message, [Out] System::String ^% text);

				ref struct OpenFileNameOptions
				{
					ref struct FileType
					{
						System::String ^ extensions;
						System::String ^ description;
					};

					System::String ^ defaultFileExtension;
					System::String ^ fileName;
					List<FileType^> ^ fileTypeList;
					bool multiSelection;
				};

				ref struct SaveFileNameOptions
				{
					ref struct FileType
					{
						System::String ^ extensions;
						System::String ^ description;
					};

					System::String ^ defaultFileExtension;
					System::String ^ fileName;
					List<FileType^> ^ fileTypeList;
				};

				ref struct FolderNameOptions
				{
					System::String ^ folderName;
					bool canCreateNewFolder;
				};

				bool GetOpenFileName([Out] List<System::String^> ^% fileNames, OpenFileNameOptions ^ options);
				bool GetSaveFileName([Out] System::String ^% fileName, SaveFileNameOptions ^ options);
				bool GetFolderName([Out] System::String ^% folderName, FolderNameOptions ^ options);

			private:

				void * addonHandle;
				TacviewSDK::Interface187 * tacviewInterface;
			};

			ref class FormatClass
			{
			public:

				FormatClass(void * newAddonHandle, TacviewSDK::Interface187 * newTacviewInterface);

				System::String ^ AltitudeToText(double value);
				bool TextToAltitude(System::String ^ text, [Out] double % value);
				bool TextToAltitudeLocalized(System::String ^ text, [Out] double % value);

				System::String ^ DistanceToText(double value);
				bool TextToDistance(System::String ^ text, [Out] double % value);
				bool TextToDistanceLocalized(System::String ^ text, [Out] double % value);

				System::String ^ SpeedToText(double value);
				bool TextToSpeed(System::String ^ text, [Out] double % value);
				bool TextToSpeedLocalized(System::String ^ text, [Out] double % value);

				System::String ^ LongitudeToText(double value);
				System::String ^ LatitudeToText(double value);
				bool TextToSpherical(System::String ^ text, [Out] double % value);

				System::String ^ AbsoluteTimeToISOText(double value, bool outputDecimals);
				bool TextToAbsoluteTime(System::String ^ text, [Out] double % value);

			private:

				void * addonHandle;
				TacviewSDK::Interface187 * tacviewInterface;
			};

			ref class MenusClass
			{
			public:

				MenusClass(void * newAddonHandle, TacviewSDK::Interface187 * newTacviewInterface);

				delegate void MenuEventHandler(int commandId);

				int AddMenu(int parentMenuId, System::String ^ menuLabel);
				int AddSeparator(int parentMenuId);
				int AddCommand(int parentMenuId, System::String ^ menuLabel, MenuEventHandler ^ eventHandler);
				int AddOption(int parentMenuId, System::String ^ menuLabel, bool optionValue, MenuEventHandler ^ eventHandler);
				int AddExclusiveOption(int parentMenuId, System::String ^ menuLabel, bool optionValue, MenuEventHandler ^ eventHandler);
				void SetOption(int commandId, bool optionValue);

			private:

				void * addonHandle;
				TacviewSDK::Interface187 * tacviewInterface;

				// This list is used only to prevent early garbage collect of callbacks given to the C++ code.

				event MenuEventHandler ^ menuEventHandler;
			};

			ref class RendererClass
			{
			public:

				ref class ContextMenuClass
				{
				public:

					delegate void ContextMenuHandler(int contextMenuId, ObjectHandle objectHandle);
					event ContextMenuHandler ^ Listeners;

					ContextMenuClass(void * newAddonHandle, TacviewSDK::Interface187 * newTacviewInterface);
					virtual ~ContextMenuClass();

					void OnContextMenu(int contextMenuId, ObjectHandle objectHandle)
					{
						Listeners(contextMenuId, objectHandle);
					}

				private:

					GCHandle selfHandle;
				};

				ref class Pick3DPointClass
				{
				public:

					delegate void Pick3DPointHandler(double longitude, double latitude, double altitude);
					event Pick3DPointHandler ^ Listeners;

					Pick3DPointClass(void * newAddonHandle, TacviewSDK::Interface187 * newTacviewInterface);
					virtual ~Pick3DPointClass();

					void OnPick3DPoint(double longitude, double latitude, double altitude)
					{
						Listeners(longitude, latitude, altitude);
					}

				private:

					GCHandle selfHandle;
				};

				RendererClass(void * newAddonHandle, TacviewSDK::Interface187 * newTacviewInterface);

				int GetWidth();
				int GetHeight();

				TextureHandle LoadTexture(System::String ^ texturePath, bool wrapRepeat, bool compressed);
				void UnloadTexture(TextureHandle textureHandle);

				VertexArrayHandle CreateVertexArray(List<float3^> ^ vertexList);
				void ReleaseVertexArray(VertexArrayHandle vertexArrayHandle);

				TextureCoordinateArrayHandle CreateTextureCoordinateArray(List<float2^> ^ uvList);
				void ReleaseTextureCoordinateArray(TextureCoordinateArrayHandle textureCoordinateArrayHandle);

				RenderStateHandle CreateRenderState(RenderState ^ renderState);
				void ReleaseRenderState(RenderStateHandle renderStateHandle);

				void DrawLines(RenderStateHandle renderStateHandle, float thickness, List<double3^> ^ vertexList);
				void DrawLines(RenderStateHandle renderStateHandle, float thickness, List<ColorVertex^> ^ vertexList);
				void DrawLineStrip(RenderStateHandle renderStateHandle, float thickness, List<double3^> ^ vertexList);
				void DrawLineStrip(RenderStateHandle renderStateHandle, float thickness, List<ColorVertex^> ^ vertexList);

				void DrawObjectVertexArray(ObjectRenderSphericalTransform ^ transform, RenderStateHandle renderStateHandle, VertexArrayHandle vertexArrayHandle, TextureCoordinateArrayHandle textureCoordinateArrayHandle);
				void DrawObjectVertexArray(ObjectRenderCartesianTransform ^ transform, RenderStateHandle renderStateHandle, VertexArrayHandle vertexArrayHandle, TextureCoordinateArrayHandle textureCoordinateArrayHandle);

				void DrawUIVertexArray(UIRenderTransform ^ transform, RenderStateHandle renderStateHandle, VertexArrayHandle vertexArrayHandle, TextureCoordinateArrayHandle textureCoordinateArrayHandle);
				void DrawUIVertexArray(UIRenderShapeTransform ^ transform, RenderStateHandle renderStateHandle, VertexArrayHandle vertexArrayHandle, TextureCoordinateArrayHandle textureCoordinateArrayHandle);

				void DrawOpaqueObject(ObjectHandle objectHandle, ObjectRenderSphericalTransform ^ transform, float alpha);
				void DrawOpaqueObject(ObjectHandle objectHandle, ObjectRenderCartesianTransform ^ transform, float alpha);

				void DrawTransparentObject(ObjectHandle objectHandle, ObjectRenderSphericalTransform ^ transform, float alpha);
				void DrawTransparentObject(ObjectHandle objectHandle, ObjectRenderCartesianTransform ^ transform, float alpha);

				void Print(UIRenderTransform ^ transform, RenderStateHandle renderStateHandle, System::String ^ text);
				void Print(UIRenderTextTransform ^ transform, RenderStateHandle renderStateHandle, System::String ^ text);

				ModelHandle Load3DModel(System::String ^ fileName);
				void Draw3DModel(ModelHandle modelHandle, ObjectRenderSphericalTransform ^ transform, uint32_t color);
				void Draw3DModel(ModelHandle modelHandle, ObjectRenderCartesianTransform ^ transform, uint32_t color);
				void DrawSemiTransparent3DModel(ModelHandle modelHandle, ObjectRenderSphericalTransform ^ transform, uint32_t color);
				void DrawSemiTransparent3DModel(ModelHandle modelHandle, ObjectRenderCartesianTransform ^ transform, uint32_t color);

				ContextMenuClass ^ ContextMenu;
				Pick3DPointClass ^ Pick3DPoint;

			private:

				void * addonHandle;
				TacviewSDK::Interface187 * tacviewInterface;
			};

			MessageBoxClass ^ MessageBox;
			FormatClass ^ Format;
			MenusClass ^ Menus;
			RendererClass ^ Renderer;

			UIClass(void * newAddonHandle, TacviewSDK::Interface187 * newTacviewInterface);

			void EnterFullScreen();
			void ExitFullScreen();

			void EnterReadMode(bool borderless);
			void ExitReadMode();

			void SetWindowParent(IntPtr parentWindow);
			void SetWindowPosition(int x, int y);
			void SetWindowPosition(int x, int y, int width, int height);
			void SetWindowSize(int width, int height);

			IntPtr GetWindowHandle();

			void Update();

		private:

			void * addonHandle;
			TacviewSDK::Interface187 * tacviewInterface;
		};

		UIClass ^ UI;

		// **************************************************************** //
		// Private implementation
		// **************************************************************** //

	private:

		void InitializeInterface();
		void ShutdownInterface();

		// The following variables are used as a link between this addon and Tacview.

		void * addonHandle;
		TacviewSDK::Interface187 * tacviewInterface;
	};
}

#endif // TACVIEW_WRAPPER_H
