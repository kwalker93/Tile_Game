#include "stdafx.h"
#include "DxSound.h"

bool interfaceExists = false;

DxSound::DxSound ()
{
   extradriverdata = 0;
}

DxSound::~DxSound ()
{
}

// InterfaceTypes is multi-valued
//		foo = DxSound::getInterface( fmod | winNative | none );
DxSound* DxSound::getInterface (  unsigned int type  )
{
   // need to determine which of the given interfaces are available

   InterfaceTypes useType;

   // set the type to use to the first type given in the parameter
   if ( ( type & fmod ) != 0 )
   {
      useType = fmod;
   }
   else if ( ( type & directSound ) != 0 )
   {
      useType = directSound;
   }
   else if ( ( type & winNative ) != 0 )
   {
      useType = winNative;
   }
   else
   {
      useType = none;
   }

   static DxSound soundInterface;

   if ( !interfaceExists )
   {
      soundInterface.setInterfaceType( useType );

      interfaceExists = true;
   }

   return &soundInterface;
}

void DxSound::setInterfaceType ( InterfaceTypes type )
{
   myInterfaceType = type;

  switch ( myInterfaceType )
   {
   case fmod:
       break;

   case directSound:
      break;

   case winNative:
      break;

   case none:
      break;

   default:
      break;
   }
}

bool DxSound::init ( HWND hwnd )
{
   // initialize interface type
   // if interface type is none, do nothing

   bool result = false;
   FMOD_RESULT fresult;

   switch ( myInterfaceType )
   {
   case fmod:
      result = fmodInterface.loadAllProcAddresses();
      assert( result );
      fresult = fmodInterface.dllPtrSystem_Create( &fmSystem );
      fmodInterface.ERRCHECK( fresult );
      fresult = fmodInterface.dllPtrSystem_GetVersion( fmSystem, &version );
      fmodInterface.ERRCHECK( fresult );

      if ( version < FMOD_VERSION )
      {
         log( "FMOD lib version dosn't match header version" );
      }
      log( "FMOD interface version loaded OK" );

      fmodInterface.dllPtrSystem_Init( fmSystem, 32, FMOD_INIT_NORMAL, extradriverdata );

      break;

   case directSound:
      dsound = new CSoundManager;

      HRESULT hr;

      hr = dsound->Initialize( hwnd, DSSCL_PRIORITY );

      if ( hr != DS_OK )
         return false;

      result = true;
      break;

   case winNative:
      result = true;
      break;

   case none:
      result = true;
      break;

   default:
      result = false;
      break;
   }

   return result;
}

void DxSound::update ()
{
   // update interfaces
   switch ( myInterfaceType )
   {
   case fmod:
      fmodInterface.dllPtrSystem_Update( fmSystem );
      break;

   case directSound:
      break;

   case winNative:
      break;

   case none:
      break;

   default:
      break;
   }
}

void DxSound::shutdown ()
{
   // unload interfaces
   switch ( myInterfaceType )
   {
   case fmod:
      fmodInterface.dllPtrSystem_Close( fmSystem );
      break;

   case directSound:
      if ( dsound )
         delete dsound;

      break;

   case winNative:
      break;

   case none:
      break;

   default:
      break;
   }
}

void DxSound::releaseSound ( DxSoundIdentifier& identifier )
{
   identifier.shutdown( &fmodInterface );
}

// continuously loop through a sound
void DxSound::loop ( DxSoundIdentifier& identifier, bool enable )
{
   identifier.loop( enable );
}

// load a sound from a file
bool DxSound::load ( const tstring& soundFileName , DxSoundIdentifier& identifier )
{
   // for type "none" only need to retrieve the sound file info
   // especially need sound length

   bool result = false;
   CSound* wave = NULL;

   FMOD_RESULT fresult;
   FMOD_SOUND* fsound = NULL;

   switch ( myInterfaceType )
   {
   case fmod:
      fresult = fmodInterface.dllPtrSystem_CreateSound( fmSystem, soundFileName.c_str(), FMOD_DEFAULT, 0, &fsound );
      identifier.load( soundFileName, fsound );
      break;

   case directSound:
      HRESULT hr;

      // attempt to load the wave file
      char s[255];
      sprintf( s, "%s", soundFileName.c_str() );
      hr = dsound->Create( &wave, s );
      if ( SUCCEEDED( hr ) )
         result = identifier.load( soundFileName, wave );
      else
         result = false;
      break;

   case winNative:
      break;

   case none:
      break;

   default:
      break;
   }

   return result;
}

// start sound from saved pause time.  this time will be zero if pause was not called.
bool DxSound::play ( DxSoundIdentifier& identifier )
{
   bool isPlaying = false;
   switch ( myInterfaceType )
   {
   case fmod:
      isPlaying = identifier.play( &fmodInterface, fmSystem );
      break;

   case directSound:
      isPlaying = identifier.play();
      break;

   case winNative:
      break;

   case none:
      break;

   default:
      break;
   }

   return isPlaying;
}

// stop a sound that is playing
bool DxSound::stop ( DxSoundIdentifier& identifier )
{
   bool isStopped = false;
   switch ( myInterfaceType )
   {
   case fmod:
      identifier.stop( &fmodInterface );
      break;

   case directSound:
      identifier.stop();
      break;

   case winNative:
      break;

   case none:
      break;

   default:
      break;
   }


   return isStopped;
}

// has a sound stopped playing
bool DxSound::isPlaying ( DxSoundIdentifier& identifier )
{
   bool isStopped = false;

   isStopped = identifier.isPlaying( &fmodInterface );

   return isStopped;
}

// pause a sound that is playing (calling play should play from paused point)
bool DxSound::pause ( DxSoundIdentifier& identifier )
{
   bool isPaused = false;

   switch ( myInterfaceType )
   {
   case fmod:
      isPaused = identifier.pause( &fmodInterface );
      break;

   case directSound:
      isPaused = identifier.pause();
      break;

   case winNative:
      break;

   case none:
      break;

   default:
      break;
   }


   return isPaused;
}

void DxSound::setVolume ( DxSoundIdentifier& identifier, int volume )
{
   switch ( myInterfaceType )
   {
   case fmod:
      identifier.setVolume( volume, &fmodInterface );
      break;

   case directSound:
      identifier.setVolume( volume );
      break;

   case winNative:
      break;

   case none:
      break;

   default:
      break;
   }
}