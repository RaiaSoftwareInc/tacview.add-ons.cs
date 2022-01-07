/*
	Tacview.Wrapper.Log
	Tacview API wrapper
	Version 1.7.3 // 2018-10-04
	Copyright (C) 2018 Raia Software. All rights reserved.

	NOTE: You need a licence of Tacview Enterprise to run C# addons.
*/

#include "Tacview.Wrapper.Headers.h"
#include "Tacview.Wrapper.h"

using namespace System::Collections::Generic;

namespace TacviewSDK
{
	Wrapper::UIClass::MessageBoxClass::MessageBoxClass(void * newAddonHandle, TacviewSDK::Interface187 * newTacviewInterface) :
		addonHandle(newAddonHandle),
		tacviewInterface(newTacviewInterface)
	{
	}

	void Wrapper::UIClass::MessageBoxClass::Info(System::String ^ _text)
	{
		pin_ptr<const wchar_t> text = PtrToStringChars(_text);
		tacviewInterface->UIMessageBoxInfo(addonHandle, text);
	}

	void Wrapper::UIClass::MessageBoxClass::Warning(System::String ^ _text)
	{
		pin_ptr<const wchar_t> text = PtrToStringChars(_text);
		tacviewInterface->UIMessageBoxWarning(addonHandle, text);
	}

	void Wrapper::UIClass::MessageBoxClass::Error(System::String ^ _text)
	{
		pin_ptr<const wchar_t> text = PtrToStringChars(_text);
		tacviewInterface->UIMessageBoxError(addonHandle, text);
	}

	Wrapper::UIClass::MessageBoxClass::Result Wrapper::UIClass::MessageBoxClass::Question(System::String ^ _text)
	{
		pin_ptr<const wchar_t> text = PtrToStringChars(_text);
		return static_cast<Wrapper::UIClass::MessageBoxClass::Result>(tacviewInterface->UIMessageBoxQuestion(addonHandle, text));
	}

	bool Wrapper::UIClass::MessageBoxClass::InputText(System::String ^ _title, System::String ^ _message, [Out] System::String ^% _text)
	{
		pin_ptr<const wchar_t> message = PtrToStringChars(_message);

		// Prepare result buffer

		static constexpr size_t resultSize = 64 * 1024;
		wchar_t * resultTextBuffer = new wchar_t[resultSize];

		if (!resultTextBuffer)
		{
			return false;
		}

		if (_text != nullptr)
		{
			pin_ptr<const wchar_t> defaultText = PtrToStringChars(_text);
			wcscpy_s(resultTextBuffer, resultSize, defaultText);
		}
		else
		{
			resultTextBuffer[0] = '\0';
		}

		pin_ptr<const wchar_t> title = PtrToStringChars(_title);

		bool result = tacviewInterface->UIMessageBoxInputText(addonHandle, title, resultTextBuffer, resultSize, message);

		if (result)
		{
			_text = gcnew System::String(resultTextBuffer);
		}

		delete[]resultTextBuffer;

		return result;
	}

	// Tacview.UI.MessageBox.GetOpenFileName

	bool Wrapper::UIClass::MessageBoxClass::GetOpenFileName([Out] List<System::String^> ^% openFileNames, OpenFileNameOptions ^ options)
	{
		TacviewSDK::OpenFileNameOptions openFileNameOptions = {0};

		pin_ptr<const wchar_t> defaultFileExtension = PtrToStringChars(options->defaultFileExtension);
		openFileNameOptions.defaultFileExtension = defaultFileExtension;

		pin_ptr<const wchar_t> fileName = PtrToStringChars(options->fileName);
		openFileNameOptions.fileName = fileName;

		static constexpr size_t MaxFileTypeCount = 64;
		TacviewSDK::OpenFileNameOptions::FileType fileTypeList[MaxFileTypeCount] = { 0 };
		openFileNameOptions.fileTypeList = fileTypeList;

		openFileNameOptions.multiSelection = options->multiSelection;

		// Prepare result buffer

		static constexpr size_t resultSize = 64 * 1024;
		wchar_t * resultFileNames = new wchar_t[resultSize];

		if (!resultFileNames)
		{
			return false;
		}

		// Dummy list to keep C# objects referenced

		std::vector<std::wstring*> extensionsList;
		std::vector<std::wstring*> descriptionList;

		size_t fileTypeIndex = 0;

		for each(auto fileType in options->fileTypeList)
		{
			pin_ptr<const wchar_t> fileTypeExtensions = PtrToStringChars(fileType->extensions);
			extensionsList.push_back(new std::wstring(fileTypeExtensions));

			pin_ptr<const wchar_t> fileTypeDescription = PtrToStringChars(fileType->description);
			descriptionList.push_back(new std::wstring(fileTypeDescription));

			fileTypeList[fileTypeIndex].extensions = extensionsList.back()->c_str();
			fileTypeList[fileTypeIndex].description = descriptionList.back()->c_str();

			++fileTypeIndex;

			if (fileTypeIndex >= MaxFileTypeCount)
			{
				break;
			}
		}

		// Display dialog box

		bool result = tacviewInterface->UIMessageBoxGetOpenFileName(addonHandle, resultFileNames, resultSize, &openFileNameOptions);

		// Cleanup parameters

		for (auto extension : extensionsList)
		{
			delete extension;
		}

		for (auto description : descriptionList)
		{
			delete description;
		}

		// Retrieve result

		openFileNames = gcnew List<System::String ^>();

		if (openFileNames)
		{
			// Extract file names

			const wchar_t * currentName = resultFileNames;

			while (*currentName)
			{
				openFileNames->Add(gcnew System::String(currentName));

				while (*currentName)
				{
					++currentName;
				}

				++currentName;
			}
		}

		delete[]resultFileNames;

		return result;
	}

