#pragma once
#include "IWindow.h"
#include "JOYP.h"
#include <SFML/Graphics.hpp>

namespace gb {
  class SFMLWindow : public IWindow {
  public:
    SFMLWindow(JOYP *joyp);
    void putImage(int width, int height, char* data);
    void open(int width, int height);
    bool isOpen();
    void pollEvents();
  private:
    int m_width, m_height;
    sf::RenderWindow m_window;
    sf::Texture m_texture;
    sf::Image m_image;
    sf::Sprite m_sprite;
    sf::Clock m_clock;

    JOYP *m_joyp;

    int m_frame_count;
  };
}