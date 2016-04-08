#include "stdafx.h"
#include "DxSound.h"

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
   soundInterface.setInterfaceType( useType );

   return &soundInterface;
}

void DxSound::setInterfaceType ( InterfaceTypes type )
{
   myInterfaceType = type;

  switch ( myInterfaceType )
   {
   case fmod:
      //fmod::system::create();
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

      //fmod::system::init();
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
      //fmod::system::update();
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
      //fmod::system::release();
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

   switch ( myInterfaceType )
   {
   case fmod:
      break;

   case directSound:
      HRESULT hr;

      // attempt to load the wave file
      char s[255];
      sprintf( s, "%s", soundFileName.c_str() );
      hr = dsound->Create( &wave, s );
      if ( SUCCEEDED( result ) )
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
      break;

   case directSound:
      isPlaying = identifier.play();
      break;

   case winNative:
      break;

   case none:
      isPlaying = identifier.play();
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
      break;

   case directSound:
      identifier.stop();
      break;

   case winNative:
      break;

   case none:
      isStopped = identifier.stop();
      break;

   default:
      break;
   }


   return isStopped;
}

// has a sound stopped playing
bool DxSound::isStopped ( DxSoundIdentifier& identifier )
{
   bool isStopped = false;

   isStopped = identifier.isStopped();

   return isStopped;
}

// pause a sound that is playing (calling play should play from paused point)
bool DxSound::pause ( DxSoundIdentifier& identifier )
{
   bool isPaused = false;

   switch ( myInterfaceType )
   {
   case fmod:
      break;

   case directSound:
      break;

   case winNative:
      break;

   case none:
      isPaused = identifier.pause();
      break;

   default:
      break;
   }


   return isPaused;
}