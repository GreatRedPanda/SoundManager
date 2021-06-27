#pragma once

#include <string>
#include "SelectedFilesPool.h"

#include "soloud.h"
#include "soloud_speech.h"
#include "soloud_openmpt.h"
#include "soloud_wav.h"
//#include "soloud_thread.h"

//#include <irrKlang.h>
#include <windows.h>
#include <iostream>
#include "Utils.h"
//#include "RtAudio.h"
//typedef signed short  MY_TYPE;
//#define FORMAT RTAUDIO_SINT16
//#define SCALE  32767.0
class RtAudioPlayer
{
	SoLoud::Soloud* soloud; // Engine core
	//SoLoud::Wav* wav;       // One sample source
	SoLoud::Wav* wav;
	int handle;
	std::wstring currentPath;
	//irrklang::ISoundEngine* engine;
	/*	struct OutputData {
		FILE* fd;
		unsigned int channels;
		};
		OutputData data;
		RtAudio *dac;
		RtAudio::StreamParameters oParams;
		RtAudio::StreamParameters iParams;
		unsigned int channels, fs, bufferFrames, device = 0, offset = 0;
		std::wstring currentFilePath;*/
public:
	RtAudioPlayer()
	{
		soloud = new SoLoud::Soloud();
		soloud->init();
		wav = new SoLoud::Wav();
		//bufferFrames = 512;
		////
		//try {
		//	dac = new RtAudio(RtAudio::WINDOWS_WASAPI);
		//}
		//catch (RtAudioError& error) {
		//	error.printMessage();
		//	exit(EXIT_FAILURE);
		//}
		//if (dac->getDeviceCount() < 1) {
		//	std::cout << "\nNo audio devices found!\n";
		//	//exit(0);
		//}
		//iParams.deviceId = dac->getDefaultInputDevice();
		//iParams.nChannels = 1;

		//oParams.deviceId = dac->getDefaultOutputDevice();
		//oParams.firstChannel = 0;
		//oParams.nChannels = 2;



	//engine= irrklang::createIrrKlangDevice();

	}
	void SetFilePath(std::wstring path);
	void Play();
	void Stop();
	float* GetSamples()
	{
		if (wav->mData == nullptr || SelectedFilesPool::Pool->GetSelectedFile() != currentPath)
		{
			//if (SelectedFilesPool::Pool->GetSelectedFile() != currentPath)
			{
				if (SelectedFilesPool::Pool->GetSelectedFile() != L"")
				{

					std::string path = StringConvert::WStringToString(SelectedFilesPool::Pool->GetSelectedFile());
					//path = "C:/Users/Office_1/Desktop/курсы юнити/Последнее по Unity/Shooter3D/Звуки/Sounds/playerSound/die_02.wav";
					wav->load(path.c_str());       // Load a wave file
					currentPath = SelectedFilesPool::Pool->GetSelectedFile();
				}
			}
		}
		return wav->mData;
	};
	int GetSamplesSize()
	{

		return wav->mSampleCount;
	};
	/*static int output(void* outputBuffer, void* inputBuffer, unsigned int nBufferFrames,
		double streamTime, RtAudioStreamStatus status, void* userData)
	{


		OutputData* oData = (OutputData*)userData;
		unsigned int count = fread(outputBuffer, oData->channels * sizeof(short), nBufferFrames, oData->fd);
		if (count < nBufferFrames) {
			unsigned int bytes = (nBufferFrames - count) * oData->channels * sizeof(short);
			unsigned int startByte = count * oData->channels * sizeof(short);
			memset((char*)(outputBuffer)+startByte, 0, bytes);
			return 1;
		}

		return 0;
	};
	static void errorCallback(RtAudioError::Type type, const std::string& errorText)
	{

		std::cout << errorText << std::endl;

	};*/

	//irrklang::ISoundSource*  getSound()
	//{
	//	

