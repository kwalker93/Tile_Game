
//=======================================================================
// Nathan Contreras
//   GameMessages header
//      Allows the user to create a GameMessages class and create message
//      boxes that are predefined, or customized.
//=======================================================================

#pragma once
#if !defined(__GAMEMESSAGES_H__)
#define __GAMEMESSAGES_H__

#include "stdafx.h"
#include <Windows.h>
#include <string>

using namespace std;

class GameMessages
{
public:
   GameMessages ( );
  ~GameMessages ( );

   int aboutMessageBox();
   int controlsMessageBox();
   int newGameMessageBox();
   int unexpectedErrorMessageBox();

   //=====================================================================
   // Allowed values for customMessageBox():
   //   MB_ABORTRETRYIGNORE || 0x00000002L
   //   MB_CANCELTRYCONTINUE || 0x00000006L
   //   MB_HELP || 0x00004000L
   //   MB_OK || 0x00000000L
   //   MB_OKCANCEL || 0x00000001L
   //   MB_RETRYCANCEL || 0x00000005L
   //   MB_YESNO || 0x00000004L
   //   MB_YESNOCANCEL || 0x00000003L
   //=======================================================================
   int customMessageBox( LPCSTR message, LPCSTR title, int style );
   
   static bool startNewGame;
   static bool exitGame;

   static bool getNewGameStatus(){ return GameMessages::startNewGame; }
   static void signalStartNewGame(){ GameMessages::startNewGame = true; }
   static void signalExitGame(){ GameMessages::exitGame = true; }
}; 

#endif