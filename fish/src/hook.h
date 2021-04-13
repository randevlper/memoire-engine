#pragma once
#include "Engine/Physics2D/Body2D.h"

namespace me {
	namespace ui {
		class Text;
	}
}

class Hook : public Body2D
{
public:
	Hook();

	void init() override;
	void tick() override;

	void OnContactStart(Collision2D collision) override;

private:
	int _score;
	me::ui::Text* _scoreText;
};