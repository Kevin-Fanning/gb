#pragma once
#include "ISoundDriver.h"

namespace gb {

  /**
   * This class emulates the sound chip of the gameboy
   */
  class SOUND {
  public:
    SOUND(ISoundDriver *soundDriver);

    void tick(int mClocks);
    void writeByte(int addr, char byte);
    char readByte(int addr);

  private:
    void recalculate(int channel);

    ISoundDriver *m_soundDriver;

    int m_length_clocks = 0;
    int m_sweep_clocks = 0;
    int m_envelope_clocks = 0;

    // current volumes (not a register)
    int m_ch1_volume = 0;
    int m_ch2_volume = 0;
    int m_ch3_volume = 0;
    int m_ch4_volume = 0;
    // envelope counters
    int m_ch1_envelope_counter = 0;
    int m_ch2_envelope_counter = 0;
    int m_ch4_envelope_counter = 0;

    // Channel 1 - square with sweep and envelope
    int m_ch1_sweepAmount = 0;
    int m_ch1_sweepTime = 0;
    bool m_ch1_sweepSubtraction = false;
    int m_ch1_length = 0;
    int m_ch1_duty = 0;
    int m_ch1_envelopeAmount = 0;
    bool m_ch1_envelopeDown = false;
    int m_ch1_initialVolume = 0;
    int m_ch1_frequency = 0;
    bool m_ch1_counter = false;
    bool m_ch1_initialFlag = false;

    // Channel 2 - square with envelope
    int m_ch2_duty = 0;
    int m_ch2_length = 0;
    int m_ch2_envelopeAmount = 0;
    int m_ch2_initialEnvelope = 0;
    bool m_ch2_envelopeDown = false;
    int m_ch2_frequency = 0;
    bool m_ch2_counter = false;
    bool m_ch2_initialFlag = false;

    // Channel 3 - Wave from ram
    bool m_ch3_enable = false;
    bool m_ch3_length = false;
    int m_ch3_outputLevel = 0;
    int m_ch3_frequency = 0;
    bool m_ch3_counter = false;
    bool m_ch3_initialFlag = false;

    // Channel 4 - White noise
    int m_ch4_length = 0;
    int m_ch4_envelopeAmount = 0;
    bool m_ch4_envelopeDown = false;
    int m_ch4_initialEnvelope = 0;
    int m_ch4_frequencyDividingRatio = 0;
    bool m_ch4_polynomialStep = false;  //false: 15 true: 7
    int m_ch4_polynomialShiftClockFrequency = 0;
    bool m_ch4_counter = false;
    bool m_ch4_initialFlag = false;

    // Channel control    0xFF24
    int m_speaker_1_volume = 0;
    int m_speaker_2_volume = 0;  // 0-7
    bool m_speaker_1_on = false;
    bool m_speaker_2_on = false;

    // Channel to Speaker Control  0xFF25
    bool m_channel_1_to_speaker_1 = false;
    bool m_channel_2_to_speaker_1 = false;
    bool m_channel_3_to_speaker_1 = false;
    bool m_channel_4_to_speaker_1 = false;
    bool m_channel_1_to_speaker_2 = false;
    bool m_channel_2_to_speaker_2 = false;
    bool m_channel_3_to_speaker_2 = false;
    bool m_channel_4_to_speaker_2 = false;

    // Sound on/off   0xFF26
    bool m_channel_1_enabled = false;
    bool m_channel_2_enabled = false;
    bool m_channel_3_enabled = false;
    bool m_channel_4_enabled = false;
    bool m_master_sound_enabled = false;

    // Wave pattern RAM 0xFF30 - 0xFF3F
    unsigned char m_waveRam[16];
  };
}