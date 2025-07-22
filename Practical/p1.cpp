
#include <Windows.h>
#include <gl/GL.h>
#include <math.h>

#pragma comment (lib, "OpenGL32.lib") // Linker -> Input  -> Edit -> OpenGL32.lib

#define WINDOW_TITLE "Prac1 Demo"

int qNum = 1;			//Question Number, Default Q1
float x = 0, y = 0;	//Origin of circle
float radius = 0.2;		//radius
float x2 = 0, y2 = 0;	//point on circle
float angle = 0;		//angle
float PI = 3.1429;		//PI
int noOfTri = 30;		//No of triangle

const float PI2 = 3.1415926f;

void drawCircle(float cx, float cy, float r, int segments, bool filled = true) {
	if (filled) {
		glBegin(GL_TRIANGLE_FAN);
	}
	else {
		glBegin(GL_LINE_LOOP);
	}
	for (int i = 0; i < segments; i++) {
		float theta = 2.0f * PI2 * i / segments;
		float x = r * cosf(theta);
		float y = r * sinf(theta);
		glVertex2f(cx + x, cy + y);
	}
	glEnd();
}

void drawEllipse(float cx, float cy, float rx, float ry, int segments, bool filled = true) {
	if (filled) {
		glBegin(GL_TRIANGLE_FAN);
	}
	else {
		glBegin(GL_LINE_LOOP);
	}
	for (int i = 0; i < segments; i++) {
		float theta = 2.0f * PI2 * i / segments;
		float x = rx * cosf(theta);
		float y = ry * sinf(theta);
		glVertex2f(cx + x, cy + y);
	}
	glEnd();
}

void drawBat(float cx, float cy, float scale, float angleDegrees = 0.0f) {
	glPushMatrix();
	glTranslatef(cx, cy, 0);
	glRotatef(angleDegrees, 0, 0, 1);
	glScalef(scale, scale, 1);

	glColor3f(0.1f, 0.1f, 0.1f);
	glBegin(GL_TRIANGLES);
	glVertex2f(-0.05f, 0.0f); glVertex2f(0.0f, 0.03f); glVertex2f(0.05f, 0.0f);
	glVertex2f(-0.07f, 0.0f); glVertex2f(-0.05f, 0.04f); glVertex2f(-0.03f, 0.0f);
	glVertex2f(0.07f, 0.0f);  glVertex2f(0.05f, 0.04f);  glVertex2f(0.03f, 0.0f);
	glEnd();

	glPopMatrix();
}

void drawCreativeEmoji() {
	glClearColor(1, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT);

	// --- Red Cloak ---
	glColor3f(0.6f, 0.0f, 0.0f);
	glBegin(GL_TRIANGLES);
	glVertex2f(-1.0f, -0.2f);
	glVertex2f(1.0f, -0.2f);
	glVertex2f(0.0f, -1.0f);
	glEnd();
	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_LINE_LOOP);
	glVertex2f(-1.0f, -0.2f);
	glVertex2f(1.0f, -0.2f);
	glVertex2f(0.0f, -1.0f);
	glEnd();

	//base face
	glColor3f(1.0f, 0.85f, 0.3f);
	drawCircle(0.0f, 0.0f, 0.9f, 100);
	glColor3f(1.0f, 0.75f, 0.0f);
	drawCircle(0.0f, 0.0f, 0.8f, 100);



	// --- Eyes ---
	glColor3f(1, 1, 1);
	drawEllipse(-0.35f, 0.35f, 0.10f, 0.14f, 50);
	drawEllipse(0.35f, 0.35f, 0.10f, 0.14f, 50);

	glColor3f(1, 0, 0);
	drawCircle(-0.35f, 0.35f, 0.09f, 50);
	drawCircle(0.35f, 0.35f, 0.09f, 50);

	glColor3f(0, 0, 0);
	drawCircle(-0.35f, 0.35f, 0.06f, 50);
	drawCircle(0.35f, 0.35f, 0.06f, 50);

	glColor3f(1, 1, 1);
	drawCircle(-0.39f, 0.40f, 0.015f, 30);  // highlight adjusted
	drawCircle(0.31f, 0.40f, 0.015f, 30);

	// --- Eyebrows ---
	glColor3f(0, 0, 0);
	glBegin(GL_QUADS);
	glVertex2f(-0.53f, 0.58f); glVertex2f(-0.17f, 0.58f);
	glVertex2f(-0.14f, 0.52f); glVertex2f(-0.56f, 0.52f);
	glEnd();
	glBegin(GL_QUADS);
	glVertex2f(0.53f, 0.58f); glVertex2f(0.17f, 0.58f);
	glVertex2f(0.14f, 0.52f); glVertex2f(0.56f, 0.52f);
	glEnd();

	// --- Vampire Mouth Arc (extended) ---
	glColor3f(0.5f, 0.0f, 0.0f);
	glBegin(GL_LINE_STRIP);
	for (int i = -20; i <= 200; i++) {
		float theta = i * PI / 180.0f;
		glVertex2f(0.20f * cosf(theta), -0.4f - 0.05f * sinf(theta));
	}
	glEnd();

	// --- Fangs ---
	glColor3f(1, 1, 1);
	glBegin(GL_TRIANGLES);
	glVertex2f(-0.15f, -0.45f); glVertex2f(-0.05f, -0.45f); glVertex2f(-0.10f, -0.65f);
	glVertex2f(0.15f, -0.45f);  glVertex2f(0.05f, -0.45f);  glVertex2f(0.10f, -0.65f);
	glEnd();

	// --- Bat Ears ---
	glColor3f(0.2f, 0.0f, 0.2f);
	glBegin(GL_TRIANGLES);
	glVertex2f(-0.5f, 0.7f); glVertex2f(-0.6f, 1.0f); glVertex2f(-0.4f, 0.9f);
	glVertex2f(0.5f, 0.7f);  glVertex2f(0.6f, 1.0f);  glVertex2f(0.4f, 0.9f);
	glEnd();

	// --- Bats in Background with Rotation ---
	drawBat(-0.7f, 0.8f, 1.0f, 0.0f);
	drawBat(0.6f, 0.85f, 0.8f, 45.0f);
	drawBat(0.0f, 0.95f, 1.2f, -30.0f);
	drawBat(0.6f, -0.95f, 1.2f, -30.0f);
	drawBat(-0.7f, -0.8f, 1.0f, 20.0f);

}

