#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <SDL.h>

int width=1280,height=720;
int loop,fps=60,delay,sdl_time,sdl_time1;
SDL_Window *window = NULL;
/*SDL_Surface *surface;*/
SDL_Renderer *renderer = NULL;
SDL_Event e;

char text[0x200];

#include "sdl_chaste_polygon.h"
#include "chaste_the_rainbow.h"
#include "chaste_the_rainbow_triangle.h"
#include "sdl_chastefont_texture.h"

int main(int argc, char** argv)
{
 if(SDL_Init(SDL_INIT_VIDEO)){printf( "SDL could not initialize! SDL_Error: %s\n",SDL_GetError());return -1;}

 window = SDL_CreateWindow( "SDL Chaste Triangle",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,width,height,0);
 if(window==NULL){printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );return -1;}
 
 /*for surface functions, including my font library which was written using surface copies*/
 /*surface = SDL_GetWindowSurface( window );*/

 renderer = SDL_CreateRenderer(window,-1,0);
 if(renderer==NULL){printf( "Renderer could not be created! SDL_Error: %s\n", SDL_GetError() );return -1;}
 
 font_8=chaste_font_load("./font/FreeBASIC Font 8.bmp");
 font_pico8=chaste_font_load("./font/PICO-8_4x6.bmp");
 
 main_font=font_8;
	
 init_polygon();
 main_polygon.radius=350;
 main_polygon.sides=24;
 main_polygon.step=1;

 chaste_palette_rainbow(40);
 /*chaste_palette_view();*/

 delay=1000/fps;
 loop=1;
 while(loop) /*wait until any key is pressed and then released*/
 {
  sdl_time = SDL_GetTicks();
  sdl_time1 = sdl_time+delay;
 
  SDL_SetRenderDrawColor(renderer,0,0,0,255);
  SDL_RenderClear(renderer);

  sprintf(text,"SDL_RenderGeometry example by Chastity White Rose");
  chaste_font_draw_string(text,main_font.char_width*1,height-main_font.char_height*4);

  sprintf(text,"Chastity\nWhite\nRose");
  chaste_font_draw_string_scaled(text,main_font.char_width*4,main_font.char_height*1,4);

  /*chaste_polygon_draw_star();*/
  /*chaste_polygon_draw_star_lines();*/

  set_tri_color(128,128,128);
  /*FillTriangle_Rainbow(100,100,100,400,400,400);*/

FillTriangle_Rainbow_Regular();

 
  /*main_polygon.radians+=PI/180;*/

  SDL_RenderPresent(renderer);
  
/*test for events and only process if they exist*/
  while(SDL_PollEvent(&e))
  {
   if( e.type == SDL_QUIT ){loop=0;}
   if(e.type == SDL_KEYUP)
   {
    if(e.key.keysym.sym==SDLK_ESCAPE){loop=0;}
   }
  }

  while(sdl_time<sdl_time1)
  {
   sdl_time=SDL_GetTicks();
  }
  
 }
 
 chaste_font_free(font_pico8);
 chaste_font_free(font_8);
	
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
