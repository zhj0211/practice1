#include <graphics.h>		// 引用图形库头文件
#include <conio.h>
#include <stdio.h>
#include <windows.h> // 包含 Windows API 头文件
#include <easyx.h>  // 包含 easyX 图形库头文件
#include "storage.h"
#include "win.h"
#include <time.h>
#include "root.h"
#include "student.h"

struct Resource
{
	IMAGE img_start[3];
}res;

static void InputUserInfo(char* name, int nameSize, char* key, int keySize) {
	// 弹出输入框，让用户输入用户名和密码
	InputBox(name, nameSize, "请输入用户名: ");
	InputBox(key, keySize, "请输入密码: ");
	int result = storage(name, key);
	if (result == 1) {
		initgraph(1080, 720);
		HWND hwnd = GetHWnd();
		SetWindowPos(hwnd, NULL, 50, 50, 1080, 720, SWP_NOZORDER);
		RECT r = { 0, 0, 1080, 720 };
		drawtext(_T("Login Successfull, welcome to the root-system!"), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		Sleep(2000);
		cleardevice();
		loadimage(res.img_start + 1, "./source/02.jpg", getwidth(), getheight());
		putimage(0, 0, res.img_start + 1);
		root();
		Sleep(2000);
	}
	else if (result == 2) {
		initgraph(1080, 720);
		HWND hwnd = GetHWnd();
		SetWindowPos(hwnd, NULL, 50, 50, 1080, 720, SWP_NOZORDER);
		RECT r = { 0, 0, 1080, 720 };
		drawtext(_T("Login Successfull, welcome to the student-system!"), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		Sleep(2000);
		cleardevice();
		loadimage(res.img_start + 2, "./source/03.jpg", getwidth(), getheight());
		putimage(0, 0, res.img_start + 2);
		student();
		Sleep(2000);
	}
	else {
		initgraph(1080, 720);
		HWND hwnd = GetHWnd();
		SetWindowPos(hwnd, NULL, 100, 100, 639, 479, SWP_NOZORDER);
		RECT r = { 0, 0, 639, 479 };
		drawtext(_T("Login Failed"), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		Sleep(2000);
		closegraph();
	}
}

void res_init(struct Resource* res)
{
	for (int i = 0; i < 3; i++)
	{
		char path[50] = { 0 };
		sprintf(path, "./source/0%d.jpg", i + 1);
		printf("Loading image: %s\n", path); // 添加调试信息
		loadimage(res->img_start + i, path, getwidth(), getheight());
	}
}

int which = 0;

static bool isInRect(ExMessage* msg, int x, int y, int w, int h)
{
	if (msg->x > x && msg->x < x + w && msg->y > y && msg->y < y + h)
	{
		return true;
	}
	return false;
}

void startupScene(ExMessage* msg, char* name, int nameSize, char* key, int keySize)
{
	putimage(0, 0, res.img_start + 0);

	if (which == 0)
	{
		// 点击登录按钮
		if (isInRect(msg, 410, 450, 286, 106) && msg->message == WM_LBUTTONDOWN)
		{
			InputUserInfo(name, nameSize, key, keySize);
		}
	}
}

int main()
{
	system("chcp 65001");
	char name[20];
	char key[20];
	// 绘图窗口初始化
	initgraph(1080, 720);
	// 图像初始化
	res_init(&res);

	RECT r = { 0, 0, 639, 479 };
	LOGFONT f;
	gettextstyle(&f);

	ExMessage msg;

	// 获取窗口句柄
	HWND hwnd = GetHWnd();

	// 使用 Windows API 设置窗口标题
	SetWindowText(hwnd, "西南大学宿舍管理系统");

	while (1)
	{
		// 处理消息 
		if (peekmessage(&msg, EX_MOUSE)) // 检查鼠标消息
		{
			startupScene(&msg, name, sizeof(name), key, sizeof(key));
		}
		Sleep(10); // 添加一个小的延迟，避免CPU占用过高
	}
	return 0;
}


