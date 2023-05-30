#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<Windows.h>
#include<string.h>
HANDLE mutex_lock = 0;
void printf_log(char* str)
{
	int str_len = strlen(str);
	for (int i = 0; i < str_len; i++) {
		printf("%c", str[i]);
		Sleep(100);
	}
}

DWORD WINAPI function(LPVOID Parameter)
{
	char* arr = ("Function is ongoing\r\n");
	while (1)
	{
		WaitForSingleObject(mutex_lock, 10000);
		printf_log(arr);
		ReleaseMutex(mutex_lock);
		Sleep(800);
	}
}


int main()
{
	HANDLE Thread_a = CreateThread(NULL,
		1024,
		function,
		NULL,0,NULL);
	mutex_lock = CreateMutex(NULL,0,NULL);
	char* arr = ("Main is ongoing\r\n");
	while (1) {
		WaitForSingleObject(mutex_lock, 10000);
		printf_log(arr);
		ReleaseMutex(mutex_lock);
		Sleep(800);
	}
}