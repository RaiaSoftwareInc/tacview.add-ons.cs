/*
	Tacview.Wrapper.Headers
	Master header for Tacview SDK wrapper
	Version 1.7.3 // 2018-09-13
	Copyright (C) 2018 Raia Software. All rights reserved.

	NOTE: You need a licence of Tacview Enterprise to run C++ addons.
*/

#pragma once

#ifndef TACVIEW_WRAPPER_HEADERS_H
#define TACVIEW_WRAPPER_HEADERS_H

// CLR

#include <vcclr.h>

// C++ library

#define NOMINMAX

#include <assert.h>
#include <algorithm>
#include <stdint.h>
#include <string>
#include <vector>

// Windows SDK

#include <Windows.h>

// Remove WIN32 defines which can change Tacview SDK signature for the C#

#undef GetOpenFileName
#undef GetSaveFileName

// Tacview SDK Interface

#include "Tacview.SDK.Interface.h"

#endif // TACVIEW_WRAPPER_HEADERS_H
