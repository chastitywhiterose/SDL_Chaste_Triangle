#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <SDL.h>

int width=1280,height=720;
int loop,fps=60,delay,sdl_time,sdl_time1;
SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;
SDL_Event e;

struct polygon
{
 double cx,cy;
 int sides;
 double radius;
 double radians;
 SDL_Color color;
 int step; /*used only in star polygons of 5 or more sides*/
};

struct polygon main_polygon;

/*Define PI the same as M_PI in math.h*/
 #define PI 3.14159265358979323846f

void init_polygon()
{
 main_polygon.cx=width/2;
 main_polygon.cy=height/2;
 main_polygon.sides=3;
 main_polygon.step=2;
 main_polygon.radius=height/2;
 main_polygon.radians=0;

 main_polygon.color.r=255;
 main_polygon.color.g=255;
 main_polygon.color.b=255;
 main_polygon.color.a=255;
}

/*these point arrays are temporary and not included in the polygon structure*/
float polygon_xpoints[0x1000],polygon_ypoints[0x1000];

/*
function to get the points of a regular polygon and load them into the above arrays of x and y points
*/
void chaste_polygon_points()
{
 double angle,x,y;
 int i=0;
 while(i<main_polygon.sides)
 {
  angle=2*PI*i/main_polygon.sides+main_polygon.radians;
  x=main_polygon.cx+sin(angle)*main_polygon.radius;
  y=main_polygon.cy-cos(angle)*main_polygon.radius;
  polygon_xpoints[i]=x;
  polygon_ypoints[i]=y;
  i++;
 }
}

/* large array for any possible combination of vertices to make many triangles*/
SDL_Vertex vertices[0x1000];

/*
 this first function draws a series of triangles to make any kind of regular polygon
 this includes star polygons by taking into account the step value between points.
*/
void chaste_polygon_draw_star()
{
 int i,i1;
 chaste_polygon_points();
 
 vertices[0].color=main_polygon.color;
 vertices[1].color=main_polygon.color;
 vertices[2].color=main_polygon.color;
 
 /*chaste_triangle_color_rgb();*/
 
 i=0;
 while(i<main_polygon.sides)
 {
  i1=(i+main_polygon.step)%main_polygon.sides;
  
  /*for each part of this loop,construct a triangle*/
  vertices[0].position.x=polygon_xpoints[i];
  vertices[0].position.y=polygon_ypoints[i];
  vertices[1].position.x=polygon_xpoints[i1];
  vertices[1].position.y=polygon_ypoints[i1];
  vertices[2].position.x=main_polygon.cx;
  vertices[2].position.y=main_polygon.cy;
  
  SDL_RenderGeometry(renderer,NULL,vertices,3,NULL,0);

  i++;
 }
 
}


int main(int argc, char** argv)
{
 if(SDL_Init(SDL_INIT_VIDEO)){printf( "SDL could not initialize! SDL_Error: %s\n",SDL_GetError());return -1;}

 window = SDL_CreateWindow( "SDL Chaste Triangle",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,width,height,0);
 if(window==NULL){printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );return -1;}
 
 renderer = SDL_CreateRenderer(window,-1,0);
 if(renderer==NULL){printf( "Renderer could not be created! SDL_Error: %s\n", SDL_GetError() );return -1;}
 
 init_polygon();
 main_polygon.radius=350;
 main_polygon.sides=3;
 main_polygon.step=2;

 delay=1000/fps;
 loop=1;
 while(loop) /*wait until any key is pressed and then released*/
 {
  sdl_time = SDL_GetTicks();
  sdl_time1 = sdl_time+delay;
 
  SDL_SetRenderDrawColor(renderer,0,0,0,255);
  SDL_RenderClear(renderer);

  chaste_polygon_draw_star();

  main_polygon.radians+=PI/180;

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
 	
 SDL_DestroyRenderer(renderer);
 SDL_DestroyWindow(window);
 SDL_Quit();
 return 0;
}

