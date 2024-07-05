#include "root.h"
#include <graphics.h> // 包含图形库头文件
#include "storage.h"
#include "table.h"
#include <windows.h>
#include <wchar.h>
#include <locale.h>
#define ROWS 20
#define COLS 3


// 定义用户信息结构体
static struct UserInfo {
    char* name;
    char* num;
    char* dorm;
    struct UserInfo* next;
};

// Create a new user information node
static UserInfo* createUserNode(const char* name, const char* num,const char* dorm) {
    UserInfo* newUser = (UserInfo*)malloc(sizeof(UserInfo));
    newUser->name = _strdup(name);
    newUser->num = _strdup(num);
    newUser->dorm = _strdup(dorm);
    newUser->next = NULL;
    return newUser;
}

// Free the user information linked list
static void freeUserList(UserInfo* head) {
    UserInfo* current = head;
    while (current != NULL) {
        UserInfo* temp = current;
        current = current->next;
        free(temp->name);
        free(temp->num);
        free(temp->dorm);
        free(temp);
    }
}

// Read user information from an SQLite database and store it in a linked list
static struct UserInfo* readUsersFromDatabase(const char* dbPath)
{
    sqlite3* db;
    char* zErrMsg = 0;
    int rc;
    UserInfo* head = NULL;
    UserInfo* tail = NULL;

    // Open the database
    rc = sqlite3_open(dbPath, &db);
    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return NULL;
    }

    //sqlite3_exec(db, G2U("insert into test values('阿巴','阿巴');"), NULL, NULL, NULL);

    // Execute the SQL query
    const char* sql = "SELECT name, num, dorm FROM DORM";
    sqlite3_stmt* stmt;
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (rc == SQLITE_OK) {
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            const char* name = (const char*)sqlite3_column_text(stmt, 0);//提取数据text,int
            const char* num = (const char*)sqlite3_column_text(stmt, 1);
            const char* dorm = (const char*)sqlite3_column_text(stmt, 2);
            UserInfo* newUser = createUserNode(name, num, dorm);
            if (head == NULL) {
                head = newUser;
            }
            else {
                tail->next = newUser;
            }
            tail = newUser;
        }
    }
    else {
        fprintf(stderr, "Failed to execute statement: %s\n", sqlite3_errmsg(db));
    }

    // Clean up
    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return head;
}

static void drawTable(int x, int y, int width, int height, int rows, int cols) {
    int rowHeight = height / rows;
    int colWidth = width / cols;
    // 绘制表格的线条
    for (int i = 0; i <= rows; i++) {
        line(x, y + i * rowHeight, x + width, y + i * rowHeight);
    }
    for (int i = 0; i <= cols; i++) {
        line(x + i * colWidth, y, x + i * colWidth, y + height);
    }
}

static void fillData(int x, int y, int width, int height, int rows, int cols, const char* data[ROWS][COLS]) {
    int rowHeight = height / rows;
    int colWidth = width / cols;

    // 设置文本颜色为红色
    settextcolor(RED);

    // 设置背景模式为透明
    setbkmode(WHITE);

    // 填充数据
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            int textX = x + j * colWidth + 7; // 5是文本的左边距
            int textY = y + i * rowHeight + 7; // 5是文本的上边距

            outtextxy(textX, textY, data[i][j]);
        }
    }
}


void table2(int current_ROWS) {

    setlocale(LC_ALL, "zh_CN.UTF-8"); // 设置本地化，以支持中文

    const char* dbPath = "D:/database/Users.db";
    UserInfo* users = readUsersFromDatabase(dbPath);

    if (users == NULL) {
        printf("Failed to load user data from database\n");
        return;
    }

    const char* data[ROWS][COLS];
    int row = 0;
    UserInfo* current = users;

    // Move the current pointer to the correct starting position
    for (int i = 0; i < current_ROWS && current != NULL; i++) {
        current = current->next;
    }
    // Fill the data array with the next ROWS entries
    while (current != NULL && row < ROWS) {
        data[row][0] = current->name;
        data[row][1] = current->num;
        data[row][2] = current->dorm;
        current = current->next;
        row++;
    }



    drawTable(390, 110, 610, 490, ROWS, COLS);
    fillData(390, 110, 610, 490, ROWS, COLS, data);

    // Free the user list
    freeUserList(users);
}
