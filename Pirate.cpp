/*****************************************
** File: Pirate.cpp
** Author: Ify Jacob
** Description: cpp file for Pirate class
*****************************************/

#include "Pirate.h"

// Pirate
// Default constructor for pirate class
Pirate::Pirate() {
  m_pirateName = "Ify Jacob"; // sets default value for m_pirateName
  m_pirateRating = 95; // sets default value for m_pirateRating
  m_pirateOrigin = "Maryland"; // sets default value for m_pirateOrigin
  m_pirateDesc = "Skilled nba 2k gamer ready to take his talents to the sea"; // sets default value for m_pirateDesc
}

// Pirate
// Overloaded constructor for pirate class
Pirate::Pirate(string name, int rating, string origin, string desc) {
  m_pirateName = name; // sets value for m_pirateName equal to name parameter
  m_pirateRating = rating; // sets value for m_pirateRating equal to rating parameter
  m_pirateOrigin = origin; // sets value for m_pirateOrigin equal to origin parameter
  m_pirateDesc = desc; // sets value for m_pirateDesc equal to desc parameter
}

// GetName
// Given that a pirate exists, Returns m_pirateName value
string Pirate::GetName() {
  return m_pirateName;
}

// GetRating
// Given that a pirate exists, Returns m_pirateRating value
int Pirate::GetRating() {
  return m_pirateRating;
}

//Function not used in project
void Pirate::SetRating(int rating) {
  if(rating > 0) {
    m_pirateRating = rating;
  }
  else
    m_pirateRating = 1;
}

// GetOrigin
// Given that a pirate exists, Returns m_pirateOrigin value
string Pirate::GetOrigin() {
  return m_pirateOrigin;
}

// GetDesc
// Given that a pirate exists, Returns m_pirateDesc value
string Pirate::GetDesc() {
  return m_pirateDesc;
}

// SetCurShip
// Given that a pirate ship exists, sets m_curShip equal to pirate ship
void Pirate::SetCurShip(Ship curShip) {
  m_curShip = curShip;
  m_curShip.m_curToughness =  m_curShip.m_toughness;
}

// CalcTreasure
// Given that the user wins battle, reads in enemyship info
// calculates treasure earned
void Pirate::CalcTreasure(Ship enemyShip) {
  int treasureGained = (enemyShip.m_cannon + enemyShip.m_toughness + enemyShip.m_speed) / 3;
  cout << m_pirateName << " shares " << treasureGained << " treasure with their crew!" << endl;
  m_pirateCargo += treasureGained;
}

// Battle
// Given another pirate and ship, has user battle enemy till toughness < 0
void Pirate::Battle(Pirate enemyPirate, Ship enemyShip) {
  cout << "A naval battle of the ages commences between " << m_pirateName << " and " << enemyPirate.GetName() << endl;
  int max = 100; // sets a max the number the rand num generator can have
  int min = 1; // sets a min the number the rand num generator can have

  enemyShip.m_curToughness = enemyShip.m_toughness; // initially sets curToughness to max toughness for enemy before battle

  //If the users ships toughness is below 1 they must repair their ship before entering battle
  // (ends battle function and adds a day)
  if(m_curShip.m_curToughness < 1) {
    cout << "Your current toughness is below 1 repair your ship before you battle!" << endl;
    m_pirateDays += 1;
    return;
  }

  //Loops runs until either the user or enemy toughness reaches 0
  while(m_curShip.m_curToughness > 0 && enemyShip.m_curToughness > 0) {
    int myHit = 0; // initializes number of hits by user to be 0
    int enemyHit = 0; // initializes number of hits by enemy to be 0

    //Loop generates a random number for each cannon
    for(int i=0; i< m_curShip.m_cannon; i++) {
      int randNum = (rand() % (max - min + 1) + min); // generates a random number variable
      //If the random number is less than or equal to the pirates rating the cannon hits
      if(randNum <= m_pirateRating)
        myHit += 1;
    }

    cout << m_pirateName << " fires " << m_curShip.m_cannon << " cannons!" << endl;
    cout << myHit << " shots hit!" << endl;

    enemyShip.m_curToughness -= myHit; // upadates enemy's curToughness by subtracting number of hits

    //If the enemy ship toughness is 0 the user wins and battle ends
    if(enemyShip.m_curToughness <= 0) {
      cout << "You win!" << endl;
      CalcTreasure(enemyShip); // calls calc treasure and produces cout statement
      m_pirateDays += 1;
      return;
    }

    //The following loops and if statements below are exactly the same as the top statement except its
    // the enemies turn
    for(int i=0; i< enemyShip.m_cannon; i++) {
      int randNum = (rand() % (max - min + 1) + min);
      if(randNum <= enemyPirate.GetRating())
        enemyHit += 1;
    }

    cout << enemyPirate.GetName() << " fires " << enemyShip.m_cannon << " back!" << endl;
    cout << enemyHit << " shots hit!" << endl;

    m_curShip.m_curToughness -= enemyHit;

    //If the users ship toughness is below 1 the user loses and their cargo is halved
    if(m_curShip.m_curToughness <= 0) {
      cout << "You lose!" << endl;
      m_pirateCargo = m_pirateCargo / 2;
      m_pirateDays += 1;
      return;
    }
  }
}