void triangle() {
	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT);
	glLineWidth(10.0);
	glPointSize(10.0);
	glBegin(GL_LINE_LOOP);
	glColor3f(1, 0, 0);
	glVertex2f(-0.5, 0);

	glColor3f(0, 1, 0);
	glVertex2f(0, 0.5);

	glColor3f(0, 0, 1);
	glVertex2f(0.5, 0);

	glEnd();
}

void pahangFlag() {
	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_QUADS);
	glColor3f(1, 1, 1);
	glVertex2f(-0.5, 0);
	glVertex2f(-0.5, 0.5);
	glVertex2f(0.5, 0.5);
	glVertex2f(0.5, 0);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(0, 0, 0);
	glVertex2f(-0.5, -0.5);
	glVertex2f(-0.5, 0);
	glVertex2f(0.5, 0);
	glVertex2f(0.5, -0.5);
	glEnd();

	glLineWidth(2.0);
	glBegin(GL_LINE_LOOP);
	glColor3f(0, 0, 1);
	glVertex2f(-0.5, 0.5);
	glVertex2f(0.5, 0.5);
	glVertex2f(0.5, -0.5);
	glVertex2f(-0.5, -0.5);
	glEnd();
}

void n9Flag() {
	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_QUADS);
	glColor3f(1, 1, 0.33);
	glVertex2f(-0.5, 0.5);
	glVertex2f(0.5, 0.5);
	glVertex2f(0.5, -0.5);
	glVertex2f(-0.5, -0.5);
	glEnd();

	glBegin(GL_TRIANGLES);
	glColor3f(1, 0, 0);
	glVertex2f(-0.5, 0.5);
	glVertex2f(0, 0.5);
	glVertex2f(0, 0);
	glEnd();

	glBegin(GL_TRIANGLES);
	glColor3f(0, 0, 0);
	glVertex2f(-0.5, 0.5);
	glVertex2f(-0.5, 0);
	glVertex2f(0, 0);
	glEnd();

	glLineWidth(2.0);
	glBegin(GL_LINE_LOOP);
	glColor3f(0, 0, 1);
	glVertex2f(-0.5, 0.5);
	glVertex2f(0.5, 0.5);
	glVertex2f(0.5, -0.5);
	glVertex2f(-0.5, -0.5);
	glEnd();
}

void englandFlag() {

	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT);

	glLineWidth(2.0);
	glBegin(GL_LINE_LOOP);
	glColor3f(0, 0, 1);
	glVertex2f(-0.5, 0.5);
	glVertex2f(0.5, 0.5);
	glVertex2f(0.5, -0.5);
	glVertex2f(-0.5, -0.5);
	glEnd();

	//top left
	glBegin(GL_QUADS);
	glColor3f(0.75, 0.75, 0.75);
	glVertex2f(-0.5, 0.5);
	glColor3f(1, 1, 1);
	glVertex2f(0, 0.5);
	glColor3f(1, 1, 1);
	glVertex2f(0, 0);
	glColor3f(1, 1, 1);
	glVertex2f(-0.5, 0);
	glEnd();

	//top right
	glBegin(GL_QUADS);
	glColor3f(0.75, 0.75, 0.75);
	glVertex2f(0.5, 0.5);
	glColor3f(1, 1, 1);
	glVertex2f(0.5, 0);
	glColor3f(1, 1, 1);
	glVertex2f(0, 0);
	glColor3f(1, 1, 1);
	glVertex2f(0, 0.5);
	glEnd();

	//bottom right
	glBegin(GL_QUADS);
	glColor3f(0.75, 0.75, 0.75);
	glVertex2f(0.5, -0.5);
	glColor3f(1, 1, 1);
	glVertex2f(0, -0.5);
	glColor3f(1, 1, 1);
	glVertex2f(0, 0);
	glColor3f(1, 1, 1);
	glVertex2f(0.5, 0);
	glEnd();

	//bottom left
	glBegin(GL_QUADS);
	glColor3f(0.75, 0.75, 0.75);
	glVertex2f(-0.5, -0.5);
	glColor3f(1, 1, 1);
	glVertex2f(0, -0.5);
	glColor3f(1, 1, 1);
	glVertex2f(0, 0);
	glColor3f(1, 1, 1);
	glVertex2f(-0.5, 0);
	glEnd();

	//red line
	glBegin(GL_QUADS);
	glColor3f(1, 0, 0);
	glVertex2f(-0.1, 0.5);
	glVertex2f(0.1, 0.5);
	glVertex2f(0.1, -0.5);
	glVertex2f(-0.1, -0.5);
	glEnd();

	//red line
	glBegin(GL_QUADS);
	glColor3f(1, 0, 0);
	glVertex2f(0.5, -0.1);
	glVertex2f(0.5, 0.1);
	glVertex2f(-0.5, 0.1);
	glVertex2f(-0.5, -0.1);
	glEnd();


}

