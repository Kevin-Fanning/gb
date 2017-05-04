#pragma once

#include "MMU.h"
#include "PPU.h"
#include "SOUND.h"
#include "Timer.h"

namespace gb {

  class CPU {
  public:
    CPU(MMU &mmu, PPU &ppu, Timer *timer, SOUND *sound);

    void reset();
    void execute();

    //program counter
    int m_reg_pc;
    void printRegisters();

    //trigger interrupts
    void RST40() { m_reg_sp -= 2; m_MMU.writeWord(m_reg_sp, m_reg_pc); m_reg_pc = 0x40; m_reg_m = 3; m_reg_t = 12; }
    void RST48() { m_reg_sp -= 2; m_MMU.writeWord(m_reg_sp, m_reg_pc); m_reg_pc = 0x48; m_reg_m = 3; m_reg_t = 12; }
    void RST50() { m_reg_sp -= 2; m_MMU.writeWord(m_reg_sp, m_reg_pc); m_reg_pc = 0x50; m_reg_m = 3; m_reg_t = 12; }
    void RST58() { m_reg_sp -= 2; m_MMU.writeWord(m_reg_sp, m_reg_pc); m_reg_pc = 0x58; m_reg_m = 3; m_reg_t = 12; }
    void RST60() { m_reg_sp -= 2; m_MMU.writeWord(m_reg_sp, m_reg_pc); m_reg_pc = 0x60; m_reg_m = 3; m_reg_t = 12; }

  private:
    //Memory manager
    MMU m_MMU;

    //Sound subsystem
    SOUND *m_SOUND;

    //Timer
    Timer *m_timer;

    //Picture processor
    PPU m_PPU;

    //clock timer
    unsigned int m_clock_m;
    unsigned int m_clock_t;

    //registers
    unsigned int m_reg_a;
    unsigned int m_reg_b;
    unsigned int m_reg_c;
    unsigned int m_reg_d;
    unsigned int m_reg_e;
    unsigned int m_reg_h;
    unsigned int m_reg_l;

    unsigned int m_reg_i;
    unsigned int m_reg_r;
    unsigned int m_reg_ime;

    //flags
    int m_reg_f;

    int m_halt;
    int m_stop;

    //stack pointer
    int m_reg_sp;
    //last operation time
    int m_reg_m;
    int m_reg_t;

    //All CPU Operations

    //Load/store
    void LDrr_aa() { m_reg_a = m_reg_a; m_reg_m = 1; m_reg_t = 4; }
    void LDrr_ab() { m_reg_a = m_reg_b; m_reg_m = 1; m_reg_t = 4; }
    void LDrr_ac() { m_reg_a = m_reg_c; m_reg_m = 1; m_reg_t = 4; }
    void LDrr_ad() { m_reg_a = m_reg_d; m_reg_m = 1; m_reg_t = 4; }
    void LDrr_ae() { m_reg_a = m_reg_e; m_reg_m = 1; m_reg_t = 4; }
    void LDrr_ah() { m_reg_a = m_reg_h; m_reg_m = 1; m_reg_t = 4; }
    void LDrr_al() { m_reg_a = m_reg_l; m_reg_m = 1; m_reg_t = 4; }
    void LDrr_ba() { m_reg_b = m_reg_a; m_reg_m = 1; m_reg_t = 4; }
    void LDrr_bb() { m_reg_b = m_reg_b; m_reg_m = 1; m_reg_t = 4; }
    void LDrr_bc() { m_reg_b = m_reg_c; m_reg_m = 1; m_reg_t = 4; }
    void LDrr_bd() { m_reg_b = m_reg_d; m_reg_m = 1; m_reg_t = 4; }
    void LDrr_be() { m_reg_b = m_reg_e; m_reg_m = 1; m_reg_t = 4; }
    void LDrr_bh() { m_reg_b = m_reg_h; m_reg_m = 1; m_reg_t = 4; }
    void LDrr_bl() { m_reg_b = m_reg_l; m_reg_m = 1; m_reg_t = 4; }
    void LDrr_ca() { m_reg_c = m_reg_a; m_reg_m = 1; m_reg_t = 4; }
    void LDrr_cb() { m_reg_c = m_reg_b; m_reg_m = 1; m_reg_t = 4; }
    void LDrr_cc() { m_reg_c = m_reg_c; m_reg_m = 1; m_reg_t = 4; }
    void LDrr_cd() { m_reg_c = m_reg_d; m_reg_m = 1; m_reg_t = 4; }
    void LDrr_ce() { m_reg_c = m_reg_e; m_reg_m = 1; m_reg_t = 4; }
    void LDrr_ch() { m_reg_c = m_reg_h; m_reg_m = 1; m_reg_t = 4; }
    void LDrr_cl() { m_reg_c = m_reg_l; m_reg_m = 1; m_reg_t = 4; }
    void LDrr_da() { m_reg_d = m_reg_a; m_reg_m = 1; m_reg_t = 4; }
    void LDrr_db() { m_reg_d = m_reg_b; m_reg_m = 1; m_reg_t = 4; }
    void LDrr_dc() { m_reg_d = m_reg_c; m_reg_m = 1; m_reg_t = 4; }
    void LDrr_dd() { m_reg_d = m_reg_d; m_reg_m = 1; m_reg_t = 4; }
    void LDrr_de() { m_reg_d = m_reg_e; m_reg_m = 1; m_reg_t = 4; }
    void LDrr_dh() { m_reg_d = m_reg_h; m_reg_m = 1; m_reg_t = 4; }
    void LDrr_dl() { m_reg_d = m_reg_l; m_reg_m = 1; m_reg_t = 4; }
    void LDrr_ea() { m_reg_e = m_reg_a; m_reg_m = 1; m_reg_t = 4; }
    void LDrr_eb() { m_reg_e = m_reg_b; m_reg_m = 1; m_reg_t = 4; }
    void LDrr_ec() { m_reg_e = m_reg_c; m_reg_m = 1; m_reg_t = 4; }
    void LDrr_ed() { m_reg_e = m_reg_d; m_reg_m = 1; m_reg_t = 4; }
    void LDrr_ee() { m_reg_e = m_reg_e; m_reg_m = 1; m_reg_t = 4; }
    void LDrr_eh() { m_reg_e = m_reg_h; m_reg_m = 1; m_reg_t = 4; }
    void LDrr_el() { m_reg_e = m_reg_l; m_reg_m = 1; m_reg_t = 4; }
    void LDrr_ha() { m_reg_h = m_reg_a; m_reg_m = 1; m_reg_t = 4; }
    void LDrr_hb() { m_reg_h = m_reg_b; m_reg_m = 1; m_reg_t = 4; }
    void LDrr_hc() { m_reg_h = m_reg_c; m_reg_m = 1; m_reg_t = 4; }
    void LDrr_hd() { m_reg_h = m_reg_d; m_reg_m = 1; m_reg_t = 4; }
    void LDrr_he() { m_reg_h = m_reg_e; m_reg_m = 1; m_reg_t = 4; }
    void LDrr_hh() { m_reg_h = m_reg_h; m_reg_m = 1; m_reg_t = 4; }
    void LDrr_hl() { m_reg_h = m_reg_l; m_reg_m = 1; m_reg_t = 4; }
    void LDrr_la() { m_reg_l = m_reg_a; m_reg_m = 1; m_reg_t = 4; }
    void LDrr_lb() { m_reg_l = m_reg_b; m_reg_m = 1; m_reg_t = 4; }
    void LDrr_lc() { m_reg_l = m_reg_c; m_reg_m = 1; m_reg_t = 4; }
    void LDrr_ld() { m_reg_l = m_reg_d; m_reg_m = 1; m_reg_t = 4; }
    void LDrr_le() { m_reg_l = m_reg_e; m_reg_m = 1; m_reg_t = 4; }
    void LDrr_lh() { m_reg_l = m_reg_h; m_reg_m = 1; m_reg_t = 4; }
    void LDrr_ll() { m_reg_l = m_reg_l; m_reg_m = 1; m_reg_t = 4; }

    //Load from mem address HL
    void LDrHLm_a() { m_reg_a = m_MMU.readByte((m_reg_h << 8) + m_reg_l); m_reg_m = 2; m_reg_t = 8; }
    void LDrHLm_b() { m_reg_b = m_MMU.readByte((m_reg_h << 8) + m_reg_l); m_reg_m = 2; m_reg_t = 8; }
    void LDrHLm_c() { m_reg_c = m_MMU.readByte((m_reg_h << 8) + m_reg_l); m_reg_m = 2; m_reg_t = 8; }
    void LDrHLm_d() { m_reg_d = m_MMU.readByte((m_reg_h << 8) + m_reg_l); m_reg_m = 2; m_reg_t = 8; }
    void LDrHLm_e() { m_reg_e = m_MMU.readByte((m_reg_h << 8) + m_reg_l); m_reg_m = 2; m_reg_t = 8; }
    void LDrHLm_h() { m_reg_h = m_MMU.readByte((m_reg_h << 8) + m_reg_l); m_reg_m = 2; m_reg_t = 8; }
    void LDrHLm_l() { m_reg_l = m_MMU.readByte((m_reg_h << 8) + m_reg_l); m_reg_m = 2; m_reg_t = 8; }

    //write to memory in location HL
    void LDHLmr_a() { m_MMU.writeByte((m_reg_h << 8) + m_reg_l, m_reg_a); m_reg_m = 2; m_reg_t = 8; }
    void LDHLmr_b() { m_MMU.writeByte((m_reg_h << 8) + m_reg_l, m_reg_b); m_reg_m = 2; m_reg_t = 8; }
    void LDHLmr_c() { m_MMU.writeByte((m_reg_h << 8) + m_reg_l, m_reg_c); m_reg_m = 2; m_reg_t = 8; }
    void LDHLmr_d() { m_MMU.writeByte((m_reg_h << 8) + m_reg_l, m_reg_d); m_reg_m = 2; m_reg_t = 8; }
    void LDHLmr_e() { m_MMU.writeByte((m_reg_h << 8) + m_reg_l, m_reg_e); m_reg_m = 2; m_reg_t = 8; }
    void LDHLmr_h() { m_MMU.writeByte((m_reg_h << 8) + m_reg_l, m_reg_h); m_reg_m = 2; m_reg_t = 8; }
    void LDHLmr_l() { m_MMU.writeByte((m_reg_h << 8) + m_reg_l, m_reg_l); m_reg_m = 2; m_reg_t = 8; }

    //load from memory address constant
    void LDrn_a() { m_reg_a = m_MMU.readByte(m_reg_pc); m_reg_pc++; m_reg_m = 2; m_reg_t = 8; }
    void LDrn_b() { m_reg_b = m_MMU.readByte(m_reg_pc); m_reg_pc++; m_reg_m = 2; m_reg_t = 8; }
    void LDrn_c() { m_reg_c = m_MMU.readByte(m_reg_pc); m_reg_pc++; m_reg_m = 2; m_reg_t = 8; }
    void LDrn_d() { m_reg_d = m_MMU.readByte(m_reg_pc); m_reg_pc++; m_reg_m = 2; m_reg_t = 8; }
    void LDrn_e() { m_reg_e = m_MMU.readByte(m_reg_pc); m_reg_pc++; m_reg_m = 2; m_reg_t = 8; }
    void LDrn_h() { m_reg_h = m_MMU.readByte(m_reg_pc); m_reg_pc++; m_reg_m = 2; m_reg_t = 8; }
    void LDrn_l() { m_reg_l = m_MMU.readByte(m_reg_pc); m_reg_pc++; m_reg_m = 2; m_reg_t = 8; }

    //copy byte in constant memory address into memory address HL
    void LDHLmn() { m_MMU.writeByte((m_reg_h << 8) + m_reg_l, m_MMU.readByte(m_reg_pc)); m_reg_pc++; m_reg_m = 3; m_reg_t = 12; }

    //Load into memory address BC/DE the byte stored in A
    void LDBCmA() { m_MMU.writeByte((m_reg_b << 8) + m_reg_c, m_reg_a); m_reg_m = 2; m_reg_t = 8; }
    void LDDEmA() { m_MMU.writeByte((m_reg_d << 8) + m_reg_e, m_reg_a); m_reg_m = 2; m_reg_t = 8; }

    //Write a into the address defined by a constant
    void LDmmA() { m_MMU.writeByte(m_MMU.readWord(m_reg_pc), m_reg_a); m_reg_pc += 2; m_reg_m = 4; m_reg_t = 16; }

    void LDABCm() { m_reg_a = m_MMU.readByte((m_reg_b << 8) + m_reg_c); m_reg_m = 2; m_reg_t = 8; }
    void LDADEm() { m_reg_a = m_MMU.readByte((m_reg_d << 8) + m_reg_e); m_reg_m = 2; m_reg_t = 8; }

    void LDAmm() { m_reg_a = m_MMU.readByte(m_MMU.readWord(m_reg_pc)); m_reg_pc += 2; m_reg_m = 4; m_reg_t = 16; }

    //load two constants into two registers
    void LDBCnn() { m_reg_c = m_MMU.readByte(m_reg_pc); m_reg_b = m_MMU.readByte(m_reg_pc + 1); m_reg_pc += 2; m_reg_m = 3; m_reg_t = 12; }
    void LDDEnn() { m_reg_e = m_MMU.readByte(m_reg_pc); m_reg_d = m_MMU.readByte(m_reg_pc + 1); m_reg_pc += 2; m_reg_m = 3; m_reg_t = 12; }
    void LDHLnn() { m_reg_l = m_MMU.readByte(m_reg_pc); m_reg_h = m_MMU.readByte(m_reg_pc + 1); m_reg_pc += 2; m_reg_m = 3; m_reg_t = 12; }
    void LDSPnn() { m_reg_sp = m_MMU.readWord(m_reg_pc); m_reg_pc += 2; m_reg_m = 3; m_reg_t = 12; }

    //read/write to/from a constant address into/out of HL
    void LDHLmm() { unsigned int i = m_MMU.readWord(m_reg_pc); m_reg_pc += 2; m_reg_l = m_MMU.readByte(i); m_reg_h = m_MMU.readByte(i + 1); m_reg_m = 5; m_reg_t = 20; }
    void LDmmHL() { unsigned int i = m_MMU.readWord(m_reg_pc); m_reg_pc += 2; m_MMU.writeWord(i, (m_reg_h << 8) + m_reg_l); m_reg_m = 5; m_reg_t = 20; }

    //Load from/into HL and increment HL
    void LDHLIA() { m_MMU.writeByte((m_reg_h << 8) + m_reg_l, m_reg_a); m_reg_l = (m_reg_l + 1) & 255; if (!m_reg_l) m_reg_h = (m_reg_h + 1) & 255; m_reg_m = 2; m_reg_t = 8; }
    void LDAHLI() { m_reg_a = m_MMU.readByte((m_reg_h << 8) + m_reg_l); m_reg_l = (m_reg_l + 1) & 255; if (!m_reg_l) m_reg_h = (m_reg_h + 1) & 255; m_reg_m = 2; m_reg_t = 8; }

    //same but decrement
    void LDHLDA() { m_MMU.writeByte((m_reg_h << 8) + m_reg_l, m_reg_a); m_reg_l = (m_reg_l - 1) & 255; if (m_reg_l == 255) m_reg_h = (m_reg_h - 1) & 255; m_reg_m = 2; m_reg_t = 8; }
    void LDAHLD() { m_reg_a = m_MMU.readByte((m_reg_h << 8) + m_reg_l); m_reg_l = (m_reg_l - 1) & 255; if (m_reg_l == 255) m_reg_h = (m_reg_h - 1) & 255; m_reg_m = 2; m_reg_t = 8; }

    //load 0xFF00 + nn into/out of A
    void LDAIOn() { m_reg_a = m_MMU.readByte(0xFF00 + m_MMU.readByte(m_reg_pc)); m_reg_pc++; m_reg_m = 3; m_reg_t = 12; }
    void LDIOnA() { m_MMU.writeByte(0xFF00 + m_MMU.readByte(m_reg_pc), m_reg_a); m_reg_pc++; m_reg_m = 3; m_reg_t = 12; }
    void LDAIOC() { m_reg_a = m_MMU.readByte(0xFF00 + m_reg_c); m_reg_m = 2; m_reg_t = 8; }
    void LDIOCA() { m_MMU.writeByte(0xFF00 + m_reg_c, m_reg_a); m_reg_m = 2; m_reg_t = 8; }

