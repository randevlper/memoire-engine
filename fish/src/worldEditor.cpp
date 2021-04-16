#include "worldEditor.h"
#include <dear-imgui/imgui.h>

#include <glm/vec2.hpp>
#include "Engine/Nodes/Node2D.h"
#include "fishSpawner.h"
#include "fish.h"
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

	ImGui::InputInt("fishDir", &spawnDir);

	fishSpawner->setSpawnDir(spawnDir);
}

void fish::editorFishSpawnerManager(Node* node)
{
	ImGui::Text("FISH SPAWNER MANAGER EDITOR");
}

void fish::editorFish(Node* node) {
	Fish* fish = dynamic_cast<Fish*>(node);
	float score = fish->getScore();
	float speed = fish->getSpeed();
	ImGui::InputFloat("Score", &score);
	ImGui::InputFloat("Speed", &speed);
	fish->setScore(score);
	fish->setSpeed(speed);
}