	// Tacview.UI.MessageBox.GetSaveFileName

	bool Wrapper::UIClass::MessageBoxClass::GetSaveFileName([Out] System::String ^% saveFileName, SaveFileNameOptions ^ options)
	{
		TacviewSDK::SaveFileNameOptions saveFileNameOptions = {0};

		pin_ptr<const wchar_t> defaultFileExtension = PtrToStringChars(options->defaultFileExtension);
		saveFileNameOptions.defaultFileExtension = defaultFileExtension;

		pin_ptr<const wchar_t> fileName = PtrToStringChars(options->fileName);
		saveFileNameOptions.fileName = fileName;

		static constexpr size_t MaxFileTypeCount = 64;
		TacviewSDK::SaveFileNameOptions::FileType fileTypeList[MaxFileTypeCount] = { 0 };
		saveFileNameOptions.fileTypeList = fileTypeList;

		// Dummy list to keep C# objects referenced

		std::vector<std::wstring*> extensionsList;
		std::vector<std::wstring*> descriptionList;

		size_t fileTypeIndex = 0;

		for each(auto fileType in options->fileTypeList)
		{
			pin_ptr<const wchar_t> fileTypeExtensions = PtrToStringChars(fileType->extensions);
			extensionsList.push_back(new std::wstring(fileTypeExtensions));

			pin_ptr<const wchar_t> fileTypeDescription = PtrToStringChars(fileType->description);
			descriptionList.push_back(new std::wstring(fileTypeDescription));

			fileTypeList[fileTypeIndex].extensions = extensionsList.back()->c_str();
			fileTypeList[fileTypeIndex].description = descriptionList.back()->c_str();

			++fileTypeIndex;

			if (fileTypeIndex >= MaxFileTypeCount)
			{
				break;
			}
		}

		// Display dialog box

		wchar_t resultFileName[260];

		bool result = tacviewInterface->UIMessageBoxGetSaveFileName(addonHandle, resultFileName, _countof(resultFileName), &saveFileNameOptions);

		// Cleanup parameters

		for (auto extension : extensionsList)
		{
			delete extension;
		}

		for (auto description : descriptionList)
		{
			delete description;
		}

		// Retrieve results

		saveFileName = gcnew System::String(resultFileName);

		return result;
	}

	// Tacview.UI.MessageBox.GetFolderName

	bool Wrapper::UIClass::MessageBoxClass::GetFolderName([Out] System::String ^% outputFolderName, FolderNameOptions ^ options)
	{
		TacviewSDK::FolderNameOptions folderNameOptions = {0};

		pin_ptr<const wchar_t> folderName = PtrToStringChars(options->folderName);
		folderNameOptions.folderName = folderName;

		folderNameOptions.canCreateNewFolder = options->canCreateNewFolder;

		wchar_t resultFileName[260];

		bool result = tacviewInterface->UIMessageBoxGetFolderName(addonHandle, resultFileName, _countof(resultFileName), &folderNameOptions);
		outputFolderName = gcnew System::String(resultFileName);

		return result;
	}

	// Tacview.UI.Format

	Wrapper::UIClass::FormatClass::FormatClass(void * newAddonHandle, TacviewSDK::Interface187 * newTacviewInterface) :
		addonHandle(newAddonHandle),
		tacviewInterface(newTacviewInterface)
	{
	}

	String ^ Wrapper::UIClass::FormatClass::AltitudeToText(double value)
	{
		wchar_t formatedValue[256];
		tacviewInterface->UIFormatAltitudeToText(addonHandle, value, formatedValue, _countof(formatedValue));
		return gcnew System::String(formatedValue);
	}

	bool Wrapper::UIClass::FormatClass::TextToAltitude(System::String ^ text, [Out] double % value)
	{
		pin_ptr<const wchar_t> formatedValue = PtrToStringChars(text);
		double resultValue;
		bool result = tacviewInterface->UIFormatTextToAltitude(addonHandle, formatedValue, resultValue);
		value = resultValue;
		return result;
	}

	bool Wrapper::UIClass::FormatClass::TextToAltitudeLocalized(System::String ^ text, [Out] double % value)
	{
		pin_ptr<const wchar_t> formatedValue = PtrToStringChars(text);
		double resultValue;
		bool result = tacviewInterface->UIFormatTextToAltitudeLocalized(addonHandle, formatedValue, resultValue);
		value = resultValue;
		return result;
	}

	String ^ Wrapper::UIClass::FormatClass::DistanceToText(double value)
	{
		wchar_t formatedValue[256];
		tacviewInterface->UIFormatDistanceToText(addonHandle, value, formatedValue, _countof(formatedValue));
		return gcnew System::String(formatedValue);
	}

