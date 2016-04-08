#include "stdafx.h"
#include "DxSoundIdentifier.h"

DxSoundIdentifier::DxSoundIdentifier ()
{
   mySoundTime = 0;
}

DxSoundIdentifier::~DxSoundIdentifier ()
{
}

bool DxSoundIdentifier::load ( const tstring& filename, CSound* wave )
{
   myFileName = filename;

   sound = wave;

   return true;
}

void DxSoundIdentifier::loop ( bool enabled )
{
   myLoopEnabled = enabled;
}

bool DxSoundIdentifier::play ()
{
   // play the sound, checking if it should be looped or not
   myIsPlaying = true;

   if ( sound )
   {
      if ( myLoopEnabled )
         sound->Play( 0, DSBPLAY_LOOPING );
      else
         sound->Play();
   }

   return myIsPlaying;
}

bool DxSoundIdentifier::stop ()
{
   // reset time in sound and stop

   myIsPlaying = false;

   mySoundTime = 0;

   if ( sound )
   {
      sound->Stop();
      sound->Reset();
   }

   return !myIsPlaying;
}

bool DxSoundIdentifier::pause ()
{
   // save current time in sound
   

   //stop the sound
   myIsPlaying = false;

   if ( sound )
   {
      sound->Stop();
   }
   
   return !myIsPlaying;
}

bool DxSoundIdentifier::isStopped ()
{
   if ( sound )
   {
      myIsPlaying = sound->IsSoundPlaying();
   }

   return myIsPlaying;
}