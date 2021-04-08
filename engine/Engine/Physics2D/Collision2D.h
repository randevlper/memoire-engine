#pragma once
class b2Contact;
class Body2D;

struct Collision2D
{
	b2Contact* contact;
	Body2D* other;
};