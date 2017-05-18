#include "SOUND.h"
#include "ISoundDriver.h"

using namespace gb;

SOUND::SOUND(ISoundDriver *soundDriver) : m_soundDriver(soundDriver) {
  for (int i = 0; i < 16; i++) {
    m_waveRam[i] = 0;
  }
}

void SOUND::tick(int mClocks) {
  m_length_clocks += mClocks;
  m_sweep_clocks += mClocks;
  m_envelope_clocks += mClocks;

  if (!m_channel_1_enabled && m_ch1_initialFlag) {
    m_channel_1_enabled = true;
    m_ch1_initialFlag = false;
    recalculate(1);
  }
  if (!m_channel_2_enabled && m_ch2_initialFlag) {
    m_channel_2_enabled = true;
    recalculate(2);
  }

  if (m_sweep_clocks >= 8192) {
    m_sweep_clocks -= 8192;
    m_ch1_sweep_counter++;
    if (m_channel_1_enabled && m_ch1_sweepAmount && m_ch1_sweep_counter == m_ch1_sweepTime) {
      int amount = m_ch1_frequency >> m_ch1_sweepAmount;
      if (m_ch1_sweepSubtraction) {
        amount = -amount;
      }
      m_ch1_frequency += amount;
      if (m_ch1_frequency > 2047) {
        m_ch1_frequency &= 2047;
        m_channel_1_enabled = false;
        m_ch1_initialFlag = false;
      }
      recalculate(1);
      m_ch1_sweep_counter = 0;
    }
  }

  if (m_envelope_clocks > 16384) {
    m_envelope_clocks -= 16384;
    m_ch1_envelope_counter++;
    m_ch2_envelope_counter++;
    m_ch4_envelope_counter++;
    if (m_ch1_envelopeAmount != 0 && m_ch1_envelopeAmount == m_ch1_envelope_counter) {
      if (m_ch1_envelopeDown && m_ch1_volume < 15) {
        m_ch1_volume++;
        recalculate(1);
      }
      else if (!m_ch1_envelopeDown && m_ch1_volume > 0) {
        m_ch1_volume--;
        recalculate(1);
      }
      m_ch1_envelope_counter = 0;
    }
    if (m_ch2_envelopeAmount != 0 && m_ch2_envelopeAmount == m_ch2_envelope_counter) {
      if (m_ch2_envelopeDown && m_ch2_volume < 15) {
        m_ch2_volume++;
        recalculate(2);
      }
      else if (!m_ch2_envelopeDown && m_ch2_volume > 0) {
        m_ch2_volume--;
        recalculate(2);
      }
      m_ch2_envelope_counter = 0;
    }
  }

  if (m_length_clocks >= 4096) {
    m_length_clocks -= 4096;

    if (m_ch1_counter) {
      if (m_ch1_length > 0) {
        m_ch1_length--;
        if (m_ch1_length == 0) {
          m_channel_1_enabled = false;
        }
        recalculate(1);
      }
    }
    if (m_ch2_counter) {
      if (m_ch2_length > 0) {
        m_ch2_length--;
        if (m_ch2_length == 0) {
          m_channel_2_enabled = false;
        }
        recalculate(2);
      }
    }
  }
}

void SOUND::recalculate(int channel) {
  if (channel == 1) {
    
    if (m_master_sound_enabled && m_channel_1_enabled && m_ch1_frequency != 0) {
      int frequency = 131072 / (2048 - m_ch1_frequency);
      float duty = 0;
      switch (m_ch1_duty) {
      case 0:
        duty = 0.125;
        break;
      case 1:
        duty = 0.25;
        break;
      case 2:
        duty = 0.5;
        break;
      case 3:
        duty = 0.75;
        break;
      }
      int volume = (m_ch1_volume / 15.0) * 100;
      m_soundDriver->setChannel(0, frequency, volume, duty, WAVEFORMS::SQUARE);
      m_soundDriver->play(0);
    }
    else {
     m_soundDriver->stop(0);
    }
  }
  else if (channel == 2) {
    if (m_master_sound_enabled && m_channel_2_enabled && m_ch2_frequency != 0) {
      int frequency = 131072 / (2048 - m_ch2_frequency);
      float duty = 0;
      switch (m_ch2_duty) {
      case 0:
        duty = 0.125;
        break;
      case 1:
        duty = 0.25;
        break;
      case 2:
        duty = 0.5;
        break;
      case 3:
        duty = 0.75;
        break;
      }
      int volume = (m_ch2_volume / 15.0) * 100;
      m_soundDriver->setChannel(1, frequency, volume, duty, WAVEFORMS::SQUARE);
      m_soundDriver->play(1);
    }
    else {
      m_soundDriver->stop(1);
    }
  }
}

