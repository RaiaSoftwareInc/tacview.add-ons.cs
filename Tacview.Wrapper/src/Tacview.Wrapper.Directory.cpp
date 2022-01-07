/*
	Tacview.Wrapper.Directory
	Tool to manage directories and their content
	Version 1.8.7 // 2021-07-15
	Copyright (C) 2018-2021 Raia Software. All rights reserved.

	NOTE: You need a licence of Tacview Enterprise to run C# addons.
*/

#include "Tacview.Wrapper.Headers.h"
#include "Tacview.Wrapper.h"

namespace TacviewSDK
{
	// Tacview.Context.Directory

	Wrapper::DirectoryClass::DirectoryClass(void * newAddonHandle, TacviewSDK::Interface187 * newTacviewInterface) :
		addonHandle(newAddonHandle),
		tacviewInterface(newTacviewInterface)
	{
	}

	bool Wrapper::DirectoryClass::CreateDirectory(System::String ^ _directoryName)
	{
		pin_ptr<const wchar_t> directoryName = PtrToStringChars(_directoryName);
		return tacviewInterface->DirectoryCreateDirectory(addonHandle, directoryName);
	}

	bool Wrapper::DirectoryClass::Delete(System::String ^ _directoryName, bool recursive)
	{
		pin_ptr<const wchar_t> directoryName = PtrToStringChars(_directoryName);
		return tacviewInterface->DirectoryDelete(addonHandle, directoryName, recursive);
	}

	List<String ^> ^ Wrapper::DirectoryClass::GetFiles(System::String ^ _directoryName, bool recursive)
	{
		pin_ptr<const wchar_t> directoryName = PtrToStringChars(_directoryName);

		static constexpr size_t bufferSize = 64 * 1024;
		wchar_t * buffer = new wchar_t[bufferSize];

		auto fileList = gcnew List<System::String ^>();

		if (buffer)
		{
			tacviewInterface->DirectoryGetFiles(addonHandle, directoryName, recursive, buffer, bufferSize);

			wchar_t * currentChar = buffer;

			while (*currentChar)
			{
				fileList->Add(gcnew System::String(currentChar));

				while (*currentChar)
				{
					++currentChar;
				}
			}

			delete[] buffer;
		}

		return fileList;
	}
}