void scotlandFlag() {
	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT);

	glLineWidth(2.0);
	glBegin(GL_LINE_LOOP);
	glColor3f(0, 0, 1);
	glVertex2f(-0.5, 0.5);
	glVertex2f(0.5, 0.5);
	glVertex2f(0.5, -0.5);
	glVertex2f(-0.5, -0.5);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(0, 0.39, 0.74);
	glVertex2f(0.5, 0.5);
	glVertex2f(0.5, -0.5);
	glVertex2f(-0.5, -0.5);
	glVertex2f(-0.5, 0.5);
	glEnd();

	//line
	glBegin(GL_POLYGON);
	glColor3f(1, 1, 1);
	glVertex2f(-0.5, 0.5);
	glVertex2f(-0.4, 0.5);
	glVertex2f(0.5, -0.4);
	glVertex2f(0.5, -0.5);
	glVertex2f(0.4, -0.5);
	glVertex2f(-0.5, 0.4);
	glEnd();

	//line
	glBegin(GL_POLYGON);
	glColor3f(1, 1, 1);
	glVertex2f(0.5, 0.5);
	glVertex2f(0.5, 0.4);
	glVertex2f(-0.4, -0.5);
	glVertex2f(-0.5, -0.5);
	glVertex2f(-0.5, -0.4);
	glVertex2f(0.4, 0.5);
	glEnd();





}

void japanFlag() {
	x = 0, y = 0;	//Origin of circle
	radius = 0.2;		//radius
	x2 = 0, y2 = 0;	//point on circle
	angle = 0;		//angle
	PI = 3.1429;		//PI
	noOfTri = 30;		//No of triangle

	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT);

	glBegin(GL_QUADS);
	glColor3f(1, 1, 1);
	glVertex2f(-0.5, 0.5);
	glVertex2f(0.5, 0.5);
	glVertex2f(0.5, -0.5);
	glVertex2f(-0.5, -0.5);
	glEnd();

	glBegin(GL_TRIANGLE_FAN);
	glColor3f(1, 0, 0);
	glVertex2f(x, y);		//Origin of the circle
	for (angle = 0; angle <= 2 * PI; angle += (2 * PI) / noOfTri) {
		x2 = x + radius * cos(angle);
		y2 = y + radius * sin(angle);
		glVertex2f(x2, y2);
	}

	glEnd();

	glLineWidth(2.0);
	glBegin(GL_LINE_LOOP);
	glColor3f(0, 0, 1);
	glVertex2f(-0.5, 0.5);
	glVertex2f(0.5, 0.5);
	glVertex2f(0.5, -0.5);
	glVertex2f(-0.5, -0.5);
	glEnd();

}

void smileyFace() {

	x = 0, y = 0;	//Origin of circle
	radius = 0.5;		//radius
	x2 = 0, y2 = 0;	//point on circle
	angle = 0;		//angle
	PI = 3.1429;		//PI
	noOfTri = 30;		//No of triangle
	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT);

	glBegin(GL_QUADS);
	glColor3f(1, 1, 1);
	glVertex2f(-0.5, 0.5);
	glVertex2f(0.5, 0.5);
	glVertex2f(0.5, -0.5);
	glVertex2f(-0.5, -0.5);
	glEnd();

	glBegin(GL_TRIANGLE_FAN);
	glColor3f(1, 1, 0.33);
	glVertex2f(x, y);		//Origin of the circle
	for (angle = 0; angle <= 2 * PI; angle += (2 * PI) / noOfTri) {
		x2 = x + radius * cos(angle);
		y2 = y + radius * sin(angle);
		glVertex2f(x2, y2);
	}

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
	//--------------------------------
	//	OpenGL drawing
	//--------------------------------

	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT);
	switch (qNum) {
	case 1:
		pahangFlag();
		break;

	case 2:
		n9Flag();
		break;

	case 3:
		englandFlag();
		break;

	case 4:
		scotlandFlag();
		break;

	case 5:
		japanFlag();
		break;
	case 6:
		drawCreativeEmoji();
		break;

	default:
		//triangle();
		japanFlag();
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
		950, 10, 300, 300,
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