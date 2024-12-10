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

    void setup();
    void pause();
    void play();
    void stop();
    void setPlaybackPosition(size_t frame);

private:
    AudioData data;
    int channels;
};

// I have greater plans for this class, leave it be, for now.
class AudioManager {
public:
    AudioManager();
    ~AudioManager();
    Sound load(const char* filePath, AudioChannel channel);
};
