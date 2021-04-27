#include "worldEditor.h"
#include <dear-imgui/imgui.h>

#include <glm/vec2.hpp>

#include "Engine/Nodes/Node2D.h"
#include "Engine/IMGUI/WorldEditor.h"

#include "fishSpawner.h"
#include "fish.h"
void fish::editorFishSpawner(Node* node)
{
	me::imgui::worldEditor::editorNode2D(node);
	FishSpawner* fishSpawner = dynamic_cast<FishSpawner*>(node);

	int spawnDir = fishSpawner->getSpawnDir();
	ImGui::InputInt("fishDir", &spawnDir);
	fishSpawner->setSpawnDir(spawnDir);
}

void fish::editorFishSpawnerManager(Node* node)
{
	ImGui::Text("FISH SPAWNER MANAGER EDITOR");
}

void fish::editorFish(Node* node) {
	me::imgui::worldEditor::editorBody2D(node);
	Fish* fish = dynamic_cast<Fish*>(node);
	float score = fish->getScore();
	float speed = fish->getSpeed();
	ImGui::InputFloat("Score", &score);
	ImGui::InputFloat("Speed", &speed);
	fish->setScore(score);
	fish->setSpeed(speed);
}

void fish::editorNet(Node* node)
{
	me::imgui::worldEditor::editorBody2D(node);
}

void fish::editorPlayerController(Node* node)
{
	me::imgui::worldEditor::editorNode2D(node);
}
