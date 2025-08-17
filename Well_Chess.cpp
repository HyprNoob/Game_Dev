/*
���ļ�Ϊѧϰ����EasyXʱ����Ŀ�ļ����ο���BiliBili Up: Voidmatrix�Ľ̳̣�
�������㿪ʼ��C++��Ϸ������EasyX��������� | ��������ƶ���С�� 
https://www.bilibili.com/video/BV1iQ4y1s7Qj ������ѧ��;��
*/


#include <graphics.h> //����ͼ�ο�ͷ�ļ�

char board_data[3][3] =
{
	{ '-', '-', '-' },
	{ '-', '-', '-' },
	{ '-', '-', '-' }
};

char current_piece = 'O';

// ʤ����⺯�������boolֵ
bool CheckWin(char c) {
	if (board_data[0][0] == c && board_data[0][1] == c && board_data[0][2] == c)
		return true;
	if (board_data[1][0] == c && board_data[1][1] == c && board_data[1][2] == c)
		return true;
	if (board_data[2][0] == c && board_data[2][1] == c && board_data[2][2] == c)
		return true;
	if (board_data[0][0] == c && board_data[1][0] == c && board_data[2][0] == c)
		return true;
	if (board_data[0][1] == c && board_data[1][1] == c && board_data[2][1] == c)
		return true;
	if (board_data[0][2] == c && board_data[1][2] == c && board_data[2][2] == c)
		return true;
	if (board_data[0][0] == c && board_data[1][1] == c && board_data[2][2] == c)
		return true;
	if (board_data[0][2] == c && board_data[1][1] == c && board_data[2][0] == c)
		return true;

	return false;
}

// ƽ�ּ�⺯�������boolֵ
bool CheckDraw() {
	for (size_t i = 0; i < 3; i++) {
		for (size_t j = 0; j < 3; j++) {
			if (board_data[i][j] == '-') {
				return false;
			}
		}
	}

	return true;
}

// ����������
void DrawBoard() {
	line(0, 240, 720, 240);
	line(0, 480, 720, 480);
	line(240, 0, 240, 720);
	line(480, 0, 480, 720);

}

// �������Ӻ���
void DrawPiece() {
	for (size_t i = 0; i < 3; i++) {
		for (size_t j = 0; j < 3; j++) {
			switch (board_data[i][j]) {
			case 'O':
				circle(240 * j + 120, 240 * i + 120, 120);
				break;
			case 'X':
				line(240 * j, 240 * i, 240 * (j + 1), 240 * (i + 1));
				line(240 * (j + 1), 240 * i, 240 * j, 240 * (i + 1));
				break;
			case '-':
				break;
			}
		}
	}
}

// ������ʾ��Ϣ
void DrawTipText() {
	static TCHAR str[64];
	_stprintf_s(str, _T("��ǰ��������%c"), current_piece);

	settextcolor(RGB(225, 175, 45));
	outtextxy(0, 0, str);
}

int main() 
{
	initgraph(720,720); //������ͼ���ڣ�720x720

	bool running = true;

	ExMessage msg;

	BeginBatchDraw();

	while (running) {

		DWORD start_time = GetTickCount();

		while (peekmessage(&msg)) {
			// ���������������Ϣ

			if (msg.message == WM_LBUTTONDOWN) {
				// ������λ��

				int x = msg.x;
				int y = msg.y;

				int index_x = x / 240;
				int index_y = y / 240;

				// ��������
				
				if (board_data[index_y][index_x] == '-') {
					board_data[index_y][index_x] = current_piece;

					//�л���������

					if (current_piece == 'O')
						current_piece = 'X';
					else
						current_piece = 'O';
				}
			}

		}

		cleardevice();

		DrawBoard();
		DrawPiece();
		DrawTipText();

		FlushBatchDraw();

		if (CheckWin('X')) {
			MessageBox(GetHWnd(), _T("X ���ʤ��"), _T("��Ϸ����"), MB_OK);
			running = false;
		}
		else if (CheckWin('O')) {
			MessageBox(GetHWnd(), _T("O ���ʤ��"), _T("��Ϸ����"), MB_OK);
			running = false;
		}
		else if (CheckDraw()) {
			MessageBox(GetHWnd(), _T("ƽ��!"), _T("��Ϸ����"), MB_OK);
			running = false;
		}

		DWORD end_time = GetTickCount();
		DWORD delta_time = end_time - start_time;

		if (delta_time < 1000 / 60) {
			Sleep(1000 / 60 - delta_time);
		}

	}

	EndBatchDraw();

	return 0;
}