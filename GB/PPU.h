#pragma once
#include "MMU.h"
#include "OAM.h"
#include "SFMLWindow.h"

namespace gb {
  class PPU {
  public:
    PPU(MMU& mmu, IWindow* window);
    void tick(int timing);
    void reset();

  private:
    void readRegisters();
    void setScanline(int line);

    void renderScan();
    void pushFrame();

    void checkLYC();

    int m_reg_background_on;
    int m_reg_sprites_on;
    int m_reg_large_sprites;
    int m_reg_tile_map;
    int m_reg_tile_set;
    int m_reg_window_on;
    int m_reg_window_tile_map;
    int m_reg_display_on;

    int m_reg_scroll_x;
    int m_reg_scroll_y;
    int m_reg_scan_line;
    int m_reg_lyc;
    int m_reg_bg_palette;

    char m_screen[160 * 144];

    IWindow* m_window;
    MMU m_MMU;
    OAM m_OAM;
    int m_timer;
    int m_currentLine;
    enum {
      VBLANK,
      HBLANK,
      OAM,
      VRAM
    } m_gpuMode;
  };
}