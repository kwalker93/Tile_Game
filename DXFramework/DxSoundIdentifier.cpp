#include "stdafx.h"
#include "DxSoundIdentifier.h"

DxSoundIdentifier::DxSoundIdentifier ()
{
   mySoundTime = 0;

   myFchannel = 0;

   myVolume = 0;

   myIsPaused = false;
   myIsPlaying = false;
   myLoopEnabled = false;

   myDsound = NULL;
   myFsound = NULL;
}

DxSoundIdentifier::~DxSoundIdentifier ()
{
}

bool DxSoundIdentifier::load ( const tstring& filename, CSound* wave )
{
   myFileName = filename;

   myDsound = wave;

   return true;
}

bool DxSoundIdentifier::load ( const tstring& filename, FMOD_SOUND* fsound )
{
   myFileName = filename;

   myFsound = fsound;

   return true;
}

bool DxSoundIdentifier::shutdown ( loadFMOD* fmodInterface )
{
   if ( myFsound )
      fmodInterface->dllPtrSound_Release( myFsound );
   
   return true;
}

void DxSoundIdentifier::loop ( bool enabled )
{
   myLoopEnabled = enabled;
}

bool DxSoundIdentifier::play ( loadFMOD* fmodInterface, FMOD_SYSTEM* fmSystem )
{
   // play the sound, checking if it should be looped or not  
   if ( myFsound && myIsPaused )
   {
      fmodInterface->dllPtrChannel_SetPaused( myFchannel, false );
      fmodInterface->dllPtrChannel_GetPaused( myFchannel, &myIsPaused );
   }
   else if ( myFsound && !myIsPlaying )
   {
      if ( myLoopEnabled )
      {
         fmodInterface->dllPtrSound_SetMode( myFsound, FMOD_LOOP_NORMAL );
         fmodInterface->dllPtrSystem_PlaySound( fmSystem, myFsound, 0, false, &myFchannel );
      }
      else
      {
         fmodInterface->dllPtrSound_SetMode( myFsound, FMOD_LOOP_OFF );
         fmodInterface->dllPtrSystem_PlaySound( fmSystem, myFsound, 0, false, &myFchannel );
      }
      fmodInterface->dllPtrChannel_IsPlaying( myFchannel, &myIsPlaying );
   }
   else if ( myDsound )
   {
      if ( myLoopEnabled )
      {
         myDsound->Play( 0, DSBPLAY_LOOPING, myVolume );
      }
      else
      {
         myDsound->Play( 0, 0, myVolume );
      }

      myIsPlaying = myDsound->IsSoundPlaying();
   }

   return myIsPlaying;
}

bool DxSoundIdentifier::stop ( loadFMOD* fmodInterface )
{
   // reset time in sound and stop
   mySoundTime = 0;

   if ( myFsound )
   {
      fmodInterface->dllPtrChannel_Stop( myFchannel );
      fmodInterface->dllPtrChannel_IsPlaying( myFchannel, &myIsPlaying );
   }
   else if ( myDsound )
   {
      myDsound->Stop();
      myDsound->Reset();
   }

   return !myIsPlaying;
}

bool DxSoundIdentifier::pause ( loadFMOD* fmodInterface )
{
   // save current time in sound
   

   //pause the sound
   if ( myFsound )
   {
      fmodInterface->dllPtrChannel_SetPaused( myFchannel, true );
      fmodInterface->dllPtrChannel_GetPaused( myFchannel, &myIsPaused );
   }
   else if ( myDsound )
   {
      HRESULT hr = myDsound->Stop();
      myIsPaused = SUCCEEDED( hr );
   }
   
   return myIsPaused;
}

bool DxSoundIdentifier::isPlaying ( loadFMOD* fmodInterface )
{
   if ( myFsound )
   {
      fmodInterface->dllPtrChannel_IsPlaying( myFchannel, &myIsPlaying );
   }
   else if ( myDsound )
   {
      myIsPlaying = myDsound->IsSoundPlaying();
   }

   return myIsPlaying;
}

void DxSoundIdentifier::setVolume ( int volume, loadFMOD* fmodInterface )
{
   if ( myFsound )
   {
      float fvol = (float)volume/100;
      fmodInterface->dllPtrChannel_SetVolume( myFchannel, fvol );
   }
   else if ( myDsound )
   {
      myVolume = volume - 100;

      myVolume *= 100;
   }
}