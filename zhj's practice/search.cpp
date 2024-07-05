#include <sqlite3.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <graphics.h>

// 回调函数，用于处理查询结果
static int callback(void* data, int argc, char** argv, char** azColName) {
    for (int i = 0; i < argc; i++) {
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }
    printf("\n");
    return 0;
}

// 根据学生姓名查找学生信息
static int searchByName(sqlite3* db, const char* name,char* num,char* dorm) {
    char* zErrMsg = 0;
    int rc;
    char sql[256];

    // 构建 SQL 查询语句
    snprintf(sql, sizeof(sql), "SELECT * FROM DORM WHERE name = '%s';", name);

    // 准备结果数组
    char* result[2] = { NULL, NULL };

    // 执行 SQL 查询
    rc = sqlite3_exec(db, sql, callback, result, &zErrMsg);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
        return 0;
    }
    else {
        printf("Search completed successfully.\n");
        num = result[0];
        dorm = result[1];
        return 1;
    }
}

int search(char* name) {
    sqlite3* db;
    int rc;

    char* num = NULL;
    char* dorm = NULL;

    // 打开数据库
    rc = sqlite3_open("D:/database/Users.db", &db);
    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }

    if (name != NULL) {
        // 根据学生姓名查找学生信息

        if (searchByName(db, name,num,dorm) != 0)
        {
            cleardevice();
            char str[100];
            sprintf(str, "Search result for %s, num: %s,dorm: %s", name,num,dorm);
            outtextxy(100, 100, str);
            Sleep(2000);
        }
    }
    else {
        fprintf(stderr, "Failed to read input.\n");
    }

    // 关闭数据库
    sqlite3_close(db);
    return 0;
}