    void LDHLSPn() {
      int i = m_MMU.readByte(m_reg_pc);
      if (i > 127) 
        i = -((~i + 1) & 255);
      m_reg_pc++;
      i += m_reg_sp;
      m_reg_h = (i >> 8) & 255;
      m_reg_l = i & 255;
      m_reg_m = 3;
      m_reg_t = 12;
      m_reg_f = 0x00;
    }
    void LDSPHL() { m_reg_sp = (m_reg_h << 8) + m_reg_l; m_reg_m = 2; m_reg_t = 8; }

    void SWAPr_a() { int tr = m_reg_a; m_reg_a = ((tr & 0xF) << 4) | ((tr & 0xF0) >> 4); m_reg_f = m_reg_a ? 0 : 0x80; ; m_reg_m = 2; m_reg_t = 8; }
    void SWAPr_b() { int tr = m_reg_b; m_reg_b = ((tr & 0xF) << 4) | ((tr & 0xF0) >> 4); m_reg_f = m_reg_b ? 0 : 0x80; ; m_reg_m = 2; m_reg_t = 8; }
    void SWAPr_c() { int tr = m_reg_c; m_reg_c = ((tr & 0xF) << 4) | ((tr & 0xF0) >> 4); m_reg_f = m_reg_c ? 0 : 0x80; ; m_reg_m = 2; m_reg_t = 8; }
    void SWAPr_d() { int tr = m_reg_d; m_reg_d = ((tr & 0xF) << 4) | ((tr & 0xF0) >> 4); m_reg_f = m_reg_d ? 0 : 0x80; ; m_reg_m = 2; m_reg_t = 8; }
    void SWAPr_e() { int tr = m_reg_e; m_reg_e = ((tr & 0xF) << 4) | ((tr & 0xF0) >> 4); m_reg_f = m_reg_e ? 0 : 0x80; ; m_reg_m = 2; m_reg_t = 8; }
    void SWAPr_h() { int tr = m_reg_h; m_reg_h = ((tr & 0xF) << 4) | ((tr & 0xF0) >> 4); m_reg_f = m_reg_h ? 0 : 0x80; ; m_reg_m = 2; m_reg_t = 8; }
    void SWAPr_l() { int tr = m_reg_l; m_reg_l = ((tr & 0xF) << 4) | ((tr & 0xF0) >> 4); m_reg_f = m_reg_l ? 0 : 0x80; ; m_reg_m = 2; m_reg_t = 8; }
    void SWAPm_hl() { int tr = m_MMU.readByte((m_reg_h << 8) + m_reg_h); m_MMU.writeByte((m_reg_h << 8) + m_reg_l, ((tr & 0xF) << 4) | ((tr & 0xF0) >> 4)); m_reg_f = tr ? 0 : 0x80; m_reg_m = 4; m_reg_t = 16; }

    //Data processing

    //add from one register into a
    void ADDr_a() { int h = ((m_reg_a & 0xF) + (m_reg_a & 0xF)) > 0xF ? 0x20 : 0; m_reg_a += m_reg_a; fzc(m_reg_a, false); if (m_reg_a > 255) m_reg_f |= 0x10; m_reg_f += h; m_reg_a &= 255; m_reg_m = 1; m_reg_t = 4; }
    void ADDr_b() { int h = ((m_reg_a & 0xF) + (m_reg_b & 0xF)) > 0xF ? 0x20 : 0; m_reg_a += m_reg_b; fzc(m_reg_a, false); if (m_reg_a > 255) m_reg_f |= 0x10; m_reg_f += h; m_reg_a &= 255; m_reg_m = 1; m_reg_t = 4; }
    void ADDr_c() { int h = ((m_reg_a & 0xF) + (m_reg_c & 0xF)) > 0xF ? 0x20 : 0; m_reg_a += m_reg_c; fzc(m_reg_a, false); if (m_reg_a > 255) m_reg_f |= 0x10; m_reg_f += h; m_reg_a &= 255; m_reg_m = 1; m_reg_t = 4; }
    void ADDr_d() { int h = ((m_reg_a & 0xF) + (m_reg_d & 0xF)) > 0xF ? 0x20 : 0; m_reg_a += m_reg_d; fzc(m_reg_a, false); if (m_reg_a > 255) m_reg_f |= 0x10; m_reg_f += h; m_reg_a &= 255; m_reg_m = 1; m_reg_t = 4; }
    void ADDr_e() { int h = ((m_reg_a & 0xF) + (m_reg_e & 0xF)) > 0xF ? 0x20 : 0; m_reg_a += m_reg_e; fzc(m_reg_a, false); if (m_reg_a > 255) m_reg_f |= 0x10; m_reg_f += h; m_reg_a &= 255; m_reg_m = 1; m_reg_t = 4; }
    void ADDr_h() { int h = ((m_reg_a & 0xF) + (m_reg_h & 0xF)) > 0xF ? 0x20 : 0; m_reg_a += m_reg_h; fzc(m_reg_a, false); if (m_reg_a > 255) m_reg_f |= 0x10; m_reg_f += h; m_reg_a &= 255; m_reg_m = 1; m_reg_t = 4; }
    void ADDr_l() { int h = ((m_reg_a & 0xF) + (m_reg_l & 0xF)) > 0xF ? 0x20 : 0; m_reg_a += m_reg_l; fzc(m_reg_a, false); if (m_reg_a > 255) m_reg_f |= 0x10; m_reg_f += h; m_reg_a &= 255; m_reg_m = 1; m_reg_t = 4; }
    //add from memory into a
    void ADDHL() {
      int i = m_MMU.readByte((m_reg_h << 8) + m_reg_l);
      int h = ((i & 0xF) + (m_reg_a & 0xF)) > 0xF ? 0x20 : 0;
      m_reg_a += i;
      fzc(m_reg_a, false);
      if (m_reg_a > 255) m_reg_f |= 0x10;
      m_reg_f += h;
      m_reg_a &= 255;
      m_reg_m = 2;
      m_reg_t = 8;
    }
    void ADDn() {
      int i = m_MMU.readByte(m_reg_pc);
      int h = ((i & 0xF) + (m_reg_a & 0xF)) > 0xF ? 0x20 : 0;
      m_reg_a += i;
      m_reg_pc++;
      fzc(m_reg_a, false);
      if (m_reg_a > 255) m_reg_f |= 0x10;
      m_reg_f += h;
      m_reg_a &= 255;
      m_reg_m = 2;
      m_reg_t = 8;
    }
    void ADDHLBC() {
      int hl = (m_reg_h << 8) + m_reg_l;
      int bc = (m_reg_b << 8) + m_reg_c;
      int h = ((hl & 0xFFF) + (bc & 0xFFF)) > 0xFFF ? 0x20 : 0;
      hl += (m_reg_b << 8) + m_reg_c;
      m_reg_f &= 0x9F;  //reset subtract and half carry
      m_reg_f += h;     //half carry
      if (hl > 65535) m_reg_f |= 0x10;  //carry
      else m_reg_f &= 0xEF;
      m_reg_h = (hl >> 8) & 255;
      m_reg_l = hl & 255;
      m_reg_m = 3;
      m_reg_t = 12;
    }
    void ADDHLDE() {
      int hl = (m_reg_h << 8) + m_reg_l;
      int de = (m_reg_d << 8) + m_reg_e;
      int h = ((hl & 0xFFF) + (de & 0xFFF)) > 0xFFF ? 0x20 : 0;
      hl += (m_reg_d << 8) + m_reg_e;
      m_reg_f &= 0x9F;  //reset subtract and half carry
      m_reg_f += h;     //half carry
      if (hl > 65535) m_reg_f |= 0x10;
      else m_reg_f &= 0xEF;
      m_reg_h = (hl >> 8) & 255; 
      m_reg_l = hl & 255;
      m_reg_m = 3;
      m_reg_t = 12;
    }
    void ADDHLHL() {
      int hl = (m_reg_h << 8) + m_reg_l;
      int h = ((hl & 0xFFF) + (hl & 0xFFF)) > 0xFFF ? 0x20 : 0;
      hl += hl;
      m_reg_f &= 0x9F;  //reset subtract and half carry
      m_reg_f += h;     //half carry
      if (hl > 65535) m_reg_f |= 0x10;
      else m_reg_f &= 0xEF;
      m_reg_h = (hl >> 8) & 255;
      m_reg_l = hl & 255;
      m_reg_m = 3;
      m_reg_t = 12;
    }
    void ADDHLSP() {
      int hl = (m_reg_h << 8) + m_reg_l;
      int h = ((hl & 0xFFF) + (m_reg_sp & 0xFFF)) > 0xFFF ? 0x20 : 0;
      hl += m_reg_sp;
      m_reg_f &= 0x9F;  //reset subtract and half carry
      m_reg_f += h;     //half carry
      if (hl > 65535) m_reg_f |= 0x10;
      else m_reg_f &= 0xEF;
      m_reg_h = (hl >> 8) & 255;
      m_reg_l = hl & 255;
      m_reg_m = 3;
      m_reg_t = 12;
    }
    void ADDSPn() {
      int i = m_MMU.readByte(m_reg_pc);
      if (i > 127) i = -((~i + 1) & 255);
      m_reg_pc++;
      int h;
      if (i > 0) {
        h = ((m_reg_sp & 0xF) + (i & 0xF)) > 0xF ? 0x20 : 0;
      } else if (i < 0) {
        h = ((m_reg_sp & 0xF) - (i & 0xF)) < 0 ? 0x20 : 0;
      }
      m_reg_f = 0;
      m_reg_f += h;
      if (m_reg_pc > 0xFFFF) m_reg_f |= 0x10;
      m_reg_pc &= 0xFFFF;
      m_reg_sp += i;
      m_reg_m = 4;
      m_reg_t = 16;
    }

    void ADCr_a() { int h = ((m_reg_a & 0xF) + (m_reg_a & 0xF) + ((m_reg_f & 0x10) ? 1 : 0)) > 0xF ? 0x20 : 0; m_reg_a += m_reg_a; m_reg_a += (m_reg_f & 0x10) ? 1 : 0; fzc(m_reg_a, false); if (m_reg_a > 255) m_reg_f |= 0x10; m_reg_f += h; m_reg_a &= 255; m_reg_m = 1; m_reg_t = 4; }
    void ADCr_b() { int h = ((m_reg_a & 0xF) + (m_reg_b & 0xF) + ((m_reg_f & 0x10) ? 1 : 0)) > 0xF ? 0x20 : 0; m_reg_a += m_reg_b; m_reg_a += (m_reg_f & 0x10) ? 1 : 0; fzc(m_reg_a, false); if (m_reg_a > 255) m_reg_f |= 0x10; m_reg_f += h; m_reg_a &= 255; m_reg_m = 1; m_reg_t = 4; }
    void ADCr_c() { int h = ((m_reg_a & 0xF) + (m_reg_c & 0xF) + ((m_reg_f & 0x10) ? 1 : 0)) > 0xF ? 0x20 : 0; m_reg_a += m_reg_c; m_reg_a += (m_reg_f & 0x10) ? 1 : 0; fzc(m_reg_a, false); if (m_reg_a > 255) m_reg_f |= 0x10; m_reg_f += h; m_reg_a &= 255; m_reg_m = 1; m_reg_t = 4; }
    void ADCr_d() { int h = ((m_reg_a & 0xF) + (m_reg_d & 0xF) + ((m_reg_f & 0x10) ? 1 : 0)) > 0xF ? 0x20 : 0; m_reg_a += m_reg_d; m_reg_a += (m_reg_f & 0x10) ? 1 : 0; fzc(m_reg_a, false); if (m_reg_a > 255) m_reg_f |= 0x10; m_reg_f += h; m_reg_a &= 255; m_reg_m = 1; m_reg_t = 4; }
    void ADCr_e() { int h = ((m_reg_a & 0xF) + (m_reg_e & 0xF) + ((m_reg_f & 0x10) ? 1 : 0)) > 0xF ? 0x20 : 0; m_reg_a += m_reg_e; m_reg_a += (m_reg_f & 0x10) ? 1 : 0; fzc(m_reg_a, false); if (m_reg_a > 255) m_reg_f |= 0x10; m_reg_f += h; m_reg_a &= 255; m_reg_m = 1; m_reg_t = 4; }
    void ADCr_h() { int h = ((m_reg_a & 0xF) + (m_reg_h & 0xF) + ((m_reg_f & 0x10) ? 1 : 0)) > 0xF ? 0x20 : 0; m_reg_a += m_reg_h; m_reg_a += (m_reg_f & 0x10) ? 1 : 0; fzc(m_reg_a, false); if (m_reg_a > 255) m_reg_f |= 0x10; m_reg_f += h; m_reg_a &= 255; m_reg_m = 1; m_reg_t = 4; }
    void ADCr_l() { int h = ((m_reg_a & 0xF) + (m_reg_l & 0xF) + ((m_reg_f & 0x10) ? 1 : 0)) > 0xF ? 0x20 : 0; m_reg_a += m_reg_l; m_reg_a += (m_reg_f & 0x10) ? 1 : 0; fzc(m_reg_a, false); if (m_reg_a > 255) m_reg_f |= 0x10; m_reg_f += h; m_reg_a &= 255; m_reg_m = 1; m_reg_t = 4; }
    void ADCHL() {
      int i = m_MMU.readByte((m_reg_h << 8) + m_reg_l);
      int h = ((m_reg_a & 0xF) + (i & 0xF) + ((m_reg_f & 0x10) ? 1 : 0)) > 0xF ? 0x20 : 0;
      m_reg_a += i;
      m_reg_a += (m_reg_f & 0x10) ? 1 : 0;
      fzc(m_reg_a, false);
      if (m_reg_a > 255) m_reg_f |= 0x10;
      m_reg_f += h;
      m_reg_a &= 255;
      m_reg_m = 2;
      m_reg_t = 8;
    }
    void ADCn() {
      int i = m_MMU.readByte(m_reg_pc);
      m_reg_pc++;
      int h = ((m_reg_a & 0xF) + (i & 0xF) + ((m_reg_f & 0x10) ? 1 : 0)) > 0xF ? 0x20 : 0;
      m_reg_a += i;
      m_reg_a += (m_reg_f & 0x10) ? 1 : 0;
      fzc(m_reg_a, false);
      if (m_reg_a > 255) m_reg_f |= 0x10;
      m_reg_h += h;
      m_reg_a &= 255; 
      m_reg_m = 2;
      m_reg_t = 8;
    }

    void SUBr_a() { m_reg_a -= m_reg_a; fzc(m_reg_a, true); if (m_reg_a & 0x100) m_reg_f |= 0x10; m_reg_a &= 255; m_reg_m = 1; m_reg_t = 4; }
    void SUBr_b() { m_reg_a -= m_reg_b; fzc(m_reg_a, true); if (m_reg_a & 0x100) m_reg_f |= 0x10; m_reg_a &= 255; m_reg_m = 1; m_reg_t = 4; }
    void SUBr_c() { m_reg_a -= m_reg_c; fzc(m_reg_a, true); if (m_reg_a & 0x100) m_reg_f |= 0x10; m_reg_a &= 255; m_reg_m = 1; m_reg_t = 4; }
    void SUBr_d() { m_reg_a -= m_reg_d; fzc(m_reg_a, true); if (m_reg_a & 0x100) m_reg_f |= 0x10; m_reg_a &= 255; m_reg_m = 1; m_reg_t = 4; }
    void SUBr_e() { m_reg_a -= m_reg_e; fzc(m_reg_a, true); if (m_reg_a & 0x100) m_reg_f |= 0x10; m_reg_a &= 255; m_reg_m = 1; m_reg_t = 4; }
    void SUBr_h() { m_reg_a -= m_reg_h; fzc(m_reg_a, true); if (m_reg_a & 0x100) m_reg_f |= 0x10; m_reg_a &= 255; m_reg_m = 1; m_reg_t = 4; }
    void SUBr_l() {
      m_reg_a -= m_reg_l;
      fzc(m_reg_a, true);
      if (m_reg_a & 0x100) m_reg_f |= 0x10;
      m_reg_a &= 255;
      m_reg_m = 1;
      m_reg_t = 4;
    }
    void SUBHL() { m_reg_a -= m_MMU.readByte((m_reg_h << 8) + m_reg_l); fzc(m_reg_a, true); if (m_reg_a & 0x100) m_reg_f |= 0x10; m_reg_a &= 255; m_reg_m = 2; m_reg_t = 8; }
    void SUBn() { m_reg_a -= m_MMU.readByte(m_reg_pc); m_reg_pc++; fzc(m_reg_a, true); if (m_reg_a & 0x100) m_reg_f |= 0x10; m_reg_a &= 255; m_reg_m = 2; m_reg_t = 8; }

