#include "worldEditor.h"
#include <dear-imgui/imgui.h>

#include <glm/vec2.hpp>
#include "Engine/Nodes/Node2D.h"
#include "fishSpawner.h"
void fish::editorFishSpawner(Node* node)
{
	FishSpawner* fishSpawner = dynamic_cast<FishSpawner*>(node);

	Transform transform = fishSpawner->getTransform();
	//Would be more performant to have the editor access the memory directly but this way its using the same interface as the User
	glm::vec2 pos = transform.getLocalPosition();
	glm::vec2 scale = transform.getLocalScale();
	float angle = transform.getLocalAngle();

	ImGui::PushItemWidth(150);
	ImGui::InputFloat("Pos X", &pos.x);
	ImGui::SameLine();
	ImGui::InputFloat("Pos Y", &pos.y);
	ImGui::InputFloat("Scale X", &scale.x);
	ImGui::SameLine();
	ImGui::InputFloat("Scale Y", &scale.y);
	ImGui::InputFloat("Angle", &angle);


	transform.setLocalPosition(pos);
	transform.setLocalScale(scale);
	transform.setLocalAngle(angle);
	fishSpawner->setTransform(transform);

	int spawnDir = fishSpawner->getSpawnDir();
	float speed = fishSpawner->getSpeed();
	float time = fishSpawner->getTime();


	ImGui::InputInt("fishDir", &spawnDir);
	ImGui::InputFloat("fishSpeed", &speed);
	ImGui::InputFloat("fishTime", &time);

	fishSpawner->setSpawnDir(spawnDir);
	fishSpawner->setSpeed(speed);
	fishSpawner->setTime(time);
}
