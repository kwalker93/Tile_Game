//-------------------------------------------------------------------------------------------
// Sound interface class.
//
// First declare a DxSound pointer variable.  You will need this to do anything with sound.
// Also declare a DxSoundIdentifier variable for every sound you will have in your program.
//
// Get the interface by calling getInterface() first to retrieve the desired sound interface.
//    example: mySoundInterface = DxSound::getInterface().
// Then call init().
//    example: mySoundInterface->init( hWnd() );
//
// To use sounds, create a DxSoundIdentifier variable
//    and feed it into these functions.
//
// You must first load a sound file into the DxSoundIdentifier
//    using DxSound::load().
//    example: mySoundInterface->load( filepath, mySoundIdentifier );
//
// When closing a program, call releaseSound() for each sound in your program.
// Then call shutdown.
//-------------------------------------------------------------------------------------------

#pragma once


#if !defined ( DxSOUND_H__ )
#define DxSOUND_H__

#include <windows.h>
#include <mmsystem.h>
#include "Utilities/NonCopyable.h"
#include "Utilities/TTypes.h"
#include "Utilities/Logger.h"
#include "DxSoundIdentifier.h"
#include "DirectSound.h"
#include "loadFMOD.h"

#pragma comment( lib, "Winmm.lib" )


class DxSound : public NonCopyable
{

private:
   DxSound ();
   ~DxSound ();

public:

   enum InterfaceTypes { fmod = 1, directSound = 2, winNative = 4, none = 8 };

   // InterfaceTypes is multi-valued
   //		foo = DxSound::getInterface( fmod | winNative | none );
   static DxSound* getInterface (  unsigned int type = none  );

   bool init ( HWND hwnd );
   void update ();
   void shutdown ();

   // release a sound (required if interface is set to fmod)
   void releaseSound ( DxSoundIdentifier& identifier );

   bool play ( DxSoundIdentifier& identifier );

   // continuously loop through a sound
   void loop ( DxSoundIdentifier& identifier, bool enable = true );

   // load a sound from a file
   bool load ( const tstring& soundFileName , DxSoundIdentifier& identifier );

   // stop a sound that is playing
   bool stop ( DxSoundIdentifier& identifier );

   // has a sound stopped playing
   bool isPlaying ( DxSoundIdentifier& identifier );

   // pause a sound that is playing (calling play should play from paused point)
   bool pause ( DxSoundIdentifier& identifier );

   // if volume is 0 or lower, then sound is muted.  if volume is 100 or greater, then sound is set to max.
   void setVolume ( DxSoundIdentifier& identifier, int volume = 100 );

   //types of sound: music, sfx

private:
   void setInterfaceType ( InterfaceTypes type );

private:
   InterfaceTypes myInterfaceType;

   static bool interfaceInitialized;

   // DirectSound interface
   CSoundManager* dsound;

   // FMOD interface
   loadFMOD fmodInterface;

   FMOD_SYSTEM* fmSystem;
   unsigned int version;
   void* extradriverdata;

};

#endif