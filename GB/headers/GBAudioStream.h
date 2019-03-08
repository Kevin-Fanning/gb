#pragma once
#include <vector>
#include <iostream>
#include <random>

#define SAMPLE_RATE (44100)

namespace gb {

  int gbAudioCallback(const void *input, void *output, unsigned long frameCount, const PaStreamCallbackTimeInfo *timeInfo, PaStreamCallbackFlags statusFlags, void *userData);

  class GBAudioStream {
  public:
    friend int gbAudioCallback(const void *input, void *output, unsigned long frameCount, const PaStreamCallbackTimeInfo *timeInfo, PaStreamCallbackFlags statusFlags, void *userData);
    void initialize(const unsigned int sampleRate) {
      if (m_buffer != nullptr) {
        delete[] m_buffer;
      }
      m_buffer = new float[sampleRate];
      m_buffer[0] = 0;
      m_size = 1;

      /* Open an audio I/O stream. */
      PaError err = Pa_OpenDefaultStream(&m_stream, 0, 1,
        paFloat32,
        SAMPLE_RATE,
        256,
        gbAudioCallback,
        this);
      if (err != paNoError) {
        std::cout << Pa_GetErrorText(err) << std::endl;
      }
    }

    void setWaveform(int frequency, int volume, float duty, WAVEFORMS waveform) {
      float amplitude = volume / 100.0f;
      if (waveform == WAVEFORMS::SQUARE) {
        int samplesPerCycle = (SAMPLE_RATE) / frequency;
        for (int i = 0; i < samplesPerCycle; i++) {
          m_buffer[i] = i < samplesPerCycle * duty ? -amplitude : amplitude;
        }
        m_size = samplesPerCycle;
      }
      else if (waveform == WAVEFORMS::WHITE_NOISE) {
        float amplitude = volume / 100.0f;
        int seed = m_random_distribution(m_random_generator);
        int last = seed & 0x1;
        int samplesPerFlip = SAMPLE_RATE / (frequency);
        for (int i = 0; i < 1000; i++) {
          if (false && (samplesPerFlip == 0 || i % samplesPerFlip == 0)) {
            int x = seed & 0x1;
            int y = seed & 0x2;
            int next = x ^ y;
            seed = seed >> 1;
            if (next) {
              seed |= 1 << 15;
            }
            else {
              seed &= 0 << 15;
            }
            int last = seed & 0x1;
            last = rand() % 1;
            m_buffer[i] = last * amplitude;
          }
          else {
            m_buffer[i] = (rand()%2) * amplitude;
          }
        }
        m_size = 1000;
      }
    }

    void play() {
      // enable output
      m_enabled = true;
      // start stream if stopped
      PaError err = Pa_IsStreamStopped(m_stream);
      if (err == 1) {
        err = Pa_StartStream(m_stream);
        if (err != paNoError) {
          std::cout << Pa_GetErrorText(err) << std::endl;
        }
      }
      else if (err != paNoError) {
        std::cout << Pa_GetErrorText(err) << std::endl;
      }
    }

    void stop() {
      m_enabled = false;
    }

    void cleanup() {
      PaError err = Pa_IsStreamActive(m_stream);
      if (err == 1) {
        err = Pa_StopStream(m_stream);
        if (err != paNoError) {
          std::cout << Pa_GetErrorText(err) << std::endl;
        }
        PaError err = Pa_CloseStream(m_stream);
        if (err != paNoError) {
          std::cout << Pa_GetErrorText(err) << std::endl;
        }
      }
      else if (err != paNoError) {
        std::cout << Pa_GetErrorText(err) << std::endl;
      }
    }

  private:
    float *m_buffer = nullptr;
    int m_size = 0;
    float m_cycleOffset = 0;
    bool m_enabled = false;
    PaStream *m_stream;
    std::default_random_engine m_random_generator;
    std::uniform_int_distribution<int> m_random_distribution = std::uniform_int_distribution<int>(0, 0xFFFF);
  };

  int gbAudioCallback(const void *inputBuffer, void *outputBuffer,
    unsigned long framesPerBuffer,
    const PaStreamCallbackTimeInfo* timeInfo,
    PaStreamCallbackFlags statusFlags,
    void *userData)
  {
    GBAudioStream *data = (GBAudioStream*)userData;
    float *out = (float*)outputBuffer;
    unsigned int i;
    (void)inputBuffer; /* Prevent unused variable warning. */

    float offset = data->m_cycleOffset;
    int j = (int)(offset * data->m_size);
    for (i = 0; i < framesPerBuffer; i++)
    {
      if (data->m_enabled && data->m_size > 0) {
        out[i] = data->m_buffer[j % data->m_size];
        j++;
      }
      else {
        out[i] = 0;
      }
    }
    data->m_cycleOffset = (float)j / data->m_size;
    return 0;
  }

};