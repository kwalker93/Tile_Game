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

class DxSoundIdentifier
{
   friend class DxSound;
public:
   DxSoundIdentifier ();
   ~DxSoundIdentifier ();

   tstring fileName () { return myFileName; }

private:
   bool load ( const tstring& filename, CSound* wave );

   void loop ( bool enabled = true );

   bool play ();
   bool stop ();
   bool pause ();
   
   bool isStopped ();
   bool isLooping () { return myLoopEnabled; }

private:
   // the actual sound for DirectSound
   CSound* sound;

   bool myIsPlaying;
   bool myLoopEnabled;

   // current time position in the sound
   int mySoundTime;

   // sound file name
   tstring myFileName;
};

#endif