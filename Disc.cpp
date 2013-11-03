/*
  Author: Chet Gnegy
  chetgnegy@gmail.com

  Disc.cpp
  This file the Disc class. This class is used as the graphical representation of a unit generator
*/

#import "Disc.h"

//Pairs the disc with a unit generator
Disc::Disc(UnitGenerator *u, double radius){
  ugen_ = u;
  r_ = radius;
}

//Cleans up the unit generator
Disc::~Disc(){
  delete ugen_;
}

void Disc::set_location(double x, double y){};

void Disc::set_velocity(double y, double z){};
