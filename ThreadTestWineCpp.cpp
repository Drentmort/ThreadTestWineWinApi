#define _CRT_SECURE_NO_WARNINGS

#include <Windows.h>
#include <process.h>
#include <stdio.h>
#include <conio.h>

void StartTest(int threadCount);
void BeginNewThread();
void ExecuteEnterReleaseAction();

DWORD WINAPI TargetTestFunc(LPVOID t);

int main(int argc, char* argv[])
{
	printf("Enter thread count\n");
	unsigned int threadCount = 100;
	scanf("%i", &threadCount);
	StartTest(threadCount);
	_getch();
	return 0;
}

void StartTest(int threadCount) 
{
	for (int i = 0; i < threadCount; i++) 
	{
		BeginNewThread();
	}
}

void BeginNewThread()
{
	HANDLE thread;
	thread = CreateThread(NULL, 0, TargetTestFunc, NULL, 0, NULL);
	printf("Thread created %d \n", GetCurrentThreadId());
}

void ExecuteEnterReleaseAction() 
{
	HANDLE mutex = CreateMutex(NULL,FALSE,NULL);
	if (mutex != NULL) 
	{
		WaitForSingleObject(mutex, INFINITE);
		ReleaseMutex(mutex);
		CloseHandle(mutex);
	}
}

DWORD WINAPI TargetTestFunc(LPVOID t)
{
	ExecuteEnterReleaseAction();
	BeginNewThread();
	ExitThread(0);
}