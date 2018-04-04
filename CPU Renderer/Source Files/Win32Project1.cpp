// Win32Project1.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "Win32Project1.h"
#include "Vertex.h"
#include "Vector3D.h"
#include "Matrix4X4.h"
#include "Polygon.h"
#include <vector>
#include <math.h>
#include <commdlg.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name

//Angles for rotation of model and zoom
float angleX = 100.0, angleY = 90.0, angleZ = 34.0;
float zoom = 7;

CHOOSECOLOR cc;                 // common dialog box structure 
static COLORREF acrCustClr[16]; // array of custom colors 
HBRUSH hbrush;                  // brush handle
HPEN hpen;						// pen handle
static DWORD rgbCurrent = 429584;        // initial color selection
static DWORD vertColour;	//
int colourChoice;

HDC backbuffDC;
HBITMAP backbuffer;
RECT client;

//Open files selection variables 
OPENFILENAME ofn;
char szFile[256];
std::wstring filename;
//std::string filename;


// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);


vector<Vertex> listVertices;
vector<Polygonface> polyFace;

Vector3D			Model2WorldTrans(Vector3D v, float pX, float pY, float pZ);
Vector3D			World2ViewTrans(Vector3D v);
Vector3D			Projection(Vector3D v);
Vector3D			GraphicsPipe(Vector3D v);
void				Readfile();
void				OnPaint(HDC hdc);
void				DrawPolygonface(HDC hdc, Polygonface p);
void				ColourPicker(CHOOSECOLOR cc, HWND hWnd, HDC hdc, int colourChoice);


int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPTSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

 	// TODO: Place code here.
	MSG msg;
	HACCEL hAccelTable;

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_WIN32PROJECT1, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WIN32PROJECT1));

	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
//ATOM 
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WIN32PROJECT1));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_WIN32PROJECT1);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;

   hInst = hInstance; // Store instance handle in our global variable

   hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window
