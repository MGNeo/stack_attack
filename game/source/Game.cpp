#include <SFML/Graphics.hpp>

#include <Game.hpp>
#include <LevelScene.hpp>

sa::Game::Game()
  :
  render_window(sf::VideoMode(game_settings.getWindowWidth(), game_settings.getWindowHeight()),
                "stack_attack",
                sf::Style::Close),
  drawer{ render_window }
{
}

void sa::Game::play()
{
  Scene::Uptr current_scene = std::make_unique<LevelScene>(resource_library, drawer, game_settings);

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
      current_scene->react(event);
    }

    const auto time = clock.getElapsedTime();
    clock.restart();
    accumulated_dt += time.asSeconds();

    if (accumulated_dt > game_settings.getMinDt())
    {
      float normalized_dt;
      if (accumulated_dt < game_settings.getMaxDt())
      {
        normalized_dt = accumulated_dt;
      } else {
        normalized_dt = game_settings.getMaxDt();
      }

      current_scene->process(normalized_dt);

      render_window.clear();
      current_scene->draw();
      render_window.display();

      accumulated_dt = 0.f;
    }

    sa::Scene::Uptr next_scene = current_scene->getNextScene();
    if (next_scene != nullptr)
    {
      current_scene = std::move(next_scene);
    }
  }
LOOP_END:;
}