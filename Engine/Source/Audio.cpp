//
// Created by Shreejit Murthy on 11/12/2024.
//

#include "Audio.hpp"
#include <log/log.h>
#include <SDL3/SDL_iostream.h>
#include <SDL3/SDL.h>

#define SOKOL_AUDIO_IMPL
#include "sokol_audio.h"

Sound::Sound(AudioData data, int channels)
    : data(data), channels(channels) {}

Sound::~Sound() {
    if (data.buffer) {
        free(data.buffer);
    }
}

void stream_callback(float* buffer, int num_frames, int num_channels, void* user_data) {
    AudioData* audio_data = (AudioData*)user_data;
    size_t samples_to_copy = num_frames;

    if (audio_data->paused) {
        memset(buffer, 0, num_frames * num_channels * sizeof(float));
        return;
    }

    for (size_t i = 0; i < samples_to_copy; ++i) {
        if (audio_data->position < audio_data->length) {
            buffer[i] = audio_data->buffer[audio_data->position++];
        } else {
            buffer[i] = 0.0f; // Silence if no more data
        }
    }
}

void Sound::play() {
    data.paused = false;
    saudio_setup((saudio_desc){
        .stream_userdata_cb = stream_callback,
        .user_data = &data,
        .num_channels = channels,
    });
}

float pcm16_to_float(int16_t sample) {
    return sample / 32768.0f;
}

AudioManager::AudioManager() {}

AudioManager::~AudioManager() {
    saudio_shutdown();
}

Sound AudioManager::load(const char* filePath, AudioChannel channel) {
    int channels = static_cast<int>(channel);
    float* buffer;
    if (filePath == nullptr) {
        log_error("AUDIO::Null file path");
    }
    SDL_IOStream* io = SDL_IOFromFile(filePath, "rb");
    if (io == nullptr) {
        log_error("AUDIO_FILE_IO::File unsuccessfully read: %s", filePath);
    }

    SDL_AudioSpec spec;
    uint8_t* raw_buffer;
    uint32_t raw_length;
    if (!SDL_LoadWAV_IO(io, false, &spec, &raw_buffer, &raw_length)) {
        log_error("AUDIO_FILE_IO::Failed to load audio: %s", SDL_GetError());
    }
    SDL_CloseIO(io);

    // Accept only S16 for now, further compatibility can be sorted later.
    if (spec.format != SDL_AUDIO_S16) {
        log_warn("AUDIO::Expected 16-bit PCM for now.");
    }

    size_t sample_count = raw_length / sizeof(int16_t);
    buffer = (float*)malloc(sample_count * sizeof(float));
    if (!buffer) {
        log_error("AUDIO::Failed to allocate audio buffer memory");
        free(raw_buffer);
    }

    int16_t* samples = (int16_t*)raw_buffer;
    for (size_t i = 0; i < sample_count; ++i) {
        buffer[i] = pcm16_to_float(samples[i]);
    }

    size_t length = sample_count / spec.channels * channels;
    size_t position = 0;

    free(raw_buffer);

    return Sound((AudioData){
        .buffer = buffer,
        .length = length,
        .position = position,
        .paused = true,
    }, channels);
}
