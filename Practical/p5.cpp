#include <Windows.h>
#include <GL/glu.h>
#include <math.h>

#pragma comment (lib, "OpenGL32.lib") // Linker -> Input  -> Edit -> OpenGL32.lib

#define WINDOW_TITLE "Prac1 Demo"

int qNum = 1;			//Question Number, Default Q1
float tz = 0,tSpeed = 1.0; //translate tz with tspeed
bool isOrtho = true;
float oNear = -10, oFar = 10;		//orthor near & far boundary
float pNear = 1, pFar = 10;		//perspective near and far boundary
float r1 = 3.0;
float ptx = 0, pty = 0;			// tx, ty with tSpeed for projection
float tx = 0;
float pry = 0 , prSpeed = 1.0;	//ry with prSpeedfor projection


void drawSphere(double r) {
	GLUquadricObj* sphere = NULL;
	sphere = gluNewQuadric();
	gluQuadricDrawStyle(sphere,GLU_LINE);
	gluSphere(sphere, r, 30, 30);
	gluDeleteQuadric(sphere);
}

void projection() {
	glMatrixMode(GL_PROJECTION);		//refer to the projection matrix
	glLoadIdentity();					//reset
	
	glTranslatef(ptx, pty, 0.0);

	if (isOrtho) {
		glOrtho(-10, 10, -10, 10, oNear, oFar);			//default viewing volume
	}
	else {
		//Perspective view
		glFrustum(-10, 10, -10, 10, pNear, pFar);
		//gluPerspective(45, 1.0, 1, 10);
	}
	
	
	

}

LRESULT WINAPI WindowProcedure(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:
		if (wParam == VK_ESCAPE)
			PostQuitMessage(0);
		else if (wParam == '1')
			qNum = 1;
		else if (wParam == '2')
			qNum = 2;
		else if (wParam == '3')
			qNum = 3;
		else if (wParam == '4')
			qNum = 4;
		else if (wParam == '5')
			qNum = 5;
		else if (wParam == '6')
			qNum = 6;
		else if (wParam == VK_UP) {
			if (isOrtho) {
				if (tz > oNear + r1) {
					tz -= tSpeed;
				}
			}
			else {
				if (tz > pNear - pFar) {
					tz -= tSpeed;
				}
			}
		}

		else if (wParam == VK_DOWN) {
			if (isOrtho) {
				if (tz < oFar - r1) {
					tz += tSpeed;
				}
			}
			else {
				if (tz < pNear - r1) { // pnear - radius
					tz += tSpeed;
				}
			}
		}

		else if (wParam == 'O') {
			isOrtho = true;
			tz = 0;
		}

		else if (wParam == 'P') {
			isOrtho = false;
			tz = 0;
		}
		else if (wParam == 'A') {
			ptx -= tSpeed;
		}
		else if (wParam == 'D')
			ptx += tSpeed;
		else if (wParam == VK_LEFT) {
			tx -= tSpeed;
		}
		else if (wParam == VK_RIGHT)
			tx += tSpeed;
		else if (wParam == 'L')
			pry += prSpeed;
		else if (wParam == 'R')
			pry -= prSpeed;
		break;

	default:
		break;
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}
//--------------------------------------------------------------------

bool initPixelFormat(HDC hdc)
{
	PIXELFORMATDESCRIPTOR pfd;
	ZeroMemory(&pfd, sizeof(PIXELFORMATDESCRIPTOR));

	pfd.cAlphaBits = 8;
	pfd.cColorBits = 32;
	pfd.cDepthBits = 24;
	pfd.cStencilBits = 0;

	pfd.dwFlags = PFD_DOUBLEBUFFER | PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW;

	pfd.iLayerType = PFD_MAIN_PLANE;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pfd.nVersion = 1;

	// choose pixel format returns the number most similar pixel format available
	int n = ChoosePixelFormat(hdc, &pfd);

	// set pixel format returns whether it sucessfully set the pixel format
	if (SetPixelFormat(hdc, n, &pfd))
	{
		return true;
	}
	else
	{
		return false;
	}
}
//--------------------------------------------------------------------




void display()
{
	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	//glLoadIdentity();

	projection();

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(tx, 0.0, tz);
	glRotatef(pry, 0.0, 1.0, 0.0);
	drawSphere(r1);


	//--------------------------------
	//	OpenGL drawing
	//--------------------------------

	switch (qNum) {
	case 1:
		//drawSphere(5.0);
		break;

	case 2:
		//drawCylinder();
		break;

	case 3:
		break;

	case 4:
		break;

	case 5:
		break;
	case 6:
		break;

	default:
		//triangle();
		break;
	}

	//--------------------------------
	//	End of OpenGL drawing
	//--------------------------------
}


//--------------------------------------------------------------------

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR, int nCmdShow)
{
	WNDCLASSEX wc;
	ZeroMemory(&wc, sizeof(WNDCLASSEX));

	wc.cbSize = sizeof(WNDCLASSEX);
	wc.hInstance = GetModuleHandle(NULL);
	wc.lpfnWndProc = WindowProcedure;
	wc.lpszClassName = WINDOW_TITLE;
	wc.style = CS_HREDRAW | CS_VREDRAW;

	if (!RegisterClassEx(&wc)) return false;

	HWND hWnd = CreateWindow(WINDOW_TITLE, WINDOW_TITLE, WS_OVERLAPPEDWINDOW,
		950, 10, 400, 400,
		NULL, NULL, wc.hInstance, NULL);

	//--------------------------------
	//	Initialize window for OpenGL
	//--------------------------------

	HDC hdc = GetDC(hWnd);

	//	initialize pixel format for the window
	initPixelFormat(hdc);

	//	get an openGL context
	HGLRC hglrc = wglCreateContext(hdc);

	//	make context current
	if (!wglMakeCurrent(hdc, hglrc)) return false;

	//--------------------------------
	//	End initialization
	//--------------------------------

	ShowWindow(hWnd, nCmdShow);

	MSG msg;
	ZeroMemory(&msg, sizeof(msg));


	while (true)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) break;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		display();

		SwapBuffers(hdc);
	}

	UnregisterClass(WINDOW_TITLE, wc.hInstance);

	return true;
}
//--------------------------------------------------------------------