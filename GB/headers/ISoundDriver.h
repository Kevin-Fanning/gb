#pragma once

namespace gb {
  const enum WAVEFORMS {
    SQUARE,
    WHITE_NOISE,
  };

  class ISoundDriver {
  public:
    virtual void init(unsigned int channels) = 0;
    virtual void cleanup() = 0;
    virtual void setChannel(int channel, int frequency, int volume, float duty, WAVEFORMS waveform) = 0;
    virtual void play(unsigned int channel) = 0;
    virtual void stop(unsigned int channel) = 0;
  };
};