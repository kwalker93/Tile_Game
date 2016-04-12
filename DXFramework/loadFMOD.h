#pragma once

#if !defined ( __LoadFMOD_H__ )
#define __LoadFMOD_H__


#include <cstdio>
#include <cstddef>
#include <cassert>
#include <iostream>
#include <windows.h>
#include <tchar.h>

#include "Utilities/TTypes.h"
#include "fmod.hpp"

class loadFMOD
{
public:

	typedef FMOD_RESULT F_API TypeFMOD_System_Create                 (FMOD_SYSTEM **system); 

	typedef FMOD_RESULT F_API TypeFMOD_System_Init                   (FMOD_SYSTEM *system, int maxchannels, FMOD_INITFLAGS flags, void *extradriverdata);
	typedef FMOD_RESULT F_API TypeFMOD_System_Close                  (FMOD_SYSTEM *system);
	typedef FMOD_RESULT F_API TypeFMOD_System_Update                 (FMOD_SYSTEM *system);
	typedef FMOD_RESULT F_API TypeFMOD_System_GetVersion             (FMOD_SYSTEM *system, unsigned int *version);
	typedef FMOD_RESULT F_API TypeFMOD_System_CreateSound            (FMOD_SYSTEM *system, const char *name_or_data, FMOD_MODE mode, FMOD_CREATESOUNDEXINFO *exinfo, FMOD_SOUND **sound);
	typedef FMOD_RESULT F_API TypeFMOD_System_PlaySound              (FMOD_SYSTEM *system, FMOD_SOUND *sound, FMOD_CHANNELGROUP *channelgroup, FMOD_BOOL paused, FMOD_CHANNEL **channel);
	typedef FMOD_RESULT F_API TypeFMOD_Sound_Release                 (FMOD_SOUND *sound);
	typedef FMOD_RESULT F_API TypeFMOD_System_CreateChannelGroup     (FMOD_SYSTEM *system, const char *name, FMOD_CHANNELGROUP **channelgroup);

	typedef FMOD_RESULT F_API TypeFMOD_Sound_SetMode                 (FMOD_SOUND *sound, FMOD_MODE mode);
	typedef FMOD_RESULT F_API TypeFMOD_Sound_GetMode                 (FMOD_SOUND *sound, FMOD_MODE *mode);
	typedef FMOD_RESULT F_API TypeFMOD_Sound_SetLoopCount            (FMOD_SOUND *sound, int loopcount);
	typedef FMOD_RESULT F_API TypeFMOD_Sound_GetLoopCount            (FMOD_SOUND *sound, int *loopcount);
	typedef FMOD_RESULT F_API TypeFMOD_Sound_SetLoopPoints           (FMOD_SOUND *sound, unsigned int loopstart, FMOD_TIMEUNIT loopstarttype, unsigned int loopend, FMOD_TIMEUNIT loopendtype);
	typedef FMOD_RESULT F_API TypeFMOD_Sound_GetLoopPoints           (FMOD_SOUND *sound, unsigned int *loopstart, FMOD_TIMEUNIT loopstarttype, unsigned int *loopend, FMOD_TIMEUNIT loopendtype);
	typedef FMOD_RESULT F_API TypeFMOD_Sound_GetName                 (FMOD_SOUND *sound, char *name, int namelen);
	typedef FMOD_RESULT F_API TypeFMOD_Sound_GetLength               (FMOD_SOUND *sound, unsigned int *length, FMOD_TIMEUNIT lengthtype);


	typedef FMOD_RESULT F_API TypeFMOD_Channel_Stop                  (FMOD_CHANNEL *channel);
	typedef FMOD_RESULT F_API TypeFMOD_Channel_SetPaused             (FMOD_CHANNEL *channel, FMOD_BOOL paused);
	typedef FMOD_RESULT F_API TypeFMOD_Channel_GetPaused             (FMOD_CHANNEL *channel, FMOD_BOOL *paused);
	typedef FMOD_RESULT F_API TypeFMOD_Channel_SetVolume             (FMOD_CHANNEL *channel, float volume);
	typedef FMOD_RESULT F_API TypeFMOD_Channel_GetVolume             (FMOD_CHANNEL *channel, float *volume);
   typedef FMOD_RESULT F_API TypeFMOD_Channel_IsPlaying             (FMOD_CHANNEL *channel, bool *isPlaying);

