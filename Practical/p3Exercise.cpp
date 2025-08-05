#include <Windows.h>
#include <gl/GL.h>
#include <math.h>

#pragma comment (lib, "OpenGL32.lib")

#define WINDOW_TITLE "OpenGL Window"

int qNum = 1;
float tx1 = 0;
float ty1 = 0;
float tx2 = 0;
float ty2 = 0;
float tSpeed = 0.1;

float rotationAngle = 0.0f;
float rotationSpeed = 0.01f;
bool isSpinning = true;

float boatPos = -1.2f;
float boatSpeed = 0.0005f;
bool isDay = true;

// --- Helper Functions ---
void drawStar(float x, float y, float size) {
	glPushMatrix();
	glTranslatef(x, y, 0);
	glScalef(size, size, 1.0f);

	glBegin(GL_POLYGON);
	glColor3f(1, 1, 0);
	glVertex2f(0, 0.5); // top
	glVertex2f(0.15, 0); // right
	glVertex2f(0, -0.5); // bottom
	glVertex2f(-0.15, 0); // left
	glEnd();

	glBegin(GL_POLYGON);
	glVertex2f(0.15, 0); // right
	glVertex2f(0.65, 0);
	glVertex2f(0, -0.5); // bottom
	glEnd();

	glBegin(GL_POLYGON);
	glVertex2f(-0.15, 0); // left
	glVertex2f(-0.65, 0);
	glVertex2f(0, -0.5); // bottom
	glEnd();

	glBegin(GL_POLYGON);
	glVertex2f(-0.15, 0); // left
	glVertex2f(0, -0.5); // bottom
	glVertex2f(-0.45, -0.8); // bottom left tip
	glEnd();

	glBegin(GL_POLYGON);
	glVertex2f(0.15, 0); // right
	glVertex2f(0, -0.5); // bottom
	glVertex2f(0.45, -0.8); // bottom right tip
	glEnd();

	glPopMatrix();
}

// Function to draw a filled circle
void drawCircle(float cx, float cy, float r, int num_segments) {
	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(cx, cy); // Center of the circle
	for (int i = 0; i <= num_segments; i++) {
		float theta = 2.0f * 3.1415926f * float(i) / float(num_segments);
		float x = r * cosf(theta);
		float y = r * sinf(theta);
		glVertex2f(cx + x, cy + y);
	}
	glEnd();
}

//void drawFlower(float x, float y) {
//	glClear(GL_COLOR_BUFFER_BIT); // Clear the color buffer
//	glLoadIdentity(); // Reset the modelview matrix
//
//	// Draw the stem
//	glColor3f(0.0f, 0.5f, 0.0f); // Dark green
//	glRectf(-0.05f, -0.8f, 0.05f, 0.2f); // Simple rectangle for stem
//
//	// Draw petals (example: 5 petals)
//	glColor3f(1.0f, 0.5f, 0.7f); // Pink petals
//	float petal_radius = 0.2f;
//	float center_x = 0.0f;
//	float center_y = 0.3f;
//	int num_petals = 5;
//	for (int i = 0; i < num_petals; ++i) {
//		float angle = 2.0f * 3.1415926f * i / num_petals;
//		float petal_offset_x = 0.15f * cosf(angle);
//		float petal_offset_y = 0.15f * sinf(angle);
//		drawCircle(center_x + petal_offset_x, center_y + petal_offset_y, petal_radius, 30);
//	}
//
//	// Draw the center of the flower
//	glColor3f(1.0f, 1.0f, 0.0f); // Yellow center
//	drawCircle(center_x, center_y, 0.1f, 30);
//}
void drawFlower(float x, float y, float size, int num_petals, float r_petal, float g_petal, float b_petal, float r_center, float g_center, float b_center) {
	// Draw the stem (adjusted to size & position)
	glColor3f(0.0f, 0.5f, 0.0f); // Dark green
	float stem_width = size * 0.1f;
	float stem_height = size * 0.8f;
	glBegin(GL_QUADS);
	glVertex2f(x - stem_width / 2, y - stem_height);
	glVertex2f(x + stem_width / 2, y - stem_height);
	glVertex2f(x + stem_width / 2, y);
	glVertex2f(x - stem_width / 2, y);
	glEnd();

	// Draw petals
	glColor3f(r_petal, g_petal, b_petal);
	float petal_radius = size * 0.2f;
	float petal_offset = size * 0.3f;
	for (int i = 0; i < num_petals; ++i) {
		float angle = 2.0f * 3.1415926f * i / num_petals;
		float petal_x = x + petal_offset * cosf(angle);
		float petal_y = y + petal_offset * sinf(angle);
		drawCircle(petal_x, petal_y, petal_radius, 30);
	}

	// Draw the center (pistil)
	glColor3f(r_center, g_center, b_center);
	drawCircle(x, y, size * 0.1f, 30);
}




