#include "MMU.h"
#include "CPU.h"
#include "PPU.h"
#include "SOUND.h"
#include "IWindow.h"
#include "SFMLWindow.h"
#include "PASound.h"
#include "JOYP.h"
#include "Timer.h"
#include "GBAudioStream.h"

#include "portaudio.h"

#include <iostream>
#include <fstream>
#include <iterator>
#include <vector>
#include <iomanip>

using namespace gb;

int main(char** args) {
  JOYP joyp;

  Timer timer;

  ISoundDriver *soundDriver = new PASound();
  soundDriver->init(4);
  SOUND sound = SOUND(soundDriver);

  MMU mmu = MMU(&joyp, &timer, &sound);
  mmu.reset();

  SFMLWindow window(&joyp);
  window.open(160, 144);
  PPU ppu = PPU(mmu, &window);

  CPU cpu = CPU(mmu, ppu, &timer, &sound);
  cpu.reset();
  ppu.reset();

  std::ifstream rom("C:\\tetris.gb", std::ios::binary);
  std::vector<char> buffer((
    std::istreambuf_iterator<char>(rom)),
    (std::istreambuf_iterator<char>()));

  mmu.setRom((unsigned char*)&buffer.front(), buffer.size());

  while (window.isOpen()) {
    window.pollEvents();
    cpu.execute();
  }

  soundDriver->cleanup();
  
  //mmu.cleanup();
}