
#include <stdafx.h>
#include <Windows.h>
#include <string>

#include "WinApplFramework/GameMessages.h"

using namespace std;

bool GameMessages::startNewGame;

//=======================================================================
GameMessages::GameMessages ( )
{
   this->startNewGame = false;
}

//=======================================================================
GameMessages::~GameMessages ( )
{
}

//=======================================================================
int GameMessages::aboutMessageBox()
{
   return MessageBox(NULL, "", "About", MB_YESNO | MB_ICONEXCLAMATION );
}

//=======================================================================
int GameMessages::controlsMessageBox()
{
   string line0 = "Winter's coming, and there's only enough acorns in the forest for one family of squirrels!\n";
   string line1 = "In Underground Squirrel Brawl, players take turns destroying the opponent's squirrels.\n\n";

   string line2 = "How to Play: \n";

   string line3 = "1. Click on one of your squirrels to select them.\n";
   string line4 = "2. Use the arrow keys to move the selected unit on the board. Be mindful of the Info page, since each squirrel has a limited movement range.\n";
   string line5 = "3. When your selected squirrel is within attacking range of the other player's squirrels, you can damage them.\n";
   string line6 = "4. Once a squirrel's health goes to 0, they're toast, so be careful!\n\n";
   string line7 = "The last player with squirrels remaining wins the game!\n\n\n\n";

   string line8 = "Oh, by the way...\n\nYou better win quickly, or else the nearby river might engulf you with its daily flooding!\n";
   
   
   string concatString = line0 + line1 + line2 + line3 + line4 + line5 + line6 + line7 + line8;

   return MessageBox(NULL, concatString.c_str(), "Controls", MB_YESNO | MB_ICONEXCLAMATION );
}
