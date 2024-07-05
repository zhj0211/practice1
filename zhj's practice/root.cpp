#include <graphics.h> // 包含图形库头文件
#include "root.h"
#include "storage.h"
#include "table.h"
#include "table2.h"
#include "pullrequest.h"
#include "add.h"
#include "delete.h"
#include "search.h"

static struct Resource
{
    IMAGE img_start[3];
}res;

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

static void res_init(struct Resource* res)
{
    for (int i = 0; i < 3; i++)
    {
        char path[50] = { 0 };
        sprintf(path, "./source/0%d.jpg", i + 1);
        printf("Loading image: %s\n", path); // 添加调试信息
        loadimage(res->img_start + i, path, getwidth(), getheight());
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

void root()
{
    sqlite3* db;
    static int rc;

    // 打开数据库
    rc = sqlite3_open("D:/database/Users.db", &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return;
    }

    res_init(&res);
    ExMessage msg;
    int current_index = 0;
    char name[20], key[5], num[15], dorm[2];

    while (1) {
        if (peekmessage(&msg, EX_MOUSE) && msg.message == WM_LBUTTONDOWN) {
            if (isInRect(&msg, 768, 636, 80, 54)) {
                current_index++;
                if (current_index > 4) current_index = 0;
                cleardevice();
                putimage(0, 0, res.img_start + 1); // 显示背景图像
                table(20 * current_index);
            }
            else if (isInRect(&msg, 520, 636, 80, 54)) {
                current_index--;
                if (current_index < 0) current_index = 4;
                cleardevice();
                putimage(0, 0, res.img_start + 1); // 显示背景图像
                table(20 * current_index);
            }
            else if (isInRect(&msg, 970, 0, 110, 92)) {
                closegraph();
                break;
            }
            else if (isInRect(&msg, 104, 123, 260, 62))
            {
                InputUserInfo1(name, sizeof(name), key, num, dorm);
                add(db, name, key, num, dorm);
                cleardevice();
                putimage(0, 0, res.img_start + 1); // 显示背景图像
                table(20 * current_index);
            }
            else if (isInRect(&msg, 257, 210, 260, 62))
            {
                InputUserInfo2(name);
                deleteData(db, *name);
                cleardevice();
                putimage(0, 0, res.img_start + 1); // 显示背景图像
                table(20 * current_index);
            }
            else if (isInRect(&msg, 104, 385, 260, 62))
            {
                InputUserInfo1(name, sizeof(name), key, num, dorm);
                PullRequest(name, key, num, dorm);
                cleardevice();
                putimage(0, 0, res.img_start + 1); // 显示背景图像
                table(20 * current_index);
            }
            else if (isInRect(&msg, 104, 517, 260, 62))
            {
                InputUserInfo2(name);
                search(name);
                cleardevice();
                putimage(0, 0, res.img_start + 1); // 显示背景图像
                table(20 * current_index);
            }
        }
        Sleep(10);
    }
    sqlite3_close(db);
}