// --- Original Part ---
void p3Q1() {
	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT);

	glPushMatrix();
	glTranslatef(tx1, ty1, 0);
	glBegin(GL_QUADS);
	glColor3f(1, 0, 0);
	glVertex2f(-0.5, 0.0);
	glVertex2f(-0.5, 0.5);
	glVertex2f(0.5, 0.5);
	glVertex2f(0.5, 0.0);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(tx2, ty2, 0);
	glBegin(GL_QUADS);
	glColor3f(0, 1, 0);
	glVertex2f(-0.5, 0.0);
	glVertex2f(-0.5, 0.5);
	glVertex2f(0.5, 0.5);
	glVertex2f(0.5, 0.0);
	glEnd();
	glPopMatrix();
}

// --- Scene Background ---
void drawBackground() {
	// Sky
	glBegin(GL_QUADS);
	if (isDay)
		glColor3f(0.53f, 0.81f, 0.92f);
	else
		glColor3f(0.05f, 0.05f, 0.2f);
	glVertex2f(-1.0f, 1.0f);
	glVertex2f(1.0f, 1.0f);
	glVertex2f(1.0f, 0.0f);
	glVertex2f(-1.0f, 0.0f);
	glEnd();

	// Sea
	glBegin(GL_QUADS);
	glColor3f(0.0f, 0.4f, 0.7f);
	glVertex2f(-1.0f, 0.0f);
	glVertex2f(1.0f, 0.0f);
	glVertex2f(1.0f, -0.5f);
	glVertex2f(-1.0f, -0.5f);
	glEnd();

	// Grass
	glBegin(GL_QUADS);
	glColor3f(0.48f, 0.98f, 0.0f);
	glVertex2f(1.0f, -0.5f);
	glVertex2f(-1.0f, -0.5f);
	glVertex2f(-1.0f, -1.0f);
	glVertex2f(1.0f, -1.0f);
	glEnd();

	// Sun or Crescent Moon
	if (isDay) {
		// Sun Body
		glBegin(GL_TRIANGLE_FAN);
		glColor3f(1.0f, 1.0f, 0.0f);
		float cx = 0.8f, cy = 0.8f, r = 0.1f;
		glVertex2f(cx, cy);
		for (int i = 0; i <= 40; i++) {
			float angle = 2.0f * 3.1415926f * i / 40.0f;
			glVertex2f(cx + r * cosf(angle), cy + r * sinf(angle));
		}
		glEnd();

		// Sun Rays
		for (int i = 0; i < 8; i++) {
			float angle = i * 3.1415926f / 4.0f;
			float sx = cx + cosf(angle) * 0.15f;
			float sy = cy + sinf(angle) * 0.15f;
			glBegin(GL_LINES);
			glColor3f(1.0f, 1.0f, 0.0f);
			glVertex2f(cx, cy);
			glVertex2f(sx, sy);
			glEnd();
		}
	}
	else {
		// Full Moon Base
		glBegin(GL_TRIANGLE_FAN);
		glColor3f(0.9f, 0.9f, 0.9f);
		float cx = 0.8f, cy = 0.8f, r = 0.1f;
		glVertex2f(cx, cy);
		for (int i = 0; i <= 40; i++) {
			float angle = 2.0f * 3.1415926f * i / 40.0f;
			glVertex2f(cx + r * cosf(angle), cy + r * sinf(angle));
		}
		glEnd();

		// Crescent Cut
		glBegin(GL_TRIANGLE_FAN);
		glColor3f(0.05f, 0.05f, 0.2f);
		float offset = 0.04f;
		glVertex2f(cx + offset, cy + offset);
		for (int i = 0; i <= 40; i++) {
			float angle = 2.0f * 3.1415926f * i / 40.0f;
			glVertex2f(cx + offset + r * cosf(angle) * 0.85f, cy + offset + r * sinf(angle) * 0.85f);
		}
		glEnd();

		// Stars
		drawStar(-0.7f, 0.7f, 0.05f);
		drawStar(-0.4f, 0.85f, 0.1f);
		drawStar(0.0f, 0.6f, 0.08f);
		drawStar(0.5f, 0.9f, 0.1f);
		drawStar(-0.2f, 0.4f, 0.1f);
	}

	// Flowers on Grass
	drawFlower(-0.5f, -0.7f, 0.2f, 6, 1.0f, 0.5f, 0.7f, 1.0f, 1.0f, 0.0f);  // Pink petals, Yellow center
	drawFlower(0.3f, -0.8f, 0.15f, 8, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f);    // Red petals, Yellow center
	drawFlower(-0.8f, -0.7f, 0.18f, 6, 1.0f, 0.8f, 0.6f, 1.0f, 1.0f, 0.0f);  //  Soft Pink petals, Yellow center
	drawFlower(0.6f, -0.6f, 0.13f, 8, 0.7f, 0.5f, 0.9f, 1.0f, 1.0f, 0.0f);    //  Lavender Purple, Yellow center


}

