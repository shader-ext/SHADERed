#include <SHADERed/Objects/KeyboardShortcuts.h>
#include <SHADERed/Objects/Logger.h>
#include <SHADERed/Objects/Settings.h>
#include <SHADERed/Objects/Names.h>

#include <fstream>
#include <sstream>
#include <filesystem>

#include <ImGuiColorTextEdit/TextEditor.h>

namespace ed {
	std::string getShortcutsFilePath()
	{
		std::string path = "data/shortcuts.kb";
		if (!ed::Settings::Instance().LinuxHomeDirectory.empty() && std::filesystem::exists(ed::Settings::Instance().ConvertPath(path)))
			path = ed::Settings::Instance().ConvertPath(path);
		return path;
	}

	static const std::map<std::string, ImGuiKey> GKeyCodes = {
		{ "Tab", ImGuiKey_Tab },
		{ "LeftArrow", ImGuiKey_LeftArrow },
		{ "RightArrow", ImGuiKey_RightArrow },
		{ "UpArrow", ImGuiKey_UpArrow },
		{ "DownArrow", ImGuiKey_DownArrow },
		{ "PageUp", ImGuiKey_PageUp },
		{ "PageDown", ImGuiKey_PageDown },
		{ "Home", ImGuiKey_Home },
		{ "End", ImGuiKey_End },
		{ "Insert", ImGuiKey_Insert },
		{ "Delete", ImGuiKey_Delete },
		{ "Backspace", ImGuiKey_Backspace },
		{ "Space", ImGuiKey_Space },
		{ "Enter", ImGuiKey_Enter },
		{ "Escape", ImGuiKey_Escape },
		{ "LeftCtrl", ImGuiKey_LeftCtrl },
		{ "LeftShift", ImGuiKey_LeftShift },
		{ "LeftAlt", ImGuiKey_LeftAlt },
		{ "LeftSuper", ImGuiKey_LeftSuper },
		{ "RightCtrl", ImGuiKey_RightCtrl },
		{ "RightShift", ImGuiKey_RightShift },
		{ "RightAlt", ImGuiKey_RightAlt },
		{ "RightSuper", ImGuiKey_RightSuper },
		{ "Menu", ImGuiKey_Menu },
		{ "0", ImGuiKey_0 },
		{ "1", ImGuiKey_1 },
		{ "2", ImGuiKey_2 },
		{ "3", ImGuiKey_3 },
		{ "4", ImGuiKey_4 },
		{ "5", ImGuiKey_5 },
		{ "6", ImGuiKey_6 },
		{ "7", ImGuiKey_7 },
		{ "8", ImGuiKey_8 },
		{ "9", ImGuiKey_9 },
		{ "A", ImGuiKey_A },
		{ "B", ImGuiKey_B },
		{ "C", ImGuiKey_C },
		{ "D", ImGuiKey_D },
		{ "E", ImGuiKey_E },
		{ "F", ImGuiKey_F },
		{ "G", ImGuiKey_G },
		{ "H", ImGuiKey_H },
		{ "I", ImGuiKey_I },
		{ "J", ImGuiKey_J },
		{ "K", ImGuiKey_K },
		{ "L", ImGuiKey_L },
		{ "M", ImGuiKey_M },
		{ "N", ImGuiKey_N },
		{ "O", ImGuiKey_O },
		{ "P", ImGuiKey_P },
		{ "Q", ImGuiKey_Q },
		{ "R", ImGuiKey_R },
		{ "S", ImGuiKey_S },
		{ "T", ImGuiKey_T },
		{ "U", ImGuiKey_U },
		{ "V", ImGuiKey_V },
		{ "W", ImGuiKey_W },
		{ "X", ImGuiKey_X },
		{ "Y", ImGuiKey_Y },
		{ "Z", ImGuiKey_Z },
		{ "F1", ImGuiKey_F1 },
		{ "F2", ImGuiKey_F2 },
		{ "F3", ImGuiKey_F3 },
		{ "F4", ImGuiKey_F4 },
		{ "F5", ImGuiKey_F5 },
		{ "F6", ImGuiKey_F6 },
		{ "F7", ImGuiKey_F7 },
		{ "F8", ImGuiKey_F8 },
		{ "F9", ImGuiKey_F9 },
		{ "F10", ImGuiKey_F10 },
		{ "F11", ImGuiKey_F11 },
		{ "F12", ImGuiKey_F12 },
		{ "F13", ImGuiKey_F13 },
		{ "F14", ImGuiKey_F14 },
		{ "F15", ImGuiKey_F15 },
		{ "F16", ImGuiKey_F16 },
		{ "F17", ImGuiKey_F17 },
		{ "F18", ImGuiKey_F18 },
		{ "F19", ImGuiKey_F19 },
		{ "F20", ImGuiKey_F20 },
		{ "F21", ImGuiKey_F21 },
		{ "F22", ImGuiKey_F22 },
		{ "F23", ImGuiKey_F23 },
		{ "F24", ImGuiKey_F24 },
		{ "Apostrophe", ImGuiKey_Apostrophe },
		{ "Comma", ImGuiKey_Comma },
		{ "Minus", ImGuiKey_Minus },
		{ "Period", ImGuiKey_Period },
		{ "Slash", ImGuiKey_Slash },
		{ "Semicolon", ImGuiKey_Semicolon },
		{ "Equal", ImGuiKey_Equal },
		{ "LeftBracket", ImGuiKey_LeftBracket },
		{ "Backslash", ImGuiKey_Backslash },
		{ "RightBracket", ImGuiKey_RightBracket },
		{ "GraveAccent", ImGuiKey_GraveAccent },
		{ "CapsLock", ImGuiKey_CapsLock },
		{ "ScrollLock", ImGuiKey_ScrollLock },
		{ "NumLock", ImGuiKey_NumLock },
		{ "PrintScreen", ImGuiKey_PrintScreen },
		{ "Pause", ImGuiKey_Pause },
		{ "Keypad0", ImGuiKey_Keypad0 },
		{ "Keypad1", ImGuiKey_Keypad1 },
		{ "Keypad2", ImGuiKey_Keypad2 },
		{ "Keypad3", ImGuiKey_Keypad3 },
		{ "Keypad4", ImGuiKey_Keypad4 },
		{ "Keypad5", ImGuiKey_Keypad5 },
		{ "Keypad6", ImGuiKey_Keypad6 },
		{ "Keypad7", ImGuiKey_Keypad7 },
		{ "Keypad8", ImGuiKey_Keypad8 },
		{ "Keypad9", ImGuiKey_Keypad9 },
		{ "KeypadDecimal", ImGuiKey_KeypadDecimal },
		{ "KeypadDivide", ImGuiKey_KeypadDivide },
		{ "KeypadMultiply", ImGuiKey_KeypadMultiply },
		{ "KeypadSubtract", ImGuiKey_KeypadSubtract },
		{ "KeypadAdd", ImGuiKey_KeypadAdd },
		{ "KeypadEnter", ImGuiKey_KeypadEnter },
		{ "KeypadEqual", ImGuiKey_KeypadEqual },
		{ "AppBack", ImGuiKey_AppBack },
		{ "AppForward", ImGuiKey_AppForward },
		{ "GamepadStart", ImGuiKey_GamepadStart },
		{ "GamepadBack", ImGuiKey_GamepadBack },
		{ "GamepadFaceLeft", ImGuiKey_GamepadFaceLeft },
		{ "GamepadFaceRight", ImGuiKey_GamepadFaceRight },
		{ "GamepadFaceUp", ImGuiKey_GamepadFaceUp },
		{ "GamepadFaceDown", ImGuiKey_GamepadFaceDown },
		{ "GamepadDpadLeft", ImGuiKey_GamepadDpadLeft },
		{ "GamepadDpadRight", ImGuiKey_GamepadDpadRight },
		{ "GamepadDpadUp", ImGuiKey_GamepadDpadUp },
		{ "GamepadDpadDown", ImGuiKey_GamepadDpadDown },
		{ "GamepadL1", ImGuiKey_GamepadL1 },
		{ "GamepadR1", ImGuiKey_GamepadR1 },
		{ "GamepadL2", ImGuiKey_GamepadL2 },
		{ "GamepadR2", ImGuiKey_GamepadR2 },
		{ "GamepadL3", ImGuiKey_GamepadL3 },
		{ "GamepadR3", ImGuiKey_GamepadR3 },
		{ "GamepadLStickLeft", ImGuiKey_GamepadLStickLeft },
		{ "GamepadLStickRight", ImGuiKey_GamepadLStickRight },
		{ "GamepadLStickUp", ImGuiKey_GamepadLStickUp },
		{ "GamepadLStickDown", ImGuiKey_GamepadLStickDown },
		{ "GamepadRStickLeft", ImGuiKey_GamepadRStickLeft },
		{ "GamepadRStickRight", ImGuiKey_GamepadRStickRight },
		{ "GamepadRStickUp", ImGuiKey_GamepadRStickUp },
		{ "GamepadRStickDown", ImGuiKey_GamepadRStickDown },
		{ "MouseLeft", ImGuiKey_MouseLeft },
		{ "MouseRight", ImGuiKey_MouseRight },
		{ "MouseMiddle", ImGuiKey_MouseMiddle },
		{ "MouseX1", ImGuiKey_MouseX1 },
		{ "MouseX2", ImGuiKey_MouseX2 },
		{ "MouseWheelX", ImGuiKey_MouseWheelX },
		{ "MouseWheelY", ImGuiKey_MouseWheelY },
		{ "ModCtrl", ImGuiKey_ModCtrl },
		{ "ModShift", ImGuiKey_ModShift },
		{ "ModAlt", ImGuiKey_ModAlt },
		{ "ModSuper", ImGuiKey_ModSuper }
	};