    void SBCr_a() { m_reg_a -= m_reg_a; m_reg_a -= ((m_reg_f & 0x10) ? 1 : 0); fzc(m_reg_a, true); if (m_reg_a & 0x100) m_reg_f |= 0x10; m_reg_a &= 255; m_reg_m = 1; m_reg_t = 4; }
    void SBCr_b() { m_reg_a -= m_reg_b; m_reg_a -= ((m_reg_f & 0x10) ? 1 : 0); fzc(m_reg_a, true); if (m_reg_a & 0x100) m_reg_f |= 0x10; m_reg_a &= 255; m_reg_m = 1; m_reg_t = 4; }
    void SBCr_c() { m_reg_a -= m_reg_c; m_reg_a -= ((m_reg_f & 0x10) ? 1 : 0); fzc(m_reg_a, true); if (m_reg_a & 0x100) m_reg_f |= 0x10; m_reg_a &= 255; m_reg_m = 1; m_reg_t = 4; }
    void SBCr_d() { m_reg_a -= m_reg_d; m_reg_a -= ((m_reg_f & 0x10) ? 1 : 0); fzc(m_reg_a, true); if (m_reg_a & 0x100) m_reg_f |= 0x10; m_reg_a &= 255; m_reg_m = 1; m_reg_t = 4; }
    void SBCr_e() { m_reg_a -= m_reg_e; m_reg_a -= ((m_reg_f & 0x10) ? 1 : 0); fzc(m_reg_a, true); if (m_reg_a & 0x100) m_reg_f |= 0x10; m_reg_a &= 255; m_reg_m = 1; m_reg_t = 4; }
    void SBCr_h() { m_reg_a -= m_reg_h; m_reg_a -= ((m_reg_f & 0x10) ? 1 : 0); fzc(m_reg_a, true); if (m_reg_a & 0x100) m_reg_f |= 0x10; m_reg_a &= 255; m_reg_m = 1; m_reg_t = 4; }
    void SBCr_l() { m_reg_a -= m_reg_l; m_reg_a -= ((m_reg_f & 0x10) ? 1 : 0); fzc(m_reg_a, true); if (m_reg_a & 0x100) m_reg_f |= 0x10; m_reg_a &= 255; m_reg_m = 1; m_reg_t = 4; }
    void SBCHL() { m_reg_a -= m_MMU.readByte((m_reg_h << 8) + m_reg_l); m_reg_a -= (m_reg_f & 0x10) ? 1 : 0; fzc(m_reg_a, true); if (m_reg_a & 0x100) m_reg_f |= 0x10; m_reg_a &= 255; m_reg_m = 2; m_reg_t = 8; }
    void SBCn() { m_reg_a -= m_MMU.readByte(m_reg_pc); m_reg_pc++; m_reg_a -= (m_reg_f & 0x10) ? 1 : 0; fzc(m_reg_a, true); if (m_reg_a & 0x100) m_reg_f |= 0x10; m_reg_a &= 255; m_reg_m = 2; m_reg_t = 8; }

    void CPr_a() { unsigned int i = m_reg_a; i -= m_reg_a; fzc(i, true); if (i > 255) m_reg_f |= 0x10; i &= 255; m_reg_m = 1; m_reg_t = 4; }
    void CPr_b() { unsigned int i = m_reg_a; i -= m_reg_b; fzc(i, true); if (i > 255) m_reg_f |= 0x10; i &= 255; m_reg_m = 1; m_reg_t = 4; }
    void CPr_c() { unsigned int i = m_reg_a; i -= m_reg_c; fzc(i, true); if (i > 255) m_reg_f |= 0x10; i &= 255; m_reg_m = 1; m_reg_t = 4; }
    void CPr_d() { unsigned int i = m_reg_a; i -= m_reg_d; fzc(i, true); if (i > 255) m_reg_f |= 0x10; i &= 255; m_reg_m = 1; m_reg_t = 4; }
    void CPr_e() { unsigned int i = m_reg_a; i -= m_reg_e; fzc(i, true); if (i > 255) m_reg_f |= 0x10; i &= 255; m_reg_m = 1; m_reg_t = 4; }
    void CPr_h() { unsigned int i = m_reg_a; i -= m_reg_h; fzc(i, true); if (i > 255) m_reg_f |= 0x10; i &= 255; m_reg_m = 1; m_reg_t = 4; }
    void CPr_l() { unsigned int i = m_reg_a; i -= m_reg_l; fzc(i, true); if (i > 255) m_reg_f |= 0x10; i &= 255; m_reg_m = 1; m_reg_t = 4; }
    void CPHL() { unsigned int i = m_reg_a; i -= m_MMU.readByte((m_reg_h << 8) + m_reg_l); fzc(i, true); if (i > 255) m_reg_f |= 0x10; i &= 255; m_reg_m = 2; m_reg_t = 8; }
    void CPn() { 
      unsigned int i = m_reg_a;
      i -= m_MMU.readByte(m_reg_pc);
      m_reg_pc++; fzc(i, true);
      if (i > 255)
        m_reg_f |= 0x10;
      i &= 255;
      m_reg_m = 2; m_reg_t = 8; }

    void ANDr_a() { m_reg_a &= m_reg_a; m_reg_a &= 255; fzc(m_reg_a, false); m_reg_m = 1; m_reg_t = 4; }
    void ANDr_b() { m_reg_a &= m_reg_b; m_reg_a &= 255; fzc(m_reg_a, false); m_reg_m = 1; m_reg_t = 4; }
    void ANDr_c() { m_reg_a &= m_reg_c; m_reg_a &= 255; fzc(m_reg_a, false); m_reg_m = 1; m_reg_t = 4; }
    void ANDr_d() { m_reg_a &= m_reg_d; m_reg_a &= 255; fzc(m_reg_a, false); m_reg_m = 1; m_reg_t = 4; }
    void ANDr_e() { m_reg_a &= m_reg_e; m_reg_a &= 255; fzc(m_reg_a, false); m_reg_m = 1; m_reg_t = 4; }
    void ANDr_h() { m_reg_a &= m_reg_h; m_reg_a &= 255; fzc(m_reg_a, false); m_reg_m = 1; m_reg_t = 4; }
    void ANDr_l() { m_reg_a &= m_reg_l; m_reg_a &= 255; fzc(m_reg_a, false); m_reg_m = 1; m_reg_t = 4; }
    void ANDHL() { m_reg_a &= m_MMU.readByte((m_reg_h << 8) + m_reg_l); m_reg_a &= 255; fzc(m_reg_a, false); m_reg_m = 2; m_reg_t = 8; }
    void ANDn() { m_reg_a &= m_MMU.readByte(m_reg_pc); m_reg_pc++; m_reg_a &= 255; fzc(m_reg_a, false); m_reg_m = 2; m_reg_t = 8; }

    void ORr_a() { m_reg_a |= m_reg_a; m_reg_a &= 255; fzc(m_reg_a, false); m_reg_m = 1; m_reg_t = 4; }
    void ORr_b() { m_reg_a |= m_reg_b; m_reg_a &= 255; fzc(m_reg_a, false); m_reg_m = 1; m_reg_t = 4; }
    void ORr_c() { m_reg_a |= m_reg_c; m_reg_a &= 255; fzc(m_reg_a, false); m_reg_m = 1; m_reg_t = 4; }
    void ORr_d() { m_reg_a |= m_reg_d; m_reg_a &= 255; fzc(m_reg_a, false); m_reg_m = 1; m_reg_t = 4; }
    void ORr_e() { m_reg_a |= m_reg_e; m_reg_a &= 255; fzc(m_reg_a, false); m_reg_m = 1; m_reg_t = 4; }
    void ORr_h() { m_reg_a |= m_reg_h; m_reg_a &= 255; fzc(m_reg_a, false); m_reg_m = 1; m_reg_t = 4; }
    void ORr_l() { m_reg_a |= m_reg_l; m_reg_a &= 255; fzc(m_reg_a, false); m_reg_m = 1; m_reg_t = 4; }
    void ORHL() { m_reg_a |= m_MMU.readByte((m_reg_h << 8) + m_reg_l); m_reg_a &= 255; fzc(m_reg_a, false); m_reg_m = 2; m_reg_t = 8; }
    void ORn() { m_reg_a |= m_MMU.readByte(m_reg_pc); m_reg_pc++; m_reg_a &= 255; fzc(m_reg_a, false); m_reg_m = 2; m_reg_t = 8; }

    void XORr_a() { m_reg_a ^= m_reg_a; m_reg_a &= 255; fzc(m_reg_a, false); m_reg_m = 1; m_reg_t = 4; }
    void XORr_b() { m_reg_a ^= m_reg_b; m_reg_a &= 255; fzc(m_reg_a, false); m_reg_m = 1; m_reg_t = 4; }
    void XORr_c() { m_reg_a ^= m_reg_c; m_reg_a &= 255; fzc(m_reg_a, false); m_reg_m = 1; m_reg_t = 4; }
    void XORr_d() { m_reg_a ^= m_reg_d; m_reg_a &= 255; fzc(m_reg_a, false); m_reg_m = 1; m_reg_t = 4; }
    void XORr_e() { m_reg_a ^= m_reg_e; m_reg_a &= 255; fzc(m_reg_a, false); m_reg_m = 1; m_reg_t = 4; }
    void XORr_h() { m_reg_a ^= m_reg_h; m_reg_a &= 255; fzc(m_reg_a, false); m_reg_m = 1; m_reg_t = 4; }
    void XORr_l() { m_reg_a ^= m_reg_l; m_reg_a &= 255; fzc(m_reg_a, false); m_reg_m = 1; m_reg_t = 4; }
    void XORHL() { m_reg_a ^= m_MMU.readByte((m_reg_h << 8) + m_reg_l); m_reg_a &= 255; fzc(m_reg_a, false); m_reg_m = 2; m_reg_t = 8; }
    void XORn() { m_reg_a ^= m_MMU.readByte(m_reg_pc); m_reg_pc++; m_reg_a &= 255; fzc(m_reg_a, false); m_reg_m = 2; m_reg_t = 8; }

    void INCr_a() { m_reg_a++; m_reg_a &= 255; fzc(m_reg_a, false); m_reg_m = 1; m_reg_t = 4; }
    void INCr_b() { m_reg_b++; m_reg_b &= 255; fzc(m_reg_b, false); m_reg_m = 1; m_reg_t = 4; }
    void INCr_c() { m_reg_c++; m_reg_c &= 255; fzc(m_reg_c, false); m_reg_m = 1; m_reg_t = 4; }
    void INCr_d() { m_reg_d++; m_reg_d &= 255; fzc(m_reg_d, false); m_reg_m = 1; m_reg_t = 4; }
    void INCr_e() { m_reg_e++; m_reg_e &= 255; fzc(m_reg_e, false); m_reg_m = 1; m_reg_t = 4; }
    void INCr_h() { m_reg_h++; m_reg_h &= 255; fzc(m_reg_h, false); m_reg_m = 1; m_reg_t = 4; }
    void INCr_l() { m_reg_l++; m_reg_l &= 255; fzc(m_reg_l, false); m_reg_m = 1; m_reg_t = 4; }
    void INCHLm() { int i = m_MMU.readByte((m_reg_h << 8) + m_reg_l) + 1; i &= 255; m_MMU.writeByte((m_reg_h << 8) + m_reg_l, i); fzc(i, false); m_reg_m = 3; m_reg_t = 12; }

    void DECr_a() { m_reg_a--; m_reg_a &= 255; fzc(m_reg_a, false); m_reg_m = 1; m_reg_t = 4; }
    void DECr_b() { m_reg_b--; m_reg_b &= 255; fzc(m_reg_b, false); m_reg_m = 1; m_reg_t = 4; }
    void DECr_c() { m_reg_c--; m_reg_c &= 255; fzc(m_reg_c, false); m_reg_m = 1; m_reg_t = 4; }
    void DECr_d() { m_reg_d--; m_reg_d &= 255; fzc(m_reg_d, false); m_reg_m = 1; m_reg_t = 4; }
    void DECr_e() { m_reg_e--; m_reg_e &= 255; fzc(m_reg_e, false); m_reg_m = 1; m_reg_t = 4; }
    void DECr_h() { m_reg_h--; m_reg_h &= 255; fzc(m_reg_h, false); m_reg_m = 1; m_reg_t = 4; }
    void DECr_l() { m_reg_l--; m_reg_l &= 255; fzc(m_reg_l, false); m_reg_m = 1; m_reg_t = 4; }
    void DECHLm() { int i = m_MMU.readByte((m_reg_h << 8) + m_reg_l) - 1; i &= 255; m_MMU.writeByte((m_reg_h << 8) + m_reg_l, i); fzc(i, false); m_reg_m = 3; m_reg_t = 12; }

    void INCBC() { m_reg_c = (m_reg_c + 1) & 255; if (!m_reg_c) m_reg_b = (m_reg_b + 1) & 255; m_reg_m = 1; m_reg_t = 4; }
    void INCDE() { m_reg_e = (m_reg_e + 1) & 255; if (!m_reg_e) m_reg_d = (m_reg_d + 1) & 255; m_reg_m = 1; m_reg_t = 4; }
    void INCHL() { m_reg_l = (m_reg_l + 1) & 255; if (!m_reg_l) m_reg_h = (m_reg_h + 1) & 255; m_reg_m = 1; m_reg_t = 4; }
    void INCSP() { m_reg_sp = (m_reg_sp + 1) & 65535; m_reg_m = 1; m_reg_t = 4; }

    void DECBC() { m_reg_c = (m_reg_c - 1) & 255; if (m_reg_c == 255) m_reg_b = (m_reg_b - 1) & 255; m_reg_m = 1; m_reg_t = 4; }
    void DECDE() { m_reg_e = (m_reg_e - 1) & 255; if (m_reg_e == 255) m_reg_d = (m_reg_d - 1) & 255; m_reg_m = 1; m_reg_t = 4; }
    void DECHL() { m_reg_l = (m_reg_l - 1) & 255; if (m_reg_l == 255) m_reg_h = (m_reg_h - 1) & 255; m_reg_m = 1; m_reg_t = 4; }
    void DECSP() { m_reg_sp = (m_reg_sp - 1) & 65535; m_reg_m = 1; m_reg_t = 4; }

    //Decimal adjust m_reg_a. Used to hold demical values
    void DAA() {
      if ((m_reg_a & 0xF) > 0x09 || m_reg_f & 0x20) {
        m_reg_a += 0x06;
      }
      if ((m_reg_a >> 4) > 9 || m_reg_f & 0x10) {
        m_reg_a += 0x60;
        m_reg_f |= 0x10;
      }
      else {
        m_reg_f &= 0xEF;
      }
      if (m_reg_a > 255) m_reg_f |= 0x10;
      m_reg_a &= 255;
      m_reg_m = 1;
      m_reg_t = 4;
    }

