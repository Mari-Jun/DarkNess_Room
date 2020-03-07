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

	//GamePlay HDC 1: �⺻, 2: ��Ʈ�� 3: ����
	static HDC Gamedc1, Gamedc2, Gamedc3;

	//HelpPage HDC
	static HDC Helpdc1;

	//PlayerDC
	static HDC Playerdc;

	PAINTSTRUCT ps;

	//�⺻ ������۸��� ���� ��Ʈ��
	static HBITMAP Bitmap, OldBitmap;

	//StartPage�� ���� ��Ʈ�� 1 : ��� �̹���, 2 : �ؽ�Ʈ
	static HBITMAP MainPageBit1, MainPageBit2;

	//GamePlay�������� ���� ��Ʈ��
	static HBITMAP GamePlayBit1, OldGamePlayBit1, GamePlayBit2, OldGamePlayBit2 ,GamePlayBit3, OldGamePlayBit3;

	//Ŭ���� ��ü��
	static Player* player;
	static MainPage* Main;
	static HelpPage* Help = NULL;
	static Camera* camera;
	static Interface* Inter;
	static LineEnemy* LEnemy[LENEMYMAX];
	static WideEnemy* WEnemy;
	static BombEnemy* BEnemy[BENEMYMAX];
	static AirEnemy* AEnemy[AENEMYMAX];

	//���콺 ��ǥ
	int Mx, My;

	//���� ������
	static int Page = 0;

	//�ε� ������ ������ ���Ǵ� ������
	static int LoadingCount = 0, LightCount = 0;

	//MainPage�� ������ �˷��ִ� ����
	static bool MainCreate = false;

	//StartPage ���̵� ������ �ʿ��� ����
	static int MainBitPade = 0, MainTextPade = 0;

	//GamePage���۽� ȿ�� ������ ���� �ʿ��� ����
	static int GamePageLoading = 0;

	//GameTime�� ��Ÿ���� ����
	static int PlayerTime = 0, EnemyTime = 0;

	//���� ���ʹ̺� �߻� �� ��
	static int LShot = 0, BShot = 0, AShot = 0;

	//�ִ� ���ʹ̺� �߻� ��
	static int LMaxShot = 0, BMaxShot = 0, AMaxShot = 0;


	switch (iMsg)
	{
	case WM_CREATE:
		//���� ����
		SoundInit();
		//�ε� �������� �ʿ��� ��ü�� �����
		CreateLoadingPage();

		//�⺻ HDC�� BITAMP ����
		hdc = GetDC(hwnd);
		mem1dc = CreateCompatibleDC(hdc);
		ReleaseDC(hwnd, hdc);

		//Loading Ÿ�̸� ����
		SetTimer(hwnd, 1, 10, NULL);
		//������ ����
		srand(unsigned int(time(NULL)));		
		break;
	case WM_GETMINMAXINFO:
		//ȭ�� ����
		((MINMAXINFO*)lParam)->ptMinTrackSize.x = WindowX;
		((MINMAXINFO*)lParam)->ptMinTrackSize.y = WindowY;
		((MINMAXINFO*)lParam)->ptMaxTrackSize.x = WindowX;
		((MINMAXINFO*)lParam)->ptMaxTrackSize.y = WindowY;
		break;
	case WM_CHAR:
		if (Page == 10) {
			player->UseSkill(wParam);
		}
		break;
	case WM_LBUTTONUP:
		Mx = LOWORD(lParam);
		My = HIWORD(lParam);
		if (MainCreate) {
			if (Page == 1) {
				Page = Main->ChangeMainPage(My, Mx);
				if (Page == 2) {
					//Page2�� HelpPage�̴�.

					//��ư Ŭ�� ���� ���
					PlayButtonClickSound();

					//MainPage ����
					DeleteMainPage(&Main);

					//HelpPage ����
					CreateHelpPage(&Help);
				}
				else if (Page == 3) {
					//Page3�� GameLoading�������̴�.

					//��ư Ŭ�� ���� ���
					PlayButtonClickSound();

					Page = 1;

					//MainCreate���� ���̵� �ƿ� ������ ���ؼ� false�� �ٲ��ش�.
					MainCreate = false;

					//MainBitPade�� MainTextPade�� ����ȿ�� ������ Pade���� 17�� �ƴ� ��츦 ����Ͽ� 17�� ������ش�.
					MainBitPade = 17;
					MainTextPade = 17;

					//���� Ÿ�̸� ����
					KillTimer(hwnd, 3);

					//MainPage ���̵� �ƿ� Ÿ�̸� ����
					//GamePageLoading Ÿ�̸��̱⵵ ��
					SetTimer(hwnd, 4, 10, NULL);
				}
				else if (Page == 4) {
					//����
					DeleteMainPage(&Main);
					exit(0);
				}
			}
			else if (Page == 2) {
				Page = Help->ChangeHelpPage(My, Mx);
				if (Page == 1) {
					PlayButtonClickSound();
					DeleteHelpPage(&Help);
					CreateMainPage(&Main);
				}
			}
		}
		break;
	case WM_LBUTTONDOWN:
		Mx = LOWORD(lParam);
		My = HIWORD(lParam);
		if (MainCreate) {
			if (Page == 1) {
				//MainPage������ ���콺 ���� Ŭ��
				Main->MainClickCheck(My, Mx);
			}
			else if (Page == 2) {
				//HelpPage������ ���콺 ���� Ŭ��
				Help->HelpClickCheck(My, Mx);
			}
		}
		break;
	case WM_MOUSEMOVE:
		Mx = LOWORD(lParam);
		My = HIWORD(lParam);
		if (Page == 1) {
			//MainPage������ ���콺 �̵�
			Main->MouseUpCheck(My, Mx);
		}
		else if (Page == 2) {
			//HelpPage������ ���콺 �̵�
			Help->MouseUpCheck(My, Mx);
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
		
				//MainPage ���̵� Ÿ�̸� ����
				SetTimer(hwnd, 2, 40, NULL);

				//MainPage����				
				Page = 1;
				CreateMainPage(&Main);

				//MainPage���� �ʿ��� HDC, BITMAP�� ����
				hdc = GetDC(hwnd);

				//MainPageBit1 = ��Ʈ��
				MainPageBit1 = (HBITMAP)LoadImage(NULL, _T(".\\BitMap\\StartBackGround.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

				//MainPageBit2 = �� �̿��� �͵�
				MainPageBit2 = CreateCompatibleBitmap(hdc, ScreenX, ScreenY);

				//Startdc1 = ��Ʈ��
				Startdc1 = CreateCompatibleDC(hdc);
				//Startdc2 = �۾�
				Startdc2 = CreateCompatibleDC(hdc);

				//HelpPage���� �ʿ��� HDC, BITMAP�� ����
				Helpdc1 = CreateCompatibleDC(hdc);

				SelectObject(Startdc1, MainPageBit1);
				SelectObject(Startdc2, MainPageBit2);

				//�ؽ�Ʈ�� ����� ������ ������ ������.
				SetBkMode(Startdc2, TRANSPARENT);

				ReleaseDC(hwnd, hdc);
			}
			break;
		case 2:
			//StartPageȭ�� ���̵� ����
			if (MainBitPade < 17)
				MainBitPade++;
			if (MainBitPade >= 10) {
				//StartPage���� ���̵� ����
				MainTextPade++;
				if (MainTextPade == 17) {
	
					//��� BGM ���
					PlayMainBKSound();

					//StartPage���̵尡 �Ϸ�Ǿ����� StartCreate�� true�� �ٲ��ش�.
					MainCreate = true;

					//MainPage ���̵� Ÿ�̸� ����
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
				MainBitPade = 13;
			}
			if (LightCount == 15 || LightCount == 33) {
				MainBitPade = 17;
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
				MainBitPade--;
				MainTextPade--;

				if ((MainBitPade == 0) && (MainTextPade == 0)) {
					//MainPage ����
					DeleteMainPage(&Main);

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
					MainPageSoundStop();

					//LoadingPage����
					CreateLoadingPage();

					//MainPage���� ���� HDC, BITMAP�� ����
					DeleteObject(MainPageBit1);
					DeleteObject(MainPageBit2);
					DeleteDC(Startdc1);
					DeleteDC(Startdc2);
					DeleteDC(Helpdc1);
				}
				if(LoadingCount<100)
					LoadingCount++;

				if (LoadingCount == 100) {
					//���� ȭ�� �������� 10���� Page�� �����Ѵ�.
					Page = 10;

					//�������̽��� �����Ѵ�.
					CreateInterface(&Inter);

					//���� BGM�� �����Ѵ�.
					PlayGameBKSound();

					//�÷��̾� ����
					CreatePlayer(&player);

					//ī�޶� ����
					CreateCamera(&camera);

					//�� ����
					CreateLEnemy(LEnemy);
					CreateWEnemy(&WEnemy);
					CreateBEnemy(BEnemy);
					CreateAEnemy(AEnemy);

					//GamePage�� ���� HDC, BITMAP�� ����
					
					hdc = GetDC(hwnd);

					Gamedc1 = CreateCompatibleDC(hdc);
					Gamedc2 = CreateCompatibleDC(hdc);
					Gamedc3 = CreateCompatibleDC(hdc);

					//�ڿ� ��� ��Ʈ���� �ֱ� ������ �����ϴ�.
					//���ٸ� PAINT�� �־���� �Ѵ�.
					GamePlayBit1 = CreateCompatibleBitmap(hdc, ALLMAPX, ALLMAPY);
					GamePlayBit2 = CreateCompatibleBitmap(hdc, ALLMAPX, ALLMAPY);
					GamePlayBit3 = CreateCompatibleBitmap(hdc, ALLMAPX, ALLMAPY);

					SelectObject(Gamedc1, GamePlayBit1);
					SelectObject(Gamedc2, GamePlayBit2);
					SelectObject(Gamedc3, GamePlayBit3);

					ReleaseDC(hwnd, hdc);
				}
			}

			if (Page == 10) {
				GamePageLoading += 5;

				if (GamePageLoading == ScreenY) {
					//GamePageLoading�� ScreeeY(820) �ȴٸ� ��� �ε��� ������ �̹Ƿ� 
					//GamePageLoadingŸ�̸� ����
					KillTimer(hwnd, 4);
					//���� Timer ����
					SetTimer(hwnd, 9, 10, NULL);
					SetTimer(hwnd, 10, 10, NULL);
				}
			}
			break;
		case 9:
			//�÷��̾� Ÿ�̸�

			//�÷��̾� �̵� �Լ� ȣ��
			player->MoveBasic();
			//ī�޶� �̵� �Լ� ȣ��
			camera->CameraMove(player);

			PlayerTime++;
			if (PlayerTime == 7) {
				//���ӽð� ���� 0.1��
				//0.1�ʸ��� Loop�� �� �� �ְ� 0���� �缳��.

				PlayerTime = 0;

				//�÷��̾ ���� ���ݿ� �¾Ҵ��� Ȯ���Ѵ�.
				player->CheckHitCheck();

				//�÷��̾� ��ų ��ٿ��� ������Ʈ�Ѵ�.
				player->SkillCoolDown(hwnd);
			}
			break;
		case 10:
			//���ʹ� Ÿ�̸�

			//������ ���� ���� ������ �����Դϴ�!
			switch (Inter->GetLevel()) {
			case 1:
				//������ �ִ� 20��
				LMaxShot = 20;
				BMaxShot = 5;
				AMaxShot = 2;
				break;
			}

			EnemyTime++;
			if (EnemyTime == 7) {
				//���ӽð� ���� 0.1��
				//0.1�ʸ��� Loop�� �� �� �ְ� 0���� �缳��.
				EnemyTime = 0;

				//���ʹ� ����

				//LineEnmey
				for (LShot; LShot < LMaxShot; LShot++) {
					SelectLShot(LEnemy, 1);
				}
				LShot = ChangeLInfo(LEnemy, player);

				//WideEnemy
				ChangeWInfo(WEnemy, player, 40);

				//BombEnemy;
				for (BShot; BShot < BMaxShot; BShot++) {
					SelectBShot(BEnemy, 10);
				}
				BShot = ChangeBInfo(BEnemy, player);

				//AirEnemy
				for (AShot; AShot < AMaxShot; AShot++) {
					SelectAShot(AEnemy, player, 20);
				}
				AShot = ChangeAInfo(AEnemy, player);
			}
			break;
		}
		InvalidateRgn(hwnd, NULL, FALSE);
		FMOD_System_Update(M_System);
		break;
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		Bitmap = CreateCompatibleBitmap(hdc, ScreenX, ScreenY);
		OldBitmap = (HBITMAP)SelectObject(mem1dc, Bitmap);

		//mem1dc�� ������۸����� �׷��ش�

		if (Page == 0) {
			PaintLoadingPage(mem1dc, LoadingCount);
		}
		else if (Page == 1 || Page == 2) {
			
			//MainCreate�� True��� MainPage�� �ϼ��� �����̰� False��� ���̵� �ƿ�, ���̵� �ε� �̿ϼ��� �����̴�.
			if(MainCreate)
				PatBlt(mem1dc, 0, 0, ScreenX, ScreenY, WHITENESS);

		
			//���ĺ��� (����ȭ)�� ���� �۾�
			BLENDFUNCTION bf1;
			bf1.AlphaFormat = AC_SRC_ALPHA;
			bf1.BlendOp = AC_SRC_OVER;
			bf1.BlendFlags = 0;
			bf1.SourceConstantAlpha = MainBitPade * 15;
			
			//���� �������� ���̵���, ���̵� �ƿ� ����
			AlphaBlend(mem1dc, 0, 0, ScreenX, ScreenY, Startdc1, 0, 0,ScreenX, ScreenY, bf1);

			//mem1dc�� �׷����� Startdc2�� �����Ѵ�.
			BitBlt(Startdc2, 0, 0, ScreenX, ScreenY, mem1dc, 0, 0, SRCCOPY);

			//Startdc2�� Page���� Paint�Ѵ�.
			if (Page == 1) {
				Main->PaintMainPage(Startdc2);
			}
			else {
				Help->PaintHelpPage(Startdc2, Helpdc1);
			}

			//���ĺ��� (����ȭ)�� ���� �۾�
			BLENDFUNCTION bf2;
			bf2.AlphaFormat = 0;
			bf2.BlendOp = AC_SRC_OVER;
			bf2.BlendFlags = 0;
			bf2.SourceConstantAlpha = MainTextPade * 15;

			//���� �������� ���̵���, ���̵� �ƿ� ����
			AlphaBlend(mem1dc, 0, 0, ScreenX, ScreenY, Startdc2, 0, 0, ScreenX, ScreenY, bf2);
		}
		else if (Page == 3) {
			PaintLoadingPage(mem1dc, LoadingCount * 2);
		}
		else if (Page == 10) {
			
			//Gamedc1�� GameMap�� �׷��ش�.
			Inter->PaintBackGround(Gamedc1, Gamedc2);			

			//�߻�ü���� Gamedc1�� �׷��ش�.
			for (int L = 0; L < LENEMYMAX; L++)
				LEnemy[L]->PaintShot(Gamedc1, Gamedc2, Gamedc3);
			WEnemy->PaintShot(Gamedc1, Gamedc2, Gamedc3);
			for (int B = 0; B < BENEMYMAX; B++)
				BEnemy[B]->PaintShot(Gamedc1, Gamedc2, Gamedc3);
			for (int A = 0; A < AENEMYMAX; A++)
				AEnemy[A]->PaintShot(Gamedc1, Gamedc2, Gamedc3);

			//���ʹ̵��� Gamedc1�� �׷��ش�.
			for (int L = 0; L < LENEMYMAX; L++)
				LEnemy[L]->PaintEnmey(Gamedc1, Gamedc2);
			WEnemy->PaintEnmey(Gamedc1, Gamedc2);
			for (int B = 0; B < BENEMYMAX; B++)
				BEnemy[B]->PaintEnmey(Gamedc1, Gamedc2);
			for (int A = 0; A < AENEMYMAX; A++)
				AEnemy[A]->PaintEnmey(Gamedc1, Gamedc2);


			//�÷��̾� ������ Gamedc1�� �׷��ش�.
			player->PaintPlayer(Gamedc1, Gamedc2);
			player->PaintPlayerIF(Gamedc1, Gamedc2);

			//GameMap ������ �׷��ش�.
			Inter->PaintBackGroundLine(Gamedc1);

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
		}
		
		//mem1dc�� hdc�� �����Ѵ�.
		BitBlt(hdc, 0, 0, ScreenX, ScreenY, mem1dc, 0, 0, SRCCOPY); 
		SelectObject(mem1dc, OldBitmap);
		DeleteObject(Bitmap);
		EndPaint(hwnd, &ps);
		break;
	
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hwnd, iMsg, wParam, lParam);
}