	bool Wrapper::UIClass::FormatClass::TextToDistance(System::String ^ text, [Out] double % value)
	{
		pin_ptr<const wchar_t> formatedValue = PtrToStringChars(text);
		double resultValue;
		bool result = tacviewInterface->UIFormatTextToDistance(addonHandle, formatedValue, resultValue);
		value = resultValue;
		return result;
	}

	bool Wrapper::UIClass::FormatClass::TextToDistanceLocalized(System::String ^ text, [Out] double % value)
	{
		pin_ptr<const wchar_t> formatedValue = PtrToStringChars(text);
		double resultValue;
		bool result = tacviewInterface->UIFormatTextToDistanceLocalized(addonHandle, formatedValue, resultValue);
		value = resultValue;
		return result;
	}

	String ^ Wrapper::UIClass::FormatClass::SpeedToText(double value)
	{
		wchar_t formatedValue[256];
		tacviewInterface->UIFormatSpeedToText(addonHandle, value, formatedValue, _countof(formatedValue));
		return gcnew System::String(formatedValue);
	}

	bool Wrapper::UIClass::FormatClass::TextToSpeed(System::String ^ text, [Out] double % value)
	{
		pin_ptr<const wchar_t> formatedValue = PtrToStringChars(text);
		double resultValue;
		bool result = tacviewInterface->UIFormatTextToSpeed(addonHandle, formatedValue, resultValue);
		value = resultValue;
		return result;
	}

	bool Wrapper::UIClass::FormatClass::TextToSpeedLocalized(System::String ^ text, [Out] double % value)
	{
		pin_ptr<const wchar_t> formatedValue = PtrToStringChars(text);
		double resultValue;
		bool result = tacviewInterface->UIFormatTextToSpeedLocalized(addonHandle, formatedValue, resultValue);
		value = resultValue;
		return result;
	}

	String ^ Wrapper::UIClass::FormatClass::LongitudeToText(double value)
	{
		wchar_t formatedValue[256];
		tacviewInterface->UIFormatLongitudeToText(addonHandle, value, formatedValue, _countof(formatedValue));
		return gcnew System::String(formatedValue);
	}

	String ^ Wrapper::UIClass::FormatClass::LatitudeToText(double value)
	{
		wchar_t formatedValue[256];
		tacviewInterface->UIFormatLatitudeToText(addonHandle, value, formatedValue, _countof(formatedValue));
		return gcnew System::String(formatedValue);
	}

	bool Wrapper::UIClass::FormatClass::TextToSpherical(System::String ^ text, [Out] double % value)
	{
		pin_ptr<const wchar_t> formatedValue = PtrToStringChars(text);
		double resultValue;
		bool result = tacviewInterface->UIFormatTextToSpherical(addonHandle, formatedValue, resultValue);
		value = resultValue;
		return result;
	}

	String ^ Wrapper::UIClass::FormatClass::AbsoluteTimeToISOText(double value, bool outputDecimals)
	{
		wchar_t formatedValue[256];
		tacviewInterface->UIFormatAbsoluteTimeToISOText(addonHandle, value, outputDecimals, formatedValue, _countof(formatedValue));
		return gcnew System::String(formatedValue);
	}

	bool Wrapper::UIClass::FormatClass::TextToAbsoluteTime(System::String ^ text, [Out] double % value)
	{
		pin_ptr<const wchar_t> formatedValue = PtrToStringChars(text);
		double resultValue;
		bool result = tacviewInterface->UIFormatTextToAbsoluteTime(addonHandle, formatedValue, resultValue);
		value = resultValue;
		return result;
	}

	// Tacview.UI.Menu

	Wrapper::UIClass::MenusClass::MenusClass(void * newAddonHandle, TacviewSDK::Interface187 * newTacviewInterface) :
		addonHandle(newAddonHandle),
		tacviewInterface(newTacviewInterface)
	{
	}

	int Wrapper::UIClass::MenusClass::AddMenu(int parentMenuId, System::String ^ _menuLabel)
	{
		pin_ptr<const wchar_t> menuLabel = PtrToStringChars(_menuLabel);
		return tacviewInterface->UIMenusAddMenu(addonHandle, parentMenuId, menuLabel);
	}

	int Wrapper::UIClass::MenusClass::AddSeparator(int parentMenuId)
	{
		return tacviewInterface->UIMenusAddSeparator(addonHandle, parentMenuId);
	}

	// NOTE: This code should be improved to prevent any possibility of garbage collecting of the client delegates.

	typedef void(__stdcall * TacviewEventsMenuEventHandler172StdCall)(int commandId);

	static void _cdecl MenuEventCallback(void * userData, int commandId)
	{
		// Tacview supports only cdecl callbacks,
		// while delegates can only be called from C++ with stdcall convention.

		static_cast<TacviewEventsMenuEventHandler172StdCall>(userData)(commandId);
	}

	int Wrapper::UIClass::MenusClass::AddCommand(int parentMenuId, System::String ^ _menuLabel, MenuEventHandler ^ eventHandler)
	{
		pin_ptr<const wchar_t> menuLabel = PtrToStringChars(_menuLabel);
		menuEventHandler += eventHandler;
		return tacviewInterface->UIMenusAddCommand(addonHandle, parentMenuId, menuLabel, MenuEventCallback, Marshal::GetFunctionPointerForDelegate(eventHandler).ToPointer());
	}

