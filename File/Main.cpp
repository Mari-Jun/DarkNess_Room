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

int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow) {
	HWND hwnd1;
	WNDCLASS WndClass1;
	MSG msg;

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

	//GamePlay HDC 1: 기본, 2: 비트맵 3: 블렌딩
	static HDC Gamedc1, Gamedc2, Gamedc3;

	//HelpPage HDC
	static HDC Helpdc1;

	//PlayerDC
	static HDC Playerdc;

	PAINTSTRUCT ps;

	//기본 더블버퍼링을 위한 비트맵
	static HBITMAP Bitmap, OldBitmap;

	//StartPage를 위한 비트맵 1 : 배경 이미지, 2 : 텍스트
	static HBITMAP MainPageBit1, MainPageBit2;

	//GamePlay페이지를 위한 비트맵
	static HBITMAP GamePlayBit1, OldGamePlayBit1, GamePlayBit2, OldGamePlayBit2 ,GamePlayBit3, OldGamePlayBit3;

	//GamePlay페이지를 위한 폰트
	static HFONT GamePlayFont;

	//클래스 객체들
	static Player* player;
	static MainPage* Main;
	static HelpPage* Help;
	static RankPage* Rank;
	static Camera* camera;
	static Interface* Inter;
	static LineEnemy* LEnemy[LENEMYMAX];
	static WideEnemy* WEnemy;
	static BombEnemy* BEnemy[BENEMYMAX];
	static AirEnemy* AEnemy[AENEMYMAX];

	//마우스 좌표
	static int Mx, My;

	//게임 페이지
	static int Page = 0;

	//로딩 페이지 구현에 사용되는 변수들
	static int LoadingCount = 0, LightCount = 0;

	//MainPage가 생성을 알려주는 변수
	static bool MainCreate = false;

	//StartPage 페이드 구현시 필요한 변수
	static int MainBitPade = 0, MainTextPade = 0;

	//GamePage시작시 효과 구현을 위해 필요한 변수
	static int GamePageLoading = 0;

	//현재 에너미별 발사 된 수
	static int LShot = 0, BShot = 0, AShot = 0;

	//최대 에너미별 발사 수
	static int LMaxShot = 0, WMaxShot = 0, BMaxShot = 0, AMaxShot = 0;

	//발사 대기 시간 설정
	static int LWT = 0, WWT = 0, BWT = 0, AWT = 0;

	//알파블렌딩
	static BLENDFUNCTION bf1, bf2;

	static int LevelTime = 0;

	switch (iMsg)
	{
	case WM_CREATE:
		//사운드 세팅
		SoundInit();
		//로딩 페이지에 필요한 객체들 만들기
		CreateLoadingPage();

		//기본 HDC및 BITAMP 생성
		hdc = GetDC(hwnd);
		mem1dc = CreateCompatibleDC(hdc);
		ReleaseDC(hwnd, hdc);

		//Loading 타이머 세팅
		SetTimer(hwnd, 1, 10, NULL);
		//랜덤을 위한
		srand(unsigned int(time(NULL)));		
		break;
	case WM_GETMINMAXINFO:
		//화면 고정
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
					//Page2는 HelpPage이다.

					//버튼 클릭 사운드 재생
					PlayButtonClickSound();

					//MainPage 삭제
					DeleteMainPage(&Main);

					//HelpPage 생성
					CreateHelpPage(&Help);
				}
				else if (Page == 3) {
					//Page3은 GameLoading페이지이다.

					//버튼 클릭 사운드 재생
					PlayButtonClickSound();

					Page = 1;

					//MainCreate역시 페이드 아웃 구현을 위해서 false로 바꿔준다.
					MainCreate = false;

					//MainBitPade와 MainTextPade가 번개효과 등으로 Pade값이 17이 아닐 경우를 대비하여 17로 만들어준다.
					MainBitPade = 17;
					MainTextPade = 17;

					//번개 타이머 제거
					KillTimer(hwnd, 3);

					//MainPage 페이드 아웃 타이머 생성
					//GamePageLoading 타이머이기도 함
					SetTimer(hwnd, 4, 10, NULL);
				}
				else if (Page == 4) {
					//종료
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
		//MainCreate가 false이기 때문에
		if (Page == 5) {
			//RankPage변환 확인
			Page = Rank->ChangeRankPage(My, Mx);
			if (Page == 0) {
				//StartPage즉 LoadingPage로 갔을 경우
				PlayButtonClickSound();
				DeleteRankPage(&Rank);

				//RankPageTimer제거
				KillTimer(hwnd, 6);

				CreateLoadingPage();
				//Loading 타이머 세팅
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
				//MainPage에서의 마우스 왼쪽 클릭
				Main->MainClickCheck(My, Mx);
			}
			else if (Page == 2) {
				//HelpPage에서의 마우스 왼쪽 클릭
				Help->HelpClickCheck(My, Mx);
			}
		}
		if (Page == 5) {
			//RankPage에서의 마우스 왼쪽 클릭
			Rank->MainClickCheck(My, Mx);
		}
		break;
	case WM_MOUSEMOVE:
		Mx = LOWORD(lParam);
		My = HIWORD(lParam);
		if (Page == 1) {
			//MainPage에서의 마우스 이동
			Main->MouseUpCheck(My, Mx);
		}
		else if (Page == 2) {
			//HelpPage에서의 마우스 이동
			Help->MouseUpCheck(My, Mx);
		}
		else if (Page == 5) {
			//RankPage에서의 마우스 이동
			Rank->MouseUpCheck(My, Mx);
		}
		break;
	case WM_TIMER:
		switch (wParam) {
		case 1:
			//Count를 1씩 증가
			LoadingCount++;
			if (LoadingCount == 200) {
				//Count가 200이 되면 로딩 완료!

				//로딩 페이지 삭제
				DeleteLoadingPage();

				//Loading 타이머 삭제
				KillTimer(hwnd, 1);
		
				//MainPage 페이드 타이머 생성
				SetTimer(hwnd, 2, 40, NULL);

				//MainPage생성				
				Page = 1;
				CreateMainPage(&Main);

				//MainPage에서 필요한 HDC, BITMAP들 생성
				hdc = GetDC(hwnd);

				//MainPageBit1 = 비트맵
				MainPageBit1 = (HBITMAP)LoadImage(NULL, _T(".\\BitMap\\StartBackGround.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

				//MainPageBit2 = 그 이외의 것들
				MainPageBit2 = CreateCompatibleBitmap(hdc, ScreenX, ScreenY);

				//Startdc1 = 비트맵
				Startdc1 = CreateCompatibleDC(hdc);
				//Startdc2 = 글씨
				Startdc2 = CreateCompatibleDC(hdc);

				//HelpPage에서 필요한 HDC, BITMAP들 생성
				Helpdc1 = CreateCompatibleDC(hdc);

				SelectObject(Startdc1, MainPageBit1);
				SelectObject(Startdc2, MainPageBit2);

				//텍스트의 배경을 투명한 색으로 지정함.
				SetBkMode(Startdc2, TRANSPARENT);

				ReleaseDC(hwnd, hdc);

				//알파블렌딩에 필요한 객체들 초기화
				bf1.AlphaFormat = AC_SRC_ALPHA;
				bf1.BlendOp = AC_SRC_OVER;
				bf1.BlendFlags = 0;

				bf2.AlphaFormat = 0;
				bf2.BlendOp = AC_SRC_OVER;
				bf2.BlendFlags = 0;
			}
			break;
		case 2:
			//StartPage화면 페이드 시작
			if (MainBitPade < 17)
				MainBitPade++;
			if (MainBitPade >= 10) {
				//StartPage글자 페이드 시작
				MainTextPade++;
				if (MainTextPade == 17) {
	
					//배경 BGM 재생
					PlayMainBKSound();

					//StartPage페이드가 완료되었으니 StartCreate를 true로 바꿔준다.
					MainCreate = true;

					//MainPage 페이드 타이머 제거
					KillTimer(hwnd, 2);

					//번개 효과를 위한 깜빡임 타이머 생성
					SetTimer(hwnd, 3, 10, NULL);
				}
			}
			break;
		case 3:
			if (LightCount == 0) 
				//번개 효과음 재생
				PlayLightningSound();
			LightCount++;
			//천둥소리 날 때를 뜻함
			if (LightCount == 12 || LightCount == 30) {
				MainBitPade = 13;
			}
			if (LightCount == 15 || LightCount == 33) {
				MainBitPade = 17;
			}
			//사운드가 루프를 돌때를 뜻함
			if (LightCount == 450) {
				LightCount = 0;
			}
			break;
		case 4:
			if (Page == 1) {
				//StartPage 화면 페이드 구현을 위해 Page가 1인 상태임
				//StartPage 화면 페이드 아웃 시작
				MainBitPade--;
				MainTextPade--;

				if ((MainBitPade == 0) && (MainTextPade == 0)) {
					//MainPage 삭제
					DeleteMainPage(&Main);

					//LoadingCount를 0으로 초기화 
					LoadingCount = 0;

					//Page를 3으로 초기화
					//Page3은 또다른 로딩 페이지이다.
					Page = 3;

					//LightCount 초기화
					LightCount = 0;
				}
			}
		
			//여기부터는 Page가 3인 상태
			if (Page == 3) {
				if (LoadingCount == 0) {
					//모든 사운드 제거
					MainPageSoundStop();

					//LoadingPage생성
					CreateLoadingPage();

					//MainPage에서 사용된 HDC, BITMAP들 삭제
					DeleteObject(MainPageBit1);
					DeleteObject(MainPageBit2);
					DeleteDC(Startdc1);
					DeleteDC(Startdc2);
					DeleteDC(Helpdc1);
				}
				if(LoadingCount<100)
					LoadingCount++;

				if (LoadingCount == 100) {
					//게임 화면 페이지인 10으로 Page를 변경한다.
					Page = 10;

					//인터페이스를 생성한다.
					CreateInterface(&Inter);

					//게임 BGM을 실행한다.
					PlayGameBKSound();

					//플레이어 생성
					CreatePlayer(&player);

					//카메라 생성
					CreateCamera(&camera);

					//적 생성
					CreateLEnemy(LEnemy);
					CreateWEnemy(&WEnemy);
					CreateBEnemy(BEnemy);
					CreateAEnemy(AEnemy);

					//GamePage를 위한 HDC, BITMAP들 생성
					
					hdc = GetDC(hwnd);

					Gamedc1 = CreateCompatibleDC(hdc);
					Gamedc2 = CreateCompatibleDC(hdc);
					Gamedc3 = CreateCompatibleDC(hdc);

					//뒤에 배경 비트맵이 있기 때문에 가능하다.
					//없다면 PAINT에 넣어줘야 한다.
					GamePlayBit1 = CreateCompatibleBitmap(hdc, ALLMAPX, ALLMAPY);
					GamePlayBit2 = CreateCompatibleBitmap(hdc, ALLMAPX, ALLMAPY);
					GamePlayBit3 = CreateCompatibleBitmap(hdc, ALLMAPX, ALLMAPY);

					GamePlayFont = CreateFontW(240, 60, 0, 0, FW_BOLD, FALSE, FALSE, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, _T("Vladimir Script"));

					SelectObject(Gamedc1, GamePlayBit1);
					SelectObject(Gamedc2, GamePlayBit2);
					SelectObject(Gamedc3, GamePlayBit3);

					SelectObject(mem1dc, GamePlayFont);

					ReleaseDC(hwnd, hdc);
				}
			}

			if (Page == 10) {
				GamePageLoading += 5;

				if (GamePageLoading == ScreenY) {
					//GamePageLoading이 ScreeeY(820) 된다면 모든 로딩이 끝난것 이므로 
					//GamePageLoading타이머 제거
					KillTimer(hwnd, 4);
					//게임 Timer 생성
					SetTimer(hwnd, 8, 100, NULL);
					SetTimer(hwnd, 9, 10, NULL);
					SetTimer(hwnd, 10, 100, NULL);
				}
			}
			break;
		case 5:
			//플레이어가 죽었을때 실행되는 타이머

			GamePageLoading -= 5;
			//게임 페이지를 닫는 이펙트를 구현한다.

			if (GamePageLoading == 0) {
				//GamePageLoading이 0이 된다면 모든 게임 페이지가 지워졌음으로
				//타이머 실행 중지
				KillTimer(hwnd, 5);

				//GamePage에서 생성된 객체들 모두 삭제
				//Interface는 제외 RankPage에서도 사용됨

				//게임 BGM을 실행한다.
				//PlayGameBKSound();

				//플레이어 제거
				DeletePlayer(&player);

				//카메라 제거
				DeleteCamera(&camera);

				//인터페이스 제거
				DeleteInterface(&Inter);

				//적 제거
				DeleteLEnemy(LEnemy);
				DeleteWEnemy(&WEnemy);
				DeleteBEnemy(BEnemy);
				DeleteAEnemy(AEnemy);

				//GamePage를 위한 HDC, BITMAP들 제거
				DeleteDC(Gamedc1);
				DeleteDC(Gamedc2);
				DeleteDC(Gamedc3);
				DeleteObject(GamePlayBit1);
				DeleteObject(GamePlayBit2);
				DeleteObject(GamePlayBit3);

				//GamePage Sound 제거
				GamePageSoundStop();

				//Page RankPage인 5로 변경
				Page = 5;

				//RankPage 생성
				CreateRankPage(&Rank);

				//ScoreRankTimer실행
				SetTimer(hwnd, 6, 10, NULL);
			}
			break;
		case 6:
			//ScoreRankTimer
			

			break;
		case 8:
			//플레이어 인터페이스 타이머

			if (Inter->GetLevel() < 10) {
				//Level을 때가 되면 변경해준다.
				LevelTime++;

				if (LevelTime == 101) {
					//게임시간 기준 50초
					//+ Level표시 시간 1초
					//Time을 0으로 초기화
					LevelTime = 0;
					Inter->ChangeLevel();

					//에너미들 초기화
					ResetLEnemy(LEnemy);
					ResetWEnemy(WEnemy);
					ResetBEnemy(BEnemy);
					ResetAEnemy(AEnemy);
					player->ResetHitCheck();
				}
			}
			else {
				LevelTime++;
				if (LevelTime > 10)
					//Level이 10일때는 스코어 점수를 업데이트 하기 위해서
					//LevelTime을 11으로 설정한다.
					LevelTime = 11;
			}
			
			//플레이어의 체력을 확인
			if (player->PlayerDie()) {
				//체력이 0이라면
				KillTimer(hwnd, 8);
				KillTimer(hwnd, 9);
				KillTimer(hwnd, 10);
				SetTimer(hwnd, 5, 10, NULL);
			}

			//플레이어 스킬 쿨다운을 업데이트한다.
			player->SkillCoolDown(hwnd);

			//플레이어 스코어 점수를 업데이트한다.
			if (LevelTime > 10)
				Inter->ChangeScore();
			break;
		case 9:
			//플레이어 이동 타이머

			//플레이어 이동 함수 호출
			player->MoveBasic();
			//카메라 이동 함수 호출
			camera->CameraMove(player);

			break;
		case 10:
			//에너미 타이머

			//레벨에 따른 세팅을 한다.
			LevelSetting(Inter->GetLevel(), LMaxShot, WMaxShot, BMaxShot, AMaxShot);
			WaitTimeSet(Inter->GetLevel(), LWT, WWT, BWT, AWT);

			if (LevelTime > 10) {
				//LevelTime이 10이상일때 설정한다.
				//LevelTime이 10이하일 경우는 인터페이스에 LEVEL표시를 그려준다. 즉 LEVEL당 텀이 있게 만든다.

				//LineEnmey
				for (LShot; LShot < LMaxShot; LShot++) {
					SelectLShot(LEnemy, LWT);
				}
				LShot = ChangeLInfo(LEnemy, player);

				//WideEnemy
				if (WMaxShot == 1)
					ChangeWInfo(WEnemy, player, WWT);

				//BombEnemy;
				for (BShot; BShot < BMaxShot; BShot++) {
					SelectBShot(BEnemy, BWT);
				}
				BShot = ChangeBInfo(BEnemy, player);

				//AirEnemy
				for (AShot; AShot < AMaxShot; AShot++) {
					SelectAShot(AEnemy, player, AWT);
				}
				AShot = ChangeAInfo(AEnemy, player);

				//플레이어가 적의 공격에 맞았는지 확인한다.
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

		//mem1dc에 더블버퍼링으로 그려준다

		if (Page == 0) {
			//로딩 페이지 그리기
			PaintLoadingPage(mem1dc, LoadingCount, Page);
		}
		else if (Page == 1 || Page == 2) {
			//Page1 : MainPage, Page2 : HelpPage 그리기
			
			//MainCreate가 True라면 MainPage가 완성된 상태이고 False라면 페이드 아웃, 페이드 인등 미완성된 상태이다.
			if(MainCreate)
				PatBlt(mem1dc, 0, 0, ScreenX, ScreenY, WHITENESS);
		
			//알파블렌딩 (투명화)를 위한 작업
			bf1.SourceConstantAlpha = MainBitPade * 15;
			
			//알파 블렌딩으로 페이드인, 페이드 아웃 구현
			AlphaBlend(mem1dc, 0, 0, ScreenX, ScreenY, Startdc1, 0, 0,ScreenX, ScreenY, bf1);

			//mem1dc에 그려진걸 Startdc2에 복사한다.
			BitBlt(Startdc2, 0, 0, ScreenX, ScreenY, mem1dc, 0, 0, SRCCOPY);

			//Startdc2에 Page들을 Paint한다.
			if (Page == 1) {
				Main->PaintMainPage(Startdc2);
			}
			else {
				Help->PaintHelpPage(Startdc2, Helpdc1);
			}

			//알파블렌딩 (투명화)를 위한 작업
			bf2.SourceConstantAlpha = MainTextPade * 15;

			//알파 블렌딩으로 페이드인, 페이드 아웃 구현
			AlphaBlend(mem1dc, 0, 0, ScreenX, ScreenY, Startdc2, 0, 0, ScreenX, ScreenY, bf2);
		}
		else if (Page == 3) {
			//GamePage 로딩 페이지 그리기
			PaintLoadingPage(mem1dc, LoadingCount * 2, Page);
		}
		else if (Page == 5) {
			//RankPage 그리기
			Rank->PaintRankPage(mem1dc);
		}
		else if (Page == 10) {
			//GamePage 그리기

			//Gamedc1에 GameMap을 그려준다.
			Inter->PaintBackGround(Gamedc1, Gamedc2);			
			Inter->PaintInterface(Gamedc1);

			//발사체들을 Gamedc1에 그려준다.
			for (int L = 0; L < LENEMYMAX; L++)
				LEnemy[L]->PaintShot(Gamedc1, Gamedc2, Gamedc3);
			WEnemy->PaintShot(Gamedc1, Gamedc2, Gamedc3);
			for (int B = 0; B < BENEMYMAX; B++)
				BEnemy[B]->PaintShot(Gamedc1, Gamedc2, Gamedc3);
			for (int A = 0; A < AENEMYMAX; A++)
				AEnemy[A]->PaintShot(Gamedc1, Gamedc2, Gamedc3);

			//에너미들을 Gamedc1에 그려준다.
			for (int L = 0; L < LENEMYMAX; L++)
				LEnemy[L]->PaintEnmey(Gamedc1, Gamedc2);
			WEnemy->PaintEnmey(Gamedc1, Gamedc2);
			for (int B = 0; B < BENEMYMAX; B++)
				BEnemy[B]->PaintEnmey(Gamedc1, Gamedc2);
			for (int A = 0; A < AENEMYMAX; A++)
				AEnemy[A]->PaintEnmey(Gamedc1, Gamedc2);


			//플레이어 관련을 Gamedc1에 그려준다.
			player->PaintPlayer(Gamedc1, Gamedc2);
			player->PaintPlayerIF(Gamedc1, Gamedc2);

			//GameMap 선들을 그려준다.
			Inter->PaintBackGroundLine(Gamedc1);

			//Gamedc1에 있는 맵을 실제 출력되는 mem1dc에 알맞게 복사한다.

			//위쪽 테두리 복사
			if(GamePageLoading<30)
				//30미만까지는 GamePageLoading의 크기 만큼 복사한다.
				BitBlt(mem1dc, 0, 0, 1280, GamePageLoading, Gamedc1, 0, 0, SRCCOPY);
			else
				//30이상이 되면 다 로딩이 됬기 떄문에 그냥 30의 크기만큼 복사한다.
				BitBlt(mem1dc, 0, 0, 1280, 30, Gamedc1, 0, 0, SRCCOPY);

			//왼쪽 / 오른쪽 테두리 복사
			if (GamePageLoading < 700) {
				//700미만까지는 GamePageLoading의 크기 만큼 복사한다.
				BitBlt(mem1dc, 0, 0, 30, GamePageLoading, Gamedc1, 0, 0, SRCCOPY);
				BitBlt(mem1dc, 1250, 0, 30, GamePageLoading, Gamedc1, ALLMAPX - 30, 0, SRCCOPY);
			}
			else {
				//700이상이 되면 다 로딩이 됬기 떄문에 그냥 700의 크기만큼 복사한다.
				BitBlt(mem1dc, 0, 0, 30, 700, Gamedc1, 0, 0, SRCCOPY);
				BitBlt(mem1dc, 1250, 0, 30, 700, Gamedc1, ALLMAPX - 30, 0, SRCCOPY);
			}
				
			if (GamePageLoading >= 700) {
				//700이상이 되어야만 복사를 시작한다.
				//플레이어 인터페이스 복사
				BitBlt(mem1dc, 0, 700, ScreenX, GamePageLoading - 700, Gamedc1, 0, ALLMAPY - 120, SRCCOPY);

				//인터페이스 오른쪽 테두리 복사
				BitBlt(mem1dc, ScreenX - 30, 700, 30, GamePageLoading - 700, Gamedc1, ALLMAPX - 30, ALLMAPY - 120, SRCCOPY);
			}
			
			if (GamePageLoading >= 30) {
				//30이상이 되어야만 복사를 시작한다.
				//벽 안 복사
				if (GamePageLoading < 700)
					//700미만까지는 GamePageLoading의 크기 만큼 복사한다.
					BitBlt(mem1dc, 30, 30, 1220, GamePageLoading - 30, Gamedc1, camera->GetCLeft(), camera->GetCTop(), SRCCOPY);
				else
					//700이상이 되면 다 로딩이 됬기 떄문에 그냥 670의 크기만큼 복사한다.
					BitBlt(mem1dc, 30, 30, 1220, 670, Gamedc1, camera->GetCLeft(), camera->GetCTop(), SRCCOPY);
			}

			if (LevelTime > 0 && LevelTime <= 10) {
				//0초과 10이하일때
				//LEVEL을 띄워준다.
				wchar_t str[10];
				swprintf_s(str, L"Level %d%d", Inter->GetLevel() / 10, Inter->GetLevel() % 10);
				SetBkMode(mem1dc, TRANSPARENT);
				SetTextColor(mem1dc, RGB(125, 0, 0));
				TextOut(mem1dc, 360, 250, str, 8);
			}
		}
		
		//mem1dc를 hdc로 복사한다.
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
