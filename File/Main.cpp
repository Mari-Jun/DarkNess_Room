#include "Resource.hpp"
#include "Sound.hpp"
#include "Player.hpp"
#include "Interface.hpp"
#include "LoadingPage.hpp"
#include "StartPage.hpp"
#include "HelpPage.hpp"
#include "CreditPage.hpp"
#include "Camera.hpp"
#include "Enemy.hpp"



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
	static HDC hdc, mem1dc;

	//StartPage HDC
	static HDC Startdc1, Startdc2;

	//GamePlay HDC 1: �⺻, 2: ��Ʈ��, 3: �ӽ�
	static HDC Gamedc1, Gamedc2, Gamedc3, Gamedc4;

	//HelpPage HDC
	static HDC Helpdc1;

	PAINTSTRUCT ps;

	//�⺻ ������۸��� ���� ��Ʈ��
	static HBITMAP Bitmap, OldBitmap;

	//StartPage�� ���� ��Ʈ�� 1 : ��� �̹���, 2 : �ؽ�Ʈ
	static HBITMAP StartPageBit1, OldStartPageBit1, StartPageBit2, OldStartPageBit2;

	//GamePlay�������� ���� ��Ʈ��
	static HBITMAP GamePlayBit1, OldGamePlayBit1, GamePlayBit2;

	//Ŭ���� ��ü��
	static Player* player;
	static ClickButton* Click;
	static HelpButton* Help = NULL;
	static Camera* camera;
	static LineEnemy* Lenemy[80];
	//static LineEnemy* LEnemy;
	//static WideEnemy* WEnemy;
	//static BombEnemy* BEnemy;
	//static RectEnemy* REnemy;

	//���콺 ��ǥ
	int Mx, My;

	//���� ������
	static int Page = 0;

	//�ε� ������ ������ ���Ǵ� ������
	static int LoadingCount = 0, LightCount = 0;

	//StartPage�� ������ �˷��ִ� ����
	static bool StartCreate = false;

	//StartPage ���̵� ������ �ʿ��� ����
	static int StartBitPade = 0, StartTextPade = 0;

	//GamePage���۽� ȿ�� ������ ���� �ʿ��� ����
	static int GamePageLoading = 0;


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

				StartPageBit1 = (HBITMAP)LoadImage(NULL, _T(".\\BitMap\\StartBackGround.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
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
				if(LoadingCount<100)
					LoadingCount++;

				if (LoadingCount == 100) {
					//���� ȭ�� �������� 10���� Page�� �����Ѵ�.
					Page = 10;

					//�������̽��� �����Ѵ�.
					CreateInterface();

					//���� BGM�� �����Ѵ�.
					PlayGameBKSound();

					//�÷��̾� ����
					CreatePlayer(&player);

					//ī�޶� ����
					CreateCamera(&camera);

					//�� ����
					CreateLEnemy(Lenemy);
					
				}
			}

			if (Page == 10) {
				GamePageLoading += 5;

				if (GamePageLoading == ScreenY) {
					//GamePageLoading�� ScreeeY(820) �ȴٸ� ��� �ε��� ������ �̹Ƿ� 
					//GamePageLoadingŸ�̸� ����
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
			camera->CameraMove(player);
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
			
			StartPageBit2 = CreateCompatibleBitmap(hdc, ScreenX, ScreenY);

			//StartCreate�� True��� StartPage�� �ϼ��� �����̰� False��� ���̵� �ƿ�, ���̵� �ε� �̿ϼ��� �����̴�.
			if(StartCreate)
				PatBlt(mem1dc, 0, 0, ScreenX, ScreenY, WHITENESS);

			//Startdc1 = ��Ʈ��
			Startdc1 = CreateCompatibleDC(hdc);
			//Startdc2 = �۾�
			Startdc2 = CreateCompatibleDC(hdc);		

			//StartPage ����� �׸��� ���� ������۸� �۾�
			OldStartPageBit1 = (HBITMAP)SelectObject(Startdc1, StartPageBit1);
			
		
			//���ĺ��� (����ȭ)�� ���� �۾�
			BLENDFUNCTION bf1;
			bf1.AlphaFormat = AC_SRC_ALPHA;
			bf1.BlendOp = AC_SRC_OVER;
			bf1.BlendFlags = 0;
			bf1.SourceConstantAlpha = StartBitPade * 15;
			
			//���� �������� ���̵���, ���̵� �ƿ� ����
			AlphaBlend(mem1dc, 0, 0, ScreenX, ScreenY, Startdc1, 0, 0,ScreenX, ScreenY, bf1);

			SelectObject(Startdc1, OldStartPageBit1);
			//DeleteObject(StartPageBit1);
			DeleteDC(Startdc1);


			//Startdc2�� ����
			OldStartPageBit2 = (HBITMAP)SelectObject(Startdc2, StartPageBit2);

			//mem1dc�� �׷����� Startdc2�� �����Ѵ�.
			BitBlt(Startdc2, 0, 0, ScreenX, ScreenY, mem1dc, 0, 0, SRCCOPY);

			//�ؽ�Ʈ�� ����� ������ ������ ������.
			SetBkMode(Startdc2, TRANSPARENT);

			//Startdc2�� Page���� Paint�Ѵ�.
			if (Page == 1) {
				PaintStartPage(Startdc2, Click);
			}
			else {
				Helpdc1 = CreateCompatibleDC(Startdc2);
				PaintHelpPage(Startdc2, Helpdc1, Help);
				DeleteObject(Helpdc1);
			}
		

			//���ĺ��� (����ȭ)�� ���� �۾�
			BLENDFUNCTION bf2;
			bf2.AlphaFormat = 0;
			bf2.BlendOp = AC_SRC_OVER;
			bf2.BlendFlags = 0;
			bf2.SourceConstantAlpha = StartTextPade * 15;

			//���� �������� ���̵���, ���̵� �ƿ� ����
			AlphaBlend(mem1dc, 0, 0, ScreenX, ScreenY, Startdc2, 0, 0, ScreenX, ScreenY, bf2);

			SelectObject(Startdc2, OldStartPageBit2);
			DeleteObject(StartPageBit2);
			DeleteDC(Startdc2);
		}
		else if (Page == 3) {
			PaintLoadingPage(mem1dc, LoadingCount * 2);
		}
		else if (Page == 10) {
			//ȭ�� �������̽� ������ ���� Gamedc1 ����
			Gamedc1 = CreateCompatibleDC(hdc);
			Gamedc2 = CreateCompatibleDC(hdc);		

			GamePlayBit1 = CreateCompatibleBitmap(hdc, ALLMAPX, ALLMAPY);

			OldGamePlayBit1 = (HBITMAP)SelectObject(Gamedc1, GamePlayBit1);
	
			//Gamedc1�� GameMap�� �׷��ش�.
			PaintBackGround(Gamedc1, Gamedc2);

			//�÷��̾� ������ Gamedc1�� �׷��ش�.
			player->PaintPlayer(Gamedc1);
			player->PaintPlayerIF(Gamedc1);

			//���ʹ̵��� Gamedc1�� �׷��ش�.
			for(int L=0; L<20; L++)
				Lenemy[L]->PaintEnmey(Gamedc1);
			

			//Gamedc1�� �ִ� ���� ���� ��µǴ� mem1dc�� �˸°� �����Ѵ�.

			//���� �׵θ� ����
			if(GamePageLoading<30)
				//30�̸������� GamePageLoading�� ũ�� ��ŭ �����Ѵ�.
				BitBlt(mem1dc, 0, 0, 1280, GamePageLoading, Gamedc1, 0, 0, SRCCOPY);
			else
				//30�̻��� �Ǹ� �� �ε��� ��� ������ �׳� 30�� ũ�⸸ŭ �����Ѵ�.
				BitBlt(mem1dc, 0, 0, 1280, 30, Gamedc1, 0, 0, SRCCOPY);

			//���� / ������ �׵θ� ����
			if (GamePageLoading < 700) {
				//700�̸������� GamePageLoading�� ũ�� ��ŭ �����Ѵ�.
				BitBlt(mem1dc, 0, 0, 30, GamePageLoading, Gamedc1, 0, 0, SRCCOPY);
				BitBlt(mem1dc, 1250, 0, 30, GamePageLoading, Gamedc1, ALLMAPX - 30, 0, SRCCOPY);
			}
			else {
				//700�̻��� �Ǹ� �� �ε��� ��� ������ �׳� 700�� ũ�⸸ŭ �����Ѵ�.
				BitBlt(mem1dc, 0, 0, 30, 700, Gamedc1, 0, 0, SRCCOPY);
				BitBlt(mem1dc, 1250, 0, 30, 700, Gamedc1, ALLMAPX - 30, 0, SRCCOPY);
			}
				
			if (GamePageLoading >= 700) {
				//700�̻��� �Ǿ�߸� ���縦 �����Ѵ�.
				//�÷��̾� �������̽� ����
				BitBlt(mem1dc, 0, 700, ScreenX, GamePageLoading - 700, Gamedc1, 0, ALLMAPY - 120, SRCCOPY);

				//�������̽� ������ �׵θ� ����
				BitBlt(mem1dc, ScreenX - 30, 700, 30, GamePageLoading - 700, Gamedc1, ALLMAPX - 30, ALLMAPY - 120, SRCCOPY);
			}
				
			
			if (GamePageLoading >= 30) {
				//30�̻��� �Ǿ�߸� ���縦 �����Ѵ�.
				//�� �� ����
				if (GamePageLoading < 700)
					//700�̸������� GamePageLoading�� ũ�� ��ŭ �����Ѵ�.
					BitBlt(mem1dc, 30, 30, 1220, GamePageLoading - 30, Gamedc1, camera->GetCLeft(), camera->GetCTop(), SRCCOPY);
				else
					//700�̻��� �Ǹ� �� �ε��� ��� ������ �׳� 670�� ũ�⸸ŭ �����Ѵ�.
					BitBlt(mem1dc, 30, 30, 1220, 670, Gamedc1, camera->GetCLeft(), camera->GetCTop(), SRCCOPY);
			}

			//����
			DeleteObject(SelectObject(Gamedc1, OldGamePlayBit1));
			DeleteObject(Gamedc1);
			DeleteObject(Gamedc2);
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