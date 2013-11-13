/*
 *  AudioHockeyTable.cpp
 *
 *  Created on: Nov 2, 2013
 *      Author: Chet Gnegy - chetgnegy@gmail.com
 *      
 *      
 *      Uses RtAudio Library and OpenGL
 */

#include <stdio.h>
#include <math.h>
#include <iostream>

#include "UGenChain.h"
#include "Disc.h"
#include "World.h"
#include "Graphics.h"
#include "Physics.h"
#include "Menu.h"

int main(int argc, char *argv[]) {
  srand (time(NULL));

  Graphics *myGraphics = new Graphics(960, 600);
  myGraphics->initialize(argc, argv);
  

  UGenChain *myChain = new UGenChain();
  //myChain->initialize();
  
  Chorus *d = new Chorus(44100);
  //myChain->add_effect(d);
  //while (true){
  //  usleep(1000000);
  //  d->set_params(.99*rand()/(1.0*RAND_MAX)+.01, .99*rand()/(1.0*RAND_MAX));
  //}
  
  Menu *myMenu = new Menu();
  World *myWorld = new World(30, 30, 9, 0);
  
  Graphics::add_drawable(myMenu, 1);
  Graphics::add_moveable(myMenu);
  
  Graphics::add_drawable(myWorld, 2);
  Physics::set_bounds(30*(1-2*World::kWallThickness), 30*(1-2*World::kWallThickness), 9, 0);
  

  

  
  // Disc *myDisc = new Disc(d, 4, false);
  // Graphics::add_drawable(myDisc);



  myGraphics->start_graphics();
  
  
  delete myWorld;
  delete myChain;
  return 1;

}