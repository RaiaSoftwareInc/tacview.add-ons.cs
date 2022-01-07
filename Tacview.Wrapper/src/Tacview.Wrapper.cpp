/*
	Tacview.Wrapper.Main
	C# DLL add-on wrapper
	Version 1.7.3 // 2018-10-04
	Copyright (C) 2018-2021 Raia Software. All rights reserved.

	NOTE: You need a licence of Tacview Enterprise to run C# addons.
*/

#include "Tacview.Wrapper.Headers.h"
#include "Tacview.Wrapper.h"

using namespace System;
using namespace System::Reflection;

// Assembly attributes

[assembly:AssemblyTitleAttribute("Tacview.Wrapper")];
[assembly:AssemblyCopyrightAttribute("Copyright © 2018-2022 Raia Software Inc.")];
[assembly:AssemblyDescriptionAttribute(".Net DLL wrapper for Tacview API")];
[assembly:AssemblyProductAttribute("Tacview")];
[assembly:AssemblyVersionAttribute("1.8.8.101")];

// API setup

namespace TacviewSDK
{
	// The following variables are used as a link between this addon and Tacview.

	void * addonHandle = nullptr;
	TacviewSDK::Interface187 * tacviewInterface = nullptr;

	/*
		TacviewAddOnInitialize is the first function called by Tacview whenever the addon is loaded in memory.
		The provided GetInterface function must be used to retrieve the interface of your choice.
		The addon must return true if it is ready to run.
	*/

	bool Wrapper::InitializeWrapper(IntPtr _addonHandle, IntPtr _tacviewGetInterface)
	{
		// Retrieve parameters

		addonHandle = (void*)_addonHandle;
		TacviewSDK::GetInterface TacviewGetInterface = (TacviewSDK::GetInterface)(void*)_tacviewGetInterface;

		// Retrieve Tacview API

		tacviewInterface = static_cast<TacviewSDK::Interface187*>(TacviewGetInterface(addonHandle, "Tacview187"));
		assert(tacviewInterface != nullptr);

		// Success

		if (tacviewInterface)
		{
			InitializeInterface();
			return true;
		}

		// Failure

		addonHandle = nullptr;
		return false;
	}

	/*
		TacviewAddOnShutdown() is called by Tacview right before unloading the DLL.
		It is called only if TacviewAddOnInitialize() has been successful.
		This is the best place to cleanup all resources allocated by your module.
	*/

	void Wrapper::ShutdownWrapper()
	{
		ShutdownInterface();

		addonHandle = NULL;
		tacviewInterface = NULL;
	}

	/*
		Interface constructor
	*/