// RepairShip
// Given pirate and ship exist ,Allows pirate to repair ship
void Pirate::RepairShip() {
  //If the current toughness equal the max toughness the user doesn't need to repair the ship
  if(m_curShip.m_curToughness == m_curShip.m_toughness) {
    cout << "Your ship is already at max toughness!" << endl;
  }
  //The user repairs the ship and calculates the number of days elasped
  else {
    int numDays =  (m_curShip.m_toughness - m_curShip.m_curToughness);
    m_curShip.m_curToughness = m_curShip.m_toughness;
    m_pirateDays += numDays;
    cout << "It takes " << numDays << " days to repair your " <<  m_curShip.m_type << endl;
  }
}

// Flee
// Given another pirate and ship, compares ship speeds
// Decides whether Pirates flees successfully
void Pirate::Flee(Pirate enemyPirate, Ship enemyShip) {
  cout << "You attempt to flee from " << enemyPirate.GetName() << endl;

  //If the user's speed is faster than the enemies ship speed or equal in speed they escape
  //If the user is slower than the enemy the battle function is called (one day is added either way)
  if(m_curShip.m_speed >= enemyShip.m_speed) {
    cout << "You narrowly escape from "<< enemyPirate.GetName() << endl;
    m_pirateDays += 1;
  }
  else {
    cout << "You fail to escape from "<< enemyPirate.GetName() << endl;
    m_pirateDays += 1;
    Battle(enemyPirate, enemyShip);
  }
}

// DisplayScore
// Given pirate and ship exist, Displays all info about pirate
void Pirate::DisplayScore() {
  cout << "**********************" << endl;
  cout << "Name: " << m_pirateName << endl;
  cout << "Rating: " << m_pirateRating << endl;
  cout << "Country of Origin: " << m_pirateOrigin << endl;
  cout << "Description: " << m_pirateDesc << endl;
  cout << "Days Sailing: " << m_pirateDays << endl;
  cout << "Cargo Captured: " << m_pirateCargo << endl;
  //If there is more than one day the ration can be calculated
  if(m_pirateDays > 0) {
    cout.setf(ios::fixed); // changes format of output
    cout.setf(ios::showpoint); // shows numbers after decimal
    cout.precision(2); // shows two numbers after decimal point
    cout << "Cargo Per Day: " <<  double(m_pirateCargo) / double(m_pirateDays) << endl;
  }
  //If the game just started the user has 0 days and 0 cargo to avoid error it displays Nan
  else
    cout << "Cargo Per Day: Nan" << endl;
  cout << "Ship Type: " << m_curShip.m_type << endl;
  cout << "Ship Cannons: " << m_curShip.m_cannon << endl;
  cout << "Ship Current Toughness: " << m_curShip.m_curToughness << endl;
  cout << "Ship Max Toughness: " << m_curShip.m_toughness << endl;
  cout << "Ship Speed: " << m_curShip.m_speed << endl;
  cout << "**********************" << endl;
}
