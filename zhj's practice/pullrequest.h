#pragma once
// storage.h
#ifndef PULLREQUEST_H
#define PULLREQUEST_H
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

int PullRequest(char* name, char* key, const char* data1, const char* data2);

#endif // PULLREQUEST_H