#include <iostream>

#include "CPU.h"
#include "MMU.h"
#include "SOUND.h"

using namespace gb;

CPU::CPU(MMU& mmu, PPU& ppu, Timer *timer, SOUND *sound) : m_PPU(ppu), m_MMU(mmu), m_timer(timer), m_SOUND(sound) {
}

void CPU::reset() {
	m_reg_a = 0;
	m_reg_b = 0;
	m_reg_c = 0;
	m_reg_d = 0;
	m_reg_e = 0;
	m_reg_f = 0;
	m_reg_h = 0;
	m_reg_l = 0;
	m_reg_m = 0;
	m_reg_t = 0;

  m_reg_i = 0;
  m_reg_r = 0;
  m_reg_ime = 1;

	m_reg_pc = 0;
	m_reg_sp = 0;

	m_clock_m = 0;
	m_clock_t = 0;
}

void CPU::execute() {
  m_reg_r = (m_reg_r + 1) & 127;
  unsigned int opcode = m_MMU.readByte(m_reg_pc);
  m_reg_pc++;
  (this->*m_opmap[opcode])();
  m_reg_pc &= 65535;
  m_clock_m += m_reg_m; m_clock_t += m_reg_t;
  if (m_MMU.inBios() && m_reg_pc == 0x0100) {
    m_MMU.setInBios(false);
  }

  //handle timer
  m_timer->tick(m_reg_m);
  //tick the sound system
  m_SOUND->tick(m_reg_m);

  //Handle interrupts
  int intEnable = m_MMU.readByte(0xFFFF);
  int intFlags = m_MMU.readByte(0xFF0F);
  if (!m_MMU.inBios() && m_reg_ime && intEnable && intFlags) {
    // an enabled interrupt was flagged
    int fired = intFlags & intEnable;

    //VBlank
    if (fired & 0x01)
    {
      m_MMU.writeByte(0xFF0F, intFlags & (255 - 0x01));
      RST40();
    }
    //LCD Stat
    else if (fired & 0x02) {
      m_MMU.writeByte(0xFF0F, intFlags & (255 - 0x02));
      RST48();
    }
    //Timer
    else if (fired & 0x03) {
      m_MMU.writeByte(0xFF0F, intFlags & (255 - 0x03));
      RST50();
    }
    //Serial Transfer end
    else if (fired & 0x04) {
      m_MMU.writeByte(0xFF0F, intFlags & (255 - 0x04));
      RST58();
    }
    //Joypad
    else if (fired & 0x05) {
      m_MMU.writeByte(0xFF0F, intFlags & (255 - 0x05));
      RST60();
    }
  }

  m_PPU.tick(m_reg_t);
}

void CPU::printRegisters() {
  std::cout << "Registers: " << m_reg_a << "," << m_reg_b << "," << m_reg_c << "," << m_reg_d << "," << m_reg_e << "," << m_reg_h << "," << m_reg_l << std::endl;
  std::cout << "SP: " << m_reg_sp << "  PC: " << m_reg_pc << std::endl;
  std::cout << "clock: " << m_clock_m << std::endl;
}