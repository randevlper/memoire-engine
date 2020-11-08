#pragma once
#include <string>
class Transform;

class Debug
{
public:
	static void Log(std::string* values, size_t count);
	static void Log(std::string value);
	static void LogError(std::string value);
	static void LogError(std::string* values, size_t count);
	static void DrawTransform(Transform* t);
private:

};