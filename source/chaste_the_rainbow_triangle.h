/*
Header file for using the global color palette from "chaste_the rainbow.h"
*/

SDL_Color tri_color={0,0,0,255};

void set_tri_color(r,g,b)
{
 tri_color.r=r;
 tri_color.g=g;
 tri_color.b=b;
 /*tri_color.a=0;*/
}

/*draw a triangle based on global tri_color variable for color*/
void FillTriangle(float x0,float y0,float x1,float y1,float x2,float y2)
{
 vertices[0].color=tri_color;
 vertices[1].color=tri_color;
 vertices[2].color=tri_color;

 vertices[0].position.x=x0;
 vertices[0].position.y=y0;
 vertices[1].position.x=x1;
 vertices[1].position.y=y1;
 vertices[2].position.x=x2;
 vertices[2].position.y=y2;
  
 SDL_RenderGeometry(renderer,NULL,vertices,3,NULL,0);
}

/*draw a triangle of any points but use the rainbow color palette*/
void FillTriangle_Rainbow(float x0,float y0,float x1,float y1,float x2,float y2)
{
 int index1,index2;
 Uint32 pixel;

 /*first color*/
 pixel=chaste_palette[chaste_palette_index];
 tri_color.r=(pixel&0xFF0000)>>16;
 tri_color.g=(pixel&0x00FF00)>>8;
 tri_color.b=(pixel&0x0000FF);
 vertices[0].color=tri_color;

 /*second color*/
 index1=(chaste_palette_index+(chaste_palette_length/3))%chaste_palette_length;
 pixel=chaste_palette[index1];
 tri_color.r=(pixel&0xFF0000)>>16;
 tri_color.g=(pixel&0x00FF00)>>8;
 tri_color.b=(pixel&0x0000FF);
 vertices[1].color=tri_color;

 /*third color*/
 index2=(index1+(chaste_palette_length/3))%chaste_palette_length;
 pixel=chaste_palette[index2];
 tri_color.r=(pixel&0xFF0000)>>16;
 tri_color.g=(pixel&0x00FF00)>>8;
 tri_color.b=(pixel&0x0000FF);
 vertices[2].color=tri_color;

 chaste_next_color();

 vertices[0].position.x=x0;
 vertices[0].position.y=y0;
 vertices[1].position.x=x1;
 vertices[1].position.y=y1;
 vertices[2].position.x=x2;
 vertices[2].position.y=y2;
  
 SDL_RenderGeometry(renderer,NULL,vertices,3,NULL,0);
}




/*
the ultimate triangle creation!
Draws a regular triangle by using the same
*/
void FillTriangle_Rainbow_Regular()
{
 int i,i1;
 int index1,index2;
 Uint32 pixel;

 chaste_polygon_points();



 i=0;
 while(i<main_polygon.sides)
 {
  i1=(i+1)%main_polygon.sides;



 /*first color*/
 pixel=chaste_palette[chaste_palette_index];
 tri_color.r=(pixel&0xFF0000)>>16;
 tri_color.g=(pixel&0x00FF00)>>8;
 tri_color.b=(pixel&0x0000FF);
 vertices[0].color=tri_color;

 /*second color*/
 index1=(chaste_palette_index+(chaste_palette_length/main_polygon.sides))%chaste_palette_length;
 pixel=chaste_palette[index1];
 tri_color.r=(pixel&0xFF0000)>>16;
 tri_color.g=(pixel&0x00FF00)>>8;
 tri_color.b=(pixel&0x0000FF);
 vertices[1].color=tri_color;

 /*third color*/
 index2=(index1+(chaste_palette_length/main_polygon.sides))%chaste_palette_length;
 pixel=chaste_palette[index2];
 tri_color.r=(pixel&0xFF0000)>>16;
 tri_color.g=(pixel&0x00FF00)>>8;
 tri_color.b=(pixel&0x0000FF);
 vertices[2].color=tri_color;

/* chaste_next_color();*/

chaste_palette_index=(chaste_palette_index+(chaste_palette_length/main_polygon.sides))%chaste_palette_length;

  
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

chaste_palette_index=(chaste_palette_index+1)%chaste_palette_length;

}
