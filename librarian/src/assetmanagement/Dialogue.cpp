#include "Dialogue.h"

namespace lb {
	Dialogue::Dialogue()
	{
		lines = std::vector<DialogueLine>();
	}

	Dialogue::Dialogue(nlohmann::json& j)
	{
		lines = std::vector<DialogueLine>();
		from_json(j);
	}

	Dialogue::~Dialogue()
	{

	}
}