#pragma once

namespace gb {
  class JOYP {
  public:
    enum Button {
      A, B, START, SELECT, UP, DOWN, LEFT, RIGHT
    };

    JOYP();

    //joypad implementation sets these
    void setButton(Button button, bool set);
    
    //Memory map can call these to set bytes
    unsigned char readByte(int addr);
    void writeByte(int addr, unsigned char byte);

    
  private:
    int m_column;
    int m_col_1;
    int m_col_2; 
  };
}