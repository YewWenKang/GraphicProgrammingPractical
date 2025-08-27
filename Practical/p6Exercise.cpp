#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <math.h>

#pragma comment (lib, "OpenGL32.lib")
#pragma comment (lib, "GLU32.lib")

#define WINDOW_TITLE "Practical 6"

float ambL[3] = { 1.0,  1.0,  1.0 };                // red colour ambient light
float pos[3] = { 0.0, 0.8, 0.0 };                 // light position (0,0.8 , 0) above sphere
float difL[3] = { 1.0,  0.0,  0.0 };                //red dif light
float posA[3] = { 0.0, 0.8, 0.0 };                // light position (0,0.8 , 0) above sphere
float posD[3] = { 0.8, 0.0, 0.0 };                // light position (0,0.8 , 0) right sphere
float ambN[3] = { 0.0, 0.0, 1.0 };                // blue amb material
float difN[3] = { 1.0, 0.0, 0.0 };                // blue dif material
bool isLightOn = false;
bool showSphere = true;

float rotation = -0.01;

LRESULT WINAPI WindowProcedure(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
    case WM_DESTROY:
        PostQuitMessage(0);
        break;

    case WM_KEYDOWN:
        if (wParam == VK_ESCAPE)
        {
            PostQuitMessage(0);
		}
        else if (wParam == VK_SPACE) {
			isLightOn = !isLightOn;
        }
        else if (wParam == 'O') {
            showSphere = true;
        }
        else if (wParam == 'P') {
            showSphere = false;
        }
        else if (wParam == VK_UP) {
            rotation = -0.01;
        }
        else if (wParam == VK_DOWN) {
            rotation = 0.01;
        }

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

void drawSphere(double r, GLenum style)
{
    GLUquadricObj* sphere = NULL;   // create the quadratic obj pointer
    sphere = gluNewQuadric();       // create the quadratic obj in the memory

    //gluQuadricDrawStyle(sphere, style);
    gluSphere(sphere, r, 30, 30);   // draw sphere

    gluDeleteQuadric(sphere);       // delete quadric object
}
void drawPyramid()
{
    glBegin(GL_TRIANGLES);
    // Front
    glVertex3f(0.0f, 0.5f, 0.0f);
    glVertex3f(-0.5f, -0.5f, 0.5f);
    glVertex3f(0.5f, -0.5f, 0.5f);

    // Right
    glVertex3f(0.0f, 0.5f, 0.0f);
    glVertex3f(0.5f, -0.5f, 0.5f);
    glVertex3f(0.5f, -0.5f, -0.5f);

    // Back
    glVertex3f(0.0f, 0.5f, 0.0f);
    glVertex3f(0.5f, -0.5f, -0.5f);
    glVertex3f(-0.5f, -0.5f, -0.5f);

    // Left
    glVertex3f(0.0f, 0.5f, 0.0f);
    glVertex3f(-0.5f, -0.5f, -0.5f);
    glVertex3f(-0.5f, -0.5f, 0.5f);
    glEnd();

    // Base (square)
    glBegin(GL_QUADS);
    glVertex3f(-0.5f, -0.5f, 0.5f);
    glVertex3f(0.5f, -0.5f, 0.5f);
    glVertex3f(0.5f, -0.5f, -0.5f);
    glVertex3f(-0.5f, -0.5f, -0.5f);
    glEnd();
}


void lighting() {
    if (isLightOn) {
        glEnable(GL_LIGHTING);
    }
    else {
		glDisable(GL_LIGHTING);
    }

    

    //Light 0 : red color amb light at pos (0 , 0.8 , 0) above sphere
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambL);
    glLightfv(GL_LIGHT0, GL_POSITION, posA);
    glEnable(GL_LIGHT0);

    //Light 1 : green color amb light at pos (0.0, 0.8 , 0) above sphere
    //glLightfv(GL_LIGHT1, GL_DIFFUSE, difL);
    //glLightfv(GL_LIGHT1, GL_POSITION, posD);
    //glEnable(GL_LIGHT1);


}

void display()
{
    glClearColor(0, 0, 0, 0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);

    lighting();

    glMatrixMode(GL_MODELVIEW);
    glRotatef(rotation, 1.0, 1.0, 1.0);

    glColor3f(1.0, 0.0, 0.0);
    //glMaterialfv(GL_FRONT, GL_AMBIENT, ambN);   //blue amb material
    glMaterialfv(GL_FRONT, GL_DIFFUSE, difN);     //blue dif material
    if (showSphere) {
        drawSphere(0.5, GLU_FILL);
    }
    else {
        drawPyramid();
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
        950, 10, 500, 500,
        NULL, NULL, wc.hInstance, NULL);

    //--------------------------------
    //  Initialize window for OpenGL
    //--------------------------------

    HDC hdc = GetDC(hWnd);

    //  initialize pixel format for the window
    initPixelFormat(hdc);

    //  get an openGL context
    HGLRC hglrc = wglCreateContext(hdc);

    //  make context current
    if (!wglMakeCurrent(hdc, hglrc)) return false;

    //--------------------------------
    //  End initialization
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