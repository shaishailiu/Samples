//=================================================================================================================================
//
// Author: Maurice Ribble
//         3D Application Research Group
//         ATI Research, Inc.
//
// A simple test case that will draw a triangle in ES.
//
//=================================================================================================================================
// $Id: //depot/3darg/Tools/Handheld/esTestApps/common/main.cpp#2 $ 
// 
// Last check-in:  $DateTime: 2008/02/26 16:36:56 $ 
// Last edited by: $Author: juanli $
//=================================================================================================================================
//   (C) ATI Research, Inc. 2006 All rights reserved. 
//=================================================================================================================================

#pragma comment( lib, "libEGL.lib" )
#pragma comment( lib, "libGLESv2.lib" )

#include <EGL/egl.h>
#include <GLES2/gl2.h>
#include <assert.h>
#include <fcntl.h>
#include <io.h>
#include <WindowsX.h>
#include "ArgDefines.h"
//#include "Scene.h"
#include "Misc.h"
#include "engine/Engine.h"
#include "game/GamePhone.h"
#include "utils/Fps.h"
#include "log/LogTrace.h"
#include "interactive/InteractiveInput.h"
//#include "engine/MainEngine.h"

// Globals
bool  g_keys[256];               // Array Used For The Keyboard Routine
bool  g_active=TRUE;             // Window Active Flag Set To TRUE By Default

InteractiveInput input;

//Scene g_scene;


LRESULT  CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

//=================================================================================================================================
///
/// Funtion to redirect stdin/stdout to a console window.
///
/// \return void
//=================================================================================================================================
void RedirectIOToConsole()
{
    BOOL bResult;

    // Could try attaching to the current console but there might not
    // be one and the output format is somewhat ugly.
    //AttachConsole(ATTACH_PARENT_PROCESS);

    // allocate a console for this app
    bResult = AllocConsole();

    if (bResult)
    {
        int hConHandle;
        HANDLE StdHandle;
        FILE *fp;
        CONSOLE_SCREEN_BUFFER_INFO coninfo;

        // set the screen buffer to be big enough to let us scroll text
        GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &coninfo);
        coninfo.dwSize.Y = 500;
        SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE), coninfo.dwSize);

        // redirect unbuffered STDOUT to the console
        StdHandle = GetStdHandle(STD_OUTPUT_HANDLE);
        hConHandle = _open_osfhandle((intptr_t)StdHandle, _O_TEXT);
        fp = _fdopen( hConHandle, "w" );
        *stdout = *fp;
        setvbuf( stdout, NULL, _IONBF, 0 );

        // redirect unbuffered STDIN to the console
        StdHandle = GetStdHandle(STD_INPUT_HANDLE);
        hConHandle = _open_osfhandle((intptr_t)StdHandle, _O_TEXT);
        fp = _fdopen( hConHandle, "r" );
        *stdin = *fp;
        setvbuf( stdin, NULL, _IONBF, 0 );
    }
}

//=================================================================================================================================
///
/// Funtion to resize the ES window.
///
/// \param nWidth the width of the new window.
/// \param nHeight the height of the new window.
///
/// \return void
//=================================================================================================================================
void ResizeScene( int nWidth, int nHeight )
{
   //glViewport( 0, 0, nWidth, nHeight);
	 //glViewport( 0, 0, nWidth, nHeight);
	//engine->resize(nWidth,nHeight);
	//getEngine()->resize(nWidth,nHeight);
	Engine::getEngine()->resize(nWidth,nHeight);
}

//=================================================================================================================================
///
/// Funtion draw the simple ES scene.
///
/// \return void
//=================================================================================================================================
int DrawScene()
{
   //g_scene.drawFrame();

   return TRUE;
}

