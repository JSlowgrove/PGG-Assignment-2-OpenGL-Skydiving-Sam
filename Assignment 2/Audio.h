#pragma once

#include <SDL_mixer.h>
#include <iostream>
#include <string>

/**
@brief Creates a Audio object to handle the SDL_Mixer.
DISCLAMER - This is my PGG Assignment 1 audio class.
*/
class Audio
{
private:
	/**Variable for if it's a Music audio type*/
	Mix_Music* audio;
	/**Variable for if it's a Sound effect type*/
	Mix_Chunk* sound;

public:
	/**
	Constructs an Audio object.
	@param std::string The file to be loaded.
	@param bool True for music file. False for sound file.
	*/
	Audio(std::string file, bool music);

	/**
	Destructs a Audio object.
	*/
	~Audio();

	/**
	Starts the Audio playing.
	Starts the Audio playing, also checks if not playing and starts again.
	*/
	void startAudio();

	/**
	Plays the sound effect.
	*/
	void playEffect();

	/**
	Stops the Audio playing.
	*/
	void stopAudio();
};