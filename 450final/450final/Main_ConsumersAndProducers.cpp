//CIS 450 final project - Matt London, Ismaeel Varis
#include <pthread.h>
#include <semaphore.h>
#include <iostream>
#include <random>
using namespace std;

#define NUM_BUFFERS 7
int buffers[NUM_BUFFERS];

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


pthread_t thread1, thread2;
sem_t mutex, empty, full;

/*void fillBuffers()
{
	for (int i = 0; i < NUM_BUFFERS; i++)
	{
		buffers[i] = rand() % 100;
	}
}*/

int main()
{
	sem_init(&mutex, 0, 1);
	sem_init(&empty, 0, NUM_BUFFERS);
	sem_init(&full, 0, 0);

	system("pause");
	return 0;
} 