//=================================================================================================================================
///
/// Funtion to create the EGL window.
///
/// \param hWnd the parent window HWND.
/// \param hInstance the class instance.
///
/// \return 1 = pass; 0 = fail.
//=================================================================================================================================
int CreateEGLContext( HWND hWnd, HINSTANCE hInstance )
{
   EGLint attribList[MAX_EGL_ATTRIBUTES];
   EGLint numConfigs;
   EGLint majorVersion;
   EGLint minorVersion;

   /// Build up the attribute list
   BuildAttribList( attribList );

   // Get Display
   g_egl.dsp = eglGetDisplay( EGL_DEFAULT_DISPLAY );
   if ( g_egl.dsp == EGL_NO_DISPLAY )
   {
      assert( 0 && "eglGetDisplay failed" );      
      return FALSE;
   }

   // Initialize EGL
   if ( ! eglInitialize( g_egl.dsp, &majorVersion, &minorVersion) )
   {
      assert( 0 && "eglInitialize failed" );
      return FALSE;
   }

   // Get configs
   if ( ! eglGetConfigs( g_egl.dsp, NULL, 0, &numConfigs ) )
   {
      assert( 0 && "eglGetConfigs failed" );      
      return FALSE;
   }

   // Choose config
   if ( !eglChooseConfig(g_egl.dsp, attribList, &g_egl.cfg, 1, &numConfigs) )
   {
      assert( 0 && "eglChooseConfig failed" );      
      return FALSE;
   }

   // Create a surface
   g_egl.surf = eglCreateWindowSurface( g_egl.dsp, g_egl.cfg, NativeWindowType( hWnd ), NULL );
   if ( g_egl.surf == EGL_NO_SURFACE )
   {
      assert( 0 && "eglCreateWindowSurface failed" );      
      return FALSE;
   }

   // Create a GL context
   EGLint ctxAttribList[] = {EGL_CONTEXT_CLIENT_VERSION, 2, EGL_NONE};
   g_egl.cxt = eglCreateContext( g_egl.dsp, g_egl.cfg, EGL_NO_CONTEXT, ctxAttribList );
   if ( g_egl.cxt == EGL_NO_CONTEXT )
   {
      assert( 0 && "eglCreateContext failed" );      
      return FALSE;
   }   

   // Make the context current
   if ( ! eglMakeCurrent( g_egl.dsp, g_egl.surf, g_egl.surf, g_egl.cxt ) )
   {
      assert( 0 && "eglMakeCurrent failed" );      
      return FALSE;
   }
   return TRUE;
}

//=================================================================================================================================
///
/// Funtion to create Window.
///
/// \param width the width of the window.
/// \param height the height of the window.
///
/// \return 0=fail; 1=pass
//=================================================================================================================================
int CreateWind( int width, int height )
{
   WNDCLASS             wc;                  // Windows Class Structure
   HWND hWnd;
   HINSTANCE hInstance;

   hInstance         = GetModuleHandle( NULL );             // Grab An Instance For Our Window
   wc.style          = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;  // Redraw On Size, And Own DC For Window.
   wc.lpfnWndProc    = WNDPROC( WndProc );                  // WndProc Handles Messages
   wc.cbClsExtra     = 0;                                   // No Extra Window Data
   wc.cbWndExtra     = 0;                                   // No Extra Window Data
   wc.hInstance      = hInstance;                           // Set The Instance
   wc.hIcon          = LoadIcon( NULL, IDI_WINLOGO );       // Load The Default Icon
   wc.hCursor        = LoadCursor( NULL, IDC_ARROW );       // Load The Arrow Pointer
   wc.hbrBackground  = NULL;                                // No Background Required For GL
   wc.lpszMenuName   = NULL;                                // We Don't Want A Menu
   wc.lpszClassName  = "OpenGL";                            // Set The Class Name

   if ( ! RegisterClass( &wc ) )                            // Attempt To Register The Window Class
   {
      MessageBox( NULL, "Failed To Register The Window Class.", "ERROR", MB_OK | MB_ICONEXCLAMATION );
      return FALSE;
   }

   if ( ! ( hWnd=CreateWindowEx(
      WS_EX_APPWINDOW | WS_EX_WINDOWEDGE,       // Extended Style For The Window
      "OpenGL",                                 // Class Name
      "Triangle ES App",                        // Window Title
      WS_OVERLAPPEDWINDOW |                     // Defined Window Style
      WS_CLIPSIBLINGS |                         // Required Window Style
      WS_CLIPCHILDREN,                          // Required Window Style
      0, 0,                                     // Window Position
      width,                                    // Window Width
      height,                                   // Window Height
      NULL,                                     // No Parent Window
      NULL,                                     // No Menu
      hInstance,                                // Instance
      NULL ) ) )                                // Dont Pass Anything To WM_CREATE
   {
      return 0;
   }

   if ( CreateEGLContext( hWnd, hInstance ) == false )
   {
      MessageBox( NULL, "Failed to create a context.", "ERROR", MB_OK|MB_ICONSTOP );
      exit( 0 );
   }

   ShowWindow( hWnd, SW_SHOW );
   SetForegroundWindow( hWnd );  // Slightly Higher Priority
   SetFocus( hWnd );             // Sets Keyboard Focus To The Window

   //engine->start();
  // getEngine()->start();
  // Engine::getFps()->frame;

   Engine::getEngine()->start();

   ResizeScene( width, height );

  GamePhone::getGame()->init();

   return TRUE;
}

