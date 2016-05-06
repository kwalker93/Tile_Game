
//=======================================================================
// Nathan Contreras
//   GameMessages class
//      Allows the user to create a GameMessages class and create message
//      boxes that are predefined, or customized.
//=======================================================================

#include <stdafx.h>
#include <Windows.h>
#include <string>

#include "WinApplFramework/GameMessages.h"

using namespace std;

bool GameMessages::startNewGame;
bool GameMessages::exitGame;

//=======================================================================
GameMessages::GameMessages ( )
{
   startNewGame = false;
}

//=======================================================================
GameMessages::~GameMessages ( )
{

}

//=======================================================================
int GameMessages::aboutMessageBox()
{
   string line0 = "UNDERGROUND SQUIRREL BRAWL\n\n";
   string line1 = "Developed by:\n";
   string line2 = "Nathan Contreras\n";
   string line3 = "Jacinto Molina\n";
   string line4 = "Kellen Walker\n\n";
   string line5 = "Northwest Vista College\n";
   string line6 = "Project Development I - GAME 2332-001\n";
   string line7 = "Spring 2016\n\n";
   string line8 = "Version 1.0";

   string concatString = line0 + line1 + line2 + line3 + line4 + line5 + line6 + line7 + line8;
   
   return MessageBox(NULL, concatString.c_str(), "About", MB_OK | MB_ICONEXCLAMATION );
}

//=======================================================================
int GameMessages::controlsMessageBox()
{
   string line0 = "Winter's coming, and there's only enough acorns in the forest for one family of squirrels!\n";
   string line1 = "In Underground Squirrel Brawl, players take turns destroying the opponent's squirrels.\n\n";

   string line2 = "How to Play: \n";

   string line3 = "1. Click on one of your squirrels to select them.\n";
   string line4 = "2. Use the arrow keys to move the selected unit on the board. Be mindful of the Info page, since each squirrel has a limited movement range.\n";
   string line5 = "3. After you've moved your selected squirrel to where you want, hit the 'ENTER' key to enter your attack phase.\n";
   string line6 = "4. While in the attack phase, a red cursor can be moved around your selected squirrel with the arrow keys.\n"; 
   string line7 = "5. When your attack cursor is highlighting an enemy squirrel, you can then press the 'SHIFT' key to damage them. If no squirrel is highlighted, pressing 'SHIFT' will simply end your turn.\n";   

   string line8 = "7. Once a squirrel's health goes to 0, they're toast, so be careful!\n\n";
   string line9 = "The last player with squirrels remaining wins the game!\n\n\n\n";

   string line10 = "Oh, by the way...\n\nYou better win quickly, or else the nearby river might engulf you with its daily flooding!\n";
   
   string concatString = line0 + line1 + line2 + line3 + line4 + line5 + line6 + line7 + line8 + line9 + line10;

   return MessageBox(NULL, concatString.c_str(), "Controls", MB_YESNO | MB_ICONEXCLAMATION );
}

//=======================================================================
int GameMessages::newGameMessageBox()
{
   return MessageBox(NULL, "Are you sure you want to start a new game?", "Start a new game?", MB_YESNO);
}

//=======================================================================
int GameMessages::unexpectedErrorMessageBox()
{
   return MessageBox(NULL, "ERROR ERROR, DEFAULT CASE ACHIEVED", "WARNING: ACORNS DETONATED", MB_OK);
}

//=======================================================================
int GameMessages::customMessageBox( LPCSTR message, LPCSTR title, int style )
{
   return MessageBox(NULL, message, title, style);
}