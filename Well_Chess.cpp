/*
本文件为学习复现EasyX时的项目文件，参考自BiliBili Up: Voidmatrix的教程：
【【从零开始的C++游戏开发】EasyX开发环境搭建 | 跟随鼠标移动的小球】 
https://www.bilibili.com/video/BV1iQ4y1s7Qj 仅作教学用途。
*/


#include <graphics.h> //引用图形库头文件

char board_data[3][3] =
{
	{ '-', '-', '-' },
	{ '-', '-', '-' },
	{ '-', '-', '-' }
};

char current_piece = 'O';

// 胜负检测函数，输出bool值
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

// 平局检测函数，输出bool值
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

// 绘制网格函数
void DrawBoard() {
	line(0, 240, 720, 240);
	line(0, 480, 720, 480);
	line(240, 0, 240, 720);
	line(480, 0, 480, 720);

}

// 绘制棋子函数
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

// 绘制提示信息
void DrawTipText() {
	static TCHAR str[64];
	_stprintf_s(str, _T("当前棋子类型%c"), current_piece);

	settextcolor(RGB(225, 175, 45));
	outtextxy(0, 0, str);
}

int main() 
{
	initgraph(720,720); //创建绘图窗口，720x720

	bool running = true;

	ExMessage msg;

	BeginBatchDraw();

	while (running) {

		DWORD start_time = GetTickCount();

		while (peekmessage(&msg)) {
			// 检查鼠标左键按下消息

			if (msg.message == WM_LBUTTONDOWN) {
				// 计算点击位置

				int x = msg.x;
				int y = msg.y;

				int index_x = x / 240;
				int index_y = y / 240;

				// 尝试落子
				
				if (board_data[index_y][index_x] == '-') {
					board_data[index_y][index_x] = current_piece;

					//切换棋子类型

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
			MessageBox(GetHWnd(), _T("X 玩家胜利"), _T("游戏结束"), MB_OK);
			running = false;
		}
		else if (CheckWin('O')) {
			MessageBox(GetHWnd(), _T("O 玩家胜利"), _T("游戏结束"), MB_OK);
			running = false;
		}
		else if (CheckDraw()) {
			MessageBox(GetHWnd(), _T("平局!"), _T("游戏结束"), MB_OK);
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