    //Bit Manipulation
    void BIT0a() { fz(m_reg_a & 0x01, false); m_reg_m = 2; m_reg_t = 8; m_reg_f |= 0x20; }
    void BIT0b() { fz(m_reg_b & 0x01, false); m_reg_m = 2; m_reg_t = 8; m_reg_f |= 0x20; }
    void BIT0c() { fz(m_reg_c & 0x01, false); m_reg_m = 2; m_reg_t = 8; m_reg_f |= 0x20; }
    void BIT0d() { fz(m_reg_d & 0x01, false); m_reg_m = 2; m_reg_t = 8; m_reg_f |= 0x20; }
    void BIT0e() { fz(m_reg_e & 0x01, false); m_reg_m = 2; m_reg_t = 8; m_reg_f |= 0x20; }
    void BIT0h() { fz(m_reg_h & 0x01, false); m_reg_m = 2; m_reg_t = 8; m_reg_f |= 0x20; }
    void BIT0l() { fz(m_reg_l & 0x01, false); m_reg_m = 2; m_reg_t = 8; m_reg_f |= 0x20; }
    void BIT0m() { fz(m_MMU.readByte((m_reg_h << 8) + m_reg_l) & 0x01, false); m_reg_m = 3; m_reg_t = 12; m_reg_f |= 0x20; }

    void BIT1a() { fz(m_reg_a & 0x02, false); m_reg_m = 2; m_reg_t = 8; m_reg_f |= 0x20; }
    void BIT1b() { fz(m_reg_b & 0x02, false); m_reg_m = 2; m_reg_t = 8; m_reg_f |= 0x20; }
    void BIT1c() { fz(m_reg_c & 0x02, false); m_reg_m = 2; m_reg_t = 8; m_reg_f |= 0x20; }
    void BIT1d() { fz(m_reg_d & 0x02, false); m_reg_m = 2; m_reg_t = 8; m_reg_f |= 0x20; }
    void BIT1e() { fz(m_reg_e & 0x02, false); m_reg_m = 2; m_reg_t = 8; m_reg_f |= 0x20; }
    void BIT1h() { fz(m_reg_h & 0x02, false); m_reg_m = 2; m_reg_t = 8; m_reg_f |= 0x20; }
    void BIT1l() { fz(m_reg_l & 0x02, false); m_reg_m = 2; m_reg_t = 8; m_reg_f |= 0x20; }
    void BIT1m() { fz(m_MMU.readByte((m_reg_h << 8) + m_reg_l) & 0x02, false); m_reg_m = 3; m_reg_t = 12; m_reg_f |= 0x20; }

    void BIT2a() { fz(m_reg_a & 0x04, false); m_reg_m = 2; m_reg_t = 8; m_reg_f |= 0x20; }
    void BIT2b() { fz(m_reg_b & 0x04, false); m_reg_m = 2; m_reg_t = 8; m_reg_f |= 0x20; }
    void BIT2c() { fz(m_reg_c & 0x04, false); m_reg_m = 2; m_reg_t = 8; m_reg_f |= 0x20; }
    void BIT2d() { fz(m_reg_d & 0x04, false); m_reg_m = 2; m_reg_t = 8; m_reg_f |= 0x20; }
    void BIT2e() { fz(m_reg_e & 0x04, false); m_reg_m = 2; m_reg_t = 8; m_reg_f |= 0x20; }
    void BIT2h() { fz(m_reg_h & 0x04, false); m_reg_m = 2; m_reg_t = 8; m_reg_f |= 0x20; }
    void BIT2l() { fz(m_reg_l & 0x04, false); m_reg_m = 2; m_reg_t = 8; m_reg_f |= 0x20; }
    void BIT2m() { fz(m_MMU.readByte((m_reg_h << 8) + m_reg_l) & 0x04, false); m_reg_m = 3; m_reg_t = 12; m_reg_f |= 0x20; }

    void BIT3a() { fz(m_reg_a & 0x08, false); m_reg_m = 2; m_reg_t = 8; m_reg_f |= 0x20; }
    void BIT3b() { fz(m_reg_b & 0x08, false); m_reg_m = 2; m_reg_t = 8; m_reg_f |= 0x20; }
    void BIT3c() { fz(m_reg_c & 0x08, false); m_reg_m = 2; m_reg_t = 8; m_reg_f |= 0x20; }
    void BIT3d() { fz(m_reg_d & 0x08, false); m_reg_m = 2; m_reg_t = 8; m_reg_f |= 0x20; }
    void BIT3e() { fz(m_reg_e & 0x08, false); m_reg_m = 2; m_reg_t = 8; m_reg_f |= 0x20; }
    void BIT3h() { fz(m_reg_h & 0x08, false); m_reg_m = 2; m_reg_t = 8; m_reg_f |= 0x20; }
    void BIT3l() { fz(m_reg_l & 0x08, false); m_reg_m = 2; m_reg_t = 8; m_reg_f |= 0x20; }
    void BIT3m() { fz(m_MMU.readByte((m_reg_h << 8) + m_reg_l) & 0x08, false); m_reg_m = 3; m_reg_t = 12; m_reg_f |= 0x20; }

    void BIT4a() { fz(m_reg_a & 0x10, false); m_reg_m = 2; m_reg_t = 8; m_reg_f |= 0x20; }
    void BIT4b() { fz(m_reg_b & 0x10, false); m_reg_m = 2; m_reg_t = 8; m_reg_f |= 0x20; }
    void BIT4c() { fz(m_reg_c & 0x10, false); m_reg_m = 2; m_reg_t = 8; m_reg_f |= 0x20; }
    void BIT4d() { fz(m_reg_d & 0x10, false); m_reg_m = 2; m_reg_t = 8; m_reg_f |= 0x20; }
    void BIT4e() { fz(m_reg_e & 0x10, false); m_reg_m = 2; m_reg_t = 8; m_reg_f |= 0x20; }
    void BIT4h() { fz(m_reg_h & 0x10, false); m_reg_m = 2; m_reg_t = 8; m_reg_f |= 0x20; }
    void BIT4l() { fz(m_reg_l & 0x10, false); m_reg_m = 2; m_reg_t = 8; m_reg_f |= 0x20; }
    void BIT4m() { fz(m_MMU.readByte((m_reg_h << 8) + m_reg_l) & 0x10, false); m_reg_m = 3; m_reg_t = 12; m_reg_f |= 0x20; }

    void BIT5a() { fz(m_reg_a & 0x20, false); m_reg_m = 2; m_reg_t = 8; m_reg_f |= 0x20; }
    void BIT5b() { fz(m_reg_b & 0x20, false); m_reg_m = 2; m_reg_t = 8; m_reg_f |= 0x20; }
    void BIT5c() { fz(m_reg_c & 0x20, false); m_reg_m = 2; m_reg_t = 8; m_reg_f |= 0x20; }
    void BIT5d() { fz(m_reg_d & 0x20, false); m_reg_m = 2; m_reg_t = 8; m_reg_f |= 0x20; }
    void BIT5e() { fz(m_reg_e & 0x20, false); m_reg_m = 2; m_reg_t = 8; m_reg_f |= 0x20; }
    void BIT5h() { fz(m_reg_h & 0x20, false); m_reg_m = 2; m_reg_t = 8; m_reg_f |= 0x20; }
    void BIT5l() { fz(m_reg_l & 0x20, false); m_reg_m = 2; m_reg_t = 8; m_reg_f |= 0x20; }
    void BIT5m() { fz(m_MMU.readByte((m_reg_h << 8) + m_reg_l) & 0x20, false); m_reg_m = 3; m_reg_t = 12; m_reg_f |= 0x20; }

    void BIT6a() { fz(m_reg_a & 0x40, false); m_reg_m = 2; m_reg_t = 8; m_reg_f |= 0x20; }
    void BIT6b() { fz(m_reg_b & 0x40, false); m_reg_m = 2; m_reg_t = 8; m_reg_f |= 0x20; }
    void BIT6c() { fz(m_reg_c & 0x40, false); m_reg_m = 2; m_reg_t = 8; m_reg_f |= 0x20; }
    void BIT6d() { fz(m_reg_d & 0x40, false); m_reg_m = 2; m_reg_t = 8; m_reg_f |= 0x20; }
    void BIT6e() { fz(m_reg_e & 0x40, false); m_reg_m = 2; m_reg_t = 8; m_reg_f |= 0x20; }
    void BIT6h() { fz(m_reg_h & 0x40, false); m_reg_m = 2; m_reg_t = 8; m_reg_f |= 0x20; }
    void BIT6l() { fz(m_reg_l & 0x40, false); m_reg_m = 2; m_reg_t = 8; m_reg_f |= 0x20; }
    void BIT6m() { fz(m_MMU.readByte((m_reg_h << 8) + m_reg_l) & 0x40, false); m_reg_m = 3; m_reg_t = 12; m_reg_f |= 0x20; }

    void BIT7a() { fz(m_reg_a & 0x80, false); m_reg_m = 2; m_reg_t = 8; m_reg_f |= 0x20; }
    void BIT7b() { fz(m_reg_b & 0x80, false); m_reg_m = 2; m_reg_t = 8; m_reg_f |= 0x20; }
    void BIT7c() { fz(m_reg_c & 0x80, false); m_reg_m = 2; m_reg_t = 8; m_reg_f |= 0x20; }
    void BIT7d() { fz(m_reg_d & 0x80, false); m_reg_m = 2; m_reg_t = 8; m_reg_f |= 0x20; }
    void BIT7e() { fz(m_reg_e & 0x80, false); m_reg_m = 2; m_reg_t = 8; m_reg_f |= 0x20; }
    void BIT7h() { fz(m_reg_h & 0x80, false); m_reg_m = 2; m_reg_t = 8; m_reg_f |= 0x20; }
    void BIT7l() { fz(m_reg_l & 0x80, false); m_reg_m = 2; m_reg_t = 8; m_reg_f |= 0x20; }
    void BIT7m() { fz(m_MMU.readByte((m_reg_h << 8) + m_reg_l) & 0x80, false); m_reg_m = 3; m_reg_t = 12; m_reg_f |= 0x20; }

    //RESET
    void RES0a() { m_reg_a &= 0xFE; m_reg_m = 2; m_reg_t = 8; }
    void RES0b() { m_reg_b &= 0xFE; m_reg_m = 2; m_reg_t = 8; }
    void RES0c() { m_reg_c &= 0xFE; m_reg_m = 2; m_reg_t = 8; }
    void RES0d() { m_reg_d &= 0xFE; m_reg_m = 2; m_reg_t = 8; }
    void RES0e() { m_reg_e &= 0xFE; m_reg_m = 2; m_reg_t = 8; }
    void RES0h() { m_reg_h &= 0xFE; m_reg_m = 2; m_reg_t = 8; }
    void RES0l() { m_reg_l &= 0xFE; m_reg_m = 2; m_reg_t = 8; }
    void RES0m() { m_MMU.writeByte((m_reg_h << 8) + m_reg_l, m_MMU.readByte(((m_reg_h << 8) + m_reg_l)) & 0xFE); m_reg_m = 4; m_reg_t = 16; }

    void RES1a() { m_reg_a &= 0xFD; m_reg_m = 2; m_reg_t = 8; }
    void RES1b() { m_reg_b &= 0xFD; m_reg_m = 2; m_reg_t = 8; }
    void RES1c() { m_reg_c &= 0xFD; m_reg_m = 2; m_reg_t = 8; }
    void RES1d() { m_reg_d &= 0xFD; m_reg_m = 2; m_reg_t = 8; }
    void RES1e() { m_reg_e &= 0xFD; m_reg_m = 2; m_reg_t = 8; }
    void RES1h() { m_reg_h &= 0xFD; m_reg_m = 2; m_reg_t = 8; }
    void RES1l() { m_reg_l &= 0xFD; m_reg_m = 2; m_reg_t = 8; }
    void RES1m() { m_MMU.writeByte((m_reg_h << 8) + m_reg_l, m_MMU.readByte(((m_reg_h << 8) + m_reg_l)) & 0xFD); m_reg_m = 4; m_reg_t = 16; }

    void RES2a() { m_reg_a &= 0xFB; m_reg_m = 2; m_reg_t = 8; }
    void RES2b() { m_reg_b &= 0xFB; m_reg_m = 2; m_reg_t = 8; }
    void RES2c() { m_reg_c &= 0xFB; m_reg_m = 2; m_reg_t = 8; }
    void RES2d() { m_reg_d &= 0xFB; m_reg_m = 2; m_reg_t = 8; }
    void RES2e() { m_reg_e &= 0xFB; m_reg_m = 2; m_reg_t = 8; }
    void RES2h() { m_reg_h &= 0xFB; m_reg_m = 2; m_reg_t = 8; }
    void RES2l() { m_reg_l &= 0xFB; m_reg_m = 2; m_reg_t = 8; }
    void RES2m() { m_MMU.writeByte((m_reg_h << 8) + m_reg_l, m_MMU.readByte(((m_reg_h << 8) + m_reg_l)) & 0xFB); m_reg_m = 4; m_reg_t = 16; }\

    void RES3a() { m_reg_a &= 0xF7; m_reg_m = 2; m_reg_t = 8; }
    void RES3b() { m_reg_b &= 0xF7; m_reg_m = 2; m_reg_t = 8; }
    void RES3c() { m_reg_c &= 0xF7; m_reg_m = 2; m_reg_t = 8; }
    void RES3d() { m_reg_d &= 0xF7; m_reg_m = 2; m_reg_t = 8; }
    void RES3e() { m_reg_e &= 0xF7; m_reg_m = 2; m_reg_t = 8; }
    void RES3h() { m_reg_h &= 0xF7; m_reg_m = 2; m_reg_t = 8; }
    void RES3l() { m_reg_l &= 0xF7; m_reg_m = 2; m_reg_t = 8; }
    void RES3m() { m_MMU.writeByte((m_reg_h << 8) + m_reg_l, m_MMU.readByte(((m_reg_h << 8) + m_reg_l)) & 0xF7); m_reg_m = 4; m_reg_t = 16; }

    void RES4a() { m_reg_a &= 0xEF; m_reg_m = 2; m_reg_t = 8; }
    void RES4b() { m_reg_b &= 0xEF; m_reg_m = 2; m_reg_t = 8; }
    void RES4c() { m_reg_c &= 0xEF; m_reg_m = 2; m_reg_t = 8; }
    void RES4d() { m_reg_d &= 0xEF; m_reg_m = 2; m_reg_t = 8; }
    void RES4e() { m_reg_e &= 0xEF; m_reg_m = 2; m_reg_t = 8; }
    void RES4h() { m_reg_h &= 0xEF; m_reg_m = 2; m_reg_t = 8; }
    void RES4l() { m_reg_l &= 0xEF; m_reg_m = 2; m_reg_t = 8; }
    void RES4m() { m_MMU.writeByte((m_reg_h << 8) + m_reg_l, m_MMU.readByte(((m_reg_h << 8) + m_reg_l)) & 0xEF); m_reg_m = 4; m_reg_t = 16; }

    void RES5a() { m_reg_a &= 0xDF; m_reg_m = 2; m_reg_t = 8; }
    void RES5b() { m_reg_b &= 0xDF; m_reg_m = 2; m_reg_t = 8; }
    void RES5c() { m_reg_c &= 0xDF; m_reg_m = 2; m_reg_t = 8; }
    void RES5d() { m_reg_d &= 0xDF; m_reg_m = 2; m_reg_t = 8; }
    void RES5e() { m_reg_e &= 0xDF; m_reg_m = 2; m_reg_t = 8; }
    void RES5h() { m_reg_h &= 0xDF; m_reg_m = 2; m_reg_t = 8; }
    void RES5l() { m_reg_l &= 0xDF; m_reg_m = 2; m_reg_t = 8; }
    void RES5m() { m_MMU.writeByte((m_reg_h << 8) + m_reg_l, m_MMU.readByte(((m_reg_h << 8) + m_reg_l)) & 0xDF); m_reg_m = 4; m_reg_t = 16; }

    void RES6a() { m_reg_a &= 0xBF; m_reg_m = 2; m_reg_t = 8; }
    void RES6b() { m_reg_b &= 0xBF; m_reg_m = 2; m_reg_t = 8; }
    void RES6c() { m_reg_c &= 0xBF; m_reg_m = 2; m_reg_t = 8; }
    void RES6d() { m_reg_d &= 0xBF; m_reg_m = 2; m_reg_t = 8; }
    void RES6e() { m_reg_e &= 0xBF; m_reg_m = 2; m_reg_t = 8; }
    void RES6h() { m_reg_h &= 0xBF; m_reg_m = 2; m_reg_t = 8; }
    void RES6l() { m_reg_l &= 0xBF; m_reg_m = 2; m_reg_t = 8; }
    void RES6m() { m_MMU.writeByte((m_reg_h << 8) + m_reg_l, m_MMU.readByte(((m_reg_h << 8) + m_reg_l)) & 0xBF); m_reg_m = 4; m_reg_t = 16; }

