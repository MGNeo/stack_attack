#include <SFML/Graphics.hpp>

#include "Game.hpp"
#include "LevelScene.hpp"

sa::Game::Game()
  :
  render_window(sf::VideoMode(800u, 600u), "stack_attack", sf::Style::Close)
{
}

void sa::Game::play()
{
  sa::Scene::Uptr current_scene = std::make_unique<sa::LevelScene>(resource_library);

  const sa::Drawer drawer{ render_window };

  sf::Clock clock;
  float accumulated_dt = 0.f;

  while (current_scene->isActive() == true)
  {
    sf::Event event;
    while (render_window.pollEvent(event) == true)
    {
      if (event.type == sf::Event::EventType::Closed)
      {
        render_window.close();
        goto LOOP_END;
      }
      current_scene->control(event);
    }

    const auto time = clock.getElapsedTime();
    accumulated_dt += time.asSeconds();

    if (accumulated_dt > MIN_DT)
    {
      float normalized_dt;
      if (accumulated_dt < MAX_DT)
      {
        normalized_dt = accumulated_dt;
      } else {
        normalized_dt = MAX_DT;
      }

      current_scene->process(normalized_dt);
      current_scene->draw(drawer);
    }

    sa::Scene::Uptr next_scene = current_scene->getNextScene();
    if (next_scene != nullptr)
    {
      current_scene = std::move(next_scene);
    }
  }
LOOP_END:;
}