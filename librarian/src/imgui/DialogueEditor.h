#pragma once

namespace me {
	namespace ui {
		class Text;
	}
}

namespace lb {
	class DialogueWriter;
}

namespace lb {
	namespace imgui {
		namespace dialogueEditor {
			void showEditor(me::ui::Text* text);
			void init(DialogueWriter* writer);
			void destroy();
		}
	}
}