    void RES7a() { m_reg_a &= 0x7F; m_reg_m = 2; m_reg_t = 8; }
    void RES7b() { m_reg_b &= 0x7F; m_reg_m = 2; m_reg_t = 8; }
    void RES7c() { m_reg_c &= 0x7F; m_reg_m = 2; m_reg_t = 8; }
    void RES7d() { m_reg_d &= 0x7F; m_reg_m = 2; m_reg_t = 8; }
    void RES7e() { m_reg_e &= 0x7F; m_reg_m = 2; m_reg_t = 8; }
    void RES7h() { m_reg_h &= 0x7F; m_reg_m = 2; m_reg_t = 8; }
    void RES7l() { m_reg_l &= 0x7F; m_reg_m = 2; m_reg_t = 8; }
    void RES7m() { m_MMU.writeByte((m_reg_h << 8) + m_reg_l, m_MMU.readByte(((m_reg_h << 8) + m_reg_l)) & 0x7F); m_reg_m = 4; m_reg_t = 16; }

    //SET
    void SET0a() { m_reg_a |= 0x01; m_reg_m = 2; m_reg_t = 8; }
    void SET0b() { m_reg_b |= 0x01; m_reg_m = 2; m_reg_t = 8; }
    void SET0c() { m_reg_c |= 0x01; m_reg_m = 2; m_reg_t = 8; }
    void SET0d() { m_reg_d |= 0x01; m_reg_m = 2; m_reg_t = 8; }
    void SET0e() { m_reg_e |= 0x01; m_reg_m = 2; m_reg_t = 8; }
    void SET0h() { m_reg_h |= 0x01; m_reg_m = 2; m_reg_t = 8; }
    void SET0l() { m_reg_l |= 0x01; m_reg_m = 2; m_reg_t = 8; }
    void SET0m() { m_MMU.writeByte((m_reg_h << 8) + m_reg_l, m_MMU.readByte(((m_reg_h << 8) + m_reg_l)) | 0x01); m_reg_m = 4; m_reg_t = 16; }

    void SET1a() { m_reg_a |= 0x02; m_reg_m = 2; m_reg_t = 8; }
    void SET1b() { m_reg_b |= 0x02; m_reg_m = 2; m_reg_t = 8; }
    void SET1c() { m_reg_c |= 0x02; m_reg_m = 2; m_reg_t = 8; }
    void SET1d() { m_reg_d |= 0x02; m_reg_m = 2; m_reg_t = 8; }
    void SET1e() { m_reg_e |= 0x02; m_reg_m = 2; m_reg_t = 8; }
    void SET1h() { m_reg_h |= 0x02; m_reg_m = 2; m_reg_t = 8; }
    void SET1l() { m_reg_l |= 0x02; m_reg_m = 2; m_reg_t = 8; }
    void SET1m() { m_MMU.writeByte((m_reg_h << 8) + m_reg_l, m_MMU.readByte(((m_reg_h << 8) + m_reg_l)) | 0x02); m_reg_m = 4; m_reg_t = 16; }

    void SET2a() { m_reg_a |= 0x04; m_reg_m = 2; m_reg_t = 8; }
    void SET2b() { m_reg_b |= 0x04; m_reg_m = 2; m_reg_t = 8; }
    void SET2c() { m_reg_c |= 0x04; m_reg_m = 2; m_reg_t = 8; }
    void SET2d() { m_reg_d |= 0x04; m_reg_m = 2; m_reg_t = 8; }
    void SET2e() { m_reg_e |= 0x04; m_reg_m = 2; m_reg_t = 8; }
    void SET2h() { m_reg_h |= 0x04; m_reg_m = 2; m_reg_t = 8; }
    void SET2l() { m_reg_l |= 0x04; m_reg_m = 2; m_reg_t = 8; }
    void SET2m() { m_MMU.writeByte((m_reg_h << 8) + m_reg_l, m_MMU.readByte(((m_reg_h << 8) + m_reg_l)) | 0x04); m_reg_m = 4; m_reg_t = 16; }\

    void SET3a() { m_reg_a |= 0x08; m_reg_m = 2; m_reg_t = 8; }
    void SET3b() { m_reg_b |= 0x08; m_reg_m = 2; m_reg_t = 8; }
    void SET3c() { m_reg_c |= 0x08; m_reg_m = 2; m_reg_t = 8; }
    void SET3d() { m_reg_d |= 0x08; m_reg_m = 2; m_reg_t = 8; }
    void SET3e() { m_reg_e |= 0x08; m_reg_m = 2; m_reg_t = 8; }
    void SET3h() { m_reg_h |= 0x08; m_reg_m = 2; m_reg_t = 8; }
    void SET3l() { m_reg_l |= 0x08; m_reg_m = 2; m_reg_t = 8; }
    void SET3m() { m_MMU.writeByte((m_reg_h << 8) + m_reg_l, m_MMU.readByte(((m_reg_h << 8) + m_reg_l)) | 0x08); m_reg_m = 4; m_reg_t = 16; }

    void SET4a() { m_reg_a |= 0x10; m_reg_m = 2; m_reg_t = 8; }
    void SET4b() { m_reg_b |= 0x10; m_reg_m = 2; m_reg_t = 8; }
    void SET4c() { m_reg_c |= 0x10; m_reg_m = 2; m_reg_t = 8; }
    void SET4d() { m_reg_d |= 0x10; m_reg_m = 2; m_reg_t = 8; }
    void SET4e() { m_reg_e |= 0x10; m_reg_m = 2; m_reg_t = 8; }
    void SET4h() { m_reg_h |= 0x10; m_reg_m = 2; m_reg_t = 8; }
    void SET4l() { m_reg_l |= 0x10; m_reg_m = 2; m_reg_t = 8; }
    void SET4m() { m_MMU.writeByte((m_reg_h << 8) + m_reg_l, m_MMU.readByte(((m_reg_h << 8) + m_reg_l)) | 0x10); m_reg_m = 4; m_reg_t = 16; }

    void SET5a() { m_reg_a |= 0x20; m_reg_m = 2; m_reg_t = 8; }
    void SET5b() { m_reg_b |= 0x20; m_reg_m = 2; m_reg_t = 8; }
    void SET5c() { m_reg_c |= 0x20; m_reg_m = 2; m_reg_t = 8; }
    void SET5d() { m_reg_d |= 0x20; m_reg_m = 2; m_reg_t = 8; }
    void SET5e() { m_reg_e |= 0x20; m_reg_m = 2; m_reg_t = 8; }
    void SET5h() { m_reg_h |= 0x20; m_reg_m = 2; m_reg_t = 8; }
    void SET5l() { m_reg_l |= 0x20; m_reg_m = 2; m_reg_t = 8; }
    void SET5m() { m_MMU.writeByte((m_reg_h << 8) + m_reg_l, m_MMU.readByte(((m_reg_h << 8) + m_reg_l)) | 0x20); m_reg_m = 4; m_reg_t = 16; }

    void SET6a() { m_reg_a |= 0x40; m_reg_m = 2; m_reg_t = 8; }
    void SET6b() { m_reg_b |= 0x40; m_reg_m = 2; m_reg_t = 8; }
    void SET6c() { m_reg_c |= 0x40; m_reg_m = 2; m_reg_t = 8; }
    void SET6d() { m_reg_d |= 0x40; m_reg_m = 2; m_reg_t = 8; }
    void SET6e() { m_reg_e |= 0x40; m_reg_m = 2; m_reg_t = 8; }
    void SET6h() { m_reg_h |= 0x40; m_reg_m = 2; m_reg_t = 8; }
    void SET6l() { m_reg_l |= 0x40; m_reg_m = 2; m_reg_t = 8; }
    void SET6m() { m_MMU.writeByte((m_reg_h << 8) + m_reg_l, m_MMU.readByte(((m_reg_h << 8) + m_reg_l)) | 0x40); m_reg_m = 4; m_reg_t = 16; }
    
    void SET7a() { m_reg_a |= 0x80; m_reg_m = 2; m_reg_t = 8; }
    void SET7b() { m_reg_b |= 0x80; m_reg_m = 2; m_reg_t = 8; }
    void SET7c() { m_reg_c |= 0x80; m_reg_m = 2; m_reg_t = 8; }
    void SET7d() { m_reg_d |= 0x80; m_reg_m = 2; m_reg_t = 8; }
    void SET7e() { m_reg_e |= 0x80; m_reg_m = 2; m_reg_t = 8; }
    void SET7h() { m_reg_h |= 0x80; m_reg_m = 2; m_reg_t = 8; }
    void SET7l() { m_reg_l |= 0x80; m_reg_m = 2; m_reg_t = 8; }
    void SET7m() { m_MMU.writeByte((m_reg_h << 8) + m_reg_l, m_MMU.readByte(((m_reg_h << 8) + m_reg_l)) | 0x80); m_reg_m = 4; m_reg_t = 16; }


    void RLA() { int ci = m_reg_f & 0x10 ? 1 : 0; int co = m_reg_a & 0x80 ? 0x10 : 0; m_reg_a = (m_reg_a << 1) + ci; m_reg_a &= 255; m_reg_f = co; m_reg_m = 1; m_reg_t = 4; }
    void RLCA() { int ci = m_reg_a & 0x80 ? 1 : 0; int co = m_reg_a & 0x80 ? 0x10 : 0; m_reg_a = (m_reg_a << 1) + ci; m_reg_a &= 255; m_reg_f = co; m_reg_m = 1; m_reg_t = 4; }
    void RRA() { int ci = m_reg_f & 0x10 ? 0x80 : 0; int co = m_reg_a & 1 ? 0x10 : 0; m_reg_a = (m_reg_a >> 1) + ci; m_reg_a &= 255; m_reg_f = co; m_reg_m = 1; m_reg_t = 4; }
    void RRCA() { int ci = m_reg_a & 0x80 ? 1 : 0; int co = m_reg_a & 1 ? 0x10 : 0; m_reg_a = (m_reg_a >> 1) + ci; m_reg_a &= 255; m_reg_f = co; m_reg_m = 1; m_reg_t = 4; }

    void RLr_a() { int ci = m_reg_f & 0x10 ? 1 : 0; int co = m_reg_a & 0x80 ? 0x10 : 0; m_reg_a = (m_reg_a << 1) + ci; m_reg_a &= 255; fzc(m_reg_a, false); m_reg_f = (m_reg_f & 0xEF) + co; m_reg_m = 2; m_reg_t = 8; }
    void RLr_b() { int ci = m_reg_f & 0x10 ? 1 : 0; int co = m_reg_b & 0x80 ? 0x10 : 0; m_reg_b = (m_reg_b << 1) + ci; m_reg_b &= 255; fzc(m_reg_b, false); m_reg_f = (m_reg_f & 0xEF) + co; m_reg_m = 2; m_reg_t = 8; }
    void RLr_c() { int ci = m_reg_f & 0x10 ? 1 : 0; int co = m_reg_c & 0x80 ? 0x10 : 0; m_reg_c = (m_reg_c << 1) + ci; m_reg_c &= 255; fzc(m_reg_c, false); m_reg_f = (m_reg_f & 0xEF) + co; m_reg_m = 2; m_reg_t = 8; }
    void RLr_d() { int ci = m_reg_f & 0x10 ? 1 : 0; int co = m_reg_d & 0x80 ? 0x10 : 0; m_reg_d = (m_reg_d << 1) + ci; m_reg_d &= 255; fzc(m_reg_d, false); m_reg_f = (m_reg_f & 0xEF) + co; m_reg_m = 2; m_reg_t = 8; }
    void RLr_e() { int ci = m_reg_f & 0x10 ? 1 : 0; int co = m_reg_e & 0x80 ? 0x10 : 0; m_reg_e = (m_reg_e << 1) + ci; m_reg_e &= 255; fzc(m_reg_e, false); m_reg_f = (m_reg_f & 0xEF) + co; m_reg_m = 2; m_reg_t = 8; }
    void RLr_h() { int ci = m_reg_f & 0x10 ? 1 : 0; int co = m_reg_h & 0x80 ? 0x10 : 0; m_reg_h = (m_reg_h << 1) + ci; m_reg_h &= 255; fzc(m_reg_h, false); m_reg_f = (m_reg_f & 0xEF) + co; m_reg_m = 2; m_reg_t = 8; }
    void RLr_l() { int ci = m_reg_f & 0x10 ? 1 : 0; int co = m_reg_l & 0x80 ? 0x10 : 0; m_reg_l = (m_reg_l << 1) + ci; m_reg_l &= 255; fzc(m_reg_l, false); m_reg_f = (m_reg_f & 0xEF) + co; m_reg_m = 2; m_reg_t = 8; }
    void RLHL() { int i = m_MMU.readByte((m_reg_h << 8) + m_reg_l); int ci = m_reg_f & 0x10 ? 1 : 0; int co = i & 0x80 ? 0x10 : 0; i = (i << 1) + ci; i &= 255; fzc(i, false); m_MMU.writeByte((m_reg_h << 8) + m_reg_l, i); m_reg_f = (m_reg_f & 0xEF) + co; m_reg_m = 4; m_reg_t = 16; }

    void RLCr_a() { int ci = m_reg_a & 0x80 ? 1 : 0; int co = m_reg_a & 0x80 ? 0x10 : 0; m_reg_a = (m_reg_a << 1) + ci; m_reg_a &= 255; fzc(m_reg_a, false); m_reg_f = (m_reg_f & 0xEF) + co; m_reg_m = 2; m_reg_t = 8; }
    void RLCr_b() { int ci = m_reg_b & 0x80 ? 1 : 0; int co = m_reg_b & 0x80 ? 0x10 : 0; m_reg_b = (m_reg_b << 1) + ci; m_reg_b &= 255; fzc(m_reg_b, false); m_reg_f = (m_reg_f & 0xEF) + co; m_reg_m = 2; m_reg_t = 8; }
    void RLCr_c() { int ci = m_reg_c & 0x80 ? 1 : 0; int co = m_reg_c & 0x80 ? 0x10 : 0; m_reg_c = (m_reg_c << 1) + ci; m_reg_c &= 255; fzc(m_reg_c, false); m_reg_f = (m_reg_f & 0xEF) + co; m_reg_m = 2; m_reg_t = 8; }
    void RLCr_d() { int ci = m_reg_d & 0x80 ? 1 : 0; int co = m_reg_d & 0x80 ? 0x10 : 0; m_reg_d = (m_reg_d << 1) + ci; m_reg_d &= 255; fzc(m_reg_d, false); m_reg_f = (m_reg_f & 0xEF) + co; m_reg_m = 2; m_reg_t = 8; }
    void RLCr_e() { int ci = m_reg_e & 0x80 ? 1 : 0; int co = m_reg_e & 0x80 ? 0x10 : 0; m_reg_e = (m_reg_e << 1) + ci; m_reg_e &= 255; fzc(m_reg_e, false); m_reg_f = (m_reg_f & 0xEF) + co; m_reg_m = 2; m_reg_t = 8; }
    void RLCr_h() { int ci = m_reg_h & 0x80 ? 1 : 0; int co = m_reg_h & 0x80 ? 0x10 : 0; m_reg_h = (m_reg_h << 1) + ci; m_reg_h &= 255; fzc(m_reg_h, false); m_reg_f = (m_reg_f & 0xEF) + co; m_reg_m = 2; m_reg_t = 8; }
    void RLCr_l() { int ci = m_reg_l & 0x80 ? 1 : 0; int co = m_reg_l & 0x80 ? 0x10 : 0; m_reg_l = (m_reg_l << 1) + ci; m_reg_l &= 255; fzc(m_reg_l, false); m_reg_f = (m_reg_f & 0xEF) + co; m_reg_m = 2; m_reg_t = 8; }
    void RLCHL() { int i = m_MMU.readByte((m_reg_h << 8) + m_reg_l); int ci = i & 0x80 ? 1 : 0; int co = i & 0x80 ? 0x10 : 0; i = (i << 1) + ci; i &= 255; fzc(i, false); m_MMU.writeByte((m_reg_h << 8) + m_reg_l, i); m_reg_f = (m_reg_f & 0xEF) + co; m_reg_m = 4; m_reg_t = 16; }

