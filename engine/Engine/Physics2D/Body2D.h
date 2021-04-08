#pragma once
#include "Engine/Nodes/Node2D.h"
#include "box2d/b2_types.h"
#include  "Collision2D.h"

class b2Body;

enum class Body2DType
{
	Static = 0,
	Kinematic = 1,
	Dynamic = 2
};

class Body2D : public Node2D
{
public:
	Body2D();
	~Body2D() override;

	void setupBox(int x, int y, int width, int height, Body2DType bodyType,
		uint16 category, uint16 mask, bool isSensor = false);
	void setPosition(glm::vec2 pos);
	glm::vec2 getPosition();

	void setVelocity(glm::vec2 value);
	
	void setIsAwake(bool value);
	bool isAwake();

	void setIsEnabled(bool value);
	bool isEnabled();

	Body2DType getBodyType();
	uint16 getCatagory();
	uint16 getMask();

	bool isSensor();

	virtual void OnContactStart(Collision2D collision);
	virtual void OnContactEnd(Collision2D collision);

	virtual nlohmann::json to_json() override;
	virtual void from_json(const nlohmann::json& j) override;

protected:
	b2Body* _body;

	glm::vec2 _startPos;
	glm::vec2 _size;
	Body2DType _bodyType;
	uint16 _catagory;
	uint16 _mask;
	bool _isSensor;
};