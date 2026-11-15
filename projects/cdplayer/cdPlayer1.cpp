// cdPlayer1.cpp: implementation of the cdPlayer class.
//
//
//	TODO: 
//		- zamienic wypisywanie bledow na rzucanie wyjatkow
//////////////////////////////////////////////////////////////////////

#include "cdPlayer1.h"

#include <windows.h>
#include <iostream.h>
#include <stdio.h>
#include <string.h>

static char returnStr[255];		// tutaj beda zwracane kody wyjscia
static char commandBuff[255];	// tutaj przechowywane jest polecenie

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

cdPlayer::cdPlayer()
{
}

cdPlayer::~cdPlayer()
{
	sendCommand ("stop cdaudio");
	sendCommand ("close cdaudio");
}





//////////////////////////////////////////////////////////////////////
// Play track from 'from' to 'to'
//////////////////////////////////////////////////////////////////////
void cdPlayer::play(unsigned from, unsigned to)
{
	// przygotowanie komendy
	if (to)
		sprintf(commandBuff, "play cdaudio from %d to %d", from, to);
	else
		sprintf(commandBuff, "play cdaudio from %d", from);

	int result;
	if ( (result = sendCommand(commandBuff) ) != S_OK)		// rzucamy wyjatek
	{
		//throw ex("cdPlayer::play(): cannot play a track");
		mciGetErrorString (result, returnStr,sizeof(returnStr));
		cerr << "cannot play a track:" << returnStr << endl;
	}
}




//////////////////////////////////////////////////////////////////////
// Stop playing
//////////////////////////////////////////////////////////////////////
void cdPlayer::stop()
{
	int result;
	
	if ( (result = sendCommand ("stop cdaudio"))!= S_OK)		// rzucamy wyjatek
	{
		//throw ex("cdPlayer::stop(): cannot play a track");
		mciGetErrorString (result, returnStr,sizeof(returnStr));
		cerr << "cannot stop:" << returnStr << endl;
	}
}




//////////////////////////////////////////////////////////////////////
// Set position to track 'track', time m:s, frame f
//	Similar to play() method.
//////////////////////////////////////////////////////////////////////
void cdPlayer::setPosition(unsigned track, unsigned m, unsigned s, unsigned f)
{
	int result;

	sprintf (commandBuff, "play cdaudio from %d:%d:%d:%d", track, m, s, f);
	result = sendCommand (commandBuff);
	if (result != S_OK)
	{
		//throw ex("cdPlayer::setPosition(): error");
		mciGetErrorString (result, returnStr,sizeof(returnStr));
		cerr << "cannot set position:" << returnStr << endl;
	}
}	


char * cdPlayer::getPosition()
{
	int result = sendCommand ("status cdaudio position");
	if (result != S_OK)		// rzucamy wyjatek
	{
		//throw ex("cdPlayer::play(): cannot play a track");
		mciGetErrorString (result, returnStr,sizeof(returnStr));
		cerr << "cannot get position:" << returnStr << endl;
	}

	char * ret = new char [sizeof (returnStr)];
	strcpy (ret, returnStr);

	return ret;
}




//////////////////////////////////////////////////////////////////////
// Get duration of disk/track
//////////////////////////////////////////////////////////////////////
char * cdPlayer::getDuration(unsigned trackNo)
{
	int result;
	char * ret = new char [sizeof (returnStr)];

	if (trackNo == CD_DURATION)
	{
		result = sendCommand ("status cdaudio number of tracks");
		strcpy (ret, returnStr);
		strcat (ret, ":");
		
		result = sendCommand ("status cdaudio length");
		strcat  (ret, returnStr);
	}
	else
	{
		sprintf (commandBuff, "status cdaudio length track %d", trackNo);
		result = sendCommand (commandBuff);
		strcpy (ret, returnStr);
	}

	if (result != S_OK)		// rzucamy wyjatek
	{
		//throw ex("cdPlayer::getDuration(): cannot play a track");
		mciGetErrorString (result, returnStr,sizeof(returnStr));
		cerr << "cannot get duration:" << returnStr << endl;
	}



	return ret;
}




//////////////////////////////////////////////////////////////////////
// Pause playing. You can resume playing with cdPlayer::resume()
//	method.
//////////////////////////////////////////////////////////////////////
void cdPlayer::pause()
{
	int result;
	
	if ((result = sendCommand ("pause cdaudio"))!= S_OK)		// rzucamy wyjatek
	{
		//throw ex("cdPlayer::play(): cannot play a track");
		mciGetErrorString (result, returnStr,sizeof(returnStr));
		cerr << "cannot play a track:" << returnStr << endl;
	}
}




//////////////////////////////////////////////////////////////////////
// Mount CD. You MUST use this metod before calling any other
//	methods
//////////////////////////////////////////////////////////////////////
void cdPlayer::mount()
{
	int result;

	if ((result = sendCommand ("open cdaudio")) != S_OK)	// tutaj rzucamy wyjatek
	{
		//throw ex ("cdPlayer::mount(): cannot mount a CD");
		cerr << "cos nie tak z mount: " << returnStr << endl;
	}

	result = sendCommand ("set cdaudio time format tmsf");
	if ( result  != S_OK)		// rzucamy wyjatek
	{
		//throw ex("cdPlayer::play(): cannot play a track");
		mciGetErrorString (result, returnStr,sizeof(returnStr));
		cerr << "mount:" << returnStr << endl;
	}

}




//////////////////////////////////////////////////////////////////////
// Unmount CD.
//////////////////////////////////////////////////////////////////////
void cdPlayer::unmount()
{
	int result;
	if (S_OK != (result = sendCommand ("close cdaudio")))
	{	// rzucamy wyjatek
		//throw ex("cdPlayer::unmount(): cannot unmount");
		mciGetErrorString (result, returnStr,sizeof(returnStr));
		cerr << "cannot unmount" << returnStr << endl;
	} 
}




//////////////////////////////////////////////////////////////////////
// Send a raw command to MCI, for ex. str="open cdaudio"
//	Returns result of mciSendString ();
//////////////////////////////////////////////////////////////////////
HRESULT cdPlayer::sendCommand(const char *str)
{
	int result = mciSendString(str, returnStr, 
		sizeof(returnStr)/sizeof(char), NULL);
	
	return result;
}




//////////////////////////////////////////////////////////////////////
// Resume playing paused by cdPlayer::pause()
//////////////////////////////////////////////////////////////////////
void cdPlayer::resume()
{
	if (S_OK != sendCommand ("resume cdaudio"))
//		throw ex("cdPlayer:resume(): not paused");
		cerr << "cant resume" << endl;		
}




//////////////////////////////////////////////////////////////////////
// Skip to next track
//////////////////////////////////////////////////////////////////////
void	cdPlayer::skipNext()
{
	int currTrack;
	char *currPos;

	currPos = getPosition();
	sscanf (currPos, "%d", &currTrack);
	setPosition (currTrack+1);
	delete currPos;
}




//////////////////////////////////////////////////////////////////////
// Skip to prev. track
//////////////////////////////////////////////////////////////////////
void	cdPlayer::skipPrev()
{
	int currTrack;
	char *currPos;

	currPos = getPosition();
	sscanf (currPos, "%d", &currTrack);
	setPosition (currTrack-1);
	delete currPos;
}