	ImGuiKey KeyboardShortcuts::GetKeyFromName(const std::string& name)
	{
		const auto& it = GKeyCodes.find(name);
		if (it != GKeyCodes.end())
		{
			return it->second;
		}

		return ImGuiKey_None;
	}

	std::string KeyboardShortcuts::GetKeyName(ImGuiKey key)
	{
		return ImGui::GetKeyName(key);
	}

	KeyboardShortcuts::KeyboardShortcuts()
	{
		m_keys[0] = m_keys[1] = ImGuiKey_None;
	}
	void KeyboardShortcuts::Load()
	{
		ed::Logger::Get().Log("Loading keyboard shortcuts");

		std::ifstream file(getShortcutsFilePath());
		std::string str;

		// pre setup Editor shortcuts (TODO: improve this... TextEditor::GetDefaultShortcuts())
		std::vector<TextEditor::Shortcut> eds = TextEditor::GetDefaultShortcuts();
		for (int i = 0; i < eds.size(); i++)
		{
			std::string shortcutName = "Editor." + std::string(EDITOR_SHORTCUT_NAMES[i]);
			Set(shortcutName, eds[i].Key1, eds[i].Key2, eds[i].Alt, eds[i].Ctrl, eds[i].Shift);
		}

		while (std::getline(file, str)) {
			std::stringstream ss(str);
			std::string name, token;

			ss >> name;

			if (name.empty()) continue;

			ImGuiKey vk1 = ImGuiKey_None, vk2 = ImGuiKey_None;
			bool alt = false, ctrl = false, shift = false;
			while (ss >> token) {
				if (token == "ModCtrl")
					ctrl = true;
				else if (token == "ModAlt")
					alt = true;
				else if (token == "ModShift")
					shift = true;
				else if (token == "NONE")
					break;
				else {
					if (vk1 == ImGuiKey_None)
						vk1 = GetKeyFromName(token);
					else if (m_data[name].Key2 == ImGuiKey_None)
						vk2 = GetKeyFromName(token);
				}
			}

			Set(name, vk1, vk2, alt, ctrl, shift);
		}

		ed::Logger::Get().Log("Loaded shortcut information");
	}
	void KeyboardShortcuts::Save()
	{
		ed::Logger::Get().Log("Saving keyboard shortcuts");

		std::ofstream file(ed::Settings::Instance().ConvertPath("data/shortcuts.kb"));
		std::string str;

		for (auto& s : m_data) {
			if (s.second.Key1 == ImGuiKey_None) {
				//file << " NONE" << std::endl;
				continue;
			}

			file << s.first;

			if (s.second.Ctrl)
				file << " ModCtrl";
			if (s.second.Alt)
				file << " ModAlt";
			if (s.second.Shift)
				file << " ModShift";
			file << " " << GetKeyName(s.second.Key1);
			if (s.second.Key2 != ImGuiKey_None)
				file << " " << GetKeyName(s.second.Key2);

			file << std::endl;
		}

		ed::Logger::Get().Log("Saved shortcut information");

		return;
	}
	std::string KeyboardShortcuts::Exists(const std::string& name, ImGuiKey Key1, ImGuiKey Key2, bool alt, bool ctrl, bool shift)
	{
		for (const auto& i : m_data) {
			if (name != i.first && i.second.Ctrl == ctrl && i.second.Alt == alt && i.second.Shift == shift && i.second.Key1 == Key1 && (Key2 == ImGuiKey_None || i.second.Key2 == Key2 || i.second.Key2 == ImGuiKey_None)) {

				// Exclude specific conflicting shortcuts
				if (!((name == "CodeUI.Save" && i.first == "Project.Save") || (name == "Project.Save" && i.first == "CodeUI.Save"))) {

					// Handle special cases for editors and plugins
					if ((name.find("Editor") == std::string::npos && i.first.find("Editor") == std::string::npos) || (name.find("Editor") != std::string::npos && i.first.find("Editor") != std::string::npos && name.find("Autocomplete") == std::string::npos && i.first.find("Autocomplete") == std::string::npos)) {
						return i.first;
					}
				}
			}
		}
		return "";
	}
	bool KeyboardShortcuts::Set(const std::string& name, ImGuiKey Key1, ImGuiKey Key2, bool alt, bool ctrl, bool shift)
	{
		if (Key1 == ImGuiKey_None || (Key2 != ImGuiKey_None && !m_canSolo(name, Key2)))
			return false;

		std::string ext = Exists(name, Key1, Key2, alt, ctrl, shift);
		if (!ext.empty())
			Remove(ext);

		m_data[name].Alt = alt;
		m_data[name].Ctrl = ctrl;
		m_data[name].Shift = shift;
		m_data[name].Key1 = Key1;
		m_data[name].Key2 = Key2;

		return true;
	}
	void KeyboardShortcuts::SetCallback(const std::string& name, std::function<void()> func)
	{
		m_data[name].Function = func;
	}
	void KeyboardShortcuts::RegisterPluginShortcut(IPlugin1* plugin, const std::string& name)
	{
		std::string actualName = "Plugin." + name;
		m_data[actualName].Plugin = plugin;
	}
	std::string KeyboardShortcuts::GetString(const std::string& name)
	{
		if (m_data[name].Key1 == ImGuiKey_None || (m_data[name].Key1 != ImGuiKey_None && m_data[name].Key2 == ImGuiKey_None)) {
			return "NONE";
		}

		std::string ret = "";
		if (m_data[name].Ctrl)
			ret += "ModCtrl+";
		if (m_data[name].Alt)
			ret += "ModAlt+";
		if (m_data[name].Shift)
			ret += "ModShift+";

		if (m_data[name].Key1 != ImGuiKey_None)
			ret += GetKeyName(m_data[name].Key1) + "+";
		if (m_data[name].Key2 != ImGuiKey_None)
			ret += GetKeyName(m_data[name].Key2) + "+";

		if (!ret.empty())
			ret.pop_back(); // Remove the last '+'

		return ret;
	}
	std::vector<std::string> KeyboardShortcuts::GetNameList()
	{
		std::vector<std::string> ret;
		for (const auto& i : m_data)
			ret.push_back(i.first);
		return ret;
	}
	bool KeyboardShortcuts::IsShortchutPressed(const Shortcut& s)
	{
		ImGuiIO& io = ImGui::GetIO();

		bool key1Pressed = (s.Key1 != ImGuiKey_None && ImGui::IsKeyPressed(s.Key1, false));
		bool key2Pressed = (s.Key2 == ImGuiKey_None || (ImGui::IsKeyPressed(s.Key2, false)));
		bool altPressed = (!s.Alt || io.KeyAlt);
		bool ctrlPressed = (!s.Ctrl || io.KeyCtrl);
		bool shiftPressed = (!s.Shift || io.KeyShift);

		return key1Pressed && key2Pressed && altPressed && ctrlPressed && shiftPressed;
	}
	void KeyboardShortcuts::Check(bool codeHasFocus)
	{
		for (const auto& it : m_data)
		{
			const std::string& name = it.first;
			const Shortcut& s = it.second;

			if (codeHasFocus &&
				name.find("Editor") == std::string::npos &&
				name.find("CodeUI") == std::string::npos &&
				name.find("Debug") == std::string::npos &&
				name != "Project.Save")
			{
				continue;
			}

			if (IsShortchutPressed(s))
			{
				if (s.Plugin != nullptr) {
					std::string actualName = name.substr(name.find_first_of('.') + 1);
					s.Plugin->HandleShortcut(actualName.c_str());
				} else
					s.Function();
			}
		}

		//ImGuiIO& io = ImGui::GetIO();

		//// Update key history
		//m_keys[0] = m_keys[1];
		//m_keys[1] = ImGuiKey_None; // Placeholder, since ImGui doesn't have a key event index.

		//bool alt = io.KeyAlt;
		//bool ctrl = io.KeyCtrl;
		//bool shift = io.KeyShift;

		//bool resetSecond = false, resetFirst = false;

		//for (const auto& hotkey : m_data) {
		//	if (codeHasFocus && !(hotkey.first.find("Editor") != std::string::npos || hotkey.first.find("CodeUI") != std::string::npos || hotkey.first.find("Debug") != std::string::npos || hotkey.first == "Project.Save"))
		//		continue;

		//	const Shortcut& s = hotkey.second;
		//	if (s.Alt == alt && s.Ctrl == ctrl && s.Shift == shift) {
		//		ImGuiKey key2 = m_keys[1];
		//		if (s.Key2 == ImGuiKey_None && s.Key1 == key2 && (s.Function != nullptr || s.Plugin != nullptr)) {
		//			/*
		//			 [ 'G', 'S' ] -> it would call the CTRL+S instead of CTRL+G+S shortcut.
		//			 That is why we check if we actually meant CTRL+S or CTRL+G+S
		//			*/
		//			bool found = false;
		//			ImGuiKey key1 = m_keys[0];
		//			if (key1 != ImGuiKey_None)
		//				for (const auto& clone : m_data)
		//					if (clone.second.Alt == alt && clone.second.Ctrl == ctrl && clone.second.Shift == shift && clone.second.Key1 == key1 && clone.second.Key2 == key2 && clone.second.Key2 != ImGuiKey_None) {
		//						found = true;
		//					}

		//			// call the proper function
		//			if (!found) {
		//				if (s.Plugin != nullptr) {
		//					std::string actualName = hotkey.first.substr(hotkey.first.find_first_of('.') + 1);
		//					s.Plugin->HandleShortcut(actualName.c_str());
		//				} else s.Function();

		//				resetSecond = true;
		//			}
		//		} else if (s.Key2 != ImGuiKey_None) {
		//			if (m_keys[0] != ImGuiKey_None) {
		//				ImGuiKey key1 = m_keys[0];

		//				if (s.Key1 == key1 && s.Key2 == key2 && (s.Function != nullptr || s.Plugin != nullptr)) {
		//					if (s.Plugin != nullptr) {
		//						std::string actualName = hotkey.first.substr(hotkey.first.find_first_of('.') + 1);
		//						s.Plugin->HandleShortcut(actualName.c_str());
		//					} else s.Function();

		//					resetFirst = resetSecond = true;
		//				}
		//			}
		//		}
		//	}
		//}

		//if (resetFirst) m_keys[0] = ImGuiKey_None;
		//if (resetSecond) m_keys[1] = ImGuiKey_None;
	}
	bool KeyboardShortcuts::m_canSolo(const std::string& name, ImGuiKey k)
	{
		bool isEditorSpecial = (name.find("Editor") != std::string::npos)
			&& !((k >= ImGuiKey_0 && k <= ImGuiKey_9) || (k >= ImGuiKey_A && k <= ImGuiKey_Z)); // the key can go solo if it's a "special" key
		
		return (k >= ImGuiKey_F1 && k <= ImGuiKey_F12)
			|| (k >= ImGuiKey_F13 && k <= ImGuiKey_F24)
			|| isEditorSpecial
			|| (name.find("Editor") == std::string::npos);
	}
}