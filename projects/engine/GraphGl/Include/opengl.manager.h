// opengl.manager.h: interface for the GlManager class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_OPENGL_MANAGER_H__9BDEA573_6300_4B2E_B55E_549E35C02B5F__INCLUDED_)
#define AFX_OPENGL_MANAGER_H__9BDEA573_6300_4B2E_B55E_549E35C02B5F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//////////////////////////////////////////////////////////////////////

#include <toolbox.h>

#include <gl\gl.h>
#include <gl\glu.h>

#pragma comment( lib, "opengl32.lib" )
#pragma comment( lib, "glu32.lib" )


class GlManager  
{
public:

		// Initialization parameters
	struct Params
	{
		HWND window;			// Window handle
		int width, height;		// Dimmensions of back-buffer
		int bpp;				// Color depth
		bool fullscreen;		// Fullscreen mode / Windowed mode
		int depth;				// Depth buffer 
		int stencil;			// Stencil buffer

			// Constructor
		Params( bool fs = false, int w = 0, int h = 0, int b = 16, int d = 16, int s = 0, HWND hw = 0 );
	};

		// Creates openGl context
	void create( Params * params = 0 );
		// Kills openGl context
	void kill();
		// Presents contents
	void present() { SwapBuffers(hDC); }

		// Constructor / Destructor
	GlManager();
	virtual ~GlManager();

protected:

		// Rendering context
	HGLRC hRC;
		// Device context
	HDC	hDC;

		// Okienko
	HWND hWnd;
	RECT windowRect;
	long windowStyle;
	bool fullscreen;
};



//////////////////////////////////////////////////////////////////////

#endif // !defined(AFX_OPENGL_MANAGER_H__9BDEA573_6300_4B2E_B55E_549E35C02B5F__INCLUDED_)