// --- Boat ---
void drawBoat() {
	glPushMatrix();
	glTranslatef(boatPos, -0.5f, 0.0f);

	glBegin(GL_QUADS);
	glColor3f(0.6f, 0.3f, 0.0f);
	glVertex2f(-0.2f, 0.25f);
	glVertex2f(0.2f, 0.25f);
	glVertex2f(0.15f, 0.3f);
	glVertex2f(-0.15f, 0.3f);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(0.7f, 0.7f, 0.7f);
	glVertex2f(0.0f, 0.3f);
	glVertex2f(0.02f, 0.3f);
	glVertex2f(0.02f, 0.5f);
	glVertex2f(0.0f, 0.5f);
	glEnd();

	glBegin(GL_TRIANGLES);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex2f(0.02f, 0.5f);
	glVertex2f(0.02f, 0.3f);
	glVertex2f(0.15f, 0.4f);
	glEnd();

	glPopMatrix();

	boatPos += boatSpeed;
	if (boatPos > 1.2f) boatPos = -1.2f;
	if (boatPos < -1.2f) boatPos = 1.2f;
}

// --- Windmill Blade ---
void drawBlade() {
	glBegin(GL_TRIANGLES);
	glColor3f(0.7f, 0.7f, 0.7f);
	glVertex2f(0.0f, 0.0f);
	glVertex2f(0.4f, 0.1f);
	glVertex2f(0.4f, -0.1f);
	glEnd();
}

// --- Windmill ---
void drawWindmill() {
	glBegin(GL_TRIANGLES);
	glColor3f(0.55f, 0.27f, 0.07f);
	glVertex2f(-0.1f, -0.8f);
	glVertex2f(0.1f, -0.8f);
	glVertex2f(0.0f, 0.1f);
	glEnd();

	glPushMatrix();
	glTranslatef(0.0f, 0.1f, 0.0f);
	glRotatef(rotationAngle, 0.0f, 0.0f, 1.0f);
	for (int i = 0; i < 4; i++) {
		drawBlade();
		glRotatef(90.0f, 0.0f, 0.0f, 1.0f);
	}
	glPopMatrix();

	glBegin(GL_TRIANGLE_FAN);
	glColor3f(0.3f, 0.3f, 0.3f);
	glVertex2f(0.0f, 0.1f);
	for (int i = 0; i <= 20; i++) {
		float angle = 2.0f * 3.1415926f * i / 20.0f;
		glVertex2f(0.05f * cosf(angle), 0.05f * sinf(angle) + 0.1f);
	}
	glEnd();

	if (isSpinning) {
		rotationAngle += rotationSpeed;
		if (rotationAngle > 360.0f) rotationAngle -= 360.0f;
		if (rotationAngle < -360.0f) rotationAngle += 360.0f;
	}
}

void p3Q2() {
	glClear(GL_COLOR_BUFFER_BIT);
	drawBackground();
	drawBoat();
	drawWindmill();
	
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
		{
			tx1 += tSpeed;
			tx2 -= tSpeed;
		}

		else if (wParam == VK_LEFT)
		{
			tx1 -= tSpeed;
			tx2 += tSpeed;
		}
		else if (wParam == VK_UP)
		{
			ty1 += tSpeed;
			ty2 -= tSpeed;
		}
		else if (wParam == VK_DOWN)
		{
			ty1 -= tSpeed;
			ty2 += tSpeed;
		}
		else if (wParam == VK_SPACE) {
			tx1 = 0;
			ty1 = 0;
			tx2 = 0;
			ty2 = 0;
			isSpinning = false;

		}
		else if (wParam == 'C') // Spin Clockwise
			rotationSpeed = fabs(rotationSpeed), isSpinning = true;
		else if (wParam == 'A') // Spin Anti-Clockwise
			rotationSpeed = -fabs(rotationSpeed), isSpinning = true;
		else if (wParam == 'W') // Accelerate
			rotationSpeed += (rotationSpeed > 0 ? 0.01f : -0.01f);
		else if (wParam == 'S') // Decelerate
			rotationSpeed -= (rotationSpeed > 0 ? 0.01f : -0.01f);
		else if (wParam == 'D') // Toggle Day/Night
			isDay = !isDay;
		else if (wParam == 'B') // Reverse Boat Direction
			boatSpeed *= -1;

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
		p3Q2();
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