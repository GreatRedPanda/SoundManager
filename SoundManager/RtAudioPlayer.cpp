#include "RtAudioPlayer.h"

void RtAudioPlayer::Play()
{
	if (SelectedFilesPool::Pool->GetSelectedFile() != L"")
	{
		if (SelectedFilesPool::Pool->GetSelectedFile() != currentPath)
		{
			std::string path = StringConvert::WStringToString(SelectedFilesPool::Pool->GetSelectedFile());
			//path = "C:/Users/Office_1/Desktop/курсы юнити/Последнее по Unity/Shooter3D/Звуки/Sounds/playerSound/die_02.wav";
			wav->load(path.c_str());       // Load a wave file
			wav->setVolume(1);
			wav->setLooping(1);                          // Tell SoLoud to loop the sound

			handle = soloud->playBackground(*wav);             // Play it
			std::wstring currentPath = SelectedFilesPool::Pool->GetSelectedFile();
		}
		//float* dataW = wav->mData;
	}
	//SoLoud::Soloud soloud; // Engine core
	//SoLoud::Speech speech; // A sound source (speech, in this case)
	//SoLoud::Wav wav;       // One sample source
	//SoLoud::Openmpt mod;   // One song source
	//soloud.init();
	////soloud.setVisualizationEnable(1);
	////if (SelectedFilesPool::Pool->GetSelectedFile() != L"")
	//{
	//	std::string path = StringConvert::WStringToUTF8(SelectedFilesPool::Pool->GetSelectedFile());
	//	path = "C:/Users/Office_1/Desktop/курсы юнити/Последнее по Unity/Shooter3D/Звуки/Concrete_Boots_Running.wav";
	//	wav.load(path.c_str());       // Load a wave file
	//	wav.setVolume(1);
	//	wav.setLooping(1);                          // Tell SoLoud to loop the sound
	//	int handle1 = soloud.playBackground(wav);             // Play it


	
		//soloud.setVolume(handle1, 0.5f);            // Set volume; 1.0f is "normal"
		//soloud.setPan(handle1, -0.2f);              // Set pan; -1 is left, 1 is right
		//soloud.setRelativePlaySpeed(handle1, 0.9f); // Play a bit slower; 1.0f is normal
		//FILE* f;
		//	fopen_s(&f, path.c_str(), "rb");
		//fopen_s(&data.fd,path.c_str(), "rb");
		//try {
  //     
		//	dac->openStream(&oParams, &iParams, RTAUDIO_SINT16, fs, &bufferFrames, &output, (void*)&data,0, &errorCallback);
		//	//dac->startStream();


		//   // dac->openStream(&parameters, &iParams, RTAUDIO_SINT16,
		//	  //  sampleRate, &bufferFrames, &output, (void*)&data,0, &errorCallback);
		//   // dac->startStream();
		//}
		//catch (RtAudioError& e) {
		//	std::cout << '\n' << e.getMessage() << '\n' << std::endl;
       
		//}
		//sf::SoundBuffer buffer;
		//sf::Sound sound;
		//buffer.loadFromFile("C:/Users/Office_1/Desktop/курсы юнити/Последнее по Unity/Shooter#D UPD2/Звуки/leaves01.ogg");
		//sound.setLoop(true);
		//sound.setVolume(1);
		//sound.setBuffer(buffer);

		//// sound.setPitch(0.01f);
		//sound.play();
		//irrklang::ISound* music = engine->play2D(path.c_str(), false, false, true, irrklang::ESM_AUTO_DETECT, false);
		//engine->getSoundSource(path.c_str()).
		//music->getSoundSource()->setStreamMode(irrklang::ESM_NO_STREAMING);
		//int len = music->getSoundSource()->getAudioFormat().getSampleDataSize();
		//irrklang::ESampleFormat f = music->getSoundSource()->getAudioFormat().SampleFormat;

		////int length= player.getSound().get
		//void* pointer = music->getSoundSource()->getSampleData();
	//}

	//music.
}
void RtAudioPlayer::Stop()
{

	soloud->stop(handle);
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