    void RRr_a() { int ci = m_reg_f & 0x10 ? 0x80 : 0; int co = m_reg_a & 1 ? 0x10 : 0; m_reg_a = (m_reg_a >> 1) + ci; m_reg_a &= 255; fzc(m_reg_a, false); m_reg_f = (m_reg_f & 0xEF) + co; m_reg_m = 2; m_reg_t = 8; }
    void RRr_b() { int ci = m_reg_f & 0x10 ? 0x80 : 0; int co = m_reg_b & 1 ? 0x10 : 0; m_reg_b = (m_reg_b >> 1) + ci; m_reg_b &= 255; fzc(m_reg_b, false); m_reg_f = (m_reg_f & 0xEF) + co; m_reg_m = 2; m_reg_t = 8; }
    void RRr_c() { int ci = m_reg_f & 0x10 ? 0x80 : 0; int co = m_reg_c & 1 ? 0x10 : 0; m_reg_c = (m_reg_c >> 1) + ci; m_reg_c &= 255; fzc(m_reg_c, false); m_reg_f = (m_reg_f & 0xEF) + co; m_reg_m = 2; m_reg_t = 8; }
    void RRr_d() { int ci = m_reg_f & 0x10 ? 0x80 : 0; int co = m_reg_d & 1 ? 0x10 : 0; m_reg_d = (m_reg_d >> 1) + ci; m_reg_d &= 255; fzc(m_reg_d, false); m_reg_f = (m_reg_f & 0xEF) + co; m_reg_m = 2; m_reg_t = 8; }
    void RRr_e() { int ci = m_reg_f & 0x10 ? 0x80 : 0; int co = m_reg_e & 1 ? 0x10 : 0; m_reg_e = (m_reg_e >> 1) + ci; m_reg_e &= 255; fzc(m_reg_e, false); m_reg_f = (m_reg_f & 0xEF) + co; m_reg_m = 2; m_reg_t = 8; }
    void RRr_h() { int ci = m_reg_f & 0x10 ? 0x80 : 0; int co = m_reg_h & 1 ? 0x10 : 0; m_reg_h = (m_reg_h >> 1) + ci; m_reg_h &= 255; fzc(m_reg_h, false); m_reg_f = (m_reg_f & 0xEF) + co; m_reg_m = 2; m_reg_t = 8; }
    void RRr_l() { int ci = m_reg_f & 0x10 ? 0x80 : 0; int co = m_reg_l & 1 ? 0x10 : 0; m_reg_l = (m_reg_l >> 1) + ci; m_reg_l &= 255; fzc(m_reg_l, false); m_reg_f = (m_reg_f & 0xEF) + co; m_reg_m = 2; m_reg_t = 8; }
    void RRHL() { int i = m_MMU.readByte((m_reg_h << 8) + m_reg_l); int ci = m_reg_f & 0x10 ? 0x80 : 0; int co = i & 1 ? 0x10 : 0; i = (i >> 1) + ci; i &= 255; fzc(i, false); m_MMU.writeByte((m_reg_h << 8) + m_reg_l, i); m_reg_f = (m_reg_f & 0xEF) + co; m_reg_m = 4; m_reg_t = 16; }

    void RRCr_a() { int ci = m_reg_a & 1 ? 0x80 : 0; int co = m_reg_a & 1 ? 0x10 : 0; m_reg_a = (m_reg_a >> 1) + ci; m_reg_a &= 255; fzc(m_reg_a, false); m_reg_f = (m_reg_f & 0xEF) + co; m_reg_m = 2; m_reg_t = 8; }
    void RRCr_b() { int ci = m_reg_b & 1 ? 0x80 : 0; int co = m_reg_b & 1 ? 0x10 : 0; m_reg_b = (m_reg_b >> 1) + ci; m_reg_b &= 255; fzc(m_reg_b, false); m_reg_f = (m_reg_f & 0xEF) + co; m_reg_m = 2; m_reg_t = 8; }
    void RRCr_c() { int ci = m_reg_c & 1 ? 0x80 : 0; int co = m_reg_c & 1 ? 0x10 : 0; m_reg_c = (m_reg_c >> 1) + ci; m_reg_c &= 255; fzc(m_reg_c, false); m_reg_f = (m_reg_f & 0xEF) + co; m_reg_m = 2; m_reg_t = 8; }
    void RRCr_d() { int ci = m_reg_d & 1 ? 0x80 : 0; int co = m_reg_d & 1 ? 0x10 : 0; m_reg_d = (m_reg_d >> 1) + ci; m_reg_d &= 255; fzc(m_reg_d, false); m_reg_f = (m_reg_f & 0xEF) + co; m_reg_m = 2; m_reg_t = 8; }
    void RRCr_e() { int ci = m_reg_e & 1 ? 0x80 : 0; int co = m_reg_e & 1 ? 0x10 : 0; m_reg_e = (m_reg_e >> 1) + ci; m_reg_e &= 255; fzc(m_reg_e, false); m_reg_f = (m_reg_f & 0xEF) + co; m_reg_m = 2; m_reg_t = 8; }
    void RRCr_h() { int ci = m_reg_h & 1 ? 0x80 : 0; int co = m_reg_h & 1 ? 0x10 : 0; m_reg_h = (m_reg_h >> 1) + ci; m_reg_h &= 255; fzc(m_reg_h, false); m_reg_f = (m_reg_f & 0xEF) + co; m_reg_m = 2; m_reg_t = 8; }
    void RRCr_l() { int ci = m_reg_l & 1 ? 0x80 : 0; int co = m_reg_l & 1 ? 0x10 : 0; m_reg_l = (m_reg_l >> 1) + ci; m_reg_l &= 255; fzc(m_reg_l, false); m_reg_f = (m_reg_f & 0xEF) + co; m_reg_m = 2; m_reg_t = 8; }
    void RRCHL() { int i = m_MMU.readByte((m_reg_h << 8) + m_reg_l); int ci = i & 1 ? 0x80 : 0; int co = i & 1 ? 0x10 : 0; i = (i >> 1) + ci; i &= 255; fzc(i, false); m_MMU.writeByte((m_reg_h << 8) + m_reg_l, i); m_reg_f = (m_reg_f & 0xEF) + co; m_reg_m = 4; m_reg_t = 16; }

    void SLAr_a() { int co = m_reg_a & 0x80 ? 0x10 : 0; m_reg_a = (m_reg_a << 1) & 255; fzc(m_reg_a, false); m_reg_f = (m_reg_f & 0xEF) + co; m_reg_m = 2; m_reg_t = 8; }
    void SLAr_b() { int co = m_reg_b & 0x80 ? 0x10 : 0; m_reg_b = (m_reg_b << 1) & 255; fzc(m_reg_b, false); m_reg_f = (m_reg_f & 0xEF) + co; m_reg_m = 2; m_reg_t = 8; }
    void SLAr_c() { int co = m_reg_c & 0x80 ? 0x10 : 0; m_reg_c = (m_reg_c << 1) & 255; fzc(m_reg_c, false); m_reg_f = (m_reg_f & 0xEF) + co; m_reg_m = 2; m_reg_t = 8; }
    void SLAr_d() { int co = m_reg_d & 0x80 ? 0x10 : 0; m_reg_d = (m_reg_d << 1) & 255; fzc(m_reg_d, false); m_reg_f = (m_reg_f & 0xEF) + co; m_reg_m = 2; m_reg_t = 8; }
    void SLAr_e() { int co = m_reg_e & 0x80 ? 0x10 : 0; m_reg_e = (m_reg_e << 1) & 255; fzc(m_reg_e, false); m_reg_f = (m_reg_f & 0xEF) + co; m_reg_m = 2; m_reg_t = 8; }
    void SLAr_h() { int co = m_reg_h & 0x80 ? 0x10 : 0; m_reg_h = (m_reg_h << 1) & 255; fzc(m_reg_h, false); m_reg_f = (m_reg_f & 0xEF) + co; m_reg_m = 2; m_reg_t = 8; }
    void SLAr_l() { int co = m_reg_l & 0x80 ? 0x10 : 0; m_reg_l = (m_reg_l << 1) & 255; fzc(m_reg_l, false); m_reg_f = (m_reg_f & 0xEF) + co; m_reg_m = 2; m_reg_t = 8; }

    void SLLr_a() { int co = m_reg_a & 0x80 ? 0x10 : 0; m_reg_a = (m_reg_a << 1) & 255 + 1; fzc(m_reg_a, false); m_reg_f = (m_reg_f & 0xEF) + co; m_reg_m = 2; m_reg_t = 8; }
    void SLLr_b() { int co = m_reg_b & 0x80 ? 0x10 : 0; m_reg_b = (m_reg_b << 1) & 255 + 1; fzc(m_reg_b, false); m_reg_f = (m_reg_f & 0xEF) + co; m_reg_m = 2; m_reg_t = 8; }
    void SLLr_c() { int co = m_reg_c & 0x80 ? 0x10 : 0; m_reg_c = (m_reg_c << 1) & 255 + 1; fzc(m_reg_c, false); m_reg_f = (m_reg_f & 0xEF) + co; m_reg_m = 2; m_reg_t = 8; }
    void SLLr_d() { int co = m_reg_d & 0x80 ? 0x10 : 0; m_reg_d = (m_reg_d << 1) & 255 + 1; fzc(m_reg_d, false); m_reg_f = (m_reg_f & 0xEF) + co; m_reg_m = 2; m_reg_t = 8; }
    void SLLr_e() { int co = m_reg_e & 0x80 ? 0x10 : 0; m_reg_e = (m_reg_e << 1) & 255 + 1; fzc(m_reg_e, false); m_reg_f = (m_reg_f & 0xEF) + co; m_reg_m = 2; m_reg_t = 8; }
    void SLLr_h() { int co = m_reg_h & 0x80 ? 0x10 : 0; m_reg_h = (m_reg_h << 1) & 255 + 1; fzc(m_reg_h, false); m_reg_f = (m_reg_f & 0xEF) + co; m_reg_m = 2; m_reg_t = 8; }
    void SLLr_l() { int co = m_reg_l & 0x80 ? 0x10 : 0; m_reg_l = (m_reg_l << 1) & 255 + 1; fzc(m_reg_l, false); m_reg_f = (m_reg_f & 0xEF) + co; m_reg_m = 2; m_reg_t = 8; }

    void SRAr_a() { int ci = m_reg_a & 0x80; int co = m_reg_a & 1 ? 0x10 : 0; m_reg_a = ((m_reg_a >> 1) + ci) & 255; fzc(m_reg_a, false); m_reg_f = (m_reg_f & 0xEF) + co; m_reg_m = 2; m_reg_m = 8; }
    void SRAr_b() { int ci = m_reg_b & 0x80; int co = m_reg_b & 1 ? 0x10 : 0; m_reg_b = ((m_reg_b >> 1) + ci) & 255; fzc(m_reg_b, false); m_reg_f = (m_reg_f & 0xEF) + co; m_reg_m = 2; m_reg_m = 8; }
    void SRAr_c() { int ci = m_reg_c & 0x80; int co = m_reg_c & 1 ? 0x10 : 0; m_reg_c = ((m_reg_c >> 1) + ci) & 255; fzc(m_reg_c, false); m_reg_f = (m_reg_f & 0xEF) + co; m_reg_m = 2; m_reg_m = 8; }
    void SRAr_d() { int ci = m_reg_d & 0x80; int co = m_reg_d & 1 ? 0x10 : 0; m_reg_d = ((m_reg_d >> 1) + ci) & 255; fzc(m_reg_d, false); m_reg_f = (m_reg_f & 0xEF) + co; m_reg_m = 2; m_reg_m = 8; }
    void SRAr_e() { int ci = m_reg_e & 0x80; int co = m_reg_e & 1 ? 0x10 : 0; m_reg_e = ((m_reg_e >> 1) + ci) & 255; fzc(m_reg_e, false); m_reg_f = (m_reg_f & 0xEF) + co; m_reg_m = 2; m_reg_m = 8; }
    void SRAr_h() { int ci = m_reg_h & 0x80; int co = m_reg_h & 1 ? 0x10 : 0; m_reg_h = ((m_reg_h >> 1) + ci) & 255; fzc(m_reg_h, false); m_reg_f = (m_reg_f & 0xEF) + co; m_reg_m = 2; m_reg_m = 8; }
    void SRAr_l() { int ci = m_reg_l & 0x80; int co = m_reg_l & 1 ? 0x10 : 0; m_reg_l = ((m_reg_l >> 1) + ci) & 255; fzc(m_reg_l, false); m_reg_f = (m_reg_f & 0xEF) + co; m_reg_m = 2; m_reg_m = 8; }

    void SRLr_a() { int co = m_reg_a & 1 ? 0x10 : 0; m_reg_a = (m_reg_a >> 1) & 255; fzc(m_reg_a, false); m_reg_f = (m_reg_f & 0xEF) + co; m_reg_m = 2; m_reg_m = 8; }
    void SRLr_b() { int co = m_reg_b & 1 ? 0x10 : 0; m_reg_b = (m_reg_b >> 1) & 255; fzc(m_reg_b, false); m_reg_f = (m_reg_f & 0xEF) + co; m_reg_m = 2; m_reg_m = 8; }
    void SRLr_c() { int co = m_reg_c & 1 ? 0x10 : 0; m_reg_c = (m_reg_c >> 1) & 255; fzc(m_reg_c, false); m_reg_f = (m_reg_f & 0xEF) + co; m_reg_m = 2; m_reg_m = 8; }
    void SRLr_d() { int co = m_reg_d & 1 ? 0x10 : 0; m_reg_d = (m_reg_d >> 1) & 255; fzc(m_reg_d, false); m_reg_f = (m_reg_f & 0xEF) + co; m_reg_m = 2; m_reg_m = 8; }
    void SRLr_e() { int co = m_reg_e & 1 ? 0x10 : 0; m_reg_e = (m_reg_e >> 1) & 255; fzc(m_reg_e, false); m_reg_f = (m_reg_f & 0xEF) + co; m_reg_m = 2; m_reg_m = 8; }
    void SRLr_h() { int co = m_reg_h & 1 ? 0x10 : 0; m_reg_h = (m_reg_h >> 1) & 255; fzc(m_reg_h, false); m_reg_f = (m_reg_f & 0xEF) + co; m_reg_m = 2; m_reg_m = 8; }
    void SRLr_l() { int co = m_reg_l & 1 ? 0x10 : 0; m_reg_l = (m_reg_l >> 1) & 255; fzc(m_reg_l, false); m_reg_f = (m_reg_f & 0xEF) + co; m_reg_m = 2; m_reg_m = 8; }

    void CPL() { m_reg_a = (~m_reg_a) & 255; m_reg_m = 1; m_reg_t = 4; m_reg_f |= 0x60; }
    void NEG() { m_reg_a = 0 - m_reg_a; fzc(m_reg_a, true); if (m_reg_a & 0x100) m_reg_f |= 0x10; m_reg_a &= 255; m_reg_m = 2; m_reg_t = 8; }

    void CCF() {
      int ci = m_reg_f & 0x10 ? 0 : 0x10;
      m_reg_f = (m_reg_f & 0x8F) + ci;
      m_reg_m = 1;
      m_reg_t = 4;
    }
    void SCF() {
      m_reg_f |= 0x10; //set C
      m_reg_f &= 0x9F; //reset N and H
      m_reg_m = 1;
      m_reg_t = 4;
    }

