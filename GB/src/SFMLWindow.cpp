#include "SFMLWindow.h"
#include "JOYP.h"
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace gb;

SFMLWindow::SFMLWindow(JOYP *joyp) {
  m_texture.create(160, 144);
  m_clock.restart();
  m_frame_count = 0;
  m_joyp = joyp;
}

void SFMLWindow::putImage(int width, int height, char* data) {
  m_window.clear();

  if (m_frame_count == 5) {
    sf::Time elapsedTime = m_clock.getElapsedTime();
    sf::Time expected = sf::microseconds(16666*5);
    if (elapsedTime < expected) {
      sf::sleep(expected - elapsedTime);
    }
    else {
      std::cout << "late frames" << std::endl;
    }
    m_clock.restart();
    m_frame_count = 0;
  }
  else {
    m_frame_count++;
  }

  m_image.create(width, height, sf::Color(255,255,255,255));

  for (int i = 0; i < width*height; i++) {
    sf::Color color;
    switch (data[i]) {
    case 3:
      color = sf::Color(0, 0, 0, 255);
      break;
    case 2:
      color = sf::Color(96, 96, 96, 255);
      break;
    case 1:
      color = sf::Color(192, 192, 192, 255);
      break;
    case 0:
    default:
      color = sf::Color(255, 255, 255, 255);
    }
    m_image.setPixel(i % width, i/width, color);
  }

  m_texture.update(m_image);
  m_sprite.setTexture(m_texture, true);
  m_window.draw(m_sprite);
  m_window.display();

}

void SFMLWindow::open(int width, int height) {
    m_window.create(sf::VideoMode(width, height), "GAMEBOY");
}

bool SFMLWindow::isOpen() {
  return m_window.isOpen();
}

void SFMLWindow::pollEvents() {
  sf::Event event;
  while (m_window.pollEvent(event)) {
    if (event.type == sf::Event::Closed) {
      m_window.close();
    } else if (event.type == sf::Event::KeyPressed) {
      switch (event.key.code) {
      case sf::Keyboard::Left:
        m_joyp->setButton(JOYP::LEFT, true);
        break;
      case sf::Keyboard::Right:
        m_joyp->setButton(JOYP::RIGHT, true);
        break;
      case sf::Keyboard::Up:
        m_joyp->setButton(JOYP::UP, true);
        break;
      case sf::Keyboard::Down:
        m_joyp->setButton(JOYP::DOWN, true);
        break;
      case sf::Keyboard::Z:
        m_joyp->setButton(JOYP::A, true);
        break;
      case sf::Keyboard::X:
        m_joyp->setButton(JOYP::B, true);
        break;
      case sf::Keyboard::Return:
        m_joyp->setButton(JOYP::START, true);
        break;
      case sf::Keyboard::BackSpace:
        m_joyp->setButton(JOYP::SELECT, true);
        break;
      }
    } else if (event.type == sf::Event::KeyReleased) {
      switch (event.key.code) {
      case sf::Keyboard::Left:
        m_joyp->setButton(JOYP::LEFT, false);
        break;
      case sf::Keyboard::Right:
        m_joyp->setButton(JOYP::RIGHT, false);
        break;
      case sf::Keyboard::Up:
        m_joyp->setButton(JOYP::UP, false);
        break;
      case sf::Keyboard::Down:
        m_joyp->setButton(JOYP::DOWN, false);
        break;
      case sf::Keyboard::Z:
        m_joyp->setButton(JOYP::A, false);
        break;
      case sf::Keyboard::X:
        m_joyp->setButton(JOYP::B, false);
        break;
      case sf::Keyboard::Return:
        m_joyp->setButton(JOYP::START, false);
        break;
      case sf::Keyboard::BackSpace:
        m_joyp->setButton(JOYP::SELECT, false);
        break;
      }
    }
  }
}