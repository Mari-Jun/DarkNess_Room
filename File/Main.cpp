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
		//사운드 세팅
		SoundInit();
		//로딩 페이지에 필요한 객체들 만들기
		CreateLoadingPage();
		//Loading 타이머 세팅
		SetTimer(hwnd, 1, 10, NULL);
		break;
	case WM_GETMINMAXINFO:
		//화면 고정
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
			//임시 코드
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
					//Page2는 HelpPage이다.

					//버튼 클릭 사운드 재생
					PlayButtonClickSound();

					//StartPage 삭제
					DeleteStartPage(&Click);

					//HelpPage 생성
					CreateHelpPage(&Help);
				}
				else if (Page == 3) {
					//Page3은 GameLoading페이지이다.

					//버튼 클릭 사운드 재생
					PlayButtonClickSound();

					Page = 1;

					//StartCreate역시 페이드 아웃 구현을 위해서 false로 바꿔준다.
					StartCreate = false;

					//StartBitPade와 StartTextPade가 번개효과 등으로 Pade값이 17이 아닐 경우를 대비하여 17로 만들어준다.
					StartBitPade = 17;
					StartTextPade = 17;

					//번개 타이머 제거
					KillTimer(hwnd, 3);

					//StartPage 페이드 아웃 타이머 생성
					//GamePageLoading 타이머이기도 함
					SetTimer(hwnd, 4, 10, NULL);
				}
				else if (Page == 4) {
					//종료
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
				//StartPage에서의 마우스 왼쪽 클릭
				StartClickCheck(Click, My, Mx);
			}
			else if (Page == 2) {
				//HelpPage에서의 마우스 왼쪽 클릭
				HelpClickCheck(Help, My, Mx);
			}
		}
		InvalidateRgn(hwnd, NULL, FALSE);
		break;
	case WM_MOUSEMOVE:
		Mx = LOWORD(lParam);
		My = HIWORD(lParam);
		if (Page == 1) {
			//StartPage에서의 마우스 이동
			MouseUpCheck(Click, My, Mx);
		}
		else if (Page == 2) {
			//HelpPage에서의 마우스 이동
			MouseUpCheck(Help, My, Mx);
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
		
				//StartPage 페이드 타이머 생성
				SetTimer(hwnd, 2, 40, NULL);

				//StartPage생성				
				Page = 1;
				CreateStartPage(&Click);
			}
			break;
		case 2:
			//StartPage화면 페이드 시작
			if (StartBitPade < 17)
				StartBitPade++;
			if (StartBitPade >= 10) {
				//StartPage글자 페이드 시작
				StartTextPade++;
				if (StartTextPade == 17) {
	
					//배경 BGM 재생
					PlayStartBKSound();

					//StartPage페이드가 완료되었으니 StartCreate를 true로 바꿔준다.
					StartCreate = true;

					//StartPage 페이드 타이머 제거
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
				StartBitPade = 13;
			}
			if (LightCount == 15 || LightCount == 33) {
				StartBitPade = 17;
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
				StartBitPade--;
				StartTextPade--;

				if ((StartBitPade == 0) && (StartTextPade == 0)) {
					//StartPage 삭제
					DeleteStartPage(&Click);

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
					StartPageSoundStop();


					//LoadingPage생성
					CreateLoadingPage();
				}
				LoadingCount++;

				if (LoadingCount == 100) {
					Page = 10;

					player = new Player(640, 450);

					CreateCamera(&camera);

					CreateInterface();

					PlayGameBKSound();

					//GamePageLoading 타이머 삭제
					KillTimer(hwnd, 4);

					//게임 Timer 생성
					SetTimer(hwnd, 10, 10, NULL);
				}
			}
			break;
		case 10:
			//Start버튼을 눌렀을때 작동한다.
			//플레이어 이동 함수 호출
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


		//mem1dc에 더블버퍼링으로 그려준다

		if (Page == 0) {
			PaintLoadingPage(mem1dc, LoadingCount);
		}
		else if (Page == 1 || Page == 2) {
			StartPageBit1 = (HBITMAP)LoadImage(NULL, _T(".\\BitMap\\StartBackGround.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
			StartPageBit2 = CreateCompatibleBitmap(hdc, ScreenX, ScreenY);

			//StartCreate가 True라면 StartPage가 완성된 상태이고 False라면 페이드 아웃, 페이드 인등 미완성된 상태이다.
			if(StartCreate)
				PatBlt(mem1dc, 0, 0, ScreenX, ScreenY, WHITENESS);

			//mem2dc = 비트맵
			mem2dc = CreateCompatibleDC(hdc);
			//mem3dc = 글씨
			mem3dc = CreateCompatibleDC(hdc);		

			//StartPage 배경을 그리기 위한 더블버퍼링 작업
			OldStartPageBit1 = (HBITMAP)SelectObject(mem2dc, StartPageBit1);
			
		
			//알파블렌딩 (투명화)를 위한 작업
			BLENDFUNCTION bf1;
			bf1.AlphaFormat = AC_SRC_ALPHA;
			bf1.BlendOp = AC_SRC_OVER;
			bf1.BlendFlags = 0;
			bf1.SourceConstantAlpha = StartBitPade * 15;
			
			//알파 블렌딩으로 페이드인, 페이드 아웃 구현
			AlphaBlend(mem1dc, 0, 0, ScreenX, ScreenY, mem2dc, 0, 0,ScreenX, ScreenY, bf1);

			SelectObject(mem2dc, OldStartPageBit1);
			DeleteObject(StartPageBit1);
			DeleteDC(mem2dc);


			//mem3dc를 선택
			OldStartPageBit2 = (HBITMAP)SelectObject(mem3dc, StartPageBit2);

			//mem1dc에 그려진걸 mem3dc에 복사한다.
			BitBlt(mem3dc, 0, 0, ScreenX, ScreenY, mem1dc, 0, 0, SRCCOPY);

			//텍스트의 배경을 투명한 색으로 지정함.
			SetBkMode(mem3dc, TRANSPARENT);

			//mem3dc에 Page들을 Paint한다.
			if (Page == 1) {
				PaintStartPage(mem3dc, Click);
			}
			else {
				Helpdc1 = CreateCompatibleDC(mem3dc);
				PaintHelpPage(mem3dc, Helpdc1, Help);
				DeleteObject(Helpdc1);
			}
		

			//알파블렌딩 (투명화)를 위한 작업
			BLENDFUNCTION bf2;
			bf2.AlphaFormat = 0;
			bf2.BlendOp = AC_SRC_OVER;
			bf2.BlendFlags = 0;
			bf2.SourceConstantAlpha = StartTextPade * 15;

			//알파 블렌딩으로 페이드인, 페이드 아웃 구현
			AlphaBlend(mem1dc, 0, 0, ScreenX, ScreenY, mem3dc, 0, 0, ScreenX, ScreenY, bf2);

			SelectObject(mem3dc, OldStartPageBit2);
			DeleteObject(StartPageBit2);
			DeleteDC(mem3dc);
		}
		else if (Page == 3) {
			PaintLoadingPage(mem1dc, LoadingCount * 2);
		}
		else if (Page == 10) {
			//화면 인터페이스 구현을 위한 Gamedc1 선언
			Gamedc1 = CreateCompatibleDC(hdc);

			GamePlayBit1 = CreateCompatibleBitmap(hdc, ALLMAPX, ALLMAPY);

			OldGamePlayBit1 = (HBITMAP)SelectObject(Gamedc1, GamePlayBit1);

			//Gamedc1에 GameMap을 그려준다.
			PaintBackGround(Gamedc1);
			player->PaintPlayer(Gamedc1);

			//Gamedc1에 있는 맵을 실제 출력되는 mem1dc에 알맞게 복사한다.

			//테두리 복사
			BitBlt(mem1dc, 0, 0, 1280, 30, Gamedc1, 0, 0, SRCCOPY);
			BitBlt(mem1dc, 0, 0, 30, 700, Gamedc1, 0, 0, SRCCOPY);
			BitBlt(mem1dc, 1250, 0, 30, 700, Gamedc1, ALLMAPX - 30, 0, SRCCOPY);

			//플레이어 인터페이스 복사
			BitBlt(mem1dc, 0, 700, ScreenX, 120, Gamedc1, 0, ALLMAPY - 120, SRCCOPY);

			//벽 안 복사
			BitBlt(mem1dc, 30, 30, 1220, 670, Gamedc1, camera->GetCLeft(), camera->GetCTop(), SRCCOPY);
			//뒤쪽 30은 플레이어에 따라 이동되게 바꿔야함


			//삭제
			DeleteObject(SelectObject(Gamedc1, OldGamePlayBit1));
			DeleteObject(Gamedc1);
		}
		
		//mem1dc를 hdc로 복사한다.
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