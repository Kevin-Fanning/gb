#pragma once;

#include "JOYP.h"
#include "SOUND.h"
#include "Timer.h"

namespace gb {
  class MMU {
  public:
    MMU(JOYP *joyp, Timer *timer, SOUND *sound);

    void reset();
    void cleanup();

    unsigned char readByte(unsigned int addr);
    unsigned int  readWord(unsigned int addr);

    void writeByte(unsigned int addr, unsigned char byte);
    void writeWord(unsigned int addr, unsigned int word);

    bool inBios();
    void setInBios(bool inBios);

    void setRom(unsigned char* bytes, unsigned int length);
  private:
    JOYP *m_JOYP;
    SOUND *m_SOUND;
    Timer *m_timer;

    bool m_inBios;

    unsigned int* m_bios;
    unsigned char* m_ram;
  };
}