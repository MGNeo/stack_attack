#include "Scene.hpp"

sa::Scene::Scene(sf::RenderWindow& _render_window,
                 sa::ResourceLibrary& _resource_library)
  :
  render_window{ _render_window },
  resource_library{ _resource_library }
{
}

sa::Scene::Uptr sa::Scene::run()
{
  sa::Scene::Uptr next_scene;

  sf::Clock clock;
  float accumulated_dt = 0.f;

  while (render_window.isOpen() == true)
  {
    sf::Event event;
    while (render_window.pollEvent(event) == true)
    {
      if (event.type == sf::Event::EventType::Closed)
      {
        render_window.close();
        goto SCENE_LOOP_END;
      }
      control(event);
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

      process(normalized_dt);
      //draw();
    }
  }
SCENE_LOOP_END:;

  return next_scene;
}

sa::Scene::~Scene()
{
}