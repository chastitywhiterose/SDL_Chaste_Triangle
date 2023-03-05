#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <SDL.h>

int width=1280,height=720;
int loop,fps=60,delay,sdl_time,sdl_time1;
SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;
SDL_Event e;

#include "sdl_chaste_polygon.h"


int main(int argc, char** argv)
{
 if(SDL_Init(SDL_INIT_VIDEO)){printf( "SDL could not initialize! SDL_Error: %s\n",SDL_GetError());return -1;}

 window = SDL_CreateWindow( "SDL Chaste Triangle",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,width,height,0);
 if(window==NULL){printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );return -1;}

 renderer = SDL_CreateRenderer(window,-1,0);
 if(renderer==NULL){printf( "Renderer could not be created! SDL_Error: %s\n", SDL_GetError() );return -1;}
	
 SDL_SetRenderDrawColor(renderer,0,0,0,255);

 init_polygon();
 main_polygon.radius=350;
 main_polygon.sides=5;
 main_polygon.step=2;

 delay=1000/fps;
 loop=1;
 while(loop) /*wait until any key is pressed and then released*/
 {
  sdl_time = SDL_GetTicks();
  sdl_time1 = sdl_time+delay;
 
  SDL_RenderClear(renderer);

  chaste_polygon_draw_star();
 
  main_polygon.radians+=PI/180;

  SDL_RenderPresent(renderer);
  
  SDL_PollEvent( &e );
  if( e.type == SDL_QUIT ){loop=0;}
  if(e.type == SDL_KEYUP)
  {
   if(e.key.keysym.sym==SDLK_ESCAPE){loop=0;}
  }
  
  while(sdl_time<sdl_time1)
  {
   sdl_time=SDL_GetTicks();
  }
  
 }
	
 SDL_DestroyRenderer(renderer);
 SDL_DestroyWindow(window);
 SDL_Quit();
 return 0;
}

/*
 This file is the Chastity's modification of an example from here:

 https://daywithstars.github.io/sdl2/geometry/2021/12/03/SDL2-new-geometry-rendering-SDL_RenderGeometry.html

 Unlike the original, this one is compatible with the C89 standard which Chastity always uses.

 Compile and run on Linux with this command:
 gcc -Wall -ansi -pedantic main.c -o main `sdl2-config --cflags --libs` -lm && ./main
*/
