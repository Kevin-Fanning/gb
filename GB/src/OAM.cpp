#include "OAM.h";
#include "MMU.h";

using namespace gb;

OAMObject::OAMObject() {}

OAMObject::OAMObject(int x, int y, int tileNumber, int palette, int xFlip, int yFlip, int belowBackground) :
  x(x), y(y), tileNumber(tileNumber), palette(palette), xFlip(xFlip), yFlip(yFlip), belowBackground(belowBackground) {

}

OAM::OAM() : m_MMU(nullptr, nullptr, nullptr) {}
OAM::OAM(MMU& mmu) : m_MMU(mmu) {}

OAMObject* OAM::getObjects() {
  OAMObject objects[40];
  int start = 0xFE00;
  for (int i = 0; i < 160; i+= 4) {
    unsigned int offset = start + i;
    //convert to signed byte in case it is negative (the value in memory is never negative, after subtracting it might be)
    int y = ((int)m_MMU.readByte(offset)) - 16;
    int x = ((int)m_MMU.readByte(offset + 1)) - 8;
    int tileNumber = m_MMU.readByte(offset + 2);
    int flags = m_MMU.readByte(offset + 3);
    int belowBackground = flags & 0x80;
    int yFlip = flags & 0x40;
    int xFlip = flags & 0x20;
    int palette = flags & 0x10;
    objects[i / 4] = OAMObject(x, y, tileNumber, palette, xFlip, yFlip, belowBackground);
  }
  return objects;
}