//  WM_DESTROY	- post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message)
	{
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{

		// Polygon line colour picker
		case ID_OBJCOLOUR_CHOOSECOLOUR:
			ColourPicker(cc, hWnd, backbuffDC, 1);
			RedrawWindow(hWnd, NULL, NULL, RDW_INVALIDATE);
			break;

		// Polygon colour picker
		case ID_POLY_COL_PICK:
			ColourPicker(cc, hWnd, backbuffDC, 2);
			RedrawWindow(hWnd, NULL, NULL, RDW_INVALIDATE);
			break;
		
		// Open object file
		case ID_FILE_OPENOBJFILE:
			ZeroMemory(&ofn, sizeof(ofn));
			ofn.lStructSize = sizeof(ofn);
			ofn.hwndOwner = NULL;
			ofn.lpstrFile = LPWSTR(szFile);
			ofn.lpstrFile[0] = '\0';
			ofn.nMaxFile = sizeof(szFile);
			ofn.lpstrFilter = TEXT("All Files (*.*)\0*.*\0");
			ofn.nFilterIndex = 1;
			ofn.lpstrFileTitle = NULL;
			ofn.nMaxFileTitle = 0;
			ofn.lpstrInitialDir = NULL;
			ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

			GetOpenFileName(&ofn);
			MessageBox(NULL, ofn.lpstrFile, TEXT("File Name"), MB_OK);
			filename.assign(ofn.lpstrFile);

			Readfile();

			RedrawWindow(hWnd, NULL, NULL, RDW_INVALIDATE);

			break;

		// About box
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;

		// Exit and destory window
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		
		// Default returns the window with the handle and messages. 
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
	break;

	case WM_PAINT:
		{
			hdc = BeginPaint(hWnd, &ps);
			// TODO: Add any drawing code here...

			GetClientRect(hWnd, &client);

			// Set up the back buffer and bitmap
			backbuffDC = CreateCompatibleDC(hdc);
			backbuffer = CreateCompatibleBitmap(hdc, client.right, client.bottom);

			// Set the brush and buffer
			HGDIOBJ original = NULL;
			original = SelectObject(backbuffDC, backbuffer);
			SetDCBrushColor(backbuffDC, RGB(0, 255, 255));
			Rectangle(backbuffDC, client.left, client.top, client.right, client.bottom);

			//draws all our major stuff (shape list)
			OnPaint(backbuffDC);

			//copy to front buffer
			BitBlt(hdc, client.top, client.left, client.right, client.bottom, backbuffDC, client.top, client.left, SRCCOPY);

			//cleanup
			DeleteDC(backbuffDC);
			DeleteObject(backbuffer);
			ReleaseDC(hWnd, hdc);
			EndPaint(hWnd, &ps);
			break;

		}
	// Controls
	case WM_KEYDOWN:
	{
		switch (wParam)
		{
			case 'W':
				angleX += 5;
				break;
			case 'Q':
				angleX -= 5;
				break; 
			case 'E':
				angleY += 5;
				break; 
			case 'D':
				angleY -= 5;
				break; 
			case 'S':
				angleZ += 5;
				break;
			case 'A':
				angleZ -= 5;
				break;
			case 'P':
				zoom++;
				break;
			case 'O':
				zoom--;
				break;
			case 'R':
				angleX = 0;
				angleY = 0;
				angleZ = 0;
				zoom = 7;
			default:
				break;
						
		}

		// Redraw window after movement	   
		RedrawWindow(hWnd, NULL, NULL, RDW_INVALIDATE);
	}

	break;
		
	
	// Destroy window if exited
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	
	//Return window as default
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}

// Function for the colour picker. 
void ColourPicker(CHOOSECOLOR cc, HWND hWnd, HDC hdc, int colourChoice)
{
	// Initialize CHOOSECOLOR 
	ZeroMemory(&cc, sizeof(cc));
	cc.lStructSize = sizeof(cc);
	cc.hwndOwner = hWnd;
	cc.lpCustColors = (LPDWORD)acrCustClr;
	cc.rgbResult = rgbCurrent;
	cc.Flags = CC_FULLOPEN | CC_RGBINIT;
	
	//
	if (ChooseColor(&cc) == TRUE)
	{
		if (colourChoice == 1)
		{
			hbrush = CreateSolidBrush(cc.rgbResult);
			rgbCurrent = cc.rgbResult;
		}
		if (colourChoice == 2)
		{
			hpen = CreatePen(PS_SOLID, 1, cc.rgbResult);
			vertColour = cc.rgbResult;
		}
	}
}

// On paint function colours in polygon faces. 
void OnPaint(HDC hdc)
{
	for (size_t i = 0; i < polyFace.size(); i++)
	{
		DrawPolygonface(hdc, polyFace[i]);
	}
}

// Opens and reads file
void Readfile()
{
	// Clears polygon face and vertices
	polyFace.clear();
	listVertices.clear();

	// Reset angles
	angleX = 0;
	angleY = 0;
	angleZ = 0;

	// Create a buffer
	char buffer[1000];
	char op;
	float x, y, z;

	Vector3D filevector;
	Vertex tempVert;
	Polygonface tempPoly;
	std::ifstream infile(filename, std::ifstream::in);
	if (infile.is_open())
	{

		while (infile.good())
		{
			infile.getline(buffer, 100);
			std::istringstream readline(buffer, std::istringstream::in);
			readline >> op >> x >> y >> z;
			if (op == 'v')
			{
				filevector.SetX(x); 
				filevector.SetY(y); 
				filevector.SetZ(z); 
				filevector.SetW(1);
				tempVert.SetPosition(filevector);
				listVertices.push_back(tempVert);
			}
			else if (op == 'f')
			{
				tempPoly.SetPointA(listVertices[x - 1]);
				tempPoly.SetPointB(listVertices[y - 1]);
				tempPoly.SetPointC(listVertices[z - 1]);
				polyFace.push_back(tempPoly);
			}
		}
	}
	else
	{
		MessageBox(NULL, TEXT("Didn't work"), TEXT("File must be in correct format"), MB_OK);
	}

}

Vector3D Model2WorldTrans(Vector3D v, float pX, float pY, float pZ)
{
	float pi = 3.14159265f;
	//x rotation
	Matrix4X4 xRotate(
		1, 0, 0, 0,
		0, (float)cos(pX*pi / 180), (float)-sin(pX*pi / 180), 0,
		0, (float)sin(pX*pi / 180), (float)cos(pX*pi / 180), 0,
		0, 0, 0, 1);

	//y rotation
	Matrix4X4 yRotate(
		(float)cos(pY*pi / 180), 0, (float)sin(pY*pi / 180), 0,
		0, 1, 0, 0,
		(float)-sin(pY*pi / 180), 1, (float)cos(pY*pi / 180), 0,
		0, 0, 0, 1);

	//z rotation
	Matrix4X4 zRotate(
		(float)cos(pZ*pi / 180), (float)-sin(pZ*pi / 180), 0, 0,
		(float)sin(pZ*pi / 180), (float)cos(pZ*pi / 180), 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1);


	v = xRotate * v;
	v = yRotate * v;
	v = zRotate * v;
	return v;
}
Vector3D World2ViewTrans(Vector3D v)
{
	//camera
	Vector3D cameraEye(0.0, 0.0, 0.0, 1);
	Vector3D cameraAt(0.0, 0.0, -1.0, 1);

	//right, up and view
	Vector3D view(cameraAt - cameraEye);
	Vector3D temp(1, 0, 0, 1);
	Vector3D up(temp.CrossProduct(view));
	Vector3D right(view.CrossProduct(up));

	//minus eye
	Matrix4X4 inverseEye(
		1.0, 0.0, 0.0, -cameraEye.GetX(),
		0.0, 1.0, 0.0, -cameraEye.GetY(),
		0.0, 0.0, 1.0, -cameraEye.GetZ(),
		0.0, 0.0, 0.0, 1.0);

	//view matrix
	Matrix4X4 viewMatrix(
		right.GetX(), right.GetY(), right.GetZ(), 0,
		up.GetX(), up.GetY(), up.GetZ(), 0,
		view.GetX(), view.GetY(), view.GetZ(), 0,
		0, 0, 0, 1);

	Matrix4X4 InverseView = viewMatrix.Inverse(viewMatrix);

	v = inverseEye * v;
	v = InverseView * v;
	return v;
}
Vector3D Projection(Vector3D v)
{
	//scalingMatrix x     y    z    w
	Matrix4X4 scaling(
		zoom, 0.0, 0.0, 0.0,
		0.0, zoom, 0.0, 0.0,
		0.0, 0.0, 0.0, 0.0,
		0.0, 0.0, 0.0, 1.0);
	//orthographicMatrix
	Matrix4X4 orthoProject(
		1.0, 0.0, 0.0, 0.0,
		0.0, 1.0, 0.0, 0.0,
		0.0, 0.0, 0.0, 0.0,
		0.0, 0.0, 0.0, 1.0);

	v = scaling * v;
	v = orthoProject * v;
	return v;
}
Vector3D GraphicsPipe(Vector3D v)
{
	v = Model2WorldTrans(v, angleX, angleY, angleZ);
	v = World2ViewTrans(v);
	v = Projection(v);
	return v;
}

void DrawPolygonface(HDC hdc, Polygonface p)
{
	POINT tempPoints[3];

	Vector3D filevector;
	filevector = GraphicsPipe(p.GetPointA().GetPosition());
	tempPoints[0].x = filevector.GetX() + (client.right / 2); 
	tempPoints[0].y = -filevector.GetY() + (client.bottom / 2);

	filevector = GraphicsPipe(p.GetPointB().GetPosition());
	tempPoints[1].x = filevector.GetX() + (client.right / 2); 
	tempPoints[1].y = -filevector.GetY() + (client.bottom / 2);

	filevector = GraphicsPipe(p.GetPointC().GetPosition());
	tempPoints[2].x = filevector.GetX() + (client.right / 2); 
	tempPoints[2].y = -filevector.GetY() + (client.bottom / 2);

	HPEN hPen = CreatePen(PS_SOLID, 1, vertColour);
	HGDIOBJ oldPen = SelectObject(hdc, hPen);
	HGDIOBJ brush = CreateSolidBrush(rgbCurrent);
	SelectObject(hdc, brush);
	Polygon(hdc, tempPoints, 3);
	SelectObject(hdc, oldPen);
	DeleteObject(hPen);
	DeleteObject(brush);
}