	int Wrapper::UIClass::MenusClass::AddOption(int parentMenuId, System::String ^ _menuLabel, bool optionValue, MenuEventHandler ^ eventHandler)
	{
		pin_ptr<const wchar_t> menuLabel = PtrToStringChars(_menuLabel);
		menuEventHandler += eventHandler;
		return tacviewInterface->UIMenusAddOption(addonHandle, parentMenuId, menuLabel, optionValue, MenuEventCallback, Marshal::GetFunctionPointerForDelegate(eventHandler).ToPointer());
	}

	int Wrapper::UIClass::MenusClass::AddExclusiveOption(int parentMenuId, System::String ^ _menuLabel, bool optionValue, MenuEventHandler ^ eventHandler)
	{
		pin_ptr<const wchar_t> menuLabel = PtrToStringChars(_menuLabel);
		menuEventHandler += eventHandler;
		return tacviewInterface->UIMenusAddExclusiveOption(addonHandle, parentMenuId, menuLabel, optionValue, MenuEventCallback, Marshal::GetFunctionPointerForDelegate(eventHandler).ToPointer());
	}

	void Wrapper::UIClass::MenusClass::SetOption(int commandId, bool optionValue)
	{
		tacviewInterface->UIMenusSetOption(addonHandle, commandId, optionValue);
	}

	Wrapper::UIClass::RendererClass::RendererClass(void * newAddonHandle, TacviewSDK::Interface187 * newTacviewInterface) :
		addonHandle(newAddonHandle),
		tacviewInterface(newTacviewInterface)
	{
		ContextMenu = gcnew ContextMenuClass(addonHandle, tacviewInterface);
		Pick3DPoint = gcnew Pick3DPointClass(addonHandle, tacviewInterface);
	}

	int Wrapper::UIClass::RendererClass::GetWidth()
	{
		return tacviewInterface->UIRendererGetWidth(addonHandle);
	}

	int Wrapper::UIClass::RendererClass::GetHeight()
	{
		return tacviewInterface->UIRendererGetHeight(addonHandle);
	}

	Wrapper::TextureHandle Wrapper::UIClass::RendererClass::LoadTexture(System::String ^ _texturePath, bool wrapRepeat, bool compressed)
	{
		pin_ptr<const wchar_t> texturePath = PtrToStringChars(_texturePath);
		return static_cast<Wrapper::TextureHandle>(tacviewInterface->UIRendererLoadTexture(addonHandle, texturePath, wrapRepeat, compressed));
	}

	void Wrapper::UIClass::RendererClass::UnloadTexture(TextureHandle textureHandle)
	{
		tacviewInterface->UIRendererUnloadTexture(addonHandle, static_cast<TacviewSDK::TextureHandle>(textureHandle));
	}

	Wrapper::VertexArrayHandle Wrapper::UIClass::RendererClass::CreateVertexArray(List<float3^> ^ _vertexList)
	{
		const size_t vertexCount = _vertexList->Count;

		TacviewSDK::float3 * vertexList = new TacviewSDK::float3[vertexCount];

		if (vertexList)
		{
			for (size_t vertexIndex = 0; vertexIndex < vertexCount; ++vertexIndex)
			{
				float3 ^ vertex = _vertexList[static_cast<int>(vertexIndex)];
				vertexList[vertexIndex] = { vertex->x, vertex->y, vertex->z };
			}
		}

		// Tacview will not crash if we pass a nullptr

		TacviewSDK::VertexArrayHandle vertexArrayHandle = tacviewInterface->UIRendererCreateVertexArray(addonHandle, vertexList, vertexCount);

		delete[]vertexList;
		vertexList = nullptr;

		return static_cast<Wrapper::VertexArrayHandle>(vertexArrayHandle);
	}

	void Wrapper::UIClass::RendererClass::ReleaseVertexArray(VertexArrayHandle vertexArrayHandle)
	{
		tacviewInterface->UIRendererReleaseVertexArray(addonHandle, static_cast<TacviewSDK::VertexArrayHandle>(vertexArrayHandle));
	}

	Wrapper::TextureCoordinateArrayHandle Wrapper::UIClass::RendererClass::CreateTextureCoordinateArray(List<float2^> ^ _uvList)
	{
		const size_t uvCount = _uvList->Count;

		TacviewSDK::float2 * uvList = new TacviewSDK::float2[uvCount];

		if (uvList)
		{
			for (size_t uvIndex = 0; uvIndex < uvCount; ++uvIndex)
			{
				float2 ^ uv = _uvList[static_cast<int>(uvIndex)];
				uvList[uvIndex] = { uv->x, uv->y };
			}
		}

		// Tacview will not crash if we pass a nullptr

		TacviewSDK::TextureCoordinateArrayHandle textureCoordinateArrayHandle = tacviewInterface->UIRendererCreateTextureCoordinateArray(addonHandle, uvList, uvCount);

		delete[]uvList;
		uvList = nullptr;

		return static_cast<Wrapper::TextureCoordinateArrayHandle>(textureCoordinateArrayHandle);
	}

