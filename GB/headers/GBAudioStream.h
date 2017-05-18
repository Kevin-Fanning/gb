#pragma once
#include <vector>
#include <iostream>
#include <SFML/Audio.hpp>

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
      else if (false && waveform == WAVEFORMS::WHITE_NOISE) {
        for (int i = 0; i < SAMPLE_RATE; i++) {
          m_buffer[i] = rand() * amplitude;
        }
        m_size = SAMPLE_RATE;
      }
      if (frequency != m_lastFrequency) {
        m_lastFrequency = frequency;
      }
    }

    void play() {
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
      PaError err = Pa_IsStreamActive(m_stream);
      if (err == 1) {
        err = Pa_StopStream(m_stream);
        if (err != paNoError) {
          std::cout << Pa_GetErrorText(err) << std::endl;
        }
      }
      else if (err != paNoError) {
        std::cout << Pa_GetErrorText(err) << std::endl;
      }
    }

    void cleanup() {
      PaError err = Pa_CloseStream(m_stream);
      if (err != paNoError) {
        std::cout << Pa_GetErrorText(err) << std::endl;
      }
    }

  private:
    float *m_buffer = nullptr;
    int m_size = 0;
    int m_lastFrequency = 0;
    float m_cycleOffset = 0;
    PaStream *m_stream;
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
      out[i] = data->m_buffer[j % data->m_size];
      j++;
    }
    data->m_cycleOffset = (float)j / data->m_size;
    return 0;
  }

};