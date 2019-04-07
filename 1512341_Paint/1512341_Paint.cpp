// 1512341_Paint.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "1512341_Paint.h"

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name
HWND toolBar;
vector<Shape *> shapeType;
vector<Shape *> shapeModel;
bool isDrawingPrivew = false;
POINT A,B;
bool checkRectangle = FALSE;
bool checkLine = TRUE;
bool checkSquare = FALSE;
bool checkEllipse = FALSE;
bool checkCircle = FALSE;
RECT rcClient;
// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);
BOOL AddButton(BYTE state, BYTE style, int iBitmap, int idCommand, LPTSTR iString, DWORD_PTR dwData);
int CaptureAnImage(HWND hWnd);

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
	LoadString(hInstance, IDC_MY1512341_PAINT, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MY1512341_PAINT));

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
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MY1512341_PAINT));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_MY1512341_PAINT);
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
      CW_USEDEFAULT,0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

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
HDC hdcMem;
HBITMAP hbmMem;
HANDLE hOld;
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;
	NMHDR* notifyMess = nullptr;
	notifyMess = (NMHDR*)lParam;
	LPNMTOOLBAR lpnmToolBar = (LPNMTOOLBAR)notifyMess;
	switch (message)
	{
		case WM_CREATE:
		{

			InitCommonControls();
			toolBar = CreateWindow(TOOLBARCLASSNAME, NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | TBSTYLE_FLAT, CW_USEDEFAULT, 0, 0, 0, hWnd, (HMENU)ID_TOOLBAR, hInst, NULL);
			SendMessage(toolBar, TB_BUTTONSTRUCTSIZE, sizeof(TBBUTTON), 0);

			//SetButtonImages();
			AddButton(TBSTATE_ENABLED, BTNS_BUTTON, 0, ID_SHAPE_LINE, _T("Line"), 0);
			AddButton(TBSTATE_ENABLED, BTNS_BUTTON, 1, ID_SHAPE_RECTANGLE, _T("*Rectangle"), 1);
			AddButton(TBSTATE_ENABLED, BTNS_BUTTON, 3, ID_SHAPE_ELLIPSE, _T("*Ellipse"), 2);
			SendMessage(toolBar, TB_AUTOSIZE, 0, (LPARAM)0);

			ShapePrototype shapePrototype(A, B);
			shapeModel.push_back(shapePrototype.make_stooge(0));
			shapeModel.push_back(shapePrototype.make_stooge(1));
			shapeModel.push_back(shapePrototype.make_stooge(2));
		}
			break;
		case WM_NOTIFY:
		{
			switch (notifyMess->code)
			{
			case NM_CLICK:
				switch (notifyMess->idFrom)
				{
				case ID_TOOLBAR:
					switch (lpnmToolBar->iItem)
					{
					case ID_SHAPE_LINE:
						checkLine = TRUE;
						checkRectangle = FALSE;
						checkSquare = FALSE;
						checkEllipse = FALSE;
						//InvalidateRect(hWnd, NULL, FALSE);
						break;
					case ID_SHAPE_RECTANGLE:
						checkRectangle = TRUE;
						checkLine = FALSE;
						checkSquare = FALSE;
						checkEllipse = FALSE;
						//InvalidateRect(hWnd, NULL, FALSE);
						break;
					case ID_SHAPE_ELLIPSE:
						checkEllipse = TRUE;
						checkRectangle = FALSE;
						checkLine = FALSE;
						checkSquare = FALSE;
						//InvalidateRect(hWnd, NULL, FALSE);
						break;
					default:
						break;
					}

				}
			}
		}
			break;
		case WM_LBUTTONDOWN:// NHẤN VÀO MÀN HÌNH
		{
			int x = GET_X_LPARAM(lParam);
			int y = GET_Y_LPARAM(lParam);
			isDrawingPrivew = true;
			A.x = x;
			A.y = y;
			for (Shape * temp : shapeModel)
				temp->setA(A);
		}
			break;
		case WM_MOUSEMOVE:
		{
			int x = GET_X_LPARAM(lParam);
			int y = GET_Y_LPARAM(lParam);
			if (isDrawingPrivew)
			{
				WCHAR buffer[1024];
				wsprintf(buffer, L"(%d,%d)", x, y);
				SetWindowText(hWnd, buffer);
				B.x = x;
				B.y = y;
				for (Shape * temp : shapeModel)
					temp->setB(B);
				InvalidateRect(hWnd, NULL, FALSE);
			}
			
		}
			break;
		case WM_LBUTTONUP: // BUÔNG RA MÀN HÌNH
		{
			/*int x = GET_X_LPARAM(lParam);
			int y = GET_Y_LPARAM(lParam);*/
			// đường thẳng
			
			if (checkLine)
				shapeType.push_back(ShapeFactory::createShape(LINE,A,B));
			// hình chữ nhật
			if (checkRectangle && !checkSquare)
				shapeType.push_back(ShapeFactory::createShape(RECTANGLE, A, B));
			// hình vuông
			if (checkRectangle && checkSquare)
			{
				 int temp = B.x - A.x;
				 if (temp < 0)
				 {
					 temp *= -1;
					 if (A.y>B.y)
						 B.y = A.y - temp;
					 else
						 B.y = A.y + temp;
				 }
				 else
				 {
					 if (B.y>A.y)
						 B.y = A.y + temp;
					 else
						 B.y = A.y - temp;
				 }
					 
				 shapeType.push_back(ShapeFactory::createShape(RECTANGLE, A, B));
			}
			// hình ellipse
			if (checkEllipse && !checkCircle)
			{
				shapeType.push_back(ShapeFactory::createShape(ELLIPSE, A, B));
			}
			// hình circle
			if (checkEllipse && checkCircle)
			{
				int temp = B.x - A.x;
				if (temp < 0)
				{
					temp *= -1;
					if (A.y>B.y)
						B.y = A.y - temp;
					else
						B.y = A.y + temp;
				}
				else
				{
					if (B.y>A.y)
						B.y = A.y + temp;
					else
						B.y = A.y - temp;
				}
				shapeType.push_back(ShapeFactory::createShape(ELLIPSE, A, B));
			}

			isDrawingPrivew = false;
			InvalidateRect(hWnd, NULL, FALSE);
		}
			break;
		case WM_COMMAND:
		{
			wmId = LOWORD(wParam);
			wmEvent = HIWORD(wParam);
			// Parse the menu selections:
			switch (wmId)
			{
			case IDM_ABOUT:
				DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
				break;
			case IDM_EXIT:
				DestroyWindow(hWnd);
				break;
			default:
				return DefWindowProc(hWnd, message, wParam, lParam);
			}
		}
			break;
		case WM_KEYDOWN:
		{
			if (wParam && MK_SHIFT && checkRectangle)
				checkSquare = TRUE;
			if (wParam && MK_SHIFT && checkEllipse)
				checkCircle = TRUE;
		}
		break;
		case WM_PAINT:
		{
			GetClientRect(hWnd, &rcClient);
			hdc = BeginPaint(hWnd, &ps);
			hdcMem = CreateCompatibleDC(hdc);
			hbmMem = CreateCompatibleBitmap(hdc, rcClient.right - rcClient.left, rcClient.bottom - rcClient.top);
			hOld = SelectObject(hdcMem, hbmMem);
			FillRect(hdcMem, &rcClient, HBRUSH(RGB(255, 255, 255)));
			SelectObject(hdcMem, GetStockObject(NULL_BRUSH));
			for (int i = 0; i < shapeType.size(); ++i)
				shapeType.at(i)->Draw(hdcMem);
			if (isDrawingPrivew && checkLine )
			{
				shapeModel.at(0)->Draw(hdcMem);
			}
			if (isDrawingPrivew && checkRectangle)
			{
				shapeModel.at(1)->Draw(hdcMem);
			}
			if (isDrawingPrivew && checkEllipse)
			{ 
				shapeModel.at(2)->Draw(hdcMem);
			}
			
			BitBlt(hdc, 0, 0, rcClient.right - rcClient.left, rcClient.bottom - rcClient.top, hdcMem, 0, 0, SRCCOPY);
			SelectObject(hdcMem, hOld);
			DeleteObject(hbmMem);
			DeleteDC(hdcMem);
			EndPaint(hWnd, &ps);
		}
			break;
		case WM_DESTROY:
			shapeType.clear();
			shapeModel.clear();
			PostQuitMessage(0);
			break;
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
BOOL AddButton(BYTE state, BYTE style, int iBitmap, int idCommand, LPTSTR iString, DWORD_PTR dwData)
{
	int iStr = SendMessage(toolBar, TB_ADDSTRING, 0, (LPARAM)iString);
	TBBUTTON button[1];

	button[0].dwData = dwData;
	button[0].fsState = state;
	button[0].iBitmap = iBitmap;


	button[0].fsStyle = style;
	button[0].idCommand = idCommand;
	button[0].iString = iStr;

	return SendMessage(toolBar, TB_ADDBUTTONS, 1, (LPARAM)&button);
}