#pragma once
// delete.h
#ifndef DELETE_H
#define DELETE_H
#include <stdio.h>
#include <sqlite3.h>
#include <stdlib.h>
#include <string.h>
#include <graphics.h>		// 引用图形库头文件
#include <conio.h>
#include <stdio.h>
#include <windows.h> // 包含 Windows API 头文件
#include <easyx.h>   // 包含 easyX 图形库头文件
#include "storage.h"

int deleteData(sqlite3* db,char name);

#endif // DELETE_H