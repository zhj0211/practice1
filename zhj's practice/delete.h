#pragma once
// delete.h
#ifndef DELETE_H
#define DELETE_H
#include <stdio.h>
#include <sqlite3.h>
#include <stdlib.h>
#include <string.h>
#include <graphics.h>		// ����ͼ�ο�ͷ�ļ�
#include <conio.h>
#include <stdio.h>
#include <windows.h> // ���� Windows API ͷ�ļ�
#include <easyx.h>   // ���� easyX ͼ�ο�ͷ�ļ�
#include "storage.h"

int deleteData(sqlite3* db,char name);

#endif // DELETE_H