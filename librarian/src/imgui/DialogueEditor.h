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
			void showEditor();
			void init(DialogueWriter* writer);
		}
	}
}