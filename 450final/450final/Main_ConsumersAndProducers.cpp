//CIS 450 final project - Matt London, Ismaeel Varis
//#define HAVE_STRUCT_TIMESPEC
#include <pthread.h>
#include <semaphore.h>
#include <iostream>
#include <random>
using namespace std;

#define NUM_BUFFERS 7
int buffer[NUM_BUFFERS];

pthread_mutex_t mutex;
sem_t empty, full;
int sizeTracker;

/*
Description: Inserts the parameter value into the main buffer.
Pre: Called in the Produce function by a pthread.
Post: If the buffer was not full, the value is inserted to the main buffer.
*/
void insertIntoBuffer(int value)
{
	if (sizeTracker < NUM_BUFFERS)
	{
		buffer[sizeTracker] = value;
		sizeTracker++;
	}
	else
	{
		cout << "buffer full" << endl;
	}
}

/*
Description: Removes the parameter value into the main buffer.
Pre: Called in the Consume function by a pthread.
Post: If the buffer was not empty, the value is removed to the main buffer.
*/
void removeFromBuffer(int index)
{
	if (sizeTracker > 0)
	{
		//*value = buffer[*value - 1];
		buffer[index] = -1;
		--sizeTracker;
	}
	else
	{
		cout << "buffer empty" << endl;
	}
}

/*
Description: A producer thread lives in this function endlessly, simply calls insert
Pre:
Post:
*/
void * Produce(void * thread)
{
	//This random generation code block was made with help from: https://stackoverflow.com/questions/4926622/how-to-generate-different-random-numbers-in-a-loop-in-c
	// Random seed
	random_device rd;

	// Initialize Mersenne Twister pseudo-random number generator
	mt19937 gen(rd());

	// Generate pseudo-random numbers
	// uniformly distributed in range (1, 100)
	uniform_int_distribution<> dis(1, 100);
	///////////////////////////////////

	int item = dis(gen);

	while (true)
	{
		sem_wait(&empty);
		pthread_mutex_lock(&mutex);
		insertIntoBuffer(item);
		cout << "Produced: " << item << " into index " << sizeTracker - 1 << " with thread " << (int)thread << endl;
		pthread_mutex_unlock(&mutex);
		sem_post(&full);
	} 
}

void * Consume(void * thread)
{
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<> dis(0, sizeTracker);
	int itemIndex = dis(gen);

	while (true)
	{
		sem_wait(&full);
		pthread_mutex_lock(&mutex);
		cout << "Consumed: " << buffer[itemIndex] << " in index " << itemIndex << " with thread " << (int)thread << endl;
		removeFromBuffer(buffer[itemIndex]);
		pthread_mutex_unlock(&mutex);
		sem_post(&empty);
	} 
}

int main()
{

	pthread_mutex_init(&mutex, NULL);
	sem_init(&empty, 0, NUM_BUFFERS);
	sem_init(&full, 0, 0);

	for (int i = 0; i < 10; i++)
	{
		pthread_t Producer;
		pthread_create(&Producer, NULL, Produce, (void*)(i + 1));
	}
	for (int i = 0; i < 10; i++)
	{
		pthread_t Consumer;
		pthread_create(&Consumer, NULL, Consume, (void*)(i + 1));
	}

	system("pause");
	return 0;
} 