void SOUND::writeByte(int addr, char byte) {
  switch (addr) {
  // Channel 1 registers
  case 0xFF10:
    m_ch1_sweepAmount = byte & 0b11;
    m_ch1_sweepSubtraction = (byte & 0b100) >> 2;
    m_ch1_sweepTime = (byte & 0b1110000) >> 4;
    m_ch1_sweep_counter = 0;
    break;
  case 0xFF11:
    m_ch1_length = byte & 0b00111111;
    m_ch1_duty = (byte & 0b11000000) >> 6;
    recalculate(1);
    break;
  case 0xFF12:
    m_ch1_envelopeAmount = byte & 0b00000111;
    m_ch1_envelopeDown = (byte & 0b00001000) >> 3;
    m_ch1_initialVolume = (byte &  0b11110000) >> 4;
    m_ch1_envelope_counter = 0;
    break;
  case 0xFF13:
    // just the low 8 bits, remove low 8 bits and add new byte
    m_ch1_frequency = m_ch1_frequency & 0b11100000000;
    m_ch1_frequency += byte;
    recalculate(1);
    break;
  case 0xFF14:
    m_ch1_frequency = m_ch1_frequency & 0b11111111;
    m_ch1_frequency += (byte & 0b111) << 8;
    m_ch1_counter = (byte & 0b1000000) >> 6;
    m_ch1_initialFlag = (byte & 0b10000000) >> 7;
    if (m_ch1_initialFlag) {
      m_channel_1_enabled = true;
      if (m_ch1_length == 0) m_ch1_length = 64;
      m_ch1_volume = m_ch1_initialVolume;
      m_ch1_envelope_counter = 0;
    }
    recalculate(1);
    break;

  // Channel 2
  case 0xFF16:
    m_ch2_length = (byte & 0x3F);
    m_ch2_duty = (byte & 0xC0) >> 6;
    recalculate(2);
    break;
  case 0xFF17:
    m_ch2_envelopeAmount = (byte & 0x07);
    m_ch2_envelopeDown = (byte >> 3) & 0x1;
    m_ch2_initialEnvelope = (byte >> 4) & 0xF;
    m_ch2_envelope_counter = 0;
    break;
  case 0xFF18:
    m_ch2_frequency &= 0xF00;
    m_ch2_frequency += byte;
    recalculate(2);
    break;
  case 0xFF19:
    m_ch2_frequency &= 0xFF;
    m_ch2_frequency += (byte & 0x7) << 8;
    m_ch2_counter = (byte >> 6) & 0x1;
    m_ch2_initialFlag = (byte >> 7) & 0x1;
    if (m_ch2_initialFlag) {
      m_channel_2_enabled = true;
      if (m_ch2_length == 0) m_ch2_length = 64;
      m_ch2_volume = m_ch2_initialEnvelope;
      m_ch2_envelope_counter = 0;
    }
    recalculate(2);
    break;

  // Channel 3
  case 0xFF1A:
    m_ch3_enable = (byte >> 7) & 0x1;
    recalculate(3);
    break;
  case 0xFF1B:
    m_ch3_length = byte;
  case 0xFF1C:
    m_ch3_outputLevel = (byte >> 5) & 0x3;
    recalculate(3);
    break;
  case 0xFF1D:
    m_ch3_frequency &= 0xF00;
    m_ch3_frequency += byte;
    recalculate(3);
    break;
  case 0xFF1E:
    m_ch3_frequency &= 0xFF;
    m_ch3_frequency += (byte & 0x7) << 8;
    m_ch3_counter = (byte >> 6) & 0x1;
    m_ch3_initialFlag = (byte >> 7) & 0x1;
    recalculate(3);
    break;
  
  // Channel 4
  case 0xFF20:
    m_ch4_length = byte & 0x3F;
    break;
  case 0xFF21:
    m_ch4_envelopeAmount = byte & 0x7;
    m_ch4_envelopeDown = (byte >> 3) & 0x1;
    m_ch4_initialEnvelope = (byte >> 4) & 0xF;
    m_ch4_envelope_counter = 0;
    break;
  case 0xFF22:
    m_ch4_frequencyDividingRatio = byte & 0x7;
    m_ch4_polynomialStep = (byte >> 3) & 0x1;
    m_ch4_polynomialShiftClockFrequency = (byte >> 4) & 0xF;
    recalculate(4);
    break;
  case 0xFF23:
    m_ch4_counter = (byte >> 6) & 0x1;
    m_ch4_initialFlag = (byte >> 7) & 0x1;
    recalculate(4);
    break;

  // Channel control
  case 0xFF24:
    m_speaker_1_volume = (byte & 0x7);
    m_speaker_1_on = (byte >> 3) & 0x1;
    m_speaker_2_volume = (byte >> 4) & 0x7;
    m_speaker_2_on = (byte >> 7) & 0x1;
    break;

  // Output selection
  case 0xFF25:
    m_channel_1_to_speaker_1 = (byte >> 0) & 0x1;
    m_channel_2_to_speaker_1 = (byte >> 1) & 0x1;
    m_channel_3_to_speaker_1 = (byte >> 2) & 0x1;
    m_channel_4_to_speaker_1 = (byte >> 3) & 0x1;
    m_channel_1_to_speaker_2 = (byte >> 4) & 0x1;
    m_channel_2_to_speaker_2 = (byte >> 5) & 0x1;
    m_channel_3_to_speaker_2 = (byte >> 6) & 0x1;
    m_channel_4_to_speaker_2 = (byte >> 7) & 0x1;
    break;

  // Sound on/off
  case 0xFF26:
    m_master_sound_enabled = (byte >> 7) & 0x1;
    recalculate(1);
    recalculate(2);
    break;
  }

  if (addr >= 0xFF30 && addr <= 0xFF3F) {
    int offset = addr - 0xFF30;
    m_waveRam[offset] = byte;
  }
}

