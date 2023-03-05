This project is dedicated to helping people solve the ancient problem of drawing a triangle with SDL. For those of you who don't know, SDL is an awesome library that people often use to make games because it lets you draw pixels to the screen and manage keyboard input.

https://www.libsdl.org/

But unlike Raylib of Allegro, it does not appear to have a standard easy way to draw shapes other than rectangles. This is a mystery people have been trying to solve. People often ask this question and people tell them "Just use OpenGL". This is not helpful for people who want to make games involving triangle or other polygons(which can all be built with triangles). Not everybody should be forced to learn OpenGL because it is not at all easy!

But while all that has been happening. A new function was added to SDL which is capable of doing exactly what we all need.

https://wiki.libsdl.org/SDL2/SDL_RenderGeometry

And someone wrote a small tutorial that I am using to learn this way.

https://daywithstars.github.io/sdl2/geometry/2021/12/03/SDL2-new-geometry-rendering-SDL_RenderGeometry.html

It is now possible to draw filled triangles using only SDL and not needing OpenGL. This is a huge game changer for those who have been frustrated by the limitations that SDL seems to impose.

As I learn more, I will provide more examples.
