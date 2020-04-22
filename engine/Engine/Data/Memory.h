#pragma once

#include <stdio.h>
#include "Engine/Utilities/DebugMemory.h"

namespace me {
	struct Memory
	{
		char* data;
		size_t size;
	};

	inline Memory* allocMemory(long fileSize) {
		Memory* mem = DBG_NEW Memory();
		mem->data = (char*)malloc(fileSize);
		mem->size = fileSize;
		return mem;
	}

	inline Memory* readBinaryFile(const char* path) {
		FILE* file = fopen(path, "rb");
		fseek(file, 0, SEEK_END);
		long fileSize = ftell(file);
		fseek(file, 0, SEEK_SET);

		me::Memory* mem = me::allocMemory(fileSize);
		fread(mem->data, 1, fileSize, file);
		//mem->data[mem->size - 1] = '\0';
		fclose(file);

		return mem;
	}

	inline void destroy(Memory* mem) {
		delete(mem->data);
		delete(mem);
	}
}