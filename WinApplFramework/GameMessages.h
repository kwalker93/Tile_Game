#pragma once
#if !defined(__GAMEMESSAGES_H__)
#define __GAMEMESSAGES_H__

#include <stdafx.h>
#include <Windows.h>

class GameMessages
{
public:
   GameMessages ( );
  ~GameMessages ( );

   int aboutMessageBox();
   int controlsMessageBox();
   
   static bool startNewGame;
   static bool getNewGameStatus(){ return GameMessages::startNewGame; }
   static void signalStartNewGame(){ GameMessages::startNewGame = true; }
}; 

#endif