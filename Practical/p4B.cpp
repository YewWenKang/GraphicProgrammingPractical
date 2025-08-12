#include <Windows.h>
#include <GL/glu.h>
#include <math.h>

#pragma comment (lib, "OpenGL32.lib") // Linker -> Input  -> Edit -> OpenGL32.lib

#define WINDOW_TITLE "Prac1 Demo"

int qNum = 1;			//Question Number, Default Q1
float yRotation = 0;  // Global rotation variable

void drawSphere(double r) {
	GLUquadricObj* sphere = NULL;
	sphere = gluNewQuadric();
	gluQuadricDrawStyle(sphere, GLU_LINE);
	gluSphere(sphere, r, 30, 30);
	gluDeleteQuadric(sphere);
}

void drawDisk(double inr, double outr) {
	GLUquadricObj* disk = NULL;
	disk = gluNewQuadric();
	gluQuadricDrawStyle(disk, GLU_LINE);
	gluDisk(disk, inr, outr, 20, 20);
	gluDeleteQuadric(disk);
}

void drawScoop(double r) {
	GLUquadricObj* scoop = NULL;
	scoop = gluNewQuadric();
	gluSphere(scoop, r, 30, 30);
	gluDeleteQuadric(scoop);
}

void drawCylinder(double br, double tr, double h, int sl, int st) {
	GLUquadricObj* cylinder = NULL;
	cylinder = gluNewQuadric();
	gluQuadricDrawStyle(cylinder, GLU_LINE);
	gluCylinder(cylinder, br, tr, h, sl, st);
	gluDeleteQuadric(cylinder);
}

void drawChocolate(double br, double tr, double h, int sl, int st) {
	GLUquadricObj* cylinder = NULL;
	cylinder = gluNewQuadric();
	gluCylinder(cylinder, br, tr, h, sl, st);
	gluDeleteQuadric(cylinder);
}

void drawCone(double tr, double h, int sl, int st) {
	GLUquadricObj* cone = NULL;
	cone = gluNewQuadric();
	gluQuadricDrawStyle(cone, GLU_LINE);
	gluCylinder(cone, tr, 0, h, sl, st);
	gluDeleteQuadric(cone);
}

void drawConeWafer(double tr, double h, int sl, int st) {
	GLUquadricObj* cone = NULL;
	cone = gluNewQuadric();
	gluCylinder(cone, tr, 0, h, sl, st);
	gluDeleteQuadric(cone);
}

void drawRing(float R, float tubeRadius, int segments) {
	for (int i = 0; i < segments; ++i) {
		float angle = (2 * 3.14159f * i) / segments;
		float x = R * cos(angle);
		float z = R * sin(angle);

		glPushMatrix();
		glTranslatef(x, 1.1f, z);  // Centered at (0, 1.1, 0)
		glRotatef(-angle * 180.0f / 3.14159f, 0, 1, 0);  // Align cylinder tangentially
		glRotatef(90, 1, 0, 0);  // Make cylinder upright
		drawCylinder(tubeRadius, tubeRadius, 0.02, 10, 10);  // Thin small cylinder
		glPopMatrix();
	}
}

void drawSprinkle(float x, float y, float z, float r, float g, float b) {
	glPushMatrix();
	glColor3f(r, g, b);
	glTranslatef(x, y, z);
	drawScoop(0.02); // very small sphere
	glPopMatrix();
}


void p4BQ1() {


	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	//glLoadIdentity();
	//glRotatef(yRotation, 0.0, 1.0, 0.0);  // Rotate around Y-axis

	glColor3f(1, 1, 1);

	// Draw Cone (Wafer)
	glPushMatrix();
	glColor3f(1, 1, 1);
	glRotatef(90, 1, 0, 0);
	glTranslatef(0.0, 0.0, -0.10);  // <- THIS controls cone position after rotation
	glLineWidth(0.5);
	drawCone(0.15, 1, 30, 10);
	glPopMatrix();

	// Draw Cone (Wafer)
	glPushMatrix();
	glColor3f(0.6, 0.3, 0.1);
	glRotatef(90, 1, 0, 0);
	glTranslatef(0.0, 0.0, -0.10);  // <- THIS controls cone position after rotation
	drawConeWafer(0.15, 1, 30, 30);
	glPopMatrix();

	// Draw Bottom Scoop (Green)
	glPushMatrix();
	glColor3f(0.0, 1.0, 0.0);
	glTranslatef(0.0, 0.2, 0.0);
	drawScoop(0.2);
	glPopMatrix();

	// Draw Top Scoop (Grey)
	float scoopY = 0.4;
	glPushMatrix();
	glColor3f(0.6, 0.6, 0.6);
	glTranslatef(0.0, scoopY, 0.0);
	drawScoop(0.2);
	glPopMatrix();

	// Colorful Sprinkles (chocolate rice)
	drawSprinkle(0.05, scoopY + 0.18, 0.02, 1.0, 0.0, 0.0); // red
	drawSprinkle(-0.04, scoopY + 0.17, -0.03, 0.0, 1.0, 0.0); // green
	drawSprinkle(0.03, scoopY + 0.19, -0.04, 0.0, 0.0, 1.0); // blue
	drawSprinkle(-0.05, scoopY + 0.16, 0.04, 1.0, 1.0, 0.0); // yellow
	drawSprinkle(0.0, scoopY + 0.20, 0.0, 1.0, 0.5, 0.0); // orange
	drawSprinkle(0.06, scoopY + 0.15, -0.02, 0.8, 0.0, 0.8); // purple
	drawSprinkle(-0.02, scoopY + 0.19, 0.05, 0.5, 0.3, 0.1); // brown





	// Topping: Cherry (Red Sphere)
	glPushMatrix();
	glColor3f(1.0, 0.0, 0.0);
	glTranslatef(-0.2, 0.5, 0.0);
	drawScoop(0.1);
	glPopMatrix();

	// Topping: Stick (Chocolate Cylinder)
	glPushMatrix();
	glColor3f(0.4, 0.2, 0.1);
	//glTranslatef(-0.2, 0.4, 0.0);
	//glRotatef(-40, 1, 0, 0);
	glTranslatef(0.0, 0.5, 0.0);  // Move to the middle top scoop
	glRotatef(-40, 1, 0, 0);      // Optional: tilt back for nice angle

	drawChocolate(0.05, 0.05, 0.4, 20, 20);
	glPopMatrix();

	// Topping: Ring (Loop Wafer without glutWireTorus)

	glPushMatrix();
	glColor3f(0.8, 0.7, 0.5);
	//glRotatef(40, 0, 0, 1);

	//glTranslatef(0.2, -0.5, 0.0);
	glRotatef(45, 0, 0, 1);
	glTranslatef(0.5, -0.8, 0);
	
	drawRing(0.10, 0.015, 24);  // Radius=0.15, Tube Thickness=0.015, 24 Segments

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



	//glRotatef(0.01, 1.0, 1.0, 1.0);

	//glColor3f(0, 1, 0);
	//glLineWidth(3);
	////drawSphere(0.2);
	//drawDisk(0.0, 0.19);

	//glColor3f(0, 0, 1);
	//drawCylinder(0.2, 0.2, 0.8, 10,10);

	//glColor3f(0, 0, 1);
	//drawCone(0.2, 0.8, 10, 10);
	//--------------------------------
	//	OpenGL drawing
	//--------------------------------

	switch (qNum) {
	case 1:
		//drawSphere();
		break;

	case 2:
		//drawCylinder();
		break;

	case 3:
		glRotatef(0.01, 0, 1.0, 0);
		p4BQ1();
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