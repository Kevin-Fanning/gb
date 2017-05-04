#pragma once
#include "MMU.h"

namespace gb {
  class OAMObject {
  public:
    OAMObject();
    OAMObject(int x, int y, int tileNumber, int palette, int xFlip, int yFlip, int belowBackground);

    int x;
    int y;
    int tileNumber;
    int palette;
    int xFlip;
    int yFlip;
    int belowBackground;
  };
  class OAM {
  public:
    OAM();
    OAM(MMU& mmu);

    OAMObject* getObjects();

  private:
    MMU m_MMU;
  };
};