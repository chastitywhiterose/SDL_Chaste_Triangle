#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>

int width=1280,height=720;
SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;
SDL_Event e;

SDL_Vertex triangleVertex[3]=
{
 {
  { 0,0}, /* first point location */ 
  { 255, 0, 0, 0xFF }, /* first color */ 
  { 0.f, 0.f }
 },
 {
  { 0, 720 }, /* second point location */ 
  { 0,255,0, 0xFF }, /* second color */
  { 0.f, 0.f }
 },
 {
  { 640, 360 }, /* third point location */ 
  { 0,0,255, 0xFF }, /* third color */
  { 0.f, 0.f }
 }
};


int main(int argc, char** argv)
{
 if(SDL_Init(SDL_INIT_VIDEO)){printf( "SDL could not initialize! SDL_Error: %s\n",SDL_GetError());return -1;}

 window = SDL_CreateWindow( "SDL Chaste Triangle",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,width,height,0);
 if(window==NULL){printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );return -1;}

 renderer = SDL_CreateRenderer(window,-1,0);
 if(renderer==NULL){printf( "Renderer could not be created! SDL_Error: %s\n", SDL_GetError() );return -1;}
	
 SDL_SetRenderDrawColor(renderer,0,0,0,255);
 SDL_RenderClear(renderer);
 if( SDL_RenderGeometry(renderer, NULL, triangleVertex, 3, NULL, 0) < 0 ) {SDL_Log("%s\n", SDL_GetError());}

 SDL_RenderPresent(renderer);
	
 while(e.type != SDL_KEYUP && e.type != SDL_QUIT) /*wait until any key is pressed and then released*/
 {
  SDL_PollEvent( &e );
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
