#include <graphics.h> // 包含图形库头文件
#include "student.h"
#include "storage.h"
#include "table.h"
#include "pullrequest.h"
#include "add.h"
#include "delete.h"
#include "search.h"
#include "table2.h"

static struct Resource
{
    IMAGE img_start1[3];
}res1;

static void res_init(struct Resource* res1)
{
    for (int i = 0; i < 3; i++)
    {
        char path[50] = { 0 };
        sprintf(path, "./source/0%d.jpg", i + 1);
        printf("Loading image: %s\n", path); // 添加调试信息
        loadimage(res1->img_start1 + i, path, getwidth(), getheight());
    }
}

static bool isInRect(ExMessage* msg, int x, int y, int w, int h)
{
    if (msg->x > x && msg->x < x + w && msg->y > y && msg->y < y + h)
    {
        return true;
    }
    return false;
}

static void InputUserInfo1(char* name, int nameSize, char* key, char* num, char* dorm) {
    // 弹出输入框，让用户输入用户名和密码
    InputBox(name, nameSize, "请输入用户名: ");
    InputBox(num, 15, "请输入学号: ");
    InputBox(key, 5, "请输入密码: ");
    InputBox(dorm, 1, "请输入宿舍代号: ");
}

static void InputUserInfo2(char* name) {
    // 弹出输入框，让用户输入用户名和密码
    InputBox(name, 20, "请输入用户名: ");
}

void student()
{
    sqlite3* db1;
    static int rc1;

    // 打开数据库
    rc1 = sqlite3_open("D:/database/Users.db", &db1);
    if (rc1 != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db1));
        sqlite3_close(db1);
        return;
    }

    res_init(&res1);
    ExMessage msg1;
    int current_index = 0;
    char name[20], key[5], num[15], dorm[2];

    while (1) {
        if (peekmessage(&msg1, EX_MOUSE) && msg1.message == WM_LBUTTONDOWN) {
            if (isInRect(&msg1, 768, 636, 80, 54)) {
                current_index++;
                if (current_index > 4) current_index = 0;
                cleardevice();
                putimage(0, 0, res1.img_start1 + 2); // 显示背景图像
                table2(20 * current_index);
            }
            else if (isInRect(&msg1, 520, 636, 80, 54)) {
                current_index--;
                if (current_index < 0) current_index = 4;
                cleardevice();
                putimage(0, 0, res1.img_start1 + 2); // 显示背景图像
                table2(20 * current_index);
            }
            else if (isInRect(&msg1, 970, 0, 110, 92)) {
                closegraph();
                break;
            }
            else if (isInRect(&msg1, 104, 123, 260, 62))
            {
                InputUserInfo2(name);
                search(name);
                cleardevice();
                putimage(0, 0, res1.img_start1 + 2); // 显示背景图像
                table2(20 * current_index);
            }
            else if (isInRect(&msg1, 257, 210, 260, 62))
            {
                InputUserInfo1(name, sizeof(name), key, num, dorm);
                PullRequest(name, key, num, dorm);
                cleardevice();
                putimage(0, 0, res1.img_start1 + 2); // 显示背景图像
                table2(20 * current_index);
            }
            else if (isInRect(&msg1, 104, 385, 260, 62))
            {
                InputUserInfo1(name, sizeof(name), key, num, dorm);
                PullRequest(name, key, num, dorm);
                cleardevice();
                putimage(0, 0, res1.img_start1 + 2); // 显示背景图像
                table2(20 * current_index);
            }
            else if (isInRect(&msg1, 104, 517, 260, 62))
            {
                cleardevice();
                outtextxy(100, 100, "警钟长鸣");
                outtextxy(100, 150, "西南大学紧急电话：");
                outtextxy(100, 200, "保卫处：023-68251110");
                outtextxy(100, 250, "校医院：023-68251120");
                Sleep(4000);
                putimage(0, 0, res1.img_start1 + 2); // 显示背景图像
                table(20 * current_index);
                
            }
        }
        Sleep(10);
    }

    sqlite3_close(db1);
}