	void Wrapper::UIClass::RendererClass::ReleaseTextureCoordinateArray(TextureCoordinateArrayHandle textureCoordinateArrayHandle)
	{
		tacviewInterface->UIRendererReleaseTextureCoordinateArray(addonHandle, static_cast<TacviewSDK::TextureCoordinateArrayHandle>(textureCoordinateArrayHandle));
	}

	Wrapper::RenderStateHandle Wrapper::UIClass::RendererClass::CreateRenderState(RenderState ^ _renderState)
	{
		TacviewSDK::RenderState renderState;

		renderState.color = _renderState->color;
		renderState.textureHandle = static_cast<TacviewSDK::TextureHandle>(_renderState->textureHandle);
		renderState.blendMode = static_cast<TacviewSDK::RenderState::BlendMode>(_renderState->blendMode);

		return static_cast<Wrapper::RenderStateHandle>(tacviewInterface->UIRendererCreateRenderState(addonHandle, &renderState));
	}

	void Wrapper::UIClass::RendererClass::ReleaseRenderState(RenderStateHandle renderStateHandle)
	{
		tacviewInterface->UIRendererReleaseRenderState(addonHandle, static_cast<TacviewSDK::RenderStateHandle>(renderStateHandle));
	}

	void Wrapper::UIClass::RendererClass::DrawObjectVertexArray(ObjectRenderSphericalTransform ^ _transform, RenderStateHandle renderStateHandle, VertexArrayHandle vertexArrayHandle, TextureCoordinateArrayHandle textureCoordinateArrayHandle)
	{
		TacviewSDK::ObjectRenderSphericalTransform transform = { 0 };

		transform.longitude = _transform->longitude;
		transform.latitude = _transform->latitude;
		transform.altitude = _transform->altitude;

		transform.roll = _transform->roll;
		transform.pitch = _transform->pitch;
		transform.yaw = _transform->yaw;

		transform.scale = _transform->scale;

		tacviewInterface->UIRendererDrawObjectVertexArray(addonHandle, &transform, static_cast<TacviewSDK::RenderStateHandle>(renderStateHandle), static_cast<TacviewSDK::VertexArrayHandle>(vertexArrayHandle), static_cast<TacviewSDK::TextureCoordinateArrayHandle>(textureCoordinateArrayHandle));
	}

	// UI.Renderer.DrawLines

	void Wrapper::UIClass::RendererClass::DrawLines(RenderStateHandle _renderStateHandle, float _thickness, List<double3 ^> ^ _vertexList)
	{
		const size_t vertexCount = _vertexList->Count;

		TacviewSDK::double3 * vertexList = new TacviewSDK::double3[vertexCount];

		if (vertexList)
		{
			for (size_t vertexIndex = 0; vertexIndex < vertexCount; ++vertexIndex)
			{
				double3 ^ vertex = _vertexList[static_cast<int>(vertexIndex)];
				vertexList[vertexIndex] = { vertex->x, vertex->y, vertex->z };
			}
		}

		// Tacview will not crash if we pass a nullptr

		tacviewInterface->UIRendererDrawLines(addonHandle, static_cast<TacviewSDK::RenderStateHandle>(_renderStateHandle), _thickness, vertexList, vertexCount);

		delete[]vertexList;
		vertexList = nullptr;
	}

	void Wrapper::UIClass::RendererClass::DrawLines(RenderStateHandle _renderStateHandle, float _thickness, List<ColorVertex ^> ^ _vertexList)
	{
		const size_t vertexCount = _vertexList->Count;

		TacviewSDK::ColorVertex * vertexList = new TacviewSDK::ColorVertex[vertexCount];

		if (vertexList)
		{
			for (size_t vertexIndex = 0; vertexIndex < vertexCount; ++vertexIndex)
			{
				ColorVertex ^ vertex = _vertexList[static_cast<int>(vertexIndex)];
				vertexList[vertexIndex] = { vertex->x, vertex->y, vertex->z };
			}
		}

		// Tacview will not crash if we pass a nullptr

		tacviewInterface->UIRendererDrawColoredLines(addonHandle, static_cast<TacviewSDK::RenderStateHandle>(_renderStateHandle), _thickness, vertexList, vertexCount);

		delete[]vertexList;
		vertexList = nullptr;
	}

	// UI.Renderer.DrawLineStrip

	void Wrapper::UIClass::RendererClass::DrawLineStrip(RenderStateHandle _renderStateHandle, float _thickness, List<double3 ^> ^ _vertexList)
	{
		const size_t vertexCount = _vertexList->Count;

		TacviewSDK::double3 * vertexList = new TacviewSDK::double3[vertexCount];

		if (vertexList)
		{
			for (size_t vertexIndex = 0; vertexIndex < vertexCount; ++vertexIndex)
			{
				double3 ^ vertex = _vertexList[static_cast<int>(vertexIndex)];
				vertexList[vertexIndex] = { vertex->x, vertex->y, vertex->z };
			}
		}

		// Tacview will not crash if we pass a nullptr

		tacviewInterface->UIRendererDrawLineStrip(addonHandle, static_cast<TacviewSDK::RenderStateHandle>(_renderStateHandle), _thickness, vertexList, vertexCount);

		delete[]vertexList;
		vertexList = nullptr;
	}

