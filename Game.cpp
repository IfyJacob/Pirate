/*****************************************
** File: Game.cpp
** Author: Ify Jacob
** Description: cpp file for Game class
*****************************************/

#include "Game.h"

// Game
// Default Constructor, runs game
Game::Game() {
  GameTitle();
  LoadShips();
  LoadPirates();
}

// LoadShips
// Reads in ship text file and stores them in ship struct list
void Game::LoadShips() {
  ifstream myFile; // initializes file that will be used for File IO
  string integer; // initializes integer that will be used for stoi
  int count = 0; // initializes count as 0

  myFile.open(PROJ2_SHIPS);

  //Loops through max num of ships and reads in each part of the ship struct using the dot operator
  //using getline and the ',' the loop reads in the type,cannon,speed, and max toughness for per ship
  for(int i = 0; i < MAX_SHIPS; i++) {
    getline(myFile, m_ships[i].m_type, ',');

    getline(myFile, integer, ',');
    m_ships[i].m_cannon = stoi(integer);

    getline(myFile, integer, ',');
    m_ships[i].m_toughness = stoi(integer);

    getline(myFile, integer, ',');
    m_ships[i].m_speed = stoi(integer);

    getline(myFile, m_ships[i].m_desc);

    count++;
  }
  cout << count << " ships loaded." << endl;
  myFile.close();
}

// LoadPirates
// Reads in pirates text file and stores them in pirates class list
void Game::LoadPirates() {
  ifstream myFile; // initializes file that will be used for File IO
  string name = "name"; // initializes name variable
  string rating = "rating"; // initializes rating variable
  string country = "country"; // initializes country variable
  string bio = "bio"; // initializes bio variable
  int rate = 0;
  int count = 0;

  myFile.open(PROJ2_PIRATES);

  //Loops through m_allPirates array and pulls a specific part of the pirate description
  //using getline then calls the pirate overloaded constructor to add the pirate to the array
  for(int i = 0; i < MAX_PIRATES; i++) {
    getline(myFile,  name, ',');

    getline(myFile,  rating, ',');
    rate = stoi(rating);

    getline(myFile,  country, ',');
    getline(myFile,  bio);

    Pirate pirateID(name, rate, country, bio);
    m_allPirates[i] = pirateID;

    count++;
  }
  cout << count << " pirates loaded." << endl;
  myFile.close();
}

// StartGame
// Given pirates and ships exist, assigns radom pirate and ship to user
void Game::StartGame() {
  Ship ship_info = m_ships[rand() % MAX_SHIPS]; // uses the ship struct and randomly assigns a ship to user
  m_myPirate = m_allPirates[rand() % MAX_PIRATES]; // uses the pirate class and randomly assings a pirate to user
  m_myPirate.SetCurShip(ship_info); // calls SetCurShip function to set the pirate ship data to the m_ship varible in Pirate.cpp

  cout << "Congratulations! " <<  m_myPirate.GetName() << " is now available to plunder!" << endl;
  cout << m_myPirate.GetName() << " is aboard a " <<   ship_info.m_type << "." << endl;

  int option = 0; // initializes the option that the user will select

  //Loop runs until the user enters a 4 to indicate their retirement
  while(option != 4) {
    cout << "What would you like to do?" << endl;
    option = MainMenu(); // calls main menu which return an int of the users choice

    //If the user does enter a 4 display score is called one last time and the game ends
    if(option == 4) {
      m_myPirate.DisplayScore();
      cout << m_myPirate.GetName() << " sails off into retirement!" << endl;
      cout << "Thanks for playing Pirates!" << endl;
    }
  }
}

// MainMenu
// Given that StarGame runs, returns an integer between 1-4
int Game::MainMenu() {
  int choice = 0; // initializes the choice that the user will select
  cout << "1. Search for Treasure" <<endl;
  cout << "2. Repair Ship" <<endl;
  cout << "3. See Score" <<endl;
  cout << "4. Retire" <<endl;

  cin >> choice;

  //Loop runs till user inputs a number between 1 and 4
  while(choice > 4 || choice < 1) {
    cout << "What would you like to do? (1-4)" << endl;
    cin >> choice;
  }

  //If the user selects 1 then SearchTreasure is called
  if(choice == 1)
    SearchTreasure();
  //If the user selects 2 then RepairShip is called
  else if(choice == 2)
    m_myPirate.RepairShip();

  //If the user selects 3 then DisplayScore is called
  else if(choice == 3)
    m_myPirate.DisplayScore();

  return choice;
}

// SearchTreasure
// Given that user inputs a 1 for main menu, facilatates a battle
void Game::SearchTreasure() {
  Pirate enemyPirate = m_allPirates[rand() % MAX_PIRATES]; // randomly assigns a pirate in m_allPirates array to be opponet
  Ship enemyShip = m_ships[rand() % MAX_SHIPS]; // randomly assigns a ship in m_ships to be enemy's ship
  cout << "You scan the horizon for prospective targets..." << endl;
  cout << "Off in the distance, you see " << enemyPirate.GetName() << " on a " <<enemyShip.m_type << endl;

  int choice = 0; // initializes the option that the user will select

  cout << "What would you like to do?" << endl;
  cout << "1. Attack " << enemyPirate.GetName() << endl;
  cout << "2. Attempt to Flee from " << enemyPirate.GetName() << endl;
  cin >> choice;

  //Loop runs until user enters a 1 or 2
  while(choice != 1 && choice != 2) {
    cout << "What would you like to do? (1-2)" << endl;
    cin >> choice;
  }

  //If user inputs a 1 the Battle function is called
  if(choice == 1)
    m_myPirate.Battle(enemyPirate , enemyShip);

  //If user inputs a 2 the Flee function is called
  if(choice == 2)
    m_myPirate.Flee(enemyPirate , enemyShip);
}

// GameTitle
// Displays Pirates!!
void GameTitle(){
  cout << "******************************************************************" << endl;
  cout << " PPPPPP   IIIIIII  RRRRRR    AAAAA   TTTTTTT  EEEEEEE  SSSSSSS  !!" << endl;
  cout << " P     P     I     R     R  A     A     T     E        S        !!" << endl;
  cout << " P     P     I     R     R  A     A     T     E        S        !!" << endl;
  cout << " PPPPPP      I     RRRRRR   AAAAAAA     T     EEEEEEE  SSSSSSS  !!" << endl;
  cout << " P           I     RR       A     A     T     E              S  !!" << endl;
  cout << " P           I     R  R     A     A     T     E              S    " << endl;
  cout << " P        IIIIIII  R    R   A     A     T     EEEEEEE  SSSSSSS  !!" << endl;
  cout << "******************************************************************" << endl;
}
