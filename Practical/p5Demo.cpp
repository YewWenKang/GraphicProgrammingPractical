#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <math.h>

#pragma comment (lib, "OpenGL32.lib")
#pragma comment (lib, "GLU32.lib")

#define WINDOW_TITLE "Practical 5"

int qNo = 1;
float tx = 0, tz = 0, tSpeed = 1.0;             // tx, tz with tSpeed for modelView
bool isOrtho = true;                            // is ortho view?
float ONear = -10, OFar = 10;                   // ortho near and far boundary
float PNear = 1, PFar = 10;                     // perspective near and far boundary
float r1 = 5.0;                                 // radius of sphere
float ptx = 0.0, pty = 0.0, ptSpeed = 0.1;      // tx, ty with tSpeed for projection
float pry = 0.0, prSpeed = 0.5;                 // ry with prSpeed for projection

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

        else if (wParam == '1')
            qNo = 1;
        else if (wParam == '2')
            qNo = 2;
        else if (wParam == '3')
            qNo = 3;
        else if (wParam == '4')
            qNo = 4;

        else if (wParam == VK_UP) {         // press UP to move backward
            if (isOrtho) {
                if (tz > ONear + r1)                    // ortho near boundary
                    tz -= tSpeed;
            }
            else {
                if (tz > PNear - PFar)          // perspective near boundary
                    tz -= tSpeed;
            }

        }
        else if (wParam == VK_DOWN) {       // press DOWN to move forward
            if (isOrtho) {
                if (tz < OFar - r1)                 // ortho far boundary
                    tz += tSpeed;
            }
            else {
                if (tz < PNear - r1)            // perspective far boundary, minus radius of sphere
                    tz += tSpeed;
            }

        }
        else if (wParam == VK_LEFT) {       // press LEFT to move left the model
            tx -= tSpeed;
        }
        else if (wParam == VK_RIGHT) {      // press RIGHT to move right the model
            tx += tSpeed;
        }
        else if (wParam == 'O') {           // press O for ortho view
            isOrtho = true;
            tz = 0;
        }
        else if (wParam == 'P') {           // press P for perspective view
            isOrtho = false;
            tz = 0;
        }
        else if (wParam == 'A') {           // press A to move left the view
            ptx -= ptSpeed;
        }
        else if (wParam == 'D') {
            ptx += ptSpeed;                 // press D to move right the view
        }
        else if (wParam == 'L') {           // press L to rotate anticlockwise for projection
            pry += prSpeed;
        }
        else if (wParam == 'R') {           // press R to rotate clockwise for projection
            pry -= prSpeed;
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

    gluQuadricDrawStyle(sphere, style);
    gluSphere(sphere, r, 30, 30);   // draw sphere

    gluDeleteQuadric(sphere);       // delete quadric object
}

void projection()
{
    glMatrixMode(GL_PROJECTION);            // refer to the projection matrix
    glLoadIdentity();                       // reset the projection matrix

    glTranslatef(ptx, pty, 0.0);            // tx, ty for projection
    glRotatef(pry, 0.0, 1.0, 0.0);          // ry for projection

    if (isOrtho) {
        glOrtho(-10, 10, -10, 10, ONear, OFar);     // ortho view
    }
    else {
        glFrustum(-10, 10, -10, 10, PNear, PFar);   // perspective view
        //gluPerspective(45, 1.0, 1, 10);
    }
}

void p4bDemo()
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);

    projection();                       // projection

    glMatrixMode(GL_MODELVIEW);         // refer to the modelview matrix
    glLoadIdentity();                   // reset the modelview matrix
    glTranslatef(tx, 0.0, tz);          // translate along z-axis

    glColor3f(1.0, 1.0, 1.0);
    drawSphere(r1, GLU_LINE);

}

void display()
{
    switch (qNo) {
    case 1:
        p4bDemo();
        break;
    case 2:
        //p4bQ1();
        break;
    case 3:
        //p4bQ1();
        break;

    default:
        p4bDemo();
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