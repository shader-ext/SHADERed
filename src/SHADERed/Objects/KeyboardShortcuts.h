#pragma once
#include <functional>
#include <map>
#include <string>
#include <vector>

#include <imgui/imgui.h>
#include <SHADERed/Objects/PluginAPI/Plugin.h>

namespace ed {
	class KeyboardShortcuts {
	public:
		static KeyboardShortcuts& Instance()
		{
			static KeyboardShortcuts ret;
			return ret;
		}
		struct Shortcut {
			ImGuiKey Key1;
			ImGuiKey Key2;
			bool Alt;
			bool Ctrl;
			bool Shift;
			std::function<void()> Function;
			IPlugin1* Plugin;

			Shortcut()
					: Key1(ImGuiKey_None)
					, Key2(ImGuiKey_None)
					, Alt(false)
					, Ctrl(false)
					, Shift(false)
					, Function(nullptr)
					, Plugin(nullptr)
			{
			}
			Shortcut(ImGuiKey k1, ImGuiKey k2, bool alt, bool ctrl, bool shift)
					: Key1(k1)
					, Key2(k2)
					, Alt(alt)
					, Ctrl(ctrl)
					, Shift(shift)
					, Plugin(nullptr)
			{
			}
		};

		KeyboardShortcuts();

		void Load();
		void Save();

		// set vk2 to negative if not used
		std::string Exists(const std::string& name, ImGuiKey Key1, ImGuiKey Key2, bool alt, bool ctrl, bool shift);
		bool Set(const std::string& name, ImGuiKey Key1, ImGuiKey Key2, bool alt, bool ctrl, bool shift);
		inline void Remove(const std::string& name)
		{
			m_data[name].Alt = m_data[name].Ctrl = m_data[name].Shift = false;
			m_data[name].Key1 = m_data[name].Key2 = ImGuiKey_None;
		}
		void SetCallback(const std::string& name, std::function<void()> func);
		void RegisterPluginShortcut(IPlugin1* plugin, const std::string& name);

		std::string GetString(const std::string& name);
		std::vector<std::string> GetNameList();

		inline std::map<std::string, Shortcut> GetMap() { return m_data; }
		inline void SetMap(std::map<std::string, Shortcut>& m) { m_data = m; }

		inline void Detach(const std::string& name) { m_data.erase(name); }

		bool IsShortchutPressed(const Shortcut& s);

		void Check(bool codeHasFocus);

		// Helper functions for key mapping
		static ImGuiKey GetKeyFromName(const std::string& name);
		static std::string GetKeyName(ImGuiKey key);

	private:
		bool m_canSolo(const std::string& name, ImGuiKey k);

		ImGuiKey m_keys[2];
		std::map<std::string, Shortcut> m_data;
	};
}