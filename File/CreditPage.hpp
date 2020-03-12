#pragma once
#include <windows.h>

//CreditPage���� ���Ǵ� �͵�

static HFONT CreditPageFont1;
static HFONT CreditPageFont2;
static HFONT CreditPageFont3;

class CreditPage {
public:
	explicit CreditPage(int B);

	const int GetBackClick() const;											//BackClick���� ��´�.

	const bool BackRange(const int y, const int x) const;					//Ŭ�� ���� Ȯ�� �Լ�

	void ChangeBackClick(const int Num);									//BackClick ����

	void BackClickCheck(const int y, const int x);							//LBUTTON_DOWN�� �� ȣ���ϴ� MainRange()�� üũ�ϴ� �Լ�
	const int ChangeCreditPage(const int y, const int x);						//LBUTTON_UP�� �� ȣ���ϴ� Page�� �ٲ��ִ� �Լ�
	void MouseUpCheck(const int y, const int x);							//MOUSEMOVE�� �� ȣ���ϴ� ��ư ���� �ִ����� Ȯ���ϴ� �Լ�

	void PaintCreditPage(HDC hdc);

private:
	int BackClick;
};

void CreateCreditPage(CreditPage** Credit);
void DeleteCreditPage(CreditPage** Credit);

