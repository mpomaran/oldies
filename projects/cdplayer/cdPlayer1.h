// cdPlayer1.h: interface for the cdPlayer class.
//
//////////////////////////////////////////////////////////////////////

#ifndef __CDPLAYER_H
#define __CDPLAYER_H

#include <windows.h>

#define CD_DURATION	0xfffff

//////////////////////////////////////////////////////////////////////
// Uwagi:
//		wszystkie czasy, tzn, w getDuration, getPosition, setPosition
//		sa zwracane w sekundach
//
//		nie bede wyjasnial, co metody robia, bo to oczywiste

class cdPlayer  
{
public:
	void		skipPrev();
	void		skipNext();
	void		resume();
	HRESULT		sendCommand (const char *str);
	void		unmount();
	void		mount();
	void		pause();
	char *		getDuration(unsigned track = CD_DURATION);
	char *		getPosition();
	void		setPosition (unsigned track=1, unsigned m=0, unsigned s=0, unsigned f=0);
	void		stop();
	void		play (unsigned from = 1, unsigned to = 0);

	// konstruktor/destruktor	
	cdPlayer();
	virtual ~cdPlayer();

};

#endif
