//CIS 450 final project - Matt London, Ismaeel Varis
//#define HAVE_STRUCT_TIMESPEC
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
pthread_mutex_t mutex;
sem_t empty, full;
int sizeTracker;

void insertIntoBuffer(int value)
{
	if (sizeTracker < NUM_BUFFERS)
	{
		buffers[sizeTracker] = value;
		sizeTracker++;
	}
	else
	{
		cout << "buffer full" << endl;
	}
}

void removeFromBuffer(int value)
{
	if (sizeTracker > 0)
	{
		buffers[sizeTracker] = -1;
		--sizeTracker;
	}
	else
	{
		cout << "buffer empty" << endl;
	}
}

void * Produce(pthread_t * thread)
{
	int item = rand() % 100;
	do 
	{
		//produce stuff
		sem_wait(&empty);
		pthread_mutex_lock(&mutex);
		insertIntoBuffer(item);
		cout << "Produced: " << item << " in thread" << *((int*)(thread));
		pthread_mutex_unlock(&mutex);
		sem_post(&full);
		
	} while (true); 
}

void * Consume(pthread_t * thread)
{
	int item = rand() % 100;
	do
	{
		//produce stuff
		sem_wait(&full);
		pthread_mutex_lock(&mutex);
		insertIntoBuffer(item);
		cout << "Consumed: " << item << " in thread" << *((int*)(thread));
		pthread_mutex_unlock(&mutex);
		sem_post(&empty);

	} while (true);
}

int main()
{
	pthread_mutex_init(&mutex, NULL);
	sem_init(&empty, 0, NUM_BUFFERS);
	sem_init(&full, 0, 0);

	pthread_t producerThread, consumerThread;


	system("pause");
	return 0;
} 