#include <stdio.h>
#include <sqlite3.h>

// 定义一个回调函数，虽然在这个示例中不会用到，但SQLite API需要它
int callback(void* NotUsed, int argc, char** argv, char** azColName) {
    return 0;
}

// 修改提交表的数据
int pullrequest(sqlite3* db, char* name,const char* key, const char* newData1, const char* newData2) {
    sqlite3_stmt* stmt;
    const char* sql = "UPDATE DORM SET key = ?, num = ?,dorm = ? WHERE name = ?";
    int rc;

    // 准备SQL语句
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
        return rc;
    }

    // 绑定参数
    sqlite3_bind_text(stmt, 1, key, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, newData1, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 3, newData2, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 4, name, -1, SQLITE_STATIC);

    // 执行SQL语句
    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
    }
    else {
        printf("Data updated successfully\n");
    }

    // 清理
    sqlite3_finalize(stmt);
    return rc;
}

int PullRequest(char* name, char* key,const char* data1, const char* data2) {
    sqlite3* db;
    int rc;

    // 打开数据库
    rc = sqlite3_open("D:/database/Users.db", &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }

    // 调用pullrequest函数修改数据
    rc = pullrequest(db, name, key,data1, data2);
    if (rc != SQLITE_DONE) {
        fprintf(stderr, "Failed to update data\n");
    }

    // 关闭数据库
    sqlite3_close(db);
    return 0;
}