	//	if (SelectedFilesPool::Pool->GetSelectedFile() != L"")
	//	{
	//		std::string path = StringConvert::WStringToUTF8(SelectedFilesPool::Pool->GetSelectedFile());
	//		
	//		
	//		//irrklang::ISoundSource* source	=engine->addSoundSourceFromFile(path.c_str(), irrklang::ESM_NO_STREAMING, true);
	//	//	source->setForcedStreamingThreshold(0);
	//		irrklang::ISoundSource* source = engine->getSoundSource(path.c_str());
	//		source->setStreamMode(irrklang::ESM_NO_STREAMING);
	//		source->setForcedStreamingThreshold(0);
	//	
	//		return  source;
	//	}
	//	return nullptr;
	//}
	/*float* getSoundSamples()
	{

		if (SelectedFilesPool::Pool->GetSelectedFile() != L"")
		{
			std::string path = StringConvert::WStringToUTF8(SelectedFilesPool::Pool->GetSelectedFile());
		
			irrklang::ISoundSource* source= engine->getSoundSource(path.c_str());
			void* pointer = source->getSampleData();
			std::vector<float> samples = std::vector<float>(0);
			std::vector<float*> myName = reinterpret_cast<std::vector<float*>>(pointer);

		}
	}*/
};

/*

	//struct OutputData {
	//	FILE* fd;
	//	unsigned int channels;
	//};
	//OutputData data;
	//RtAudio *dac;
	//RtAudio::StreamParameters oParams;
	//RtAudio::StreamParameters iParams;
	//unsigned int channels, fs, bufferFrames, device = 0, offset = 0;
	//std::wstring currentFilePath;

RtAudioPlayer()
{
	bufferFrames = 512;
	//
	try {
		dac = new RtAudio(RtAudio::WINDOWS_WASAPI);
	}
	catch (RtAudioError& error) {
		error.printMessage();
		exit(EXIT_FAILURE);
	}
	if (dac->getDeviceCount() < 1) {
		std::cout << "\nNo audio devices found!\n";
		//exit(0);
	}
	iParams.deviceId = dac->getDefaultInputDevice();
	iParams.nChannels = 1;

	oParams.deviceId = dac->getDefaultOutputDevice();
	oParams.firstChannel = 0;
	oParams.nChannels = 2;
}
void SetFilePath(std::wstring path);
void Play();
void Stop();

static int output(void* outputBuffer, void* inputBuffer, unsigned int nBufferFrames,
	double streamTime, RtAudioStreamStatus status, void* userData)
{


	OutputData* oData = (OutputData*)userData;
	unsigned int count = fread(outputBuffer, oData->channels * sizeof(MY_TYPE), nBufferFrames, oData->fd);
	if (count < nBufferFrames) {
		unsigned int bytes = (nBufferFrames - count) * oData->channels * sizeof(MY_TYPE);
		unsigned int startByte = count * oData->channels * sizeof(MY_TYPE);
		memset((char*)(outputBuffer)+startByte, 0, bytes);
		return 1;
	}

	return 0;
}
static void errorCallback(RtAudioError::Type type, const std::string& errorText)
{

	std::cout << errorText << std::endl;

}


static int saw(void* outputBuffer, void* inputBuffer, unsigned int nBufferFrames,
	double streamTime, RtAudioStreamStatus status, void* userData)
{
	unsigned int i, j;
	double* buffer = (double*)outputBuffer;
	double* lastValues = (double*)userData;
	if (status)
		std::cout << "Stream underflow detected!" << std::endl;
	// Write interleaved audio data.
	for (i = 0; i < nBufferFrames; i++) {
		for (j = 0; j < 2; j++) {
			*buffer++ = lastValues[j];
			lastValues[j] += 0.005 * (j + 1 + (j * 0.1));
			if (lastValues[j] >= 1.0) lastValues[j] -= 2.0;
		}
	}
	return 0;
};
*/