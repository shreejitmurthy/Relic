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

class Audio {
public:
    Audio();
    void load(const char* filePath, AudioChannel channel);
    ~Audio();

    void setup();
    void pause();
    void play();
    void stop();
    void setPlaybackPosition(size_t frame);

private:
    AudioData data;
    int channels;
};
