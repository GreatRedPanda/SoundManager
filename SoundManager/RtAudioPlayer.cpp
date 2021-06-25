#include "RtAudioPlayer.h"
#include "Utils.h"
void RtAudioPlayer::Play()
{
	if (SelectedFilesPool::Pool->GetSelectedFile() != L"")
	{
		std::string path = StringConvert::WStringToUTF8(SelectedFilesPool::Pool->GetSelectedFile());

		irrklang::ISound* music = engine->play2D(path.c_str(), false, false, true, irrklang::ESM_AUTO_DETECT, false);
	}

	//music.
}
void RtAudioPlayer::Stop()
{


}
////#include "Utils.h"
//void RtAudioPlayer::Play()
//{
//    //RtAudio::StreamParameters parameters;
//    //parameters.deviceId = dac->getDefaultOutputDevice();
//    //parameters.nChannels = 2;
//    //parameters.firstChannel = 0;
//    //unsigned int sampleRate = 44100;
//    //unsigned int bufferFrames = 256; // 256 sample frames
//    //double data[10] = { 1,0,0,0,0,0,0,0,0,0 };
//    std::string path = "D:\\For Unity courses\\Звуки\\Sounds\\zapsplat_household_clock_ticking_001_18192.mp3";
//    
//    fopen_s(&data.fd,path.c_str(), "rb");
//    try {
//       
//        dac->openStream(&oParams, &iParams, FORMAT, fs, &bufferFrames, &output, (void*)&data,0, &errorCallback);
//        dac->startStream();
//
//
//       // dac->openStream(&parameters, &iParams, RTAUDIO_SINT16,
//          //  sampleRate, &bufferFrames, &output, (void*)&data,0, &errorCallback);
//       // dac->startStream();
//    }
//    catch (RtAudioError& e) {
//        std::cout << '\n' << e.getMessage() << '\n' << std::endl;
//       
//    }
//}
//
//void RtAudioPlayer::Stop()
//{
//    try {
//        // Stop the stream
//        dac->stopStream();
//    }
//    catch (RtAudioError& e) {
//        e.printMessage();
//    }
//    if (dac->isStreamOpen()) dac->closeStream();
//}
