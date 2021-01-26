# Tactics map generation

![Screenshot](https://raw.githubusercontent.com/floriansimon1/game/main/screenshot.png "Screenshot")

The point of this christmas project is to experiment around ECS, C++20 features and OpenGL to create a program that can generate random maps in the
style of those you can find in one of my favorite childhood video games, Final Fantasy Tactics Advance. It is fairly basic and only covers the relief
generation. I do not intend to improve on this, and I consider it to be done.

## Building

This CMake project depends on SFML, GLM, Glad and coro (for C++ coroutines) as well as range-v3 (for C++ ranges). You can fetch most of those dependencies from
conan center, but you'll have to create binaries for coro yourself using the coro Conan recipe on my GitHub if you're interested. There are a few scripts in the
the `scripts` subdirectory that will help set you on the right track to build this yourself. Please note that since this uses C++20 features that are very new, I
can only guarantee that it compiles under GCC 10+.