    //STACK
    void PUSHBC() { m_reg_sp--; m_MMU.writeByte(m_reg_sp, m_reg_b); m_reg_sp--; m_MMU.writeByte(m_reg_sp, m_reg_c); m_reg_m = 3; m_reg_t = 12; }
    void PUSHDE() { m_reg_sp--; m_MMU.writeByte(m_reg_sp, m_reg_d); m_reg_sp--; m_MMU.writeByte(m_reg_sp, m_reg_e); m_reg_m = 3; m_reg_t = 12; }
    void PUSHHL() { m_reg_sp--; m_MMU.writeByte(m_reg_sp, m_reg_h); m_reg_sp--; m_MMU.writeByte(m_reg_sp, m_reg_l); m_reg_m = 3; m_reg_t = 12; }
    void PUSHAF() { m_reg_sp--; m_MMU.writeByte(m_reg_sp, m_reg_a); m_reg_sp--; m_MMU.writeByte(m_reg_sp, m_reg_f); m_reg_m = 3; m_reg_t = 12; }

    void POPBC() { m_reg_c = m_MMU.readByte(m_reg_sp); m_reg_sp++; m_reg_b = m_MMU.readByte(m_reg_sp); m_reg_sp++; m_reg_m = 3; m_reg_t = 12; }
    void POPDE() { m_reg_e = m_MMU.readByte(m_reg_sp); m_reg_sp++; m_reg_d = m_MMU.readByte(m_reg_sp); m_reg_sp++; m_reg_m = 3; m_reg_t = 12; }
    void POPHL() { m_reg_l = m_MMU.readByte(m_reg_sp); m_reg_sp++; m_reg_h = m_MMU.readByte(m_reg_sp); m_reg_sp++; m_reg_m = 3; m_reg_t = 12; }
    void POPAF() { m_reg_f = m_MMU.readByte(m_reg_sp); m_reg_sp++; m_reg_a = m_MMU.readByte(m_reg_sp); m_reg_sp++; m_reg_m = 3; m_reg_t = 12; }

    //JUMP
    void JPnn() { m_reg_pc = m_MMU.readWord(m_reg_pc); m_reg_m = 3; m_reg_t = 12; }
    void JPHL() { m_reg_pc = (m_reg_h << 8) + m_reg_l; m_reg_m = 1; m_reg_t = 4; }
    void JPNZnn() { m_reg_m = 3; m_reg_t = 12; if ((m_reg_f &= 0x80) == 0x00) { m_reg_pc = m_MMU.readWord(m_reg_pc); m_reg_m++; m_reg_t += 4; } else m_reg_pc += 2; }
    void JPZnn() { m_reg_m = 3; m_reg_t = 12; if ((m_reg_f &= 0x80) == 0x80) { m_reg_pc = m_MMU.readWord(m_reg_pc); m_reg_m++; m_reg_t += 4; } else m_reg_pc += 2; }
    void JPNCnn() { m_reg_m = 3; m_reg_t = 12; if ((m_reg_f &= 0x10) == 0x00) { m_reg_pc = m_MMU.readWord(m_reg_pc); m_reg_m++; m_reg_t += 4; } else m_reg_pc += 2; }
    void JPCnn() { m_reg_m = 3; m_reg_t = 12; if ((m_reg_f &= 0x10) == 0x10) { m_reg_pc = m_MMU.readWord(m_reg_pc); m_reg_m++; m_reg_t += 4; } else m_reg_pc += 2; }

    void JRn() { int i = m_MMU.readByte(m_reg_pc); if (i > 127) i = -((~i + 1) & 255); m_reg_pc++; m_reg_m = 2; m_reg_t = 8; m_reg_pc += i; m_reg_m++; m_reg_t += 4; }
    void JRNZn() { int i = m_MMU.readByte(m_reg_pc); if (i > 127) i = -((~i + 1) & 255); m_reg_pc++; m_reg_m = 2; m_reg_t = 8; if ((m_reg_f & 0x80) == 0x00) { m_reg_pc += i; m_reg_m++; m_reg_t += 4; } }
    void JRZn() { int i = m_MMU.readByte(m_reg_pc); if (i > 127) i = -((~i + 1) & 255); m_reg_pc++; m_reg_m = 2; m_reg_t = 8; if ((m_reg_f & 0x80) == 0x80) { m_reg_pc += i; m_reg_m++; m_reg_t += 4; } }
    void JRNCn() { int i = m_MMU.readByte(m_reg_pc); if (i > 127) i = -((~i + 1) & 255); m_reg_pc++; m_reg_m = 2; m_reg_t = 8; if ((m_reg_f & 0x10) == 0x00) { m_reg_pc += i; m_reg_m++; m_reg_t += 4; } }
    void JRCn() { int i = m_MMU.readByte(m_reg_pc); if (i > 127) i = -((~i + 1) & 255); m_reg_pc++; m_reg_m = 2; m_reg_t = 8; if ((m_reg_f & 0x10) == 0x10) { m_reg_pc += i; m_reg_m++; m_reg_t += 4; } }

    void DJNZn() { int i = m_MMU.readByte(m_reg_pc); if (i > 127) i = -((~i + 1) & 255); m_reg_pc++; m_reg_m = 2; m_reg_t = 8; m_reg_b--; if (m_reg_b) { m_reg_pc += i; m_reg_m++; m_reg_t += 4; } }

    void CALLnn() { m_reg_sp -= 2; m_MMU.writeWord(m_reg_sp, m_reg_pc + 2); m_reg_pc = m_MMU.readWord(m_reg_pc); m_reg_m = 5; m_reg_t = 20; }
    void CALLNZnn() { m_reg_m = 3; m_reg_t = 12; if ((m_reg_f & 0x80) == 0x00) { m_reg_sp -= 2; m_MMU.writeWord(m_reg_sp, m_reg_pc + 2); m_reg_pc = m_MMU.readWord(m_reg_pc); m_reg_m += 2; m_reg_t += 8; } else m_reg_pc += 2; }
    void CALLZnn() { m_reg_m = 3; m_reg_t = 12; if ((m_reg_f & 0x80) == 0x80) { m_reg_sp -= 2; m_MMU.writeWord(m_reg_sp, m_reg_pc + 2); m_reg_pc = m_MMU.readWord(m_reg_pc); m_reg_m += 2; m_reg_t += 8; } else m_reg_pc += 2; }
    void CALLNCnn() { m_reg_m = 3; m_reg_t = 12; if ((m_reg_f & 0x10) == 0x00) { m_reg_sp -= 2; m_MMU.writeWord(m_reg_sp, m_reg_pc + 2); m_reg_pc = m_MMU.readWord(m_reg_pc); m_reg_m += 2; m_reg_t += 8; } else m_reg_pc += 2; }
    void CALLCnn() { m_reg_m = 3; m_reg_t = 12; if ((m_reg_f & 0x10) == 0x10) { m_reg_sp -= 2; m_MMU.writeWord(m_reg_sp, m_reg_pc + 2); m_reg_pc = m_MMU.readWord(m_reg_pc); m_reg_m += 2; m_reg_t += 8; } else m_reg_pc += 2; }

    void RET() { m_reg_pc = m_MMU.readWord(m_reg_sp); m_reg_sp += 2; m_reg_m = 3; m_reg_t = 12; }
    void RETI() { m_reg_ime = 1; m_reg_pc = m_MMU.readWord(m_reg_sp); m_reg_sp += 2; m_reg_m = 3; m_reg_t = 12; }
    void RETNZ() { m_reg_m = 1; m_reg_t = 4; if ((m_reg_f & 0x80) == 0x00) { m_reg_pc = m_MMU.readWord(m_reg_sp); m_reg_sp += 2; m_reg_m += 2; m_reg_t += 8; } }
    void RETZ() { m_reg_m = 1; m_reg_t = 4; if ((m_reg_f & 0x80) == 0x80) { m_reg_pc = m_MMU.readWord(m_reg_sp); m_reg_sp += 2; m_reg_m += 2; m_reg_t += 8; } }
    void RETNC() { m_reg_m = 1; m_reg_t = 4; if ((m_reg_f & 0x10) == 0x00) { m_reg_pc = m_MMU.readWord(m_reg_sp); m_reg_sp += 2; m_reg_m += 2; m_reg_t += 8; } }
    void RETC() { m_reg_m = 1; m_reg_t = 4; if ((m_reg_f & 0x10) == 0x10) { m_reg_pc = m_MMU.readWord(m_reg_sp); m_reg_sp += 2; m_reg_m += 2; m_reg_t += 8; } }

    void RST00() { m_reg_sp -= 2; m_MMU.writeWord(m_reg_sp, m_reg_pc); m_reg_pc = 0x00; m_reg_m = 3; m_reg_t = 12; }
    void RST08() { m_reg_sp -= 2; m_MMU.writeWord(m_reg_sp, m_reg_pc); m_reg_pc = 0x08; m_reg_m = 3; m_reg_t = 12; }
    void RST10() { m_reg_sp -= 2; m_MMU.writeWord(m_reg_sp, m_reg_pc); m_reg_pc = 0x10; m_reg_m = 3; m_reg_t = 12; }
    void RST18() { m_reg_sp -= 2; m_MMU.writeWord(m_reg_sp, m_reg_pc); m_reg_pc = 0x18; m_reg_m = 3; m_reg_t = 12; }
    void RST20() { m_reg_sp -= 2; m_MMU.writeWord(m_reg_sp, m_reg_pc); m_reg_pc = 0x20; m_reg_m = 3; m_reg_t = 12; }
    void RST28() { m_reg_sp -= 2; m_MMU.writeWord(m_reg_sp, m_reg_pc); m_reg_pc = 0x28; m_reg_m = 3; m_reg_t = 12; }
    void RST30() { m_reg_sp -= 2; m_MMU.writeWord(m_reg_sp, m_reg_pc); m_reg_pc = 0x30; m_reg_m = 3; m_reg_t = 12; }
    void RST38() { m_reg_sp -= 2; m_MMU.writeWord(m_reg_sp, m_reg_pc); m_reg_pc = 0x38; m_reg_m = 3; m_reg_t = 12; }

    void NOP() { m_reg_m = 1; m_reg_t = 4; }
    void HALT() { m_halt = 1; m_reg_m = 1; m_reg_t = 4; }
    void STOP() { m_reg_m = 1; m_reg_t = 4; }

    void DI() { m_reg_ime = 0; m_reg_m = 1; m_reg_t = 4; }
    void EI() { m_reg_ime = 1; m_reg_m = 1; m_reg_t = 4; }

    //not implemented yet..
    void LDmmSP() { m_reg_m = 1; m_reg_t = 4; }

    //extended instruction set
    //read next byte, it maps to the cb set
    void MAPcb() {
      int next = m_MMU.readByte(m_reg_pc);
      m_reg_pc++;
      m_reg_pc &= 65535;
      if (next < 256) {
        (this->*m_cbmap[next])();
      }
    }

    void XX() { int opc = m_reg_pc - 1; m_stop = 1; }

    //clear flags and set zero flag and subtraction flag
    void fzc(int i, bool subtraction) { m_reg_f = 0; if (!(i & 255)) m_reg_f |= 0x80; if (subtraction) m_reg_f |= 0x40; }
    //don't clear flags, just set zero and subtraction
    void fz(int i, bool subtraction) {
      if (!(i & 255)) {
        m_reg_f |= 0x80;
      } else{
        m_reg_f &= 0x7F;
      }
      if (subtraction) {
        m_reg_f |= 0x40;
      } else {
        m_reg_f &= 0xBF;
      }
    }

