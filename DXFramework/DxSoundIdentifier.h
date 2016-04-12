//-------------------------------------------------------------------------
// Class that contains the actual sound.
//
// To use this, declare a DxSoundIdentifier variable 
//    and use it as a parameter in DxSound functions
//-------------------------------------------------------------------------

#pragma once

#if !defined ( __DxSOUNDIDENTIFIER_H__ )
#define __DxSOUNDIDENTIFIER_H__

#include "Utilities/TTypes.h"
#include "DirectSound.h"
#include "loadFMOD.h"

class DxSoundIdentifier
{
   friend class DxSound;
public:
   DxSoundIdentifier ();
   ~DxSoundIdentifier ();

   tstring fileName () { return myFileName; }

private:
   bool shutdown ( loadFMOD* fmodInterface = NULL );

   bool load ( const tstring& filename, CSound* wave );
   bool load ( const tstring& filename, FMOD_SOUND* fsound );

   void loop ( bool enabled = true );

   bool play ( loadFMOD* fmodInterface = NULL, FMOD_SYSTEM* fmSystem = NULL );
   bool stop ( loadFMOD* fmodInterface = NULL );
   bool pause ( loadFMOD* fmodInterface = NULL );
   
   bool isPlaying ( loadFMOD* fmodInterface = NULL );
   bool isLooping () { return myLoopEnabled; }

   void setVolume ( int volume, loadFMOD* fmodInterface = NULL );

private:
   // the actual sound for DirectSound
   CSound* myDsound;

   // volume setting for DirectSound
   long myVolume;

   // the actual sound for FMOD
   FMOD_SOUND* myFsound;
   FMOD_CHANNEL* myFchannel;

   bool myIsPlaying;
   FMOD_BOOL myIsPaused;
   bool myLoopEnabled;

   // current time position in the sound
   int mySoundTime;

   // sound file name
   tstring myFileName;
};

#endif