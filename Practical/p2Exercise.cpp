
#include <Windows.h>
#include <gl/GL.h>
#include <math.h>


#pragma comment (lib, "OpenGL32.lib")

#define WINDOW_TITLE "OpenGL Window"

float tx = 0;
float ty = 0;
float tSpeed = 0.1;
int qNum = 1;

float r = 1;
float g = 0.5;
float b = 0.5;
float colorSpeed = 0.0001f;
float rotateSpeed = 0.0001f;
float scaleSpeed = 0.005f;



void p2Q1() {
	glLoadIdentity();

	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT);

	r = 1;
	g = 1;
	b = 1;

	//glLoadIdentity();			//reset the transformaiton

	glTranslatef(tx, ty, 0.0);	//translate x and y, tx & ty



	glBegin(GL_QUADS);			//quad
	glColor3f(r, g, b);
	glVertex2f(-0.5, 0.0);
	glVertex2f(-0.5, 0.5);
	glVertex2f(0.5, 0.5);
	glVertex2f(0.5, 0.0);
	glEnd();

}

void p2Q2() {
	
	static float time = 0.0f;
	static float angle = 0.0f;
	time += colorSpeed;
	angle += 0.01;

	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();

	glScalef(1, 1, 1.0f);


	//// Simple color cycling logic
	//r += colorSpeed;
	//g += colorSpeed * 2;
	//b += colorSpeed * 3;

	//// Wrap colors around [0, 1]
	//if (r > 1.0f) r = 0.0f;
	//if (g > 1.0f) g = 0.0f;
	//if (b > 1.0f) b = 0.0f;


	// Smooth color cycling using sine waves
    r = (sin(time) + 1.0f) / 2.0f;     // cycles between 0 to 1
    g = (sin(time + 2.0f) + 1.0f) / 2.0f;
    b = (sin(time + 4.0f) + 1.0f) / 2.0f;
	glRotatef(angle, 0, 0, 1);		// rz(90), anti clockwise


	glBegin(GL_POLYGON);
	glColor3f(r, g, b);
	glVertex2f(0, 0.5); //top
	glVertex2f(0.15, 0); //right
	glVertex2f(0, -0.5); //bottom
	glVertex2f(-0.15, 0); //left
	glEnd();

	glBegin(GL_POLYGON);
	glVertex2f(0.15, 0); //right
	glVertex2f(0.65, 0);
	glVertex2f(0, -0.5); //bottom
	glEnd();

	glBegin(GL_POLYGON);
	glVertex2f(-0.15, 0); //left
	glVertex2f(-0.65, 0);
	glVertex2f(0, -0.5); //bottom
	glEnd();

	glBegin(GL_POLYGON);
	glVertex2f(-0.15, 0); //left
	glVertex2f(0, -0.5); //bottom
	glVertex2f(-0.45, -0.8); //bottom
	glEnd();

	glBegin(GL_POLYGON);
	glVertex2f(0.15, 0); //right
	glVertex2f(0, -0.5); //bottom
	glVertex2f(0.45, -0.8); //bottom
	glEnd();


}

void p2Q3() {
	glLoadIdentity();
	static float angle = 0.0f; // angle in radians
	float radius = 0.5f;       // radius of the circular path

	// Update the angle to move anti-clockwise
	angle += rotateSpeed; // Increase for faster movement

	float x = cos(angle) * radius;
	float y = sin(angle) * radius;

	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT);

	glRotatef(0.01, 0, 0, 1);		// rz(90), anti clockwise

	glPointSize(10.0f);
	glBegin(GL_POINTS);
	glColor3f(1, 0, 0); 
	glVertex2f(x,y);
	glEnd();
}

void p2Q4() {
	static bool growing = true;
	static float scale = 0.1f;

	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();

	// Update scale value
	if (growing)
		scale += scaleSpeed;
	else
		scale -= scaleSpeed;

	// Toggle direction
	if (scale > 100.0f)
		growing = false;
	else if (scale < 0.1f)
		growing = true;

	// Apply the scale transformation
	glScalef(scale, scale, 1.0f);

	// Draw a fixed-size box centered at origin
	glColor3f(1.0f, 0.0f, 0.0f); // red

	glBegin(GL_QUADS);
	glVertex2f(-0.01f, -0.01f);
	glVertex2f(-0.01f, 0.01f);
	glVertex2f(0.01f, 0.01f);
	glVertex2f(0.01f, -0.01f);
	glEnd();
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
		else if (wParam == VK_RIGHT)
			tx += tSpeed;
		else if (wParam == VK_LEFT)
			tx -= tSpeed;
		else if (wParam == VK_UP)
			ty += tSpeed;
		else if (wParam == VK_DOWN)
			ty -= tSpeed;
		else if (wParam == 'R') {
			r = 1;
			g = 0;
			b = 0;
		}

		else if (wParam == 'G') {
			r = 0;
			g = 1;
			b = 0;
		}

		else if (wParam == 'B') {
			r = 0;
			g = 0;
			b = 1;
		}

		else if (wParam == VK_SPACE) {
			r = 1;
			g = 1;
			b = 1;
			tx = 0;
			ty = 0;
		}

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
		p2Q1();
		break;

	case 2:
		p2Q2();
		break;

	case 3:
		p2Q3();
		break;

	case 4:
		p2Q4();
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