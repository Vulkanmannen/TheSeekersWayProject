#include "Sounds.h"
#include <string>
#include <fstream>
#include <sstream>
#include <SFML\Audio\SoundBuffer.hpp>
#include <windows.h>
Sounds* Sounds::sInstance = 0;

//ger v�rde till variable och laddar all musik som �r skrivna i en text fil
Sounds::Sounds()	
{
	for(std::ifstream fil("musik lista.txt");!fil.eof();)
	{
		std::string filnamn;
		std::getline(fil, filnamn, '\n');
		sf::SoundBuffer* buff = new sf::SoundBuffer();
		buff->loadFromFile(filnamn);
		bufferlista.insert(std::pair<std::string, sf::SoundBuffer*>(filnamn, buff));
		filnamn.clear();
	}

	sf::Listener::setGlobalVolume(100);
}

//tar bort pekare
Sounds::~Sounds()
{
	for(SoundVector::size_type i = 0; i < mSounds.size();i++)
	{
		delete mSounds[i];
	}
	
	for(BufferMap::iterator i = bufferlista.begin(); i != bufferlista.end(); i++)
	{
		delete i->second;
	}
}

// returnerar den enda instancen av Sound managern
Sounds* Sounds::getInstance()
{
	if(sInstance == 0)
	{
		sInstance = new Sounds;
	}
	return sInstance;
}

//spelar musik en g�ng
void Sounds::Play(std::string namn)
{
	Play(namn, 100);
}

//best�mmer volumen
void Sounds::Play(std::string namn, float volume)
{

	Playbase(namn, volume, false);
}

//ist�llet f�r att det spelas en g�ng s� upprepas det
void Sounds::Loop(std::string namn)
{
	Loop(namn, 100);
}

//best�mmer volumen
void Sounds::Loop(std::string namn, float volume)
{
	Playbase(namn, volume, true);
}

//funktion som lettar efter musik och l�gger den i en spelare och loopar eller spelar den.
void Sounds::Playbase(std::string namn, float volume, bool repeat)
{
	if(bufferlista[namn]!=NULL)
	{
		int x;

		//loop som lettar efter plats i spelaren f�r att spela musik
		for(int i=0;i<10;i++)
		{
			//skapa ny plats om det finns mindre �n 10 ljud spelare
			if(mSounds.size() < 10)
			{
				x=mSounds.size();
				mSounds.push_back(new sf::Sound(*bufferlista[namn]));
				mSounds[x]->setVolume(volume);
				mSounds[x]->setLoop(repeat);
				mSounds[x]->play();
				break;
			}

			//byter ut en som ljud som inte spelas mot en som ska spela
			else if(mSounds[i]->getStatus() == sf::Sound::Stopped)
			{
				x=i;
				mSounds[x]->setBuffer(*bufferlista[namn]);
				mSounds[x]->setVolume(volume);
				mSounds[x]->setLoop(repeat);
				mSounds[x]->play();
				break;
			}
	
		}
	}
	else
	{
		//felmedelandet
		namn = "Failed to load sound file: \n" + namn;

		//convert from string to wstring
		int len;
		int slength = (int)namn.length() + 1;
		len = MultiByteToWideChar(CP_ACP, 0, namn.c_str(), slength, 0, 0); 
		wchar_t* buf = new wchar_t[len];
		MultiByteToWideChar(CP_ACP, 0, namn.c_str(), slength, buf, len);
		std::wstring r(buf);
		delete[] buf;
		
		//convert from wstring to LPCWSTR
#ifdef UNICODE
		std::wstring stemp = r; // Temporary buffer is required
		LPCWSTR result = stemp.c_str();
#else
		LPCWSTR result = s.c_str();
#endif

		//"Failed to load sound file: "
		MessageBox(NULL, result, (LPCWSTR)L"CANNOT LOAD", MB_OK);
        std::exit(EXIT_FAILURE);
	}
}

//stoppa all ljud/musik fr�n att spelas, men ljud som skapas efter�t blir inte p�verkade.
void Sounds::StopAll()					
{
	for(SoundVector::size_type i = 0; i < mSounds.size();i++)
	{
		if(mSounds[i]->getStatus() == sf::Sound::Playing)
		{
			mSounds[i]->stop();
		}
	}
}

//pausa all ljud/musik som spelas f�r n�rvarande.
void Sounds::PauseAll()					
{
	for(SoundVector::size_type i = 0; i < mSounds.size();i++)
	{
		if(mSounds[i]->getStatus() == sf::Sound::Playing)
		{
			mSounds[i]->pause();
		}
	}
}

//avpausa alla pausade
void Sounds::UnPauseAll()				
{
	for(SoundVector::size_type i = 0; i < mSounds.size();i++)
	{
		if(mSounds[i]->getStatus() == sf::Sound::Paused)
		{
			mSounds[i]->play();
		}
	}
}

//st�ller in master ljudets v�rde
void Sounds::setMasterVolume(float volume)				
{
	sf::Listener::setGlobalVolume(volume);
}

//h�mta master ljudets v�rde
float Sounds::getMasterVolume()				
{
	return sf::Listener::getGlobalVolume();
}

//funktion som lettar efter musikbuffer och returnerar den
sf::SoundBuffer Sounds::getBuffer(std::string namn)
{
	if(bufferlista[namn]!=NULL)
	{
		return *bufferlista[namn];
	}
	else
	{
		//felmedelandet
		namn = "Failed to load sound file: \n" + namn;

		//convert from string to wstring
		int len;
		int slength = (int)namn.length() + 1;
		len = MultiByteToWideChar(CP_ACP, 0, namn.c_str(), slength, 0, 0); 
		wchar_t* buf = new wchar_t[len];
		MultiByteToWideChar(CP_ACP, 0, namn.c_str(), slength, buf, len);
		std::wstring r(buf);
		delete[] buf;
		
		//convert from wstring to LPCWSTR
#ifdef UNICODE
		std::wstring stemp = r; // Temporary buffer is required
		LPCWSTR result = stemp.c_str();
#else
		LPCWSTR result = s.c_str();
#endif

		//"Failed to load sound file: "
		MessageBox(NULL, result, (LPCWSTR)L"CANNOT LOAD", MB_OK);
        std::exit(EXIT_FAILURE);
	}
}