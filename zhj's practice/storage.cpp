#include "storage.h"
#include <locale.h>

// 定义用户信息结构体
static struct UserInfo {
    char* name;
    char* num;
    char* key;
    char* dorm;
    struct UserInfo* next;
};

// Create a new user information node
static UserInfo* createUserNode(const char* name, const char* num, const char* key, const char* dorm) {
    UserInfo* newUser = (UserInfo*)malloc(sizeof(UserInfo));
    newUser->name = _strdup(name);
    newUser->num = _strdup(num);
    newUser->key = _strdup(key);
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
        free(temp->key);
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

    // Execute the SQL query
    const char* sql = "SELECT name, num, key, dorm FROM DORM";
    sqlite3_stmt* stmt;
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (rc == SQLITE_OK) {
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            const char* name = (const char*)sqlite3_column_text(stmt, 0);//提取数据text,int
            const char* num = (const char*)sqlite3_column_text(stmt, 1);
            const char* key = (const char*)sqlite3_column_text(stmt, 2);
            const char* dorm = (const char*)sqlite3_column_text(stmt, 3);
            UserInfo* newUser = createUserNode(name, num, key, dorm);
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

// Search for a user in the linked list by name and key
static int search(UserInfo* head, const char* name, const char* key) {
    UserInfo* current = head;
    while (current != NULL)
    {
        if (strcmp(current->name, name) == 0 && strcmp(current->key, key) == 0)
        {
            if (strcmp(current->name, "root") == 0)
            {
                // Match found for root
                return 1;
            }
            else
            {
                // Match found for non-root
                return 2;
            }
        }
        current = current->next;
    }
    // Match not found
    return 0;
}

int storage(const char* searchName,const char* searchKey) {
    UserInfo* head = NULL;
    const char* dbPath = "D:/database/Users.db";

    // Read user information from the database
    UserInfo* users = readUsersFromDatabase(dbPath);

    // Print the user information in the linked list
    UserInfo* current = users;
    while (current != NULL) {
        printf("Name: %s, Num: %d, Key: %s, Dorm: %s\n",
            current->name, current->num, current->key, current->dorm);
        current = current->next;
    }


    // Call the search function and check the result
    if (search(users, searchName, searchKey)==1) {
        
        return 1;
    }
    else if (search(users, searchName, searchKey)==2) {
        return 2;
    }
    else {
        // 释放链表
        freeUserList(users);
        return 0;
    }
}