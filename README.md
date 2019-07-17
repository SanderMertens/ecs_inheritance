# ecs_inheritance
ECS demo that showcases inheritance. The demo uses the Flecs ECS framework (https://github.com/SanderMertens/flecs).

## Getting started
This demo uses the bake build system (https://github.com/SanderMertens/bake). To install bake on Linux and MacOS, do:

```
git clone https://github.com/SanderMertens/bake
make -C bake/build-$(uname)
bake/bake setup
```

Before you can run the demo, make sure to have SDL2 installed.

On MacOS:

```
brew install sdl2
```

On Debian/Ubuntu:

```
sudo apt-get install sdl2
```

To install and run the demo, do:

```
bake clone SanderMertens/ecs_inheritance
bake run ecs_inheritance
```

## Inheritance
Inheritance in ECS lets entities share components from one or more "base" entities by instantiating them. Inheritance can be specified as part of an ECS type, when an entity is created or dynamically while the simulation is running. Inheritance relationships can be added and removed at any point in time, just like components.

To learn more, see this section of the Flecs manual:
https://github.com/SanderMertens/flecs/blob/master/Manual.md#inheritance
