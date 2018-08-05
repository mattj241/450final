//CIS 450 final project - Matt London, Ismaeel Varis
//#define HAVE_STRUCT_TIMESPEC
#include <pthread.h>
#include <semaphore.h>
#include <iostream>
#include <stdlib.h>     /* srand, rand */
#include <ctime> 
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

void removeFromBuffer(int * value)
{
	if (sizeTracker > 0)
	{
		*value = buffers[*value - 1];
		--sizeTracker;
	}
	else
	{
		cout << "buffer empty" << endl;
	}
}

void * Produce(void * thread)
{
	srand((unsigned)time(0));

	int item = rand() % 7;
	while (true)
	{
		//produce stuff
		sem_wait(&empty);
		pthread_mutex_lock(&mutex);
		insertIntoBuffer(item);
		//cout << "Produced: " << item << " in thread" << *((int *)thread) << endl;
		cout << "Produced: " << item << " in thread " << thread << endl;
		pthread_mutex_unlock(&mutex);
		sem_post(&full);
		
	} 
	//pthread_exit(NULL);
	return Produce;
}

void * Consume(void * thread)
{
	srand((unsigned)time(0));

	int item = rand() % 100;
	//pthread_t * curr = static_cast<pthread_t*>(thread);
	while (true)
	{
		//produce stuff
		sem_wait(&full);
		pthread_mutex_lock(&mutex);
		removeFromBuffer(&item);
		//cout << "Consumed: " << item << " in thread" << *((int *)thread) << endl;
		cout << "Consumed: " << item << " in thread " << thread <<  endl;
		pthread_mutex_unlock(&mutex);
		sem_post(&empty);
	} 
	//pthread_exit(NULL);
	return Consume;
}

int main()
{

	pthread_mutex_init(&mutex, NULL);
	sem_init(&empty, 0, NUM_BUFFERS);
	sem_init(&full, 0, 0);

	for (int i = 0; i < 10; i++)
	{
		pthread_t t;
		pthread_create(&t, NULL, Produce, (void*)(i + 1));
		//printf("Creating Producer %d \n", i + 1);
	}
	for (int i = 0; i < 10; i++)
	{
		pthread_t t;
		pthread_create(&t, NULL, Consume, (void*)(i + 1));
		//printf("Creating Consumer %d \n", i + 1);
	}

	cout << ' ';
	std::getchar();
	return 0;
} 