char SOUND::readByte(int addr) {
  switch (addr) {
  // Channel 1
  case 0xFF10:
    return (m_ch1_sweepTime << 4) + ((m_ch1_sweepSubtraction ? 1 : 0) << 3) + m_ch1_sweepAmount;
  case 0xFF11:
    return m_ch1_duty << 6;
  case 0xFF12:
    return (m_ch1_initialVolume << 4) + ((m_ch1_envelopeDown ? 1 : 0) << 3) + m_ch1_envelopeAmount;
  case 0xFF13:
    return m_ch1_frequency & 0xFF;
  case 0xFF14:
    return (m_ch1_counter ? 1 : 0) << 6;

  // Channel 2
  case 0xFF16:
    return m_ch2_duty << 6;
  case 0xFF17:
    return (m_ch2_initialEnvelope << 4) + ((m_ch2_envelopeDown ? 1 : 0) << 3) + m_ch2_envelopeAmount;
  case 0xFF18:
    return m_ch2_frequency & 0xFF;
  case 0xFF19:
    return (m_ch2_counter ? 1 : 0) << 6;

  // Channel 3
  case 0xFF1A:
    return (m_ch3_enable ? 1 : 0) << 7;
  case 0xFF1B:
    return m_ch3_length & 0xFF;
  case 0xFF1C:
    return m_ch3_outputLevel << 5;
  case 0xFF1D:
    return m_ch3_frequency & 0xFF;
  case 0xFF1E:
    return (m_ch3_counter ? 1 : 0) << 6;

  // Channel 4
  case 0xFF20:
    return m_ch4_length & 0x7F;
  case 0xFF21:
    return (m_ch4_initialEnvelope << 4) + ((m_ch4_envelopeDown ? 1 : 0) << 3) + m_ch4_envelopeAmount;
  case 0xFF22:
    return (m_ch4_polynomialShiftClockFrequency << 4) + ((m_ch4_polynomialStep ? 1 : 0) << 3) + m_ch4_frequencyDividingRatio;
  case 0xFF23:
    return ((m_ch4_counter ? 1 : 0) << 6);

  // Channel control
  case 0xFF24:
    return ((m_speaker_2_on ? 1 : 0) << 7) + (m_speaker_2_volume << 4) + ((m_speaker_1_on ? 1 : 0) << 3) + m_speaker_1_volume;
  case 0xFF25:
    return ((m_channel_4_to_speaker_2 ? 1 : 0) << 7) +
      ((m_channel_3_to_speaker_2 ? 1 : 0) << 6) +
      ((m_channel_2_to_speaker_2 ? 1 : 0) << 5) +
      ((m_channel_1_to_speaker_2 ? 1 : 0) << 4) +
      ((m_channel_4_to_speaker_1 ? 1 : 0) << 3) +
      ((m_channel_3_to_speaker_1 ? 1 : 0) << 2) +
      ((m_channel_2_to_speaker_1 ? 1 : 0) << 1) +
      (m_channel_1_to_speaker_1 ? 1 : 0);
  case 0xFF26:
    return ((m_master_sound_enabled ? 1 : 0) << 7) +
      ((m_channel_4_enabled ? 1 : 0) << 3) +
      ((m_channel_3_enabled ? 1 : 0) << 2) +
      ((m_channel_2_enabled ? 1 : 0) << 1) +
      (m_channel_1_enabled ? 1 : 0);
  }

  if (addr >= 0xFF30 && addr <= 0xFF3F) {
    return m_waveRam[addr - 0xFF30];
  }
  return 0;
}