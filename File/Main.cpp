#include "Resourec.h"
#include "Sound.h"
#include "Player.h"
#include "Interface.h"
#include "LoadingPage.h"
#include "StartPage.h"
#include "HelpPage.h"
#include "CreditPage.h"
#include "Camera.h"



LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam);

HINSTANCE StartPagehInst;

int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow) {
	HWND hwnd1;
	WNDCLASS WndClass1;
	MSG msg;
	StartPagehInst = hInstance;

	WndClass1.style = CS_HREDRAW | CS_VREDRAW;
	WndClass1.lpfnWndProc = WndProc;
	WndClass1.cbClsExtra = 0;
	WndClass1.cbWndExtra = 0;
	WndClass1.hInstance = hInstance;
	WndClass1.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass1.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass1.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass1.lpszMenuName = NULL;
	WndClass1.lpszClassName = _T("Project");

	RegisterClass(&WndClass1);

	hwnd1 = CreateWindowW(
		L"Project",
		L"Darkness Room",
		WS_OVERLAPPEDWINDOW,
		WindowPosX,
		WindowPosY,
		WindowX,
		WindowY,
		NULL,
		NULL,
		hInstance,
		NULL
	);

	ShowWindow(hwnd1, nCmdShow);

	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return (int)msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam) {
	HDC hdc, mem1dc, mem2dc, mem3dc;
	HDC Gamedc1;
	HDC Helpdc1;
	PAINTSTRUCT ps;
	HBITMAP Bitmap, OldBitmap;
	HBITMAP StartPageBit1, OldStartPageBit1, StartPageBit2, OldStartPageBit2;
	HBITMAP GamePlayBit1, OldGamePlayBit1;

	static Player* player;
	static ClickButton* Click;
	static HelpButton* Help = NULL;
	static Camera* camera;

	int Mx, My;
	static int Page = 0;
	static int LoadingCount = 0, LightCount = 0;
	static bool StartCreate = false;
	static int StartBitPade = 0, StartTextPade = 0;


	switch (iMsg)
	{
	case WM_CREATE:
		//���� ����
		SoundInit();
		//�ε� �������� �ʿ��� ��ü�� �����
		CreateLoadingPage();
		//Loading Ÿ�̸� ����
		SetTimer(hwnd, 1, 10, NULL);
		break;
	case WM_GETMINMAXINFO:
		//ȭ�� ����
		((MINMAXINFO*)lParam)->ptMinTrackSize.x = WindowX;
		((MINMAXINFO*)lParam)->ptMinTrackSize.y = WindowY;
		((MINMAXINFO*)lParam)->ptMaxTrackSize.x = WindowX;
		((MINMAXINFO*)lParam)->ptMaxTrackSize.y = WindowY;
		break;
	case WM_KEYDOWN:
		InvalidateRgn(hwnd, NULL, FALSE);
		break;
	case WM_CHAR:
		switch (wParam) {
		case 'c':
			//�ӽ� �ڵ�
			Page = 1;
			KillTimer(hwnd, 10);
			DeleteInterface();
			CreateStartPage(&Click);
			PlayStartBKSound();
			PlayLightningSound();
			SetTimer(hwnd, 3, 10, NULL);
			break;
		}
		break;
	case WM_LBUTTONUP:
		Mx = LOWORD(lParam);
		My = HIWORD(lParam);
		if (StartCreate) {
			if (Page == 1) {
				Page = ChangeStartPage(Click, My, Mx);
				if (Page == 2) {
					//Page2�� HelpPage�̴�.

					//��ư Ŭ�� ���� ���
					PlayButtonClickSound();

					//StartPage ����
					DeleteStartPage(&Click);

					//HelpPage ����
					CreateHelpPage(&Help);
				}
				else if (Page == 3) {
					//Page3�� GameLoading�������̴�.

					//��ư Ŭ�� ���� ���
					PlayButtonClickSound();

					Page = 1;

					//StartCreate���� ���̵� �ƿ� ������ ���ؼ� false�� �ٲ��ش�.
					StartCreate = false;

					//StartBitPade�� StartTextPade�� ����ȿ�� ������ Pade���� 17�� �ƴ� ��츦 ����Ͽ� 17�� ������ش�.
					StartBitPade = 17;
					StartTextPade = 17;

					//���� Ÿ�̸� ����
					KillTimer(hwnd, 3);

					//StartPage ���̵� �ƿ� Ÿ�̸� ����
					//GamePageLoading Ÿ�̸��̱⵵ ��
					SetTimer(hwnd, 4, 10, NULL);
				}
				else if (Page == 4) {
					//����
					DeleteInterface();
					exit(0);
				}
			}
			else if (Page == 2) {
				Page = ChangeHelpPage(Help, My, Mx);
				if (Page == 1) {
					PlayButtonClickSound();
					DeleteHelpPage(&Help);
					CreateStartPage(&Click);
				}
			}
		}
		InvalidateRgn(hwnd, NULL, FALSE);
		break;
	case WM_LBUTTONDOWN:
		Mx = LOWORD(lParam);
		My = HIWORD(lParam);
		if (StartCreate) {
			if (Page == 1) {
				//StartPage������ ���콺 ���� Ŭ��
				StartClickCheck(Click, My, Mx);
			}
			else if (Page == 2) {
				//HelpPage������ ���콺 ���� Ŭ��
				HelpClickCheck(Help, My, Mx);
			}
		}
		InvalidateRgn(hwnd, NULL, FALSE);
		break;
	case WM_MOUSEMOVE:
		Mx = LOWORD(lParam);
		My = HIWORD(lParam);
		if (Page == 1) {
			//StartPage������ ���콺 �̵�
			MouseUpCheck(Click, My, Mx);
		}
		else if (Page == 2) {
			//HelpPage������ ���콺 �̵�
			MouseUpCheck(Help, My, Mx);
		}
		break;
	case WM_TIMER:
		switch (wParam) {
		case 1:
			//Count�� 1�� ����
			LoadingCount++;
			if (LoadingCount == 200) {
				//Count�� 200�� �Ǹ� �ε� �Ϸ�!

				//�ε� ������ ����
				DeleteLoadingPage();

				//Loading Ÿ�̸� ����
				KillTimer(hwnd, 1);
		
				//StartPage ���̵� Ÿ�̸� ����
				SetTimer(hwnd, 2, 40, NULL);

				//StartPage����				
				Page = 1;
				CreateStartPage(&Click);
			}
			break;
		case 2:
			//StartPageȭ�� ���̵� ����
			if (StartBitPade < 17)
				StartBitPade++;
			if (StartBitPade >= 10) {
				//StartPage���� ���̵� ����
				StartTextPade++;
				if (StartTextPade == 17) {
	
					//��� BGM ���
					PlayStartBKSound();

					//StartPage���̵尡 �Ϸ�Ǿ����� StartCreate�� true�� �ٲ��ش�.
					StartCreate = true;

					//StartPage ���̵� Ÿ�̸� ����
					KillTimer(hwnd, 2);

					//���� ȿ���� ���� ������ Ÿ�̸� ����
					SetTimer(hwnd, 3, 10, NULL);
				}
			}
			break;
		case 3:
			if (LightCount == 0) 
				//���� ȿ���� ���
				PlayLightningSound();
			LightCount++;
			//õ�ռҸ� �� ���� ����
			if (LightCount == 12 || LightCount == 30) {
				StartBitPade = 13;
			}
			if (LightCount == 15 || LightCount == 33) {
				StartBitPade = 17;
			}
			//���尡 ������ ������ ����
			if (LightCount == 450) {
				LightCount = 0;
			}
			break;
		case 4:
			if (Page == 1) {
				//StartPage ȭ�� ���̵� ������ ���� Page�� 1�� ������
				//StartPage ȭ�� ���̵� �ƿ� ����
				StartBitPade--;
				StartTextPade--;

				if ((StartBitPade == 0) && (StartTextPade == 0)) {
					//StartPage ����
					DeleteStartPage(&Click);

					//LoadingCount�� 0���� �ʱ�ȭ 
					LoadingCount = 0;

					//Page�� 3���� �ʱ�ȭ
					//Page3�� �Ǵٸ� �ε� �������̴�.
					Page = 3;

					//LightCount �ʱ�ȭ
					LightCount = 0;
				}
			}
		
			//������ʹ� Page�� 3�� ����
			if (Page == 3) {
				if (LoadingCount == 0) {
					//��� ���� ����
					StartPageSoundStop();


					//LoadingPage����
					CreateLoadingPage();
				}
				LoadingCount++;

				if (LoadingCount == 100) {
					Page = 10;

					player = new Player(640, 450);

					CreateCamera(&camera);

					CreateInterface();

					PlayGameBKSound();

					//GamePageLoading Ÿ�̸� ����
					KillTimer(hwnd, 4);

					//���� Timer ����
					SetTimer(hwnd, 10, 10, NULL);
				}
			}
			break;
		case 10:
			//Start��ư�� �������� �۵��Ѵ�.
			//�÷��̾� �̵� �Լ� ȣ��
			player->MoveBasic();
			CameraMove(camera, player);
			break;

		}
		FMOD_System_Update(M_System);
		InvalidateRgn(hwnd, NULL, FALSE);
		break;
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		mem1dc = CreateCompatibleDC(hdc);
		Bitmap = CreateCompatibleBitmap(hdc, ScreenX, ScreenY);
		
		OldBitmap = (HBITMAP)SelectObject(mem1dc, Bitmap);


		//mem1dc�� ������۸����� �׷��ش�

		if (Page == 0) {
			PaintLoadingPage(mem1dc, LoadingCount);
		}
		else if (Page == 1 || Page == 2) {
			StartPageBit1 = (HBITMAP)LoadImage(NULL, _T(".\\BitMap\\StartBackGround.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
			StartPageBit2 = CreateCompatibleBitmap(hdc, ScreenX, ScreenY);

			//StartCreate�� True��� StartPage�� �ϼ��� �����̰� False��� ���̵� �ƿ�, ���̵� �ε� �̿ϼ��� �����̴�.
			if(StartCreate)
				PatBlt(mem1dc, 0, 0, ScreenX, ScreenY, WHITENESS);

			//mem2dc = ��Ʈ��
			mem2dc = CreateCompatibleDC(hdc);
			//mem3dc = �۾�
			mem3dc = CreateCompatibleDC(hdc);		

			//StartPage ����� �׸��� ���� ������۸� �۾�
			OldStartPageBit1 = (HBITMAP)SelectObject(mem2dc, StartPageBit1);
			
		
			//���ĺ��� (����ȭ)�� ���� �۾�
			BLENDFUNCTION bf1;
			bf1.AlphaFormat = AC_SRC_ALPHA;
			bf1.BlendOp = AC_SRC_OVER;
			bf1.BlendFlags = 0;
			bf1.SourceConstantAlpha = StartBitPade * 15;
			
			//���� �������� ���̵���, ���̵� �ƿ� ����
			AlphaBlend(mem1dc, 0, 0, ScreenX, ScreenY, mem2dc, 0, 0,ScreenX, ScreenY, bf1);

			SelectObject(mem2dc, OldStartPageBit1);
			DeleteObject(StartPageBit1);
			DeleteDC(mem2dc);


			//mem3dc�� ����
			OldStartPageBit2 = (HBITMAP)SelectObject(mem3dc, StartPageBit2);

			//mem1dc�� �׷����� mem3dc�� �����Ѵ�.
			BitBlt(mem3dc, 0, 0, ScreenX, ScreenY, mem1dc, 0, 0, SRCCOPY);

			//�ؽ�Ʈ�� ����� ������ ������ ������.
			SetBkMode(mem3dc, TRANSPARENT);

			//mem3dc�� Page���� Paint�Ѵ�.
			if (Page == 1) {
				PaintStartPage(mem3dc, Click);
			}
			else {
				Helpdc1 = CreateCompatibleDC(mem3dc);
				PaintHelpPage(mem3dc, Helpdc1, Help);
				DeleteObject(Helpdc1);
			}
		

			//���ĺ��� (����ȭ)�� ���� �۾�
			BLENDFUNCTION bf2;
			bf2.AlphaFormat = 0;
			bf2.BlendOp = AC_SRC_OVER;
			bf2.BlendFlags = 0;
			bf2.SourceConstantAlpha = StartTextPade * 15;

			//���� �������� ���̵���, ���̵� �ƿ� ����
			AlphaBlend(mem1dc, 0, 0, ScreenX, ScreenY, mem3dc, 0, 0, ScreenX, ScreenY, bf2);

			SelectObject(mem3dc, OldStartPageBit2);
			DeleteObject(StartPageBit2);
			DeleteDC(mem3dc);
		}
		else if (Page == 3) {
			PaintLoadingPage(mem1dc, LoadingCount * 2);
		}
		else if (Page == 10) {
			//ȭ�� �������̽� ������ ���� Gamedc1 ����
			Gamedc1 = CreateCompatibleDC(hdc);

			GamePlayBit1 = CreateCompatibleBitmap(hdc, ALLMAPX, ALLMAPY);

			OldGamePlayBit1 = (HBITMAP)SelectObject(Gamedc1, GamePlayBit1);

			//Gamedc1�� GameMap�� �׷��ش�.
			PaintBackGround(Gamedc1);
			player->PaintPlayer(Gamedc1);

			//Gamedc1�� �ִ� ���� ���� ��µǴ� mem1dc�� �˸°� �����Ѵ�.

			//�׵θ� ����
			BitBlt(mem1dc, 0, 0, 1280, 30, Gamedc1, 0, 0, SRCCOPY);
			BitBlt(mem1dc, 0, 0, 30, 700, Gamedc1, 0, 0, SRCCOPY);
			BitBlt(mem1dc, 1250, 0, 30, 700, Gamedc1, ALLMAPX - 30, 0, SRCCOPY);

			//�÷��̾� �������̽� ����
			BitBlt(mem1dc, 0, 700, ScreenX, 120, Gamedc1, 0, ALLMAPY - 120, SRCCOPY);

			//�� �� ����
			BitBlt(mem1dc, 30, 30, 1220, 670, Gamedc1, camera->GetCLeft(), camera->GetCTop(), SRCCOPY);
			//���� 30�� �÷��̾ ���� �̵��ǰ� �ٲ����


			//����
			DeleteObject(SelectObject(Gamedc1, OldGamePlayBit1));
			DeleteObject(Gamedc1);
		}
		
		//mem1dc�� hdc�� �����Ѵ�.
		BitBlt(hdc, 0, 0, ScreenX, ScreenY, mem1dc, 0, 0, SRCCOPY); 
	
		SelectObject(mem1dc, OldBitmap);
		DeleteObject(Bitmap);
		DeleteObject(mem1dc);
		EndPaint(hwnd, &ps);
		break;
	
	case WM_DESTROY:
		DeleteInterface();
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hwnd, iMsg, wParam, lParam);
}