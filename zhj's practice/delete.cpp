#include "table.h"


int deleteData(sqlite3* db,const char name) {
    sqlite3_stmt* stmt;
    const char* sql = "DELETE FROM DORM WHERE name = ?";
    int rc;

    // 准备SQL语句
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
        return rc;
    }

    // 绑定参数
    sqlite3_bind_text(stmt, 1, &name, - 1, SQLITE_STATIC);

    // 执行SQL语句
    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
    }
    else {
        printf("Data deleted successfully\n");
    }

    // 清理
    sqlite3_finalize(stmt);
    return rc;
}