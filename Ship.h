//Title: Ship.h
//Author: Ify Jacob
//Description: Ship struct for Pirate game

#ifndef SHIP_H //Include/Header Guard
#define SHIP_H //Include/Header Guard

#include <string>
#include <iostream>
#include <cstdlib>

using namespace std;

// Name: Ship struct
// Desc - Used to store data about ships
struct Ship{
  string m_type; //Type of Ship
  int m_cannon; //Cannons on Ship
  int m_toughness; //Max Toughness of ship
  int m_curToughness; //Current toughness of ship (can't exceed max)
  int m_speed; //Speed of Ship
  string m_desc; //Description of ship
  Ship(){} //Default constructor
  Ship (string type, int cannon, int toughness, int speed, string desc){ //Overloaded Constructor
    m_type = type; //Type of ship
    m_cannon = cannon; //Cannons on ship
    m_toughness = toughness; //Max Toughness of ship
    m_curToughness = toughness; //Current Toughness of ship (changes during battle)
    m_speed = speed; //Speed of ship
    m_desc = desc; //Description of ship
  }
};

#endif