    void(gb::CPU::*m_opmap[256])() = {
      &gb::CPU::NOP,
      &gb::CPU::LDBCnn,
      &gb::CPU::LDBCmA,
      &gb::CPU::INCBC,
      &gb::CPU::INCr_b,
      &gb::CPU::DECr_b,
      &gb::CPU::LDrn_b,
      &gb::CPU::RLCA,
      &gb::CPU::LDmmSP,
      &gb::CPU::ADDHLBC,
      &gb::CPU::LDABCm,
      &gb::CPU::DECBC,
      &gb::CPU::INCr_c,
      &gb::CPU::DECr_c,
      &gb::CPU::LDrn_c,
      &gb::CPU::RRCA,
      //0x10
      &gb::CPU::STOP, // STOP 0 was DJNZn - I don't know why
      &gb::CPU::LDDEnn,
      &gb::CPU::LDDEmA,
      &gb::CPU::INCDE,
      &gb::CPU::INCr_d,
      &gb::CPU::DECr_d,
      &gb::CPU::LDrn_d,
      &gb::CPU::RLA,
      &gb::CPU::JRn,
      &gb::CPU::ADDHLDE,
      &gb::CPU::LDADEm,
      &gb::CPU::DECDE,
      &gb::CPU::INCr_e,
      &gb::CPU::DECr_e,
      &gb::CPU::LDrn_e,
      &gb::CPU::RRA,
      //0x20
      &gb::CPU::JRNZn,
      &gb::CPU::LDHLnn,
      &gb::CPU::LDHLIA,
      &gb::CPU::INCHL,
      &gb::CPU::INCr_h,
      &gb::CPU::DECr_h,
      &gb::CPU::LDrn_h,
      &gb::CPU::DAA,
      &gb::CPU::JRZn,
      &gb::CPU::ADDHLHL,
      &gb::CPU::LDAHLI,
      &gb::CPU::DECHL,
      &gb::CPU::INCr_l,
      &gb::CPU::DECr_l,
      &gb::CPU::LDrn_l,
      &gb::CPU::CPL,
      //0x30
      &gb::CPU::JRNCn,
      &gb::CPU::LDSPnn,
      &gb::CPU::LDHLDA,
      &gb::CPU::INCSP,
      &gb::CPU::INCHLm,
      &gb::CPU::DECHLm,
      &gb::CPU::LDHLmn,
      &gb::CPU::SCF,
      &gb::CPU::JRCn,
      &gb::CPU::ADDHLSP,
      &gb::CPU::LDAHLD,
      &gb::CPU::DECSP,
      &gb::CPU::INCr_a,
      &gb::CPU::DECr_a,
      &gb::CPU::LDrn_a,
      &gb::CPU::CCF,
      //0x40
      &gb::CPU::LDrr_bb,
      &gb::CPU::LDrr_bc,
      &gb::CPU::LDrr_bd,
      &gb::CPU::LDrr_be,
      &gb::CPU::LDrr_bh,
      &gb::CPU::LDrr_bl,
      &gb::CPU::LDrHLm_b,
      &gb::CPU::LDrr_ba,
      &gb::CPU::LDrr_cb,
      &gb::CPU::LDrr_cc,
      &gb::CPU::LDrr_cd,
      &gb::CPU::LDrr_ce,
      &gb::CPU::LDrr_ch,
      &gb::CPU::LDrr_cl,
      &gb::CPU::LDrHLm_c,
      &gb::CPU::LDrr_ca,
      //0x50
      &gb::CPU::LDrr_db,
      &gb::CPU::LDrr_dc,
      &gb::CPU::LDrr_dd,
      &gb::CPU::LDrr_de,
      &gb::CPU::LDrr_dh,
      &gb::CPU::LDrr_dl,
      &gb::CPU::LDrHLm_d,
      &gb::CPU::LDrr_da,
      &gb::CPU::LDrr_eb,
      &gb::CPU::LDrr_ec,
      &gb::CPU::LDrr_ed,
      &gb::CPU::LDrr_ee,
      &gb::CPU::LDrr_eh,
      &gb::CPU::LDrr_el,
      &gb::CPU::LDrHLm_e,
      &gb::CPU::LDrr_ea,
      //0x60
      &gb::CPU::LDrr_hb,
      &gb::CPU::LDrr_hc,
      &gb::CPU::LDrr_hd,
      &gb::CPU::LDrr_he,
      &gb::CPU::LDrr_hh,
      &gb::CPU::LDrr_hl,
      &gb::CPU::LDrHLm_h,
      &gb::CPU::LDrr_ha,
      &gb::CPU::LDrr_lb,
      &gb::CPU::LDrr_lc,
      &gb::CPU::LDrr_ld,
      &gb::CPU::LDrr_le,
      &gb::CPU::LDrr_lh,
      &gb::CPU::LDrr_ll,
      &gb::CPU::LDrHLm_l,
      &gb::CPU::LDrr_la,
      //0x70
      &gb::CPU::LDHLmr_b,
      &gb::CPU::LDHLmr_c,
      &gb::CPU::LDHLmr_d,
      &gb::CPU::LDHLmr_e,
      &gb::CPU::LDHLmr_h,
      &gb::CPU::LDHLmr_l,
      &gb::CPU::HALT,
      &gb::CPU::LDHLmr_a,
      &gb::CPU::LDrr_ab,
      &gb::CPU::LDrr_ac,
      &gb::CPU::LDrr_ad,
      &gb::CPU::LDrr_ae,
      &gb::CPU::LDrr_ah,
      &gb::CPU::LDrr_al,
      &gb::CPU::LDrHLm_a,
      &gb::CPU::LDrr_aa,
      //0x80
      &gb::CPU::ADDr_b,
      &gb::CPU::ADDr_c,
      &gb::CPU::ADDr_d,
      &gb::CPU::ADDr_e,
      &gb::CPU::ADDr_h,
      &gb::CPU::ADDr_l,
      &gb::CPU::ADDHL,
      &gb::CPU::ADDr_a,
      &gb::CPU::ADCr_b,
      &gb::CPU::ADCr_c,
      &gb::CPU::ADCr_d,
      &gb::CPU::ADCr_e,
      &gb::CPU::ADCr_h,
      &gb::CPU::ADCr_l,
      &gb::CPU::ADCHL,
      &gb::CPU::ADCr_a,
      //0x90
      &gb::CPU::SUBr_b,
      &gb::CPU::SUBr_c,
      &gb::CPU::SUBr_d,
      &gb::CPU::SUBr_e,
      &gb::CPU::SUBr_h,
      &gb::CPU::SUBr_l,
      &gb::CPU::SUBHL,
      &gb::CPU::SUBr_a,
      &gb::CPU::SBCr_b,
      &gb::CPU::SBCr_c,
      &gb::CPU::SBCr_d,
      &gb::CPU::SBCr_e,
      &gb::CPU::SBCr_h,
      &gb::CPU::SBCr_l,
      &gb::CPU::SBCHL,
      &gb::CPU::SBCr_a,
      //0xA0
      &gb::CPU::ANDr_b,
      &gb::CPU::ANDr_c,
      &gb::CPU::ANDr_d,
      &gb::CPU::ANDr_e,
      &gb::CPU::ANDr_h,
      &gb::CPU::ANDr_l,
      &gb::CPU::ANDHL,
      &gb::CPU::ANDr_a,
      &gb::CPU::XORr_b,
      &gb::CPU::XORr_c,
      &gb::CPU::XORr_d,
      &gb::CPU::XORr_e,
      &gb::CPU::XORr_h,
      &gb::CPU::XORr_l,
      &gb::CPU::XORHL,
      &gb::CPU::XORr_a,
      //0xB0
      &gb::CPU::ORr_b,
      &gb::CPU::ORr_c,
      &gb::CPU::ORr_d,
      &gb::CPU::ORr_e,
      &gb::CPU::ORr_h,
      &gb::CPU::ORr_l,
      &gb::CPU::ORHL,
      &gb::CPU::ORr_a,
      &gb::CPU::CPr_b,
      &gb::CPU::CPr_c,
      &gb::CPU::CPr_d,
      &gb::CPU::CPr_e,
      &gb::CPU::CPr_h,
      &gb::CPU::CPr_l,
      &gb::CPU::CPHL,
      &gb::CPU::CPr_a,
      //0xC0
      &gb::CPU::RETNZ,
      &gb::CPU::POPBC,
      &gb::CPU::JPNZnn,
      &gb::CPU::JPnn,
      &gb::CPU::CALLNZnn,
      &gb::CPU::PUSHBC,
      &gb::CPU::ADDn,
      &gb::CPU::RST00,
      &gb::CPU::RETZ,
      &gb::CPU::RET,
      &gb::CPU::JPZnn,
      &gb::CPU::MAPcb,  //Extension opcode
      &gb::CPU::CALLZnn,
      &gb::CPU::CALLnn,
      &gb::CPU::ADCn,
      &gb::CPU::RST08,
      //0xD0
      &gb::CPU::RETNC,
      &gb::CPU::POPDE,
      &gb::CPU::JPNCnn,
      &gb::CPU::XX,
      &gb::CPU::CALLNCnn,
      &gb::CPU::PUSHDE,
      &gb::CPU::SUBn,
      &gb::CPU::RST10,
      &gb::CPU::RETC,
      &gb::CPU::RETI,
      &gb::CPU::JPCnn,
      &gb::CPU::XX,
      &gb::CPU::CALLCnn,
      &gb::CPU::XX,
      &gb::CPU::SBCn,
      &gb::CPU::RST18,
      //0xE0
      &gb::CPU::LDIOnA,
      &gb::CPU::POPHL,
      &gb::CPU::LDIOCA,
      &gb::CPU::XX,
      &gb::CPU::XX,
      &gb::CPU::PUSHHL,
      &gb::CPU::ANDn,
      &gb::CPU::RST20,
      &gb::CPU::ADDSPn,
      &gb::CPU::JPHL,
      &gb::CPU::LDmmA,
      &gb::CPU::XX,
      &gb::CPU::XX,
      &gb::CPU::XX,
      &gb::CPU::XORn,
      &gb::CPU::RST28,
      //0xF0
      &gb::CPU::LDAIOn,
      &gb::CPU::POPAF,
      &gb::CPU::LDAIOC,
      &gb::CPU::DI,
      &gb::CPU::XX,
      &gb::CPU::PUSHAF,
      &gb::CPU::ORn,
      &gb::CPU::RST30,
      &gb::CPU::LDHLSPn,
      &gb::CPU::LDSPHL,
      &gb::CPU::LDAmm,
      &gb::CPU::EI,
      &gb::CPU::XX,
      &gb::CPU::XX,
      &gb::CPU::CPn,
      &gb::CPU::RST38
    };

    void(gb::CPU::*m_cbmap[256])() = {
      //0x00
      &gb::CPU::RLCr_b,
      &gb::CPU::RLCr_c,
      &gb::CPU::RLCr_d,
      &gb::CPU::RLCr_e,
      &gb::CPU::RLCr_h,
      &gb::CPU::RLCr_l,
      &gb::CPU::RLCHL,
      &gb::CPU::RLCr_a,
      &gb::CPU::RRCr_b,
      &gb::CPU::RRCr_c,
      &gb::CPU::RRCr_d,
      &gb::CPU::RRCr_e,
      &gb::CPU::RRCr_h,
      &gb::CPU::RRCr_l,
      &gb::CPU::RRCHL,
      &gb::CPU::RRCr_a,
      //0x10
      &gb::CPU::RLr_b,
      &gb::CPU::RLr_c,
      &gb::CPU::RLr_d,
      &gb::CPU::RLr_e,
      &gb::CPU::RLr_h,
      &gb::CPU::RLr_l,
      &gb::CPU::RLHL,
      &gb::CPU::RLr_a,
      &gb::CPU::RRr_b,
      &gb::CPU::RRr_c,
      &gb::CPU::RRr_d,
      &gb::CPU::RRr_e,
      &gb::CPU::RRr_h,
      &gb::CPU::RRr_l,
      &gb::CPU::RRHL,
      &gb::CPU::RRr_a,
      //0x20
      &gb::CPU::SLAr_b,
      &gb::CPU::SLAr_c,
      &gb::CPU::SLAr_d,
      &gb::CPU::SLAr_e,
      &gb::CPU::SLAr_h,
      &gb::CPU::SLAr_l,
      &gb::CPU::XX,      //SLA (HL)
      &gb::CPU::SLAr_a,
      &gb::CPU::SRAr_b,
      &gb::CPU::SRAr_c,
      &gb::CPU::SRAr_d,
      &gb::CPU::SRAr_e,
      &gb::CPU::SRAr_h,
      &gb::CPU::SRAr_l,
      &gb::CPU::XX,      //SRA (HL)
      &gb::CPU::SRAr_a,
      //0x30
      &gb::CPU::SWAPr_b,
      &gb::CPU::SWAPr_c,
      &gb::CPU::SWAPr_d,
      &gb::CPU::SWAPr_e,
      &gb::CPU::SWAPr_h,
      &gb::CPU::SWAPr_l,
      &gb::CPU::SWAPm_hl,
      &gb::CPU::SWAPr_a,
      &gb::CPU::SRLr_b,
      &gb::CPU::SRLr_c,
      &gb::CPU::SRLr_d,
      &gb::CPU::SRLr_e,
      &gb::CPU::SRLr_h,
      &gb::CPU::SRLr_l,
      &gb::CPU::XX,       //SRL (HL)
      &gb::CPU::SRLr_a,
      //0x40
      &gb::CPU::BIT0b,
      &gb::CPU::BIT0c,
      &gb::CPU::BIT0d,
      &gb::CPU::BIT0e,
      &gb::CPU::BIT0h,
      &gb::CPU::BIT0l,
      &gb::CPU::BIT0m,
      &gb::CPU::BIT0a,
      &gb::CPU::BIT1b,
      &gb::CPU::BIT1c,
      &gb::CPU::BIT1d,
      &gb::CPU::BIT1e,
      &gb::CPU::BIT1h,
      &gb::CPU::BIT1l,
      &gb::CPU::BIT1m,
      &gb::CPU::BIT1a,
      //0x50
      &gb::CPU::BIT2b,
      &gb::CPU::BIT2c,
      &gb::CPU::BIT2d,
      &gb::CPU::BIT2e,
      &gb::CPU::BIT2h,
      &gb::CPU::BIT2l,
      &gb::CPU::BIT2m,
      &gb::CPU::BIT2a,
      &gb::CPU::BIT3b,
      &gb::CPU::BIT3c,
      &gb::CPU::BIT3d,
      &gb::CPU::BIT3e,
      &gb::CPU::BIT3h,
      &gb::CPU::BIT3l,
      &gb::CPU::BIT3m,
      &gb::CPU::BIT3a,
      //0x60
      &gb::CPU::BIT4b,
      &gb::CPU::BIT4c,
      &gb::CPU::BIT4d,
      &gb::CPU::BIT4e,
      &gb::CPU::BIT4h,
      &gb::CPU::BIT4l,
      &gb::CPU::BIT4m,
      &gb::CPU::BIT4a,
      &gb::CPU::BIT5b,
      &gb::CPU::BIT5c,
      &gb::CPU::BIT5d,
      &gb::CPU::BIT5e,
      &gb::CPU::BIT5h,
      &gb::CPU::BIT5l,
      &gb::CPU::BIT5m,
      &gb::CPU::BIT5a,
      //0x70
      &gb::CPU::BIT6b,
      &gb::CPU::BIT6c,
      &gb::CPU::BIT6d,
      &gb::CPU::BIT6e,
      &gb::CPU::BIT6h,
      &gb::CPU::BIT6l,
      &gb::CPU::BIT6m,
      &gb::CPU::BIT6a,
      &gb::CPU::BIT7b,
      &gb::CPU::BIT7c,
      &gb::CPU::BIT7d,
      &gb::CPU::BIT7e,
      &gb::CPU::BIT7h,
      &gb::CPU::BIT7l,
      &gb::CPU::BIT7m,
      &gb::CPU::BIT7a,
      //0x80
      &gb::CPU::RES0b,   //RES 0b
      &gb::CPU::RES0c,
      &gb::CPU::RES0d,
      &gb::CPU::RES0e,
      &gb::CPU::RES0h,
      &gb::CPU::RES0l,
      &gb::CPU::RES0m,
      &gb::CPU::RES0a,
      &gb::CPU::RES1b,    //RES 1b
      &gb::CPU::RES1c,
      &gb::CPU::RES1d,
      &gb::CPU::RES1e,
      &gb::CPU::RES1h,
      &gb::CPU::RES1l,
      &gb::CPU::RES1m,
      &gb::CPU::RES1a,
      //0x90
      &gb::CPU::RES2b,    //RES 2b
      &gb::CPU::RES2c,
      &gb::CPU::RES2d,
      &gb::CPU::RES2e,
      &gb::CPU::RES2h,
      &gb::CPU::RES2l,
      &gb::CPU::RES2m,
      &gb::CPU::RES2a,
      &gb::CPU::RES3b,    //RES 3b
      &gb::CPU::RES3c,
      &gb::CPU::RES3d,
      &gb::CPU::RES3e,
      &gb::CPU::RES3h,
      &gb::CPU::RES3l,
      &gb::CPU::RES3m,
      &gb::CPU::RES3a,
      //0xA0
      &gb::CPU::RES4b,    //RES 4b
      &gb::CPU::RES4c,
      &gb::CPU::RES4d,
      &gb::CPU::RES4e,
      &gb::CPU::RES4h,
      &gb::CPU::RES4l,
      &gb::CPU::RES4m,
      &gb::CPU::RES4a,
      &gb::CPU::RES5b,    //RES 5b
      &gb::CPU::RES5c,
      &gb::CPU::RES5d,
      &gb::CPU::RES5e,
      &gb::CPU::RES5h,
      &gb::CPU::RES5l,
      &gb::CPU::RES5m,
      &gb::CPU::RES5a,
      //0xB0
      &gb::CPU::RES6b,    //RES 6b
      &gb::CPU::RES6c,
      &gb::CPU::RES6d,
      &gb::CPU::RES6e,
      &gb::CPU::RES6h,
      &gb::CPU::RES6l,
      &gb::CPU::RES6m,
      &gb::CPU::RES6a,
      &gb::CPU::RES7b,    //RES 7b
      &gb::CPU::RES7c,
      &gb::CPU::RES7d,
      &gb::CPU::RES7e,
      &gb::CPU::RES7h,
      &gb::CPU::RES7l,
      &gb::CPU::RES7m,
      &gb::CPU::RES7a,
      //0xC0
      &gb::CPU::SET0b,   //SET 0b
      &gb::CPU::SET0c,
      &gb::CPU::SET0d,
      &gb::CPU::SET0e,
      &gb::CPU::SET0h,
      &gb::CPU::SET0l,
      &gb::CPU::SET0m,
      &gb::CPU::SET0a,
      &gb::CPU::SET1b,
      &gb::CPU::SET1c,
      &gb::CPU::SET1d,
      &gb::CPU::SET1e,
      &gb::CPU::SET1h,
      &gb::CPU::SET1l,
      &gb::CPU::SET1m,
      &gb::CPU::SET1a,
      //0xD0
      &gb::CPU::SET2b,   //SET 2b
      &gb::CPU::SET2c,
      &gb::CPU::SET2d,
      &gb::CPU::SET2e,
      &gb::CPU::SET2h,
      &gb::CPU::SET2l,
      &gb::CPU::SET2m,
      &gb::CPU::SET2a,
      &gb::CPU::SET3b,
      &gb::CPU::SET3c,
      &gb::CPU::SET3d,
      &gb::CPU::SET3e,
      &gb::CPU::SET3h,
      &gb::CPU::SET3l,
      &gb::CPU::SET3m,
      &gb::CPU::SET3a,
      //0xE0
      &gb::CPU::SET4b,   //SET 4b
      &gb::CPU::SET4c,
      &gb::CPU::SET4d,
      &gb::CPU::SET4e,
      &gb::CPU::SET4h,
      &gb::CPU::SET4l,
      &gb::CPU::SET4m,
      &gb::CPU::SET4a,
      &gb::CPU::SET5b,
      &gb::CPU::SET5c,
      &gb::CPU::SET5d,
      &gb::CPU::SET5e,
      &gb::CPU::SET5h,
      &gb::CPU::SET5l,
      &gb::CPU::SET5m,
      &gb::CPU::SET5a,
      //0xF0
      &gb::CPU::SET6b,   //SET 6b
      &gb::CPU::SET6c,
      &gb::CPU::SET6d,
      &gb::CPU::SET6e,
      &gb::CPU::SET6h,
      &gb::CPU::SET6l,
      &gb::CPU::SET6m,
      &gb::CPU::SET6a,
      &gb::CPU::SET7b,
      &gb::CPU::SET7c,
      &gb::CPU::SET7d,
      &gb::CPU::SET7e,
      &gb::CPU::SET7h,
      &gb::CPU::SET7l,
      &gb::CPU::SET7m,
      &gb::CPU::SET7a
    };
  };
  
}