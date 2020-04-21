#pragma once
struct ma_device;
struct ma_decoder;

//Get this out of here when done testing

class Audio
{
public:
	static int init();
	static void playTest();
	static void destroy();

	static unsigned int _frame;

private:
	static bool _isInit;
	static ma_device* _device;
	static ma_decoder* _decoder;

};