	void Wrapper::InitializeInterface()
	{
		AddOns = gcnew AddOnsClass(addonHandle, tacviewInterface);
		Context = gcnew ContextClass(addonHandle, tacviewInterface);
		Directory = gcnew DirectoryClass(addonHandle, tacviewInterface);
		Events = gcnew EventsClass(addonHandle, tacviewInterface);
		Log = gcnew LogClass(addonHandle, tacviewInterface);
		Math = gcnew MathClass(addonHandle, tacviewInterface);
		Media = gcnew MediaClass(addonHandle, tacviewInterface);
		Path = gcnew PathClass(addonHandle, tacviewInterface);
		Settings = gcnew SettingsClass(addonHandle, tacviewInterface);
		SoundPlayer = gcnew SoundPlayerClass(addonHandle, tacviewInterface);
		StaticObjects = gcnew StaticObjectsClass(addonHandle, tacviewInterface);
		String = gcnew StringClass(addonHandle, tacviewInterface);
		Telemetry = gcnew TelemetryClass(addonHandle, tacviewInterface);
		Database = gcnew DatabaseClass(addonHandle, tacviewInterface);
		Terrain = gcnew TerrainClass(addonHandle, tacviewInterface);
		UI = gcnew UIClass(addonHandle, tacviewInterface);

		// Tags (Class)

		Telemetry->Tags->Air = tacviewInterface->TelemetryTagsAir;
		Telemetry->Tags->Ground = tacviewInterface->TelemetryTagsGround;
		Telemetry->Tags->Sea = tacviewInterface->TelemetryTagsSea;

		Telemetry->Tags->Weapon = tacviewInterface->TelemetryTagsWeapon;
		Telemetry->Tags->Sensor = tacviewInterface->TelemetryTagsSensor;
		Telemetry->Tags->Navaid = tacviewInterface->TelemetryTagsNavaid;
		Telemetry->Tags->Abstract = tacviewInterface->TelemetryTagsAbstract;
		Telemetry->Tags->Misc = tacviewInterface->TelemetryTagsMisc;

		// Tags (Basic Types)

		Telemetry->Tags->FixedWing = tacviewInterface->TelemetryTagsFixedWing;
		Telemetry->Tags->Rotorcraft = tacviewInterface->TelemetryTagsRotorcraft;

		Telemetry->Tags->Armor = tacviewInterface->TelemetryTagsArmor;
		Telemetry->Tags->AntiAircraft = tacviewInterface->TelemetryTagsAntiAircraft;
		Telemetry->Tags->Vehicle = tacviewInterface->TelemetryTagsVehicle;
		Telemetry->Tags->Watercraft = tacviewInterface->TelemetryTagsWatercraft;

		Telemetry->Tags->Human = tacviewInterface->TelemetryTagsHuman;
		Telemetry->Tags->Biologic = tacviewInterface->TelemetryTagsBiologic;

		Telemetry->Tags->Missile = tacviewInterface->TelemetryTagsMissile;
		Telemetry->Tags->Rocket = tacviewInterface->TelemetryTagsRocket;
		Telemetry->Tags->Bomb = tacviewInterface->TelemetryTagsBomb;
		Telemetry->Tags->Torpedo = tacviewInterface->TelemetryTagsTorpedo;
		Telemetry->Tags->Projectile = tacviewInterface->TelemetryTagsProjectile;
		Telemetry->Tags->Beam = tacviewInterface->TelemetryTagsBeam;

		Telemetry->Tags->Decoy = tacviewInterface->TelemetryTagsDecoy;

		Telemetry->Tags->Building = tacviewInterface->TelemetryTagsBuilding;

		Telemetry->Tags->Bullseye = tacviewInterface->TelemetryTagsBullseye;
		Telemetry->Tags->Waypoint = tacviewInterface->TelemetryTagsWaypoint;

		// Text types (Object class)

		Telemetry->TypeNames->Air = gcnew System::String(TacviewSDK::Tag::Air);
		Telemetry->TypeNames->Ground = gcnew System::String(TacviewSDK::Tag::Ground);
		Telemetry->TypeNames->Sea = gcnew System::String(TacviewSDK::Tag::Sea);

		Telemetry->TypeNames->Weapon = gcnew System::String(TacviewSDK::Tag::Weapon);
		Telemetry->TypeNames->Sensor = gcnew System::String(TacviewSDK::Tag::Sensor);
		Telemetry->TypeNames->Navaid = gcnew System::String(TacviewSDK::Tag::Navaid);
		Telemetry->TypeNames->Abstract = gcnew System::String(TacviewSDK::Tag::Abstract);
		Telemetry->TypeNames->Misc = gcnew System::String(TacviewSDK::Tag::Misc);

		Telemetry->TypeNames->Static = gcnew System::String(TacviewSDK::Tag::Static);
		Telemetry->TypeNames->Heavy = gcnew System::String(TacviewSDK::Tag::Heavy);
		Telemetry->TypeNames->Medium = gcnew System::String(TacviewSDK::Tag::Medium);
		Telemetry->TypeNames->Light = gcnew System::String(TacviewSDK::Tag::Light);
		Telemetry->TypeNames->Minor = gcnew System::String(TacviewSDK::Tag::Minor);

		// Text types (Basic Types)

		Telemetry->TypeNames->FixedWing = gcnew System::String(TacviewSDK::Tag::FixedWing);
		Telemetry->TypeNames->Rotorcraft = gcnew System::String(TacviewSDK::Tag::Rotorcraft);

		Telemetry->TypeNames->Armor = gcnew System::String(TacviewSDK::Tag::Armor);
		Telemetry->TypeNames->AntiAircraft = gcnew System::String(TacviewSDK::Tag::AntiAircraft);
		Telemetry->TypeNames->Vehicle = gcnew System::String(TacviewSDK::Tag::Vehicle);
		Telemetry->TypeNames->Watercraft = gcnew System::String(TacviewSDK::Tag::Watercraft);
		Telemetry->TypeNames->Human = gcnew System::String(TacviewSDK::Tag::Human);
		Telemetry->TypeNames->Biologic = gcnew System::String(TacviewSDK::Tag::Biologic);

		Telemetry->TypeNames->Missile = gcnew System::String(TacviewSDK::Tag::Missile);
		Telemetry->TypeNames->Rocket = gcnew System::String(TacviewSDK::Tag::Rocket);
		Telemetry->TypeNames->Bomb = gcnew System::String(TacviewSDK::Tag::Bomb);
		Telemetry->TypeNames->Torpedo = gcnew System::String(TacviewSDK::Tag::Torpedo);
		Telemetry->TypeNames->Projectile = gcnew System::String(TacviewSDK::Tag::Projectile);
		Telemetry->TypeNames->Beam = gcnew System::String(TacviewSDK::Tag::Beam);

		Telemetry->TypeNames->Decoy = gcnew System::String(TacviewSDK::Tag::Decoy);

		Telemetry->TypeNames->Building = gcnew System::String(TacviewSDK::Tag::Building);

		Telemetry->TypeNames->Bullseye = gcnew System::String(TacviewSDK::Tag::Bullseye);
		Telemetry->TypeNames->Waypoint = gcnew System::String(TacviewSDK::Tag::Waypoint);

		// Text types (Specific Types)

		Telemetry->TypeNames->Tank = gcnew System::String(TacviewSDK::Tag::Tank);
		Telemetry->TypeNames->Warship = gcnew System::String(TacviewSDK::Tag::Warship);
		Telemetry->TypeNames->AircraftCarrier = gcnew System::String(TacviewSDK::Tag::AircraftCarrier);
		Telemetry->TypeNames->Submarine = gcnew System::String(TacviewSDK::Tag::Submarine);
		Telemetry->TypeNames->Infantry = gcnew System::String(TacviewSDK::Tag::Infantry);
		Telemetry->TypeNames->Parachutist = gcnew System::String(TacviewSDK::Tag::Parachutist);

		Telemetry->TypeNames->Shell = gcnew System::String(TacviewSDK::Tag::Shell);
		Telemetry->TypeNames->Bullet = gcnew System::String(TacviewSDK::Tag::Bullet);

		Telemetry->TypeNames->Flare = gcnew System::String(TacviewSDK::Tag::Flare);
		Telemetry->TypeNames->Chaff = gcnew System::String(TacviewSDK::Tag::Chaff);
		Telemetry->TypeNames->SmokeGrenade = gcnew System::String(TacviewSDK::Tag::SmokeGrenade);

		Telemetry->TypeNames->Aerodrome = gcnew System::String(TacviewSDK::Tag::Aerodrome);

		Telemetry->TypeNames->Container = gcnew System::String(TacviewSDK::Tag::Container);
		Telemetry->TypeNames->Shrapnel = gcnew System::String(TacviewSDK::Tag::Shrapnel);
		Telemetry->TypeNames->Explosion = gcnew System::String(TacviewSDK::Tag::Explosion);

		// Text types (Composite Tags)

		Telemetry->TypeNames->CompositeFixedWing = gcnew System::String(TacviewSDK::Tag::CompositeFixedWing);
		Telemetry->TypeNames->CompositeRotorcraft = gcnew System::String(TacviewSDK::Tag::CompositeRotorcraft);

		Telemetry->TypeNames->CompositeAntiAircraft = gcnew System::String(TacviewSDK::Tag::CompositeAntiAircraft);
		Telemetry->TypeNames->CompositeArmor = gcnew System::String(TacviewSDK::Tag::CompositeArmor);
		Telemetry->TypeNames->CompositeTank = gcnew System::String(TacviewSDK::Tag::CompositeTank);
		Telemetry->TypeNames->CompositeGroundVehicle = gcnew System::String(TacviewSDK::Tag::CompositeGroundVehicle);

		Telemetry->TypeNames->CompositeWatercraft = gcnew System::String(TacviewSDK::Tag::CompositeWatercraft);
		Telemetry->TypeNames->CompositeWarship = gcnew System::String(TacviewSDK::Tag::CompositeWarship);
		Telemetry->TypeNames->CompositeAircraftCarrier = gcnew System::String(TacviewSDK::Tag::CompositeAircraftCarrier);
		Telemetry->TypeNames->CompositeSubmarine = gcnew System::String(TacviewSDK::Tag::CompositeSubmarine);

		Telemetry->TypeNames->CompositeSonobuoy = gcnew System::String(TacviewSDK::Tag::CompositeSonobuoy);

		Telemetry->TypeNames->CompositeHuman = gcnew System::String(TacviewSDK::Tag::CompositeHuman);
		Telemetry->TypeNames->CompositeInfantry = gcnew System::String(TacviewSDK::Tag::CompositeInfantry);
		Telemetry->TypeNames->CompositeParachutist = gcnew System::String(TacviewSDK::Tag::CompositeParachutist);

		Telemetry->TypeNames->CompositeMissile = gcnew System::String(TacviewSDK::Tag::CompositeMissile);
		Telemetry->TypeNames->CompositeRocket = gcnew System::String(TacviewSDK::Tag::CompositeRocket);
		Telemetry->TypeNames->CompositeBomb = gcnew System::String(TacviewSDK::Tag::CompositeBomb);
		Telemetry->TypeNames->CompositeProjectile = gcnew System::String(TacviewSDK::Tag::CompositeProjectile);
		Telemetry->TypeNames->CompositeBeam = gcnew System::String(TacviewSDK::Tag::CompositeBeam);
		Telemetry->TypeNames->CompositeShell = gcnew System::String(TacviewSDK::Tag::CompositeShell);
		Telemetry->TypeNames->CompositeBullet = gcnew System::String(TacviewSDK::Tag::CompositeBullet);
		Telemetry->TypeNames->CompositeBallisticShell = gcnew System::String(TacviewSDK::Tag::CompositeBallisticShell);

		Telemetry->TypeNames->CompositeDecoy = gcnew System::String(TacviewSDK::Tag::CompositeDecoy);
		Telemetry->TypeNames->CompositeFlare = gcnew System::String(TacviewSDK::Tag::CompositeFlare);
		Telemetry->TypeNames->CompositeChaff = gcnew System::String(TacviewSDK::Tag::CompositeChaff);
		Telemetry->TypeNames->CompositeSmokeGrenade = gcnew System::String(TacviewSDK::Tag::CompositeSmokeGrenade);

		Telemetry->TypeNames->CompositeBuilding = gcnew System::String(TacviewSDK::Tag::CompositeBuilding);
		Telemetry->TypeNames->CompositeAerodrome = gcnew System::String(TacviewSDK::Tag::CompositeAerodrome);

		Telemetry->TypeNames->CompositeBullseye = gcnew System::String(TacviewSDK::Tag::CompositeBullseye);
		Telemetry->TypeNames->CompositeWaypoint = gcnew System::String(TacviewSDK::Tag::CompositeWaypoint);

		Telemetry->TypeNames->CompositeContainer = gcnew System::String(TacviewSDK::Tag::CompositeContainer);
		Telemetry->TypeNames->CompositeShrapnel = gcnew System::String(TacviewSDK::Tag::CompositeShrapnel);
		Telemetry->TypeNames->CompositeMinorObject = gcnew System::String(TacviewSDK::Tag::CompositeMinorObject);
		Telemetry->TypeNames->CompositeExplosion = gcnew System::String(TacviewSDK::Tag::CompositeExplosion);

		// Properties

		Telemetry->Property->Text->CallSign = gcnew System::String(TacviewSDK::Property::Text::CallSign);
		Telemetry->Property->Text->Color = gcnew System::String(TacviewSDK::Property::Text::Color);
		Telemetry->Property->Text->Event = gcnew System::String(TacviewSDK::Property::Text::Event);
		Telemetry->Property->Text->FocusedTarget = gcnew System::String(TacviewSDK::Property::Text::FocusedTarget);
		Telemetry->Property->Text->LockedTarget = gcnew System::String(TacviewSDK::Property::Text::LockedTarget);
		Telemetry->Property->Text->Name = gcnew System::String(TacviewSDK::Property::Text::Name);
		Telemetry->Property->Text->Pilot = gcnew System::String(TacviewSDK::Property::Text::Pilot);
		Telemetry->Property->Text->Type = gcnew System::String(TacviewSDK::Property::Text::Type);

		Telemetry->Property->Numeric->Disabled = gcnew System::String(TacviewSDK::Property::Numeric::Disabled);
		Telemetry->Property->Numeric->EngagementMode = gcnew System::String(TacviewSDK::Property::Numeric::EngagementMode);
		Telemetry->Property->Numeric->EngagementMode2 = gcnew System::String(TacviewSDK::Property::Numeric::EngagementMode2);
		Telemetry->Property->Numeric->EngagementRange = gcnew System::String(TacviewSDK::Property::Numeric::EngagementRange);
		Telemetry->Property->Numeric->EngagementRange2 = gcnew System::String(TacviewSDK::Property::Numeric::EngagementRange2);
		Telemetry->Property->Numeric->VerticalEngagementRange = gcnew System::String(TacviewSDK::Property::Numeric::VerticalEngagementRange);
		Telemetry->Property->Numeric->VerticalEngagementRange2 = gcnew System::String(TacviewSDK::Property::Numeric::VerticalEngagementRange2);
		Telemetry->Property->Numeric->IAS = gcnew System::String(TacviewSDK::Property::Numeric::IAS);

		Telemetry->Property->Numeric->Importance = gcnew System::String(TacviewSDK::Property::Numeric::Importance);
		Telemetry->Property->Numeric->MinRange = gcnew System::String(TacviewSDK::Property::Numeric::MinRange);
		Telemetry->Property->Numeric->MaxRange = gcnew System::String(TacviewSDK::Property::Numeric::MaxRange);
	}

	/*
		Interface destructor
	*/

	void Wrapper::ShutdownInterface()
	{
		AddOns = nullptr;
		Context = nullptr;
		Directory = nullptr;
		Events = nullptr;
		Log = nullptr;
		Math = nullptr;
		Media = nullptr;
		Path = nullptr;
		Settings = nullptr;
		StaticObjects = nullptr;
		String = nullptr;
		Telemetry = nullptr;
		Terrain = nullptr;
		Database = nullptr;
		UI = nullptr;
	}

	// Tacview.Close

	void Wrapper::Close()
	{
		tacviewInterface->Close(addonHandle);
	}
}
