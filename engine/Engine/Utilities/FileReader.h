#pragma once
#include "bx/file.h"

class FileReader : public bx::FileReader
{
	typedef bx::FileReader super;

public:
	virtual bool open(const bx::FilePath& _filePath, bx::Error* _err) override
	{
		return super::open(_filePath, _err);
	}
};