#include <Windows.h>
#include <gl/GL.h>
#include <math.h>


#pragma comment (lib, "OpenGL32.lib")

#define WINDOW_TITLE "OpenGL Window"

int qNum = 1;


void p3Q1() {
	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT);

	glPushMatrix();
	glScalef(0.5, 0.5, 0.5);

	glPushMatrix();
	glTranslatef(0.0f, 0.5f, 0.0f);	//ty(0.5) up
	glBegin(GL_TRIANGLES);			//obj 1 triangle
	glColor3f(1, 0, 0);
	glVertex2f(-0.5, 0);
	glVertex2f(0, 0.5);
	glVertex2f(0.5, 0);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glRotatef(90, 0, 0, 1);

	glPushMatrix();
	glTranslatef(0.5f, 0.0f, 0.0f);//tx(0.5) right
	glBegin(GL_QUADS);				//obj 2 quads
	glColor3f(0, 1, 0);
	glVertex2f(-0.5, 0.0);
	glVertex2f(-0.5, 0.5);
	glVertex2f(0.5, 0.5);
	glVertex2f(0.5, 0.0);
	glEnd();
	glPopMatrix();


	glPushMatrix();
	glTranslatef(-0.5f, 0.0f, 0.0f);//tx(-0.5) left
	glBegin(GL_QUADS);				//obj 3 quads
	glColor3f(0, 0, 1);
	glVertex2f(-0.5, 0.0);
	glVertex2f(-0.5, 0.5);
	glVertex2f(0.5, 0.5);
	glVertex2f(0.5, 0.0);
	glEnd();
	glPopMatrix();

	glPopMatrix();

	glPopMatrix();

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
		//else if (wParam == VK_RIGHT)
		//	tx += tSpeed;
		//else if (wParam == VK_LEFT)
		//	tx -= tSpeed;
		//else if (wParam == VK_UP)
		//	ty += tSpeed;
		//else if (wParam == VK_DOWN)
		//	ty -= tSpeed;
		//else if (wParam == 'R') {
		//	r = 1;
		//	g = 0;
		//	b = 0;
		//}

		//else if (wParam == 'G') {
		//	r = 0;
		//	g = 1;
		//	b = 0;
		//}

		//else if (wParam == 'B') {
		//	r = 0;
		//	g = 0;
		//	b = 1;
		//}

		//else if (wParam == VK_SPACE) {
		//	r = 1;
		//	g = 1;
		//	b = 1;
		//	tx = 0;
		//	ty = 0;
		//}

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

	switch (qNum) {
	case 1:
		p3Q1();
		break;

	case 2:
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
		CW_USEDEFAULT, CW_USEDEFAULT, 500, 500,
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