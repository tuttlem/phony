#  Phony game library
 
A bootstrap project for getting game applications up and running, quickly.

![Screenshot](https://github.com/tuttlem/phony/raw/master/data/phony-screen.png)

## Installation

Ensure that you have the required dependencies installed locally.

You will need:

* lua
* libsdl2-dev
* libsdl2-image-dev
* libsdl2-mixer-dev
* libsdl2-net-dev

```
pacman -S lua sdl2_gfx sdl2_image sdl2_mixer sdl2_net sdl2_ttf
```

## Building

You can now just build the source tree. This has been converted into a [cmake](https://cmake.org/) project.

```
ccmake .
```

You should be left with a binary, that built the test application. Run it from the project directory.

```
bin/phony
```

## Development

### Get Started

To get started, simply copy the entire `phony` project folder and rename it to something appropriate for your project. Remove any source control information from the copied version of the project.

```
cp -R phony my-app

cd my-app
rm -Rf .git
```

### Engine

The game engine is based on the idea of game states, represented by the `game_state` class. The example class that's bundled with the project (inside of `gmain.cpp`) is called `blank_state`.

```c++
class blank_state : public game_state {
public:
  blank_state() : light1(GL_LIGHT1) {
    pressed = false;
  }

  const bool init() {
    /* state setup code */
    return game_state::init();
  }

  const bool teardown() {
    /* state teardown code */
    return game_state::teardown();
  }

  const bool render() {
    /* frame render code */
    return true;
  }

  const bool update(const unsigned int elapsed) {
    /* frame update code */
    return !pressed;
  }

  void key_pressed(const SDL_Event &key) {
    pressed = true;
  }

  void resize(const int width, const int height) {
    std::cout << "resized to " << width << ", " << height << std::endl;
    scene::resize_3d(width, height);
  }

};
```

This is then injected into the game engine with the main code:

```c++
phony_init(
  config->get_int("window.width"),
  config->get_int("window.height"),
  config->get_string("window.title")
);

phony_run(std::make_shared<blank_state>());
phony_teardown();
```

### Configuration

The configuration system is based on the `lua` language. Free `lua` text is read into the system and is made available through the `config` object.

```c++
auto config = phony::lua_config::from_file("data/config.lua");
```

As above now, the `window.width`, `window.height`, and `window.title` values are controllable via the configuration file.

The configuration file itself as you would expect, is quite simple:

```lua
window = {
   width = 640,
   height = 480,
   title = "Phony"
}
```