	void Wrapper::UIClass::RendererClass::DrawLineStrip(RenderStateHandle _renderStateHandle, float _thickness, List<ColorVertex ^> ^ _vertexList)
	{
		const size_t vertexCount = _vertexList->Count;

		TacviewSDK::ColorVertex * vertexList = new TacviewSDK::ColorVertex[vertexCount];

		if (vertexList)
		{
			for (size_t vertexIndex = 0; vertexIndex < vertexCount; ++vertexIndex)
			{
				ColorVertex ^ vertex = _vertexList[static_cast<int>(vertexIndex)];
				vertexList[vertexIndex] = { vertex->x, vertex->y, vertex->z };
			}
		}

		// Tacview will not crash if we pass a nullptr

		tacviewInterface->UIRendererDrawColoredLineStrip(addonHandle, static_cast<TacviewSDK::RenderStateHandle>(_renderStateHandle), _thickness, vertexList, vertexCount);

		delete[]vertexList;
		vertexList = nullptr;
	}

	// UI.Renderer.DrawObjectVertexArray

	void Wrapper::UIClass::RendererClass::DrawObjectVertexArray(ObjectRenderCartesianTransform ^ _transform, RenderStateHandle renderStateHandle, VertexArrayHandle vertexArrayHandle, TextureCoordinateArrayHandle textureCoordinateArrayHandle)
	{
		TacviewSDK::ObjectRenderCartesianTransform transform = { 0 };

		transform.x = _transform->x;
		transform.y = _transform->y;
		transform.z = _transform->z;

		transform.roll = _transform->roll;
		transform.pitch = _transform->pitch;
		transform.yaw = _transform->yaw;

		transform.scale = _transform->scale;

		tacviewInterface->UIRendererDrawObjectVertexArray2(addonHandle, &transform, static_cast<TacviewSDK::RenderStateHandle>(renderStateHandle), static_cast<TacviewSDK::VertexArrayHandle>(vertexArrayHandle), static_cast<TacviewSDK::TextureCoordinateArrayHandle>(textureCoordinateArrayHandle));
	}

	void Wrapper::UIClass::RendererClass::DrawUIVertexArray(UIRenderTransform ^ _transform, RenderStateHandle renderStateHandle, VertexArrayHandle vertexArrayHandle, TextureCoordinateArrayHandle textureCoordinateArrayHandle)
	{
		TacviewSDK::UIRenderTransform transform = {0};

		transform.x = _transform->x;
		transform.y = _transform->y;
		transform.z = _transform->z;

		transform.roll = _transform->roll;
		transform.pitch = _transform->pitch;
		transform.yaw = _transform->yaw;

		transform.scale = _transform->scale;

		tacviewInterface->UIRendererDrawUIVertexArray(addonHandle, &transform, static_cast<TacviewSDK::RenderStateHandle>(renderStateHandle), static_cast<TacviewSDK::VertexArrayHandle>(vertexArrayHandle), static_cast<TacviewSDK::TextureCoordinateArrayHandle>(textureCoordinateArrayHandle));
	}

	void Wrapper::UIClass::RendererClass::DrawUIVertexArray(UIRenderShapeTransform ^ _transform, RenderStateHandle renderStateHandle, VertexArrayHandle vertexArrayHandle, TextureCoordinateArrayHandle textureCoordinateArrayHandle)
	{
		TacviewSDK::UIRenderShapeTransform transform = { 0 };

		transform.x = _transform->x;
		transform.y = _transform->y;
		transform.z = _transform->z;

		transform.roll = _transform->roll;
		transform.pitch = _transform->pitch;
		transform.yaw = _transform->yaw;

		transform.scaleX = _transform->scaleX;
		transform.scaleY = _transform->scaleY;

		tacviewInterface->UIRendererDrawUIVertexArray2(addonHandle, &transform, static_cast<TacviewSDK::RenderStateHandle>(renderStateHandle), static_cast<TacviewSDK::VertexArrayHandle>(vertexArrayHandle), static_cast<TacviewSDK::TextureCoordinateArrayHandle>(textureCoordinateArrayHandle));
	}

	void Wrapper::UIClass::RendererClass::DrawOpaqueObject(ObjectHandle objectHandle, ObjectRenderSphericalTransform ^ _transform, float alpha)
	{
		TacviewSDK::ObjectRenderSphericalTransform transform = { 0 };

		transform.longitude = _transform->longitude;
		transform.latitude = _transform->latitude;
		transform.altitude = _transform->altitude;

		transform.roll = _transform->roll;
		transform.pitch = _transform->pitch;
		transform.yaw = _transform->yaw;

		transform.scale = _transform->scale;

		tacviewInterface->UIRendererDrawOpaqueObject(addonHandle, static_cast<TacviewSDK::ObjectHandle>(objectHandle), &transform, alpha);
	}

	void Wrapper::UIClass::RendererClass::DrawOpaqueObject(ObjectHandle objectHandle, ObjectRenderCartesianTransform ^ _transform, float alpha)
	{
		TacviewSDK::ObjectRenderCartesianTransform transform = { 0 };

		transform.x = _transform->x;
		transform.y = _transform->y;
		transform.z = _transform->z;

		transform.roll = _transform->roll;
		transform.pitch = _transform->pitch;
		transform.yaw = _transform->yaw;

		transform.scale = _transform->scale;

		tacviewInterface->UIRendererDrawOpaqueObject2(addonHandle, static_cast<TacviewSDK::ObjectHandle>(objectHandle), &transform, alpha);
	}