	typedef FMOD_RESULT F_API TypeFMOD_Channel_SetMode               (FMOD_CHANNEL *channel, FMOD_MODE mode);
	typedef FMOD_RESULT F_API TypeFMOD_Channel_GetMode               (FMOD_CHANNEL *channel, FMOD_MODE *mode);
	typedef FMOD_RESULT F_API TypeFMOD_Channel_SetLoopCount          (FMOD_CHANNEL *channel, int loopcount);
	typedef FMOD_RESULT F_API TypeFMOD_Channel_GetLoopCount          (FMOD_CHANNEL *channel, int *loopcount);
	typedef FMOD_RESULT F_API TypeFMOD_Channel_SetLoopPoints         (FMOD_CHANNEL *channel, unsigned int loopstart, FMOD_TIMEUNIT loopstarttype, unsigned int loopend, FMOD_TIMEUNIT loopendtype);
	typedef FMOD_RESULT F_API TypeFMOD_Channel_GetLoopPoints         (FMOD_CHANNEL *channel, unsigned int *loopstart, FMOD_TIMEUNIT loopstarttype, unsigned int *loopend, FMOD_TIMEUNIT loopendtype);



	//----------------------------------------------------------------------------------------

	TypeFMOD_System_Create                *dllPtrSystem_Create;
	TypeFMOD_System_Init                  *dllPtrSystem_Init;
	TypeFMOD_System_Close                 *dllPtrSystem_Close;
	TypeFMOD_System_Update                *dllPtrSystem_Update;
	TypeFMOD_System_GetVersion            *dllPtrSystem_GetVersion;
	TypeFMOD_System_CreateSound           *dllPtrSystem_CreateSound;
	TypeFMOD_System_PlaySound             *dllPtrSystem_PlaySound;
	TypeFMOD_Sound_Release                *dllPtrSound_Release;
	TypeFMOD_System_CreateChannelGroup    *dllPtrSystem_CreateChannelGroup;
	TypeFMOD_Sound_SetMode                *dllPtrSound_SetMode;
	TypeFMOD_Sound_GetMode                *dllPtrSound_GetMode;
	TypeFMOD_Sound_SetLoopCount           *dllPtrSound_SetLoopCount;
	TypeFMOD_Sound_GetLoopCount           *dllPtrSound_GetLoopCount;
	TypeFMOD_Sound_SetLoopPoints          *dllPtrSound_SetLoopPoints;
	TypeFMOD_Sound_GetLoopPoints          *dllPtrSound_GetLoopPoints;
	TypeFMOD_Sound_GetName                *dllPtrSound_GetName;
	TypeFMOD_Sound_GetLength              *dllPtrSound_GetLength;
	TypeFMOD_Channel_Stop                 *dllPtrChannel_Stop;
	TypeFMOD_Channel_SetPaused            *dllPtrChannel_SetPaused;
	TypeFMOD_Channel_GetPaused            *dllPtrChannel_GetPaused;
	TypeFMOD_Channel_SetVolume            *dllPtrChannel_SetVolume;
	TypeFMOD_Channel_GetVolume            *dllPtrChannel_GetVolume;
   TypeFMOD_Channel_IsPlaying            *dllPtrChannel_IsPlaying;
	TypeFMOD_Channel_SetMode              *dllPtrChannel_SetMode;
	TypeFMOD_Channel_GetMode              *dllPtrChannel_GetMode;
	TypeFMOD_Channel_SetLoopCount         *dllPtrChannel_SetLoopCount;
	TypeFMOD_Channel_GetLoopCount         *dllPtrChannel_GetLoopCount;
	TypeFMOD_Channel_SetLoopPoints        *dllPtrChannel_SetLoopPoints;
	TypeFMOD_Channel_GetLoopPoints        *dllPtrChannel_GetLoopPoints;


public:
	loadFMOD ();
	~loadFMOD ();

	bool loadAllProcAddresses ();

	bool checkDllPtr ( void* p, const TCHAR* name );

	tstring assetFile ( const tstring& filename );

	void ERRCHECK ( FMOD_RESULT result );

private:

	HINSTANCE fmodInst;
	FMOD_SYSTEM* fmSystem;
};

#endif