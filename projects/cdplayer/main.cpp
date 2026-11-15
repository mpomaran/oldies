#include "cdPlayer1.h"
#include <iostream.h>

void main ()
{
	cdPlayer player;

	// inicjacja
	cerr << "mounting...";
	player.mount();
	cerr << "ok.\n";

	// odtwarzamy...
	cerr << "playing...";
	player.play (2,3);
	cerr << "ok.\n\n";

	char *sth = player.getDuration();
	cerr << " CD duration --> t:mm:ss:ff: -->" << sth << endl;
	delete sth;
	sth = player.getDuration(2);
	cerr << " track duration --> mm:ss:ff: -->" << sth << endl;
	delete sth;
	sth = player.getPosition();
	cerr << " track position --> t:mm:ss:ff: -->" << sth << endl;
	delete sth;

	player.setPosition(3);
	sth = player.getPosition();
	cerr << " track position --> t:mm:ss:ff: -->" << sth << endl;
	delete sth;

	// next/prev
	player.skipNext();
	sth = player.getPosition();
	cerr << " track position --> t:mm:ss:ff: -->" << sth << endl;
	delete sth;
	player.skipPrev();
	sth = player.getPosition();
	cerr << " track position --> t:mm:ss:ff: -->" << sth << endl;
	delete sth;


	int i;
	cin >> i;
	try{
	player.pause();
//	player.stop();
	}
	catch (...)
	{
		cerr << "errorek\n";
		cin >> i;
	}

	cin >> i;
	player.resume();
	cin >> i;

}

	