	void Wrapper::UIClass::RendererClass::DrawTransparentObject(ObjectHandle objectHandle, ObjectRenderSphericalTransform ^ _transform, float alpha)
	{
		TacviewSDK::ObjectRenderSphericalTransform transform = { 0 };

		transform.longitude = _transform->longitude;
		transform.latitude = _transform->latitude;
		transform.altitude = _transform->altitude;

		transform.roll = _transform->roll;
		transform.pitch = _transform->pitch;
		transform.yaw = _transform->yaw;

		transform.scale = _transform->scale;

		tacviewInterface->UIRendererDrawTransparentObject(addonHandle, static_cast<TacviewSDK::ObjectHandle>(objectHandle), &transform, alpha);
	}

	void Wrapper::UIClass::RendererClass::DrawTransparentObject(ObjectHandle objectHandle, ObjectRenderCartesianTransform ^ _transform, float alpha)
	{
		TacviewSDK::ObjectRenderCartesianTransform transform = { 0 };

		transform.x = _transform->x;
		transform.y = _transform->y;
		transform.z = _transform->z;

		transform.roll = _transform->roll;
		transform.pitch = _transform->pitch;
		transform.yaw = _transform->yaw;

		transform.scale = _transform->scale;

		tacviewInterface->UIRendererDrawTransparentObject2(addonHandle, static_cast<TacviewSDK::ObjectHandle>(objectHandle), &transform, alpha);
	}

	void Wrapper::UIClass::RendererClass::Print(UIRenderTransform ^ _transform, RenderStateHandle renderStateHandle, System::String ^ _text)
	{
		TacviewSDK::UIRenderTransform transform = {0};

		transform.x = _transform->x;
		transform.y = _transform->y;
		transform.z = _transform->z;

		transform.roll = _transform->roll;
		transform.pitch = _transform->pitch;
		transform.yaw = _transform->yaw;

		transform.scale = _transform->scale;

		pin_ptr<const wchar_t> text = PtrToStringChars(_text);
		tacviewInterface->UIRendererPrint(addonHandle, &transform, static_cast<TacviewSDK::RenderStateHandle>(renderStateHandle), text);
	}

	void Wrapper::UIClass::RendererClass::Print(UIRenderTextTransform ^ _transform, RenderStateHandle renderStateHandle, System::String ^ _text)
	{
		TacviewSDK::UIRenderTextTransform transform = { 0 };

		transform.x = _transform->x;
		transform.y = _transform->y;
		transform.z = _transform->z;

		transform.scale = _transform->scale;

		pin_ptr<const wchar_t> text = PtrToStringChars(_text);
		tacviewInterface->UIRendererPrint2(addonHandle, &transform, static_cast<TacviewSDK::RenderStateHandle>(renderStateHandle), text);
	}

	// UI.Renderer.Load3DModel

	ModelHandle Wrapper::UIClass::RendererClass::Load3DModel(System::String ^ _fileName)
	{
		pin_ptr<const wchar_t> fileName = PtrToStringChars(_fileName);
		return tacviewInterface->UIRendererLoad3DModel(addonHandle, fileName);
	}

	// UI.Renderer.Draw3DModel

	void Wrapper::UIClass::RendererClass::Draw3DModel(ModelHandle modelHandle, ObjectRenderSphericalTransform ^ _transform, uint32_t color)
	{
		TacviewSDK::ObjectRenderSphericalTransform transform = { 0 };

		transform.longitude = _transform->longitude;
		transform.latitude = _transform->latitude;
		transform.altitude = _transform->altitude;

		transform.roll = _transform->roll;
		transform.pitch = _transform->pitch;
		transform.yaw = _transform->yaw;

		transform.scale = _transform->scale;

		tacviewInterface->UIRendererDraw3DModel(addonHandle, modelHandle, &transform, color);
	}

	void Wrapper::UIClass::RendererClass::Draw3DModel(ModelHandle modelHandle, ObjectRenderCartesianTransform ^ _transform, uint32_t color)
	{
		TacviewSDK::ObjectRenderCartesianTransform transform = { 0 };

		transform.x = _transform->x;
		transform.y = _transform->y;
		transform.z = _transform->z;

		transform.roll = _transform->roll;
		transform.pitch = _transform->pitch;
		transform.yaw = _transform->yaw;

		transform.scale = _transform->scale;

		tacviewInterface->UIRendererDraw3DModel2(addonHandle, modelHandle, &transform, color);
	}

	// UI.Renderer.DrawSemiTransparent3DModel

	void Wrapper::UIClass::RendererClass::DrawSemiTransparent3DModel(ModelHandle modelHandle, ObjectRenderSphericalTransform ^ _transform, uint32_t color)
	{
		TacviewSDK::ObjectRenderSphericalTransform transform = { 0 };

		transform.longitude = _transform->longitude;
		transform.latitude = _transform->latitude;
		transform.altitude = _transform->altitude;

		transform.roll = _transform->roll;
		transform.pitch = _transform->pitch;
		transform.yaw = _transform->yaw;

		transform.scale = _transform->scale;

		tacviewInterface->UIRendererDrawSemiTransparent3DModel(addonHandle, modelHandle, &transform, color);
	}

