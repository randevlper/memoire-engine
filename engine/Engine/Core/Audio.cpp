#include "Audio.h"

#define DR_MP3_IMPLEMENTATION
#include <extras/dr_mp3.h>   /* Enables MP3 decoding. */
#define MINIAUDIO_IMPLEMENTATION
#include <miniaudio.h>

#include "Engine/Utilities/Debug.h"
#include "Engine/Utilities/DebugMemory.h"

bool Audio::_isInit = false;
unsigned int Audio::_frame = 0;
ma_decoder* Audio::_decoder = DBG_NEW ma_decoder();
ma_device* Audio::_device = DBG_NEW ma_device();

//This is called on its own thread?
void data_callback(ma_device* pDevice, void* pOutput, const void* pInput, ma_uint32 frameCount)
{
	Audio::_frame++;
	ma_decoder* pDecoder = (ma_decoder*)pDevice->pUserData;
	if (pDecoder == NULL) {
		return;
	}

	//Debug::Log("Data Callback");

	ma_decoder_read_pcm_frames(pDecoder, pOutput, frameCount);

	(void)pInput;

	if (Audio::_frame > frameCount) {
		//Debug::Log("Stopping!");
		//Cannot call stop from in here
		//Need to use the events
		//ma_device_stop(pDevice);
		ma_decoder_seek_to_pcm_frame(pDecoder, 0);
		Audio::_frame = 0;
	}
}


int Audio::init()
{
	ma_result result;
	ma_device_config deviceConfig;

	result = ma_decoder_init_file("assets/audio/ohno.mp3", NULL, _decoder);
	if (result != MA_SUCCESS) {
		return -2;
	}

	deviceConfig = ma_device_config_init(ma_device_type_playback);
	deviceConfig.playback.format = _decoder->outputFormat;
	deviceConfig.playback.channels = _decoder->outputChannels;
	deviceConfig.sampleRate = _decoder->outputSampleRate;
	deviceConfig.dataCallback = data_callback;
	deviceConfig.pUserData = _decoder;

	if (ma_device_init(NULL, &deviceConfig, _device) != MA_SUCCESS) {
		Debug::Log("Failed to open playback device.\n");
		ma_decoder_uninit(_decoder);
		return -3;
	}

	return 0;
}

void Audio::playTest()
{
	if (ma_device_start(_device) != MA_SUCCESS) {
		Debug::Log("Failed to start playback device.");
		//ma_device_uninit(_device);
		//ma_decoder_uninit(_decoder);
		//return -4;
		Debug::Log("Stopping!");
		ma_device_stop(_device);
		ma_decoder_seek_to_pcm_frame(_decoder, 0);

	}
	Debug::Log("Tryplay");
}

void Audio::destroy()
{
	ma_device_uninit(_device);
	ma_decoder_uninit(_decoder);
	delete(_device);
	delete(_decoder);
}
