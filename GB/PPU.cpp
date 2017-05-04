#include "MMU.h"
#include "PPU.h"
#include "OAM.h";

#include <iostream>
#include <iomanip>

using namespace gb;

PPU::PPU(MMU& mmu, IWindow* window) : m_MMU(mmu), m_window(window) {
  m_timer = 0;
  m_gpuMode = HBLANK;
  m_currentLine = 0;
  m_OAM = gb::OAM(m_MMU);
}

void PPU::reset() {
  m_reg_scroll_x = 0;
  m_reg_scroll_y = 0;
  
  m_reg_background_on = false;
  m_reg_scan_line = 0;
  m_reg_bg_palette = 255;
  m_reg_large_sprites = 0;
  m_reg_sprites_on = 0;
  m_reg_tile_map = 0;
  m_reg_tile_set = 0;
  m_reg_window_on = 0;
  m_reg_window_tile_map = 0;
  m_reg_display_on = 0;
}

void PPU::readRegisters() {
  int control = m_MMU.readByte(0xFF40);
  m_reg_scroll_x = m_MMU.readByte(0xFF43);
  m_reg_scroll_y = m_MMU.readByte(0xFF42);
  m_reg_scan_line = m_MMU.readByte(0xFF44);
  m_reg_bg_palette = m_MMU.readByte(0xFF47);

  m_reg_background_on = control & 0x01;
  m_reg_sprites_on = control & 0x02;
  m_reg_large_sprites = control & 0x04;
  m_reg_tile_map = control & 0x08;
  m_reg_tile_set = control & 0x10;
  m_reg_window_on = control & 0x20;
  m_reg_window_tile_map = control & 0x40;
  m_reg_display_on = control & 0x80;
}

void PPU::setScanline(int line) {
  line &= 0xFF;
  m_MMU.writeByte(0xFF44, line);
}

void PPU::renderScan() {
  readRegisters();

  int y = m_reg_scroll_y + m_currentLine;
  int tileY = y / 8;
  int tileOffsetY = y % 8;

  //scan background tiles
  for (int i = 0; i < 160; i++) {
    int x = m_reg_scroll_x + i;
    int tileX = x / 8;
    int tileOffsetX = 7 - x % 8;

    int mapOffset = m_reg_tile_map ? 0x9c00 : 0x9800;
    int index = tileY * 32 + tileX;
    int tile = m_MMU.readByte(mapOffset + index);

    if (!m_reg_tile_set) {
      if (tile < 128) {
        tile += 256;
      }
    }

    int tileOffset = m_reg_tile_set ? 0x8000 : 0x8800;
    int addr = tileOffset + tile * 16 + tileOffsetY * 2;
    //get lo byte
    int first = m_MMU.readByte(addr);
    //get hi byte
    int second = m_MMU.readByte(addr + 1);
    int lo = (first >> tileOffsetX) & 0x01;
    int high = (second >> tileOffsetX) & 0x01;
    int value = (high << 1) + lo;
    //lookup value in palette
    int color = (m_reg_bg_palette & (0x3 << (value*2))) >> (value*2);
    m_screen[m_currentLine * 160 + i] = color;
  }

  //scan sprite tiles
  OAMObject* objects = m_OAM.getObjects();
  for (int i = 0; i < 40; i++) {
    OAMObject object = objects[i];
    if (object.x > -8 && object.x <= 160 && m_currentLine >= object.y && m_currentLine < object.y + 8) {
      int tileOffset = 0x8000 + object.tileNumber*16;
      int row = m_currentLine - object.y;
      int first = m_MMU.readByte(tileOffset + row*2);
      int second = m_MMU.readByte(tileOffset + row*2 + 1);
      for (int j = 0; j < 8; j++) {
        int column = j + object.x;
        if (column >= 0 && column <= 160) {
          int lo;
          int high;
          if (object.xFlip) {
            lo = (first >> j) & 0x01;
            high = (second >> j) & 0x01;
          }
          else {
            lo = (first >> (7 - j)) & 0x01;
            high = (second >> (7 - j)) & 0x01;
          }
          int value = (high << 1) + lo;
          int currentValue = m_screen[m_currentLine * 160 + column];
          if (!object.belowBackground && value != 0x00) {
            m_screen[m_currentLine * 160 + column] = value;
          }
          else if (object.belowBackground && currentValue == 0x00) {
            m_screen[m_currentLine * 160 + column] = value;
          }
        }
      }
    }
  }
}

void PPU::pushFrame() {
  m_window->putImage(160, 144, m_screen);
}

void PPU::tick(int timing) {
  m_timer += timing;

  switch (m_gpuMode) {
  case OAM:
    //OAM mode is 80 ticks long
    if (m_timer >= 80) {
      m_gpuMode = VRAM;
      m_MMU.writeByte(0xFF41, 3);
      m_timer = 0;
    }
    break;
  case VRAM:
    if (m_timer >= 172) {
      m_gpuMode = HBLANK;
      m_MMU.writeByte(0xFF41, 0);
      m_timer = 0;
      //Write line to texture
      renderScan();
      setScanline(m_currentLine+1);
    }
    break;
  case HBLANK:
    if (m_timer >= 204) {
      m_timer = 0;
      m_currentLine++;
      if (m_currentLine > 143) {
        m_gpuMode = VBLANK;
        m_MMU.writeByte(0xFF41, 1);
        //Render frame
        pushFrame();
        // Set VBlank interrupt flag
        m_MMU.writeByte(0xFF0F, m_MMU.readByte(0xFF0F) | 0x01);
      }
      else {
        m_gpuMode = OAM;
        m_MMU.writeByte(0xFF41, 2);
      }
    }
    break;
  case VBLANK:
    if (m_timer >= 456) {
      m_timer = 0;
      if (m_currentLine > 153) {
        m_gpuMode = OAM;
        m_MMU.writeByte(0xFF41, 2);
        m_currentLine = 0;
      }
      else {
        setScanline(m_currentLine);
        m_currentLine++;
      }
    }
    break;
  }
}