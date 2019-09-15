#pragma once
class Transform;
class Collider;

class Debug
{
public:
	static void Log(char* value);
	static void DrawTransform(Transform* t);
	static void DrawCollider(Collider* col);
private:

};