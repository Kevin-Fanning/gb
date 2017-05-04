#include "JOYP.h"
#include <iostream>
using namespace gb;

JOYP::JOYP() {
  m_column = 0;
  //"off" state is 1 on gameboy
  m_col_1 = 0b1111;
  m_col_2 = 0b1111;
}

unsigned char JOYP::readByte(int addr) {
  return m_column ? m_col_2 : m_col_1;
}

void JOYP::writeByte(int addr, unsigned char byte) {
  if (byte & 0x10) {
    m_column = 0;
  }
  else if (byte & 0x20) {
    m_column = 1;
  }
}

void JOYP::setButton(Button button, bool set) {
  switch (button) {
  case A:
    set ? m_col_1 &= 0b1110 : m_col_1 |= 0b0001;
    break;
  case B:
    set ? m_col_1 &= 0b1101 : m_col_1 |= 0b0010;
    break;
  case SELECT:
    set ? m_col_1 &= 0b1011 : m_col_1 |= 0b0100;
    break;
  case START:
    set ? m_col_1 &= 0b0111 : m_col_1 |= 0b1000;
    break;
  case RIGHT:
    set ? m_col_2 &= 0b1110 : m_col_2 |= 0b0001;
    break;
  case LEFT:
    set ? m_col_2 &= 0b1101 : m_col_2 |= 0b0010;
    break;
  case UP:
    set ? m_col_2 &= 0b1011 : m_col_2 |= 0b0100;
    break;
  case DOWN:
    set ? m_col_2 &= 0b0111 : m_col_2 |= 0b1000;
    break;
  }
}