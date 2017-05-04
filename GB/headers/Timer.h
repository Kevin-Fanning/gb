#pragma once

namespace gb {
  class Timer {
  private:
    int m_div;
    int m_counter;
    int m_modulo;
    int m_speed;
    int m_remainder;

    bool m_running;
    bool m_interrupt;

  public:
    Timer() {
      m_div = 0;
      m_remainder = 0;
      m_counter = 0;
      m_modulo = 0;
      m_speed = 0;
      m_running = false;
      m_interrupt = false;
    }

    void tick(const int mclocks) {
      const int add = (mclocks + m_remainder) / 4;
      m_remainder = (mclocks + m_remainder) % 4;
      m_div += add;
      m_div &= 0xFF;
    }

    int getDiv() {
      return m_div;
    }
    void setDiv() {
      m_div = 0;
    }
    int getCounter() {
      return m_counter;
    }
    int getModulo() {
      return m_modulo;
    }
    void setModulo(int modulo) {
      m_modulo = modulo;
    }

    void configure(int byte) {
      const int speed = byte & 0b11;
      switch (speed) {
        case 0:
          m_speed = 1;
          break;
        case 1:
          m_speed = 64;
          break;
        case 2:
          m_speed = 16;
          break;
        case 3:
          m_speed = 4;
          break;
      }
      m_running = (byte & 0b100) != 0;
    }

    bool getInterrupt() {
      return m_interrupt;
    }

    void resetInterrupt() {
      m_interrupt = false;
    }
  };
};