#pragma once

#include <cstddef>

typedef struct {
    float* buffer;
    size_t length;
    size_t position;
    bool paused;
} AudioData;

enum class AudioChannel {
    Mono = 1,
    Stereo = 2
};

class Sound {
public:
    Sound(AudioData data, int channels);
    ~Sound();

    /* 
     * Change this to be "init" or something like that, ideally
     * this just does saudio_setup, then the pause and other
     * functions handle playback
     */
    void play();
    // TODO: The below.
    void pause();
    void resume();
    void stop();
    void setPlaybackPosition(size_t frame);

private:
    AudioData data;                 // Internal audio data
    int channels;                        // Mono or stereo
};

class AudioManager {
public:
    AudioManager();
    ~AudioManager();
    Sound load(const char* filePath, AudioChannel channel);
    // void startPlayback();
    
    // AudioData data;
    // int channels;
    // bool paused;
};
