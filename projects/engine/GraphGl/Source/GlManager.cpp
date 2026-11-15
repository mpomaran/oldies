// GlManager.cpp: implementation of the GlManager class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "opengl.manager.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

GlManager::Params::Params( bool fs, int w, int h, int b, int d, int s, HWND hw )
{
	fullscreen = fs;
	width = w;
	height = h;
	bpp = b;
	depth = d;
	stencil = s;
	window = hw;
}



//////////////////////////////////////////////////////////////////////

GlManager::GlManager()
{
	hRC = 0; hDC = 0;
	fullscreen = false;
	hWnd = 0;
}



//////////////////////////////////////////////////////////////////////

GlManager::~GlManager()
{
	kill();
}



//////////////////////////////////////////////////////////////////////

void GlManager::create( Params * params )
{
	// Ubijamy poprzedniego
	kill();

	// Jezeli nie podamy parametrow, uzywamy domyslnych
	if( !params ) params = &Params( false );

	// Jezeli w parametrach nie ma uchwytu okna, bierzemy domyslny
	if( !params->window ) params->window = g_window;

	// Wypelnienie pixel-format-descriptor
	PIXELFORMATDESCRIPTOR pfd = 
	{
		sizeof(PIXELFORMATDESCRIPTOR),
		1,							
		PFD_SUPPORT_OPENGL |	
		PFD_DOUBLEBUFFER,	
		PFD_TYPE_RGBA,		
		params->bpp,		
		0, 0, 0, 0, 0, 0,	
		params->bpp == 32 ? 8 : 0,		
		0,					
		0,					
		0, 0, 0, 0,			
		params->depth,
		params->stencil,		
		0,					
		PFD_MAIN_PLANE,		
		0,					
		0, 0, 0					
	};

	hWnd = params->window;

	// Wskakiwanie w fullscreen
	if( params->fullscreen )	
	{
		// Zapamietanie okna
		windowStyle = GetWindowLong( hWnd, GWL_STYLE );
		GetWindowRect( hWnd, &windowRect );

		// Zmiana stylu okienka
		SetWindowLong(hWnd, GWL_STYLE, WS_POPUP);
		SetWindowPos(hWnd, HWND_TOP, 0, 0, params->width, params->height, 0);
		UpdateWindow(hWnd);
		ShowWindow(hWnd, SW_SHOW);
		
		DEVMODE dm;
		ZeroMemory(&dm, sizeof(dm));
		dm.dmSize = sizeof(dm);
		dm.dmBitsPerPel = params->bpp;
		dm.dmPelsWidth = params->width;
		dm.dmPelsHeight = params->height;
		dm.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;
		ChangeDisplaySettings(&dm,CDS_FULLSCREEN);

		fullscreen = true;
	}
	else
	{
		pfd.dwFlags |= PFD_DRAW_TO_WINDOW;

		
		// Wymiary ekranu vs wymiary okna ?

		//DEVMODE dm;
		//EnumDisplaySettings( NULL, ENUM_CURRENT_SETTINGS, &dm ); 
		/*
		DMode.wWidth = dm.dmPelsWidth;
		DMode.wHeight = dm.dmPelsHeight;
		*/
		//DMode.bBpp = (BYTE)dm.dmBitsPerPel;
		

		//RECT r;
		//GetClientRect( Window.hWnd, &r );

		//DMode.wWidth = (WORD)r.right;
		//DMode.wHeight = (WORD)r.bottom;
	}	

	hDC=GetDC(hWnd);
	int pf = ChoosePixelFormat(hDC,&pfd);
	SetPixelFormat(hDC,pf,&pfd);
	hRC=wglCreateContext(hDC);
	wglMakeCurrent(hDC,hRC);
	
	//InitStruct = is;

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	// Wlaczanie Z-buffer'a
	if( params->depth )
	{
		glClearDepth(1.0);				
		glEnable(GL_DEPTH_TEST);	
		glDepthFunc(GL_LEQUAL);
	}

	// TODO: InitViewport
}



//////////////////////////////////////////////////////////////////////

void GlManager::kill()
{
	// TODO: Czy jest to dobry test ?
	if( hRC == 0 ) return;

	ChangeDisplaySettings(NULL,0);					

	if(hRC)
	{
		wglMakeCurrent(NULL,NULL);
		wglDeleteContext(hRC);
		hRC=NULL;
	}

	if(hDC)
	{
		ReleaseDC(hWnd,hDC);
		hDC = NULL;
	}
	
	if( fullscreen && hWnd )
	{
		SetWindowLong( hWnd, GWL_STYLE, windowStyle );
		
		MoveWindow( hWnd, 
			windowRect.left, windowRect.top, 
			windowRect.right - windowRect.left,
			windowRect.bottom - windowRect.top, true );
		
		UpdateWindow( hWnd );

		fullscreen = false;
	}
}



//////////////////////////////////////////////////////////////////////

// TODO: InitViewport