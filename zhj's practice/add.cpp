#include "table.h"
#include "pullrequest.h"

int add(sqlite3* db, const char* name, const char* num, const char* key, const char* dorm) {
    sqlite3_stmt* stmt;
    const char* sql = "INSERT INTO DORM (name, num, key, dorm) VALUES (?, ?, ?, ?)";
    int rc;

    // 准备SQL语句
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
        return rc;
    }

    // 绑定参数
    sqlite3_bind_text(stmt, 1, name, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, num, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 3, key, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 4, dorm, -1, SQLITE_STATIC);

    // 执行SQL语句
    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
    }
    else {
        printf("Data inserted successfully\n");
    }
    // 清理
    sqlite3_finalize(stmt);
    return rc;
}
