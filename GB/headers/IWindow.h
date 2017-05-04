#pragma once

namespace gb {
  class IWindow {
  public:
    virtual void open(int width, int height) = 0;
    virtual void putImage(int width, int height, char* data) = 0;
    virtual bool isOpen() = 0;
    virtual void pollEvents() = 0;
  };
}