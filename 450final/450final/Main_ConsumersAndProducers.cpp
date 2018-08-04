//CIS 450 final project - Matt London, Ismaeel Varis
#include <pthread.h>
#include <semaphore.h>
#include <iostream>
#include <random>
using namespace std;

#define NUM_BUFFERS 7

/*
Good viewing material:
https://www.youtube.com/watch?v=eRfOrgchJZQ

From textbook:

int n; //where n = # of buffers (7 in our case)
semaphore mutex = 1;
semaphore empty = n;
semaphore full = 0

//Consumer process
do { 
wait(full);
wait(mutex);
. . .
remove an item from buffer to next consumed
. . .
signal(mutex);
signal(empty);
. . .
consume the item in next consumed 
. . .
} while (true);

//Producer process
do {
wait(empty);
wait(mutex);
. . .
add next process to buffer
. . .
signal(mutex);
signal(full);
. . .
produce the item in next process
. . .
} while (true);*/

int buffers[NUM_BUFFERS];

pthread_t thread1, thread2;
sem_t mutex, empty, full;

//int sem_init(*mutex, NULL, 1);

/*void fillBuffers()
{
	for (int i = 0; i < NUM_BUFFERS; i++)
	{
		buffers[i] = rand() % 100;
	}
}*/

int main()
{
	system("pause");
	return 0;
} 