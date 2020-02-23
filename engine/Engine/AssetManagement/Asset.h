#pragma once
class Asset
{
public:
	Asset(){}
	virtual ~Asset(){}

	virtual void load(){}
	virtual void destroy(){}

private:

};