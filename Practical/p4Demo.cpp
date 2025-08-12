#include <Windows.h>
#include <gl/GL.h>
#include <math.h>


#pragma comment (lib, "OpenGL32.lib")

#define WINDOW_TITLE "OpenGL Window"

int qNum = 1;
int rx = 1, ry = 1, rz = 1;
float lowerArmAngle = 0.0f;  // For up/down movement of lower arm
float armRotation = 0.0f;    // For whole arm rotation



void drawCube(float size) {
	glBegin(GL_QUADS);
	// Face 1
	glColor3f(1, 0, 0);
	glVertex3f(0.0f, 0.0f, size);
	glVertex3f(size, 0.0f, size);
	glVertex3f(size, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	// Face 2
	glColor3f(0, 1, 0);
	glVertex3f(0.0f, 0.0f, size);
	glVertex3f(0.0f, size, size);
	glVertex3f(0.0f, size, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	// Face 3
	glColor3f(0, 0, 1);
	glVertex3f(0.0f, size, 0.0f);
	glVertex3f(0.0f, size, size);
	glVertex3f(size, size, size);
	glVertex3f(size, size, 0.0f);
	// Face 4
	glColor3f(1, 1, 0);
	glVertex3f(size, size, 0.0f);
	glVertex3f(size, size, size);
	glVertex3f(size, 0.0f, size);
	glVertex3f(size, 0.0f, 0.0f);
	// Face Up
	glColor3f(1, 0, 1);
	glVertex3f(0.0f, 0.0f, size);
	glVertex3f(0.0f, size, size);
	glVertex3f(size, size, size);
	glVertex3f(size, 0.0f, size);
	// Face Bottom
	glColor3f(0, 1, 1);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, size, 0.0f);
	glVertex3f(size, size, 0.0f);
	glVertex3f(size, 0.0f, 0.0f);
	glEnd();

}



void drawPyramid(float size) {
	glBegin(GL_LINE_LOOP);
	glColor3f(0, 1, 1);
	glVertex3f(0.0f, 0.0f, size);
	glVertex3f(size, 0.0f, size);
	glVertex3f(size, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glColor3f(1, 0, 0);
	glVertex3f(0.0f, 0.0f, size);
	glVertex3f(size, 0.0f, size);
	glVertex3f(0.5f, size, 0.5f);
	glEnd();
	glBegin(GL_LINE_LOOP);
	glColor3f(1, 0, 0);
	glVertex3f(size, 0.0f, size);
	glVertex3f(size, 0.0f, 0.0f);
	glVertex3f(0.5f, size, 0.5f);
	glEnd();
	glBegin(GL_LINE_LOOP);
	glColor3f(1, 0, 0);
	glVertex3f(size, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.5f, size, 0.5f);
	glEnd();
	glBegin(GL_LINE_LOOP);
	glColor3f(1, 0, 0);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, size);
	glVertex3f(0.5f, size, 0.5f);
	glEnd();


}

void p4Demo() {
	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	glRotatef(0.01, 1, 0, 0);
	drawCube(0.5f);
	drawCube(-0.5f);

}

void p4Q1() {
	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	glRotatef(0.01, rx, ry, rz);

	drawPyramid(0.5f);
}

void p4Q2() {
	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	glRotatef(0.01, rx, ry, rz);

	glBegin(GL_LINE_LOOP);
	// Face 1
	glColor3f(1, 0, 0);
	glVertex3f(0.0f, 0.0f, 1);
	glVertex3f(1, 0.0f, 1);
	glVertex3f(1, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glEnd();
	glBegin(GL_LINE_LOOP);
	// Face 2
	glColor3f(0, 1, 0);
	glVertex3f(0.0f, 0.0f, 1);
	glVertex3f(0.0f, 1, 1);
	glVertex3f(0.0f, 1, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glEnd();
	glBegin(GL_LINE_LOOP);
	// Face 3
	glColor3f(0, 0, 1);
	glVertex3f(0.0f, 1, 0.0f);
	glVertex3f(0.0f, 1, 1);
	glVertex3f(1, 1, 1);
	glVertex3f(1, 1, 0.0f);
	glEnd();
	glBegin(GL_LINE_LOOP);
	// Face 4
	glColor3f(1, 1, 0);
	glVertex3f(1, 1, 0.0f);
	glVertex3f(1, 1, 1);
	glVertex3f(1, 0.0f, 1);
	glVertex3f(1, 0.0f, 0.0f);
	glEnd();
	glBegin(GL_LINE_LOOP);
	// Face Up
	glColor3f(1, 0, 1);
	glVertex3f(0.0f, 0.0f, 1);
	glVertex3f(0.0f, 1, 1);
	glVertex3f(1, 1, 1);
	glVertex3f(1, 0.0f, 1);
	glEnd();
	glBegin(GL_LINE_LOOP);
	// Face Bottom
	glColor3f(0, 1, 1);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 1, 0.0f);
	glVertex3f(1, 1, 0.0f);
	glVertex3f(1, 0.0f, 0.0f);
	glEnd();
}

void drawWireCube(float width, float height, float depth) {
	float w = width / 2.0f;
	float h = height / 2.0f;
	float d = depth / 2.0f;

	// Front Face
	glBegin(GL_LINE_LOOP);
	glVertex3f(-w, -h, d);
	glVertex3f(w, -h, d);
	glVertex3f(w, h, d);
	glVertex3f(-w, h, d);
	glEnd();

	// Back Face
	glBegin(GL_LINE_LOOP);
	glVertex3f(-w, -h, -d);
	glVertex3f(w, -h, -d);
	glVertex3f(w, h, -d);
	glVertex3f(-w, h, -d);
	glEnd();

	// Connecting Edges
	glBegin(GL_LINES);
	glVertex3f(-w, -h, d); glVertex3f(-w, -h, -d);
	glVertex3f(w, -h, d);  glVertex3f(w, -h, -d);
	glVertex3f(w, h, d);   glVertex3f(w, h, -d);
	glVertex3f(-w, h, d);  glVertex3f(-w, h, -d);
	glEnd();
}


void p4Q3() {
	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	glLoadIdentity();

	// Whole arm rotation (LEFT/RIGHT keys)
	glRotatef(armRotation, 0, 1, 1);

	// Draw Upper Arm (Fixed Box on Positive X)
	glPushMatrix();
	glTranslatef(0.4f, 0.0f, 0.0f);  // Move to right side (positive X)
	drawWireCube(0.8f, 0.3f, 0.3f);
	glPopMatrix();

	// Draw Lower Arm (Rotatable Box on Negative X side)
	glPushMatrix();
	// Move pivot to left face bottom-right point of upper arm
	glTranslatef(0.0f, -0.15f, 0.15f); // X: 0 (left face), Y: bottom, Z: right edge
	glRotatef(lowerArmAngle, 0, 0, 1);  // Rotate around Z-axis (in-place)
	glTranslatef(-0.4f, 0.15f, -0.15f); // Offset back to center of lower arm
	drawWireCube(0.8f, 0.3f, 0.3f);
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
		else if (wParam == 'X')
			rx = 1, ry = 0, rz = 0;
		else if (wParam == 'Y')
			rx = 0, ry = 1, rz = 0;
		else if (wParam == 'Z')
			rx = 0, ry = 0, rz = 1;
		else if (wParam == VK_UP)
			lowerArmAngle -= 5.0f;  // Lower Arm Up
		else if (wParam == VK_DOWN)
			lowerArmAngle += 5.0f;  // Lower Arm Down
		else if (wParam == VK_RIGHT)
			armRotation += 5.0f;    // Rotate whole arm right
		else if (wParam == VK_LEFT)
			armRotation -= 5.0f;    // Rotate whole arm left
		else if (wParam == VK_SPACE) { // Reset
			lowerArmAngle = 0.0f;
			armRotation = 0.0f;
		}
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
		p4Q1();
		break;

	case 2:
		p4Q2();
		break;

	case 3:
		p4Q3();
		break;

	case 4:
		p4Demo();
		break;

	case 5:
		break;
	case 6:
		break;

	default:
		p4Demo();
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