#pragma once

namespace me {
	namespace imgui {
		void create();
		void beginFrame();
		void endFrame();
		void destroy();
		bool isAnyWindowFocused();
		bool isIMGUIOpen();
		void setIMGUIVisibility(bool isOpen);
	}
}