//=================================================================================================================================
///
/// Callback function for this simple ES app.
///
/// \param hWnd handle For this window.
/// \param uMsg message for this window.
/// \param wParam additional message info.
/// \param lParam additional message info.
///
/// \return void
//=================================================================================================================================
LRESULT CALLBACK WndProc( HWND      hWnd,
                          UINT      uMsg,
                          WPARAM    wParam,
                          LPARAM    lParam)
{
   switch ( uMsg )      // Check For Windows Messages
   {
   case WM_ACTIVATE:
      {
         if ( ! HIWORD( wParam ) )     // Check Minimization State
         {
            g_active = TRUE;
         }
         else
         {
            g_active = FALSE;
         }
         return 0;
      }

   case WM_SYSCOMMAND:
      {
         if ( ( wParam == SC_SCREENSAVE ) ||
              ( wParam == SC_MONITORPOWER ) )
         {
            return 0;
         }
         break;
      }

   case WM_CLOSE:
      {
         PostQuitMessage( 0 );
         return 0;
      }

   case WM_KEYDOWN:
      {
         g_keys[wParam] = TRUE;
		 GamePhone::getGame()->keyHander(g_keys);
         return 0;
      }

   case WM_KEYUP:
      {
         g_keys[wParam] = FALSE;
		 GamePhone::getGame()->keyHander(g_keys);
         return 0;
      }

   case WM_SIZE:
      {
         ResizeScene( LOWORD( lParam ), HIWORD( lParam ) );  // LoWord=Width, HiWord=Height
         return 0;
      }
   case WM_LBUTTONDOWN:
	   {
		 int x = GET_X_LPARAM(lParam) + 5;
		 int y = GET_Y_LPARAM(lParam) + 30;
		 GamePhone::getGame()->mouseDownHander(x,y);
		 return 0;
	   }
   case WM_MOUSEMOVE:
	   {
		   int x = GET_X_LPARAM(lParam) + 5;
		   int y = GET_Y_LPARAM(lParam) + 30;
		   GamePhone::getGame()->mouseMoveHander(x,y);
		   input.mouseMove(x, y);
		   return 0;
	   }
   case WM_LBUTTONUP:
	   {
		   int x = GET_X_LPARAM(lParam) + 5;
		   int y = GET_Y_LPARAM(lParam) + 30;
		   GamePhone::getGame()->mouseUpHander(x,y);
		   return 0;
	   }
   case WM_RBUTTONDOWN:
	   {
			int x = GET_X_LPARAM(lParam) + 5;
			int y = GET_Y_LPARAM(lParam) + 30;
			input.rightMouseDown(x, y);
			return 0;
	   }
   case WM_RBUTTONUP:
	   {
			int x = GET_X_LPARAM(lParam) + 5;
			int y = GET_Y_LPARAM(lParam) + 30;
			input.rightMouseUp(x, y);
			return 0;
	   }
   case WM_MOUSEWHEEL:
	   {
			short zDelta = (short)HIWORD(wParam);
			//InteractiveInput::mouseWheel(zDelta);
			input.mouseWheel(zDelta);
			return 0;
	   }
   }

   // Pass All Unhandled Messages To DefWindowProc
   return DefWindowProc( hWnd, uMsg, wParam, lParam );
}

//=================================================================================================================================
///
/// WinMain function for this simple ES app.
///
/// \param hInstance instance.
/// \param hPrevInstance previous instance.
/// \param lpCmdLine command line parameters.
/// \param nCmdShow window show state.
///
/// \return void
//=================================================================================================================================
int WINAPI WinMain( HINSTANCE  hInstance,
                    HINSTANCE  hPrevInstance,
                    LPSTR      lpCmdLine,
                    int        nCmdShow)
{
   MSG  msg;
   BOOL done=FALSE;

   // redirect stdin/stdout to a console window
   RedirectIOToConsole();

   MainFuncInit();

   if ( ! CreateWind( 1500, 900 ) )
   {
      return 0;
   }


   //g_scene.loadData("./data/uniforms.txt");
   
   while ( ! done )
   {
      if ( PeekMessage( &msg, NULL, 0, 0, PM_REMOVE ) )  // Is There A Message Waiting?
      {
         if ( msg.message == WM_QUIT )
         {
            done=TRUE;
         }
         else
         {
            TranslateMessage( &msg );
            DispatchMessage( &msg );
         }
      }
      else
      {
         if ( ( g_active && !DrawScene() ) || g_keys[VK_ESCAPE] )
         {
            done=TRUE;  // ESC or DrawGLScene Signalled A Quit
         }
         else
         {
            eglSwapBuffers( g_egl.dsp, g_egl.surf );
         }
      }

	  //engine->render();
	  //getEngine()->render();
	  //Engine::getEngine()->render();
	  GamePhone::getGame()->update();
   }

   eglDestroyContext( g_egl.dsp, g_egl.cxt );
   eglDestroySurface( g_egl.dsp, g_egl.surf );
   eglTerminate( g_egl.dsp );
  // g_scene.freeResources();
   return 0;
}
