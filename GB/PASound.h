#pragma once

#include "portaudio.h"
#include "ISoundDriver.h"
#include "GBAudioStream.h"

namespace gb {

  class PASound : public ISoundDriver {
  private:
    unsigned int m_numChannels;
    GBAudioStream *m_channels;

  public:
    void cleanup() {
      for (unsigned int i = 0; i < m_numChannels; i++) {
        m_channels[i].cleanup();
      }
      PaError err = Pa_Terminate();
      if (err != paNoError) {
        std::cout << Pa_GetErrorText(err) << std::endl;
      }
    }

    void init(unsigned int channels) {
      PaError err = Pa_Initialize();
      if (err != paNoError) {
        std::cout << Pa_GetErrorText(err) << std::endl;
      }
      m_numChannels = channels;
      m_channels = new GBAudioStream[channels];
      for (unsigned int i = 0; i < m_numChannels; i++) {
        m_channels[i].initialize(SAMPLE_RATE);
      }
    }

    void setChannel(int channel, int frequency, int volume, float duty, WAVEFORMS waveform) {
      if (channel < m_numChannels) {
        m_channels[channel].setWaveform(frequency, volume, duty, waveform);
      }
      else {
        std::cout << "channel index out of range" << std::endl;
      }
    }

    void play(unsigned int channel) {
      if (channel < m_numChannels) {
        m_channels[channel].play();
      }
      else {
        std::cout << "channel index out of range" << std::endl;
      }
    }

    void stop(unsigned int channel) {
      if (channel < m_numChannels) {
        m_channels[channel].stop();
      }
      else {
        std::cout << "channel index out of range" << std::endl;
      }
    }
  };
};