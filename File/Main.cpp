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
#include "RankPage.hpp"
#include "LevelSet.hpp"


LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam);

HINSTANCE hInst;

int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow) {
	HWND hwnd1;
	WNDCLASS WndClass1;
	MSG msg;
	hInst = hInstance;

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

	//��� ȭ���� HDC
	//HDC 1: ��Ʈ��, 2: �۾��� �⺻ 3: ����
	static HDC Gamedc[3];
	
	//�⺻ ������۸��� ���� ��Ʈ��
	static HBITMAP Bitmap, OldBitmap;

	//��� �������� ���� ��Ʈ��
	static HBITMAP GamePlayBit[3];

	//���ĺ���
	static BLENDFUNCTION bf1, bf2;

	//GamePlay�������� ���� ��Ʈ
	static HFONT GamePlayFont;

	PAINTSTRUCT ps;

	//Ŭ���� ��ü��
	static Player* player;
	static MainPage* Main;
	static HelpPage* Help;
	static RankPage* Rank;
	static CreditPage* Credit;
	static Camera* camera;
	static Interface* Inter;
	static LineEnemy* LEnemy[LENEMYMAX];
	static WideEnemy* WEnemy;
	static BombEnemy* BEnemy[BENEMYMAX];
	static AirEnemy* AEnemy[AENEMYMAX];
	static LevelSet* Level;

	//���콺 ��ǥ
	static int Mx, My;

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

	//Level�� �ö󰡴� �ð�
	static int LevelTime = 0;

	//Rank ������ ���� ��
	static int Ranking = 0;

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
		if (Page == 5) {
			Rank->SetName(Ranking, wParam);
		}
		break;
	case WM_LBUTTONUP:
		Mx = LOWORD(lParam);
		My = HIWORD(lParam);
		if (MainCreate) {
			if (Page == 1) {
				//StartPage(MainPage)�� ���
				Page = Main->ChangeMainPage(My, Mx);
				if (Page == 2) {
					//Page2�� HelpPage�̴�.

					//��ư Ŭ�� ���� ���
					PlayButtonClickSound();

					//MainPage ����
					DeleteMainPage(&Main);

					//HelpPage ����
					CreateHelpPage(&Help, hInst);
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
					//Mainȭ������ ���ƿ��� ���
					PlayButtonClickSound();
					DeleteHelpPage(&Help);
					CreateMainPage(&Main);
				}
				else if (Page == 6) {
					//Creditȭ������ ���� ���
					PlayButtonClickSound();
					CreateCreditPage(&Credit);
				}
			}
			else if (Page == 6) {
				Page = Credit->ChangeCreditPage(My, Mx);
				if (Page == 2) {
					//Helpȭ������ ���ƿ��� ���
					PlayButtonClickSound();
					DeleteCreditPage(&Credit);
				}
			}
		}
		//MainCreate�� false�̱� ������
		if (Page == 5) {
			//RankPage��ȯ Ȯ��
			Page = Rank->ChangeRankPage(My, Mx);
			if (Page == 0) {
				//StartPage�� LoadingPage�� ���� ���
				PlayButtonClickSound();
				DeleteRankPage(&Rank);

				//HDC, BitMap �����
				for (int i = 0; i < 2; i++) {
					DeleteObject(GamePlayBit[i]);
					DeleteDC(Gamedc[i]);
				}

				//ĳ�� �����
				HideCaret(hwnd);
				DestroyCaret();

				//RankPageTimer����
				KillTimer(hwnd, 6);

				CreateLoadingPage();
				//Loading Ÿ�̸� ����
				SetTimer(hwnd, 1, 10, NULL);
				LoadingCount = 199;
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
			else if (Page == 6) {
				//CreditPage������ ���콺 ���� Ŭ��
				Credit->BackClickCheck(My, Mx);
			}
		}
		if (Page == 5) {
			//RankPage������ ���콺 ���� Ŭ��
			Rank->MainClickCheck(My, Mx);
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
		else if (Page == 5) {
			//RankPage������ ���콺 �̵�
			Rank->MouseUpCheck(My, Mx);
		}
		else if (Page == 6) {
			//CreditPage������ ���콺 �̵�
			Credit->MouseUpCheck(My, Mx);
		}
		break;
	case WM_TIMER:
		switch (wParam) {
		case 1:
			//LoadingPage Timer1

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

				//GamePlayBit[0] = ��Ʈ��
				//GamePlayBit[0] = (HBITMAP)LoadImage(NULL, _T(".\\BitMap\\StartBackGround.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
				GamePlayBit[0] = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(IDB_StarkBackground));

				//GamePlayBit[1] = �� �̿��� �͵�
				GamePlayBit[1] = CreateCompatibleBitmap(hdc, ScreenX, ScreenY);

				//Gamedc[0] = ��Ʈ�� Gamedc[1] = �۾� Gamedc[2] = HelpPage
				for(int i=0; i<3; i++)
					Gamedc[i] = CreateCompatibleDC(hdc);
	
				//HelpPage���� �ʿ��� HDC, BITMAP�� ����

				SelectObject(Gamedc[0], GamePlayBit[0]);
				SelectObject(Gamedc[1], GamePlayBit[1]);

				//�ؽ�Ʈ�� ����� ������ ������ ������.
				SetBkMode(Gamedc[1], TRANSPARENT);

				ReleaseDC(hwnd, hdc);

				//���ĺ����� �ʿ��� ��ü�� �ʱ�ȭ
				bf1.AlphaFormat = AC_SRC_ALPHA;
				bf1.BlendOp = AC_SRC_OVER;
				bf1.BlendFlags = 0;

				bf2.AlphaFormat = 0;
				bf2.BlendOp = AC_SRC_OVER;
				bf2.BlendFlags = 0;
			}
			break;
		case 2:
			//MainPage ���̵� Ÿ�̸�

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
			//MainPage ���� Ÿ�̸�

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
			//MainPage ���� (Start��ư ������ ���) Ÿ�̸�

			if (Page == 1) {
				//MainPage ȭ�� ���̵� ������ ���� Page�� 1(MainPage)�� ������
				//MainPage ȭ�� ���̵� �ƿ� ����
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
		
			//������ʹ� Page�� 3(LoadingPage2)�� ����
			if (Page == 3) {
				if (LoadingCount == 0) {
					//��� ���� ����
					MainPageSoundStop();

					//LoadingPage����
					CreateLoadingPage();

					//MainPage���� ���� HDC, BITMAP�� ����
					for (int i = 0; i < 3; i++) {
						DeleteObject(GamePlayBit[i]);
						DeleteDC(Gamedc[i]);
					}
					
				}
				if(LoadingCount<100)
					LoadingCount++;

				if (LoadingCount == 100) {
					//���� ȭ�� �������� 10���� Page�� �����Ѵ�.
					Page = 10;

					//�������̽��� �����Ѵ�.
					CreateInterface(&Inter, hInst);

					//���� BGM�� �����Ѵ�.
					PlayGameBKSound();

					//�÷��̾� ����
					CreatePlayer(&player, hInst);

					//ī�޶� ����
					CreateCamera(&camera);

					//�� ����
					CreateLEnemy(LEnemy, hInst);
					CreateWEnemy(&WEnemy, hInst);
					CreateBEnemy(BEnemy, hInst);
					CreateAEnemy(AEnemy, hInst);

					//�������� ����
					CreateLevelSet(&Level);

					//GamePage�� ���� HDC, BITMAP�� ����
					
					hdc = GetDC(hwnd);

					for (int i = 0; i < 3; i++) {
						Gamedc[i] = CreateCompatibleDC(hdc);
						GamePlayBit[i] = CreateCompatibleBitmap(hdc, ALLMAPX, ALLMAPY);
						SelectObject(Gamedc[i], GamePlayBit[i]);
					}

					GamePlayFont = CreateFontW(240, 60, 0, 0, FW_BOLD, FALSE, FALSE, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, _T("Vladimir Script"));

					SelectObject(mem1dc, GamePlayFont);

					ReleaseDC(hwnd, hdc);
				}
			}

			if (Page == 10) {
				GamePageLoading += 5;

				if (GamePageLoading == ScreenY) {
					//GamePageLoading�� ScreeeY(820) �ȴٸ� ��� �ε��� ������ �̹Ƿ� 
					//GamePageLoadingŸ�̸� ����
					KillTimer(hwnd, 4);
					
					//������ ���������� LevelTime �ʱ�ȭ
					LevelTime = 0;

					//���� ������ �߱� ������ LevelUp ���� ���
					PlayLevelUpSound();

					//���� Timer ����
					SetTimer(hwnd, 8, 100, NULL);
					SetTimer(hwnd, 9, 10, NULL);
					SetTimer(hwnd, 10, 100, NULL);
				}
			}
			break;
		case 5:
			//�÷��̾ �׾����� ����Ǵ� Ÿ�̸�

			GamePageLoading -= 5;
			//���� �������� �ݴ� ����Ʈ�� �����Ѵ�.

			if (GamePageLoading == 0) {
				//GamePageLoading�� 0�� �ȴٸ� ��� ���� �������� ������������
				//Ÿ�̸� ���� ����
				KillTimer(hwnd, 5);

				//GamePage���� ������ ��ü�� ��� ����
				//Interface�� ���� RankPage������ ����

				//�÷��̾� ����
				DeletePlayer(&player);

				//ī�޶� ����
				DeleteCamera(&camera);

				//�� ����
				DeleteLEnemy(LEnemy);
				DeleteWEnemy(&WEnemy);
				DeleteBEnemy(BEnemy);
				DeleteAEnemy(AEnemy);

				//���� ���� ����
				DeleteLevelSet(&Level);

				//GamePage�� ���� HDC, BITMAP�� ����
				for (int i = 0; i < 3; i++) {
					DeleteObject(GamePlayBit[i]);
					DeleteDC(Gamedc[i]);
				}

				//Page RankPage�� 5�� ����
				Page = 5;

				//RankPage ����
				CreateRankPage(&Rank);

				//���� �÷��̾� ���ھ� ����
				Ranking = Rank->CreateRank(Inter);			

				//�������̽� ����
				DeleteInterface(&Inter);

				//RankPage���� �ʿ��� HDC, BITMAP�� ����
				hdc = GetDC(hwnd);

				//GamePlayBit[0] = ��Ʈ��
				//GamePlayBit[0] = (HBITMAP)LoadImage(NULL, _T(".\\BitMap\\RankPage.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
				GamePlayBit[0] = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(IDB_RankPage));

				//GamePlayBit[1] = �� �̿��� �͵�
				GamePlayBit[1] = CreateCompatibleBitmap(hdc, ScreenX, ScreenY);

				for (int i = 0; i < 2; i++) {
					Gamedc[i] = CreateCompatibleDC(hdc);
					SelectObject(Gamedc[i], GamePlayBit[i]);
				}

				SetBkMode(Gamedc[1], TRANSPARENT);

				ReleaseDC(hwnd, hdc);

				//ĳ�� ����
				CreateCaret(hwnd, NULL, 15, 40);
				ShowCaret(hwnd);

				//GamePage Sound ����
				GamePageSoundStop();

				//RankPageSound ���
				PlayRankPageSound();

				//ScoreRankTimer����
				SetTimer(hwnd, 6, 10, NULL);
			}
			break;
		case 6:
			//ScoreRankTimer			
			break;
		case 8:
			//�÷��̾� �������̽� Ÿ�̸�

			if (Inter->GetLevel() < 10) {
				//Level�� ���� �Ǹ� �������ش�.
				LevelTime++;

				if (LevelTime == 501) {
					//���ӽð� ���� 50��
					//+ Levelǥ�� �ð� 1��
					//Time�� 0���� �ʱ�ȭ
					LevelTime = 0;
					Inter->ChangeLevel();

					//���� ���� �߱� ������ LevelUp ���� ���
					PlayLevelUpSound();

					//���ʹ̵� �ʱ�ȭ
					AllEnemyReset(LEnemy, WEnemy, BEnemy, AEnemy);
					player->ResetHitCheck();
				}
			}
			else {
				LevelTime++;
				if (LevelTime > 10)
					//Level�� 10�϶��� ���ھ� ������ ������Ʈ �ϱ� ���ؼ�
					//LevelTime�� 11���� �����Ѵ�.
					LevelTime = 11;
			}
			
			//�÷��̾��� ü���� Ȯ��
			if (player->PlayerDie()) {
				//ü���� 0�̶��
				KillTimer(hwnd, 8);
				KillTimer(hwnd, 9);
				KillTimer(hwnd, 10);
				SetTimer(hwnd, 5, 10, NULL);
			}

			//�÷��̾� ��ų ��ٿ��� ������Ʈ�Ѵ�.
			player->SkillCoolDown(hwnd);

			//�÷��̾� ���ھ� ������ ������Ʈ�Ѵ�.
			if (LevelTime > 10)
				Inter->ChangeScore();
			break;
		case 9:
			//�÷��̾� �̵� Ÿ�̸�

			//�÷��̾� �̵� �Լ� ȣ��
			player->MoveBasic();
			//ī�޶� �̵� �Լ� ȣ��
			camera->CameraMove(player);

			break;
		case 10:
			//���ʹ� Ÿ�̸�

			//������ ���� ������ �Ѵ�.
			Level->LevelSetting(Inter->GetLevel());
			Level->WaitTimeSetting(Inter->GetLevel());

			if (LevelTime > 10) {
				//LevelTime�� 10�̻��϶� �����Ѵ�.
				//LevelTime�� 10������ ���� �������̽��� LEVELǥ�ø� �׷��ش�. �� LEVEL�� ���� �ְ� �����.

				//������ �����Ѵ�.
				AllEnemySet(LEnemy, WEnemy, BEnemy, AEnemy, player, Level);

				//�÷��̾ ���� ���ݿ� �¾Ҵ��� Ȯ���Ѵ�.
				player->CheckHitCheck(Inter);
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
			//�ε� ������ �׸���
			PaintLoadingPage(mem1dc, LoadingCount, Page);
		}
		else if (Page == 1 || Page == 2 || Page == 6) {
			//Page1 : MainPage, Page2 : HelpPage �׸���, Page6 : CreditPage �׸���
			
			//MainCreate�� True��� MainPage�� �ϼ��� �����̰� False��� ���̵� �ƿ�, ���̵� �ε� �̿ϼ��� �����̴�.
			if(MainCreate)
				PatBlt(mem1dc, 0, 0, ScreenX, ScreenY, WHITENESS);
		
			//���ĺ��� (����ȭ)�� ���� �۾�
			bf1.SourceConstantAlpha = MainBitPade * 15;
			
			//���� �������� ���̵���, ���̵� �ƿ� ����
			AlphaBlend(mem1dc, 0, 0, ScreenX, ScreenY, Gamedc[0], 0, 0,ScreenX, ScreenY, bf1);

			//mem1dc�� �׷����� Gamedc[1]�� �����Ѵ�.
			BitBlt(Gamedc[1], 0, 0, ScreenX, ScreenY, mem1dc, 0, 0, SRCCOPY);

			//Gamedc[1]�� Page���� Paint�Ѵ�.
			if (Page == 1) {
				//StartPage�׸���
				Main->PaintMainPage(Gamedc[1]);
			}
			else if (Page == 2) {
				//HelpPage �׸���
				Help->PaintHelpPage(Gamedc[1], Gamedc[2]);
			}
			else {
				//CreditPage �׸���
				Credit->PaintCreditPage(Gamedc[1]);
			}

			//���ĺ��� (����ȭ)�� ���� �۾�
			bf2.SourceConstantAlpha = MainTextPade * 15;

			//���� �������� ���̵���, ���̵� �ƿ� ����
			AlphaBlend(mem1dc, 0, 0, ScreenX, ScreenY, Gamedc[1], 0, 0, ScreenX, ScreenY, bf2);
		}
		else if (Page == 3) {
			//GamePage �ε� ������ �׸���
			PaintLoadingPage(mem1dc, LoadingCount * 2, Page);
		}
		else if (Page == 5) {
			//Gamedc[0]�� �׷����� Gamedc[1]�� �����Ѵ�.
			BitBlt(Gamedc[1], 0, 0, ScreenX, ScreenY, Gamedc[0], 0, 0, SRCCOPY);

			//RankPage �׸���
			Rank->PaintRankPage(Gamedc[1], Ranking);

			//Gamedc[1]�� �׷����� mem1dc�� �����Ѵ�.
			BitBlt(mem1dc, 0, 0, ScreenX, ScreenY, Gamedc[1], 0, 0, SRCCOPY);

		
		}
		else if (Page == 10) {
			//GamePage �׸���

			//Gamedc[1]�� GameMap�� �׷��ش�.
			Inter->PaintBackGround(Gamedc[1], Gamedc[0]);			
			Inter->PaintInterface(Gamedc[1]);

			//���� �׷��ش�.
			AllEnemyPaint(LEnemy, WEnemy, BEnemy, AEnemy, Gamedc);

			//�÷��̾� ������ Gamedc[1]�� �׷��ش�.
			player->PaintPlayer(Gamedc[1], Gamedc[0]);
			player->PaintPlayerIF(Gamedc[1], Gamedc[0]);

			//GameMap ������ �׷��ش�.
			Inter->PaintBackGroundLine(Gamedc[1]);

			//Gamedc[1]�� �ִ� ���� ���� ��µǴ� mem1dc�� �˸°� �����Ѵ�.

			//���� �׵θ� ����
			if(GamePageLoading<30)
				//30�̸������� GamePageLoading�� ũ�� ��ŭ �����Ѵ�.
				BitBlt(mem1dc, 0, 0, 1280, GamePageLoading, Gamedc[1], 0, 0, SRCCOPY);
			else
				//30�̻��� �Ǹ� �� �ε��� ��� ������ �׳� 30�� ũ�⸸ŭ �����Ѵ�.
				BitBlt(mem1dc, 0, 0, 1280, 30, Gamedc[1], 0, 0, SRCCOPY);

			//���� / ������ �׵θ� ����
			if (GamePageLoading < 700) {
				//700�̸������� GamePageLoading�� ũ�� ��ŭ �����Ѵ�.
				BitBlt(mem1dc, 0, 0, 30, GamePageLoading, Gamedc[1], 0, 0, SRCCOPY);
				BitBlt(mem1dc, 1250, 0, 30, GamePageLoading, Gamedc[1], ALLMAPX - 30, 0, SRCCOPY);
			}
			else {
				//700�̻��� �Ǹ� �� �ε��� ��� ������ �׳� 700�� ũ�⸸ŭ �����Ѵ�.
				BitBlt(mem1dc, 0, 0, 30, 700, Gamedc[1], 0, 0, SRCCOPY);
				BitBlt(mem1dc, 1250, 0, 30, 700, Gamedc[1], ALLMAPX - 30, 0, SRCCOPY);
			}
				
			if (GamePageLoading >= 700) {
				//700�̻��� �Ǿ�߸� ���縦 �����Ѵ�.
				//�÷��̾� �������̽� ����
				BitBlt(mem1dc, 0, 700, ScreenX, GamePageLoading - 700, Gamedc[1], 0, ALLMAPY - 120, SRCCOPY);

				//�������̽� ������ �׵θ� ����
				BitBlt(mem1dc, ScreenX - 30, 700, 30, GamePageLoading - 700, Gamedc[1], ALLMAPX - 30, ALLMAPY - 120, SRCCOPY);
			}
			
			if (GamePageLoading >= 30) {
				//30�̻��� �Ǿ�߸� ���縦 �����Ѵ�.
				//�� �� ����
				if (GamePageLoading < 700)
					//700�̸������� GamePageLoading�� ũ�� ��ŭ �����Ѵ�.
					BitBlt(mem1dc, 30, 30, 1220, GamePageLoading - 30, Gamedc[1], camera->GetCLeft(), camera->GetCTop(), SRCCOPY);
				else
					//700�̻��� �Ǹ� �� �ε��� ��� ������ �׳� 670�� ũ�⸸ŭ �����Ѵ�.
					BitBlt(mem1dc, 30, 30, 1220, 670, Gamedc[1], camera->GetCLeft(), camera->GetCTop(), SRCCOPY);
			}

			if (LevelTime > 0 && LevelTime <= 10) {
				//0�ʰ� 10�����϶�
				//LEVEL�� ����ش�.
				wchar_t str[10];
				swprintf_s(str, L"Level %d%d", Inter->GetLevel() / 10, Inter->GetLevel() % 10);
				SetBkMode(mem1dc, TRANSPARENT);
				SetTextColor(mem1dc, RGB(125, 0, 0));
				TextOut(mem1dc, 360, 250, str, 8);
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