	void Wrapper::UIClass::RendererClass::DrawSemiTransparent3DModel(ModelHandle modelHandle, ObjectRenderCartesianTransform ^ _transform, uint32_t color)
	{
		TacviewSDK::ObjectRenderCartesianTransform transform = { 0 };

		transform.x = _transform->x;
		transform.y = _transform->y;
		transform.z = _transform->z;

		transform.roll = _transform->roll;
		transform.pitch = _transform->pitch;
		transform.yaw = _transform->yaw;

		transform.scale = _transform->scale;

		tacviewInterface->UIRendererDrawSemiTransparent3DModel2(addonHandle, modelHandle, &transform, color);
	}

	// UI.Renderer.Redraw

	Wrapper::UIClass::UIClass(void * newAddonHandle, TacviewSDK::Interface187 * newTacviewInterface) :
		addonHandle(newAddonHandle),
		tacviewInterface(newTacviewInterface)
	{
		MessageBox = gcnew MessageBoxClass(newAddonHandle, newTacviewInterface);
		Menus = gcnew MenusClass(newAddonHandle, newTacviewInterface);
		Format = gcnew FormatClass(newAddonHandle, newTacviewInterface);
		Renderer = gcnew RendererClass(newAddonHandle, newTacviewInterface);
	}

	void Wrapper::UIClass::EnterFullScreen()
	{
		tacviewInterface->UIEnterFullScreen(addonHandle);
	}

	void Wrapper::UIClass::ExitFullScreen()
	{
		tacviewInterface->UIExitFullScreen(addonHandle);
	}

	void Wrapper::UIClass::EnterReadMode(bool borderless)
	{
		tacviewInterface->UIEnterReadMode(addonHandle, borderless);
	}

	void Wrapper::UIClass::ExitReadMode()
	{
		tacviewInterface->UIExitReadMode(addonHandle);
	}

	void Wrapper::UIClass::SetWindowParent(IntPtr parentWindow)
	{
		tacviewInterface->UISetWindowParent(addonHandle, (HWND)parentWindow.ToPointer());
	}

	void Wrapper::UIClass::SetWindowPosition(int x, int y)
	{
		tacviewInterface->UISetWindowPosition(addonHandle, x, y);
	}

	void Wrapper::UIClass::SetWindowPosition(int x, int y, int width, int height)
	{
		tacviewInterface->UISetWindowPosition2(addonHandle, x, y, width, height);
	}

	void Wrapper::UIClass::SetWindowSize(int width, int height)
	{
		tacviewInterface->UISetWindowSize(addonHandle, width, height);
	}

	IntPtr Wrapper::UIClass::GetWindowHandle()
	{
		return IntPtr(tacviewInterface->UIGetWindowHandle(addonHandle));
	}

	void Wrapper::UIClass::Update()
	{
		tacviewInterface->UIUpdate(addonHandle);
	}

	// Tacview.UI.Renderer.Pick3DPoint

	static void _cdecl Pick3DPointEventHandler(void * userData, double longitude, double latitude, double altitude)
	{
		Wrapper::UIClass::RendererClass::Pick3DPointClass ^ self = (Wrapper::UIClass::RendererClass::Pick3DPointClass ^)GCHandle::FromIntPtr(IntPtr(userData)).Target;
		self->OnPick3DPoint(longitude, latitude, altitude);
	}

	Wrapper::UIClass::RendererClass::Pick3DPointClass::Pick3DPointClass(void * addonHandle, TacviewSDK::Interface187 * tacviewInterface)
	{
		selfHandle = GCHandle::Alloc(this);
		tacviewInterface->UIRendererPick3DPointRegisterListener(addonHandle, Pick3DPointEventHandler, GCHandle::ToIntPtr(selfHandle).ToPointer());
	}

	Wrapper::UIClass::RendererClass::Pick3DPointClass::~Pick3DPointClass()
	{
		selfHandle.Free();
	}
	// Tacview.UI.Renderer.ContextMenu

	static void _cdecl ContextMenuEventHandler(void * userData, int contextMenuId, TacviewSDK::ObjectHandle objectHandle)
	{
		Wrapper::UIClass::RendererClass::ContextMenuClass ^ self = (Wrapper::UIClass::RendererClass::ContextMenuClass^)GCHandle::FromIntPtr(IntPtr(userData)).Target;
		self->OnContextMenu(contextMenuId, static_cast<TacviewSDK::Wrapper::ObjectHandle>(objectHandle));
	}

	Wrapper::UIClass::RendererClass::ContextMenuClass::ContextMenuClass(void * addonHandle, TacviewSDK::Interface187 * tacviewInterface)
	{
		selfHandle = GCHandle::Alloc(this);
		tacviewInterface->UIRendererContextMenuRegisterListerner(addonHandle, ContextMenuEventHandler, GCHandle::ToIntPtr(selfHandle).ToPointer());
	}

	Wrapper::UIClass::RendererClass::ContextMenuClass::~ContextMenuClass()
	{
		selfHandle.Free();
	}
}