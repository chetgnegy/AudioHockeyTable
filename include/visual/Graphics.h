/*
  Author: Chet Gnegy
  chetgnegy@gmail.com

  Graphics.h
  This is the object that interacts directly with OpenGL.
*/

#ifndef _GRAPHICSBOX_H_
#define _GRAPHICSBOX_H_

#include <list>
#include <math.h>
#include "Drawable.h"
#include "Moveable.h"
  
#ifdef __MACOSX_CORE__
  #include <GLUT/glut.h>
#else
  #include <GL/gl.h>
  #include <GL/glu.h>
  #include <GL/glut.h>
#endif



class Graphics{
public: 
  Graphics(int w, int h);
  ~Graphics();
  // Creates the OpenGL instance
  int initialize(int argc, char *argv[]);
  
  // Starts the main loop
  void start_graphics();

  // Marks something to be drawn. Things without transparency
  // should be pushed to the front of the list. 
  static void add_drawable(Drawable *, int priority = 999999);
  static bool remove_drawable(Drawable *);
  static void add_moveable(Moveable *);
  static bool remove_moveable(Moveable *);
  
  static std::list<Drawable *> draw_list_;
  static std::list<Moveable *> move_list_;
  static std::list<int> draw_priority_;
private:
  void display_function();
  int w_, h_;

  
};



#endif