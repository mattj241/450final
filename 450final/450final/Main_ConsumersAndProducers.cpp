/*
CIS 450 final project
Matt London, Ismaeel Varis
Dr. Ali Elkateeb

Demonstration in correct use of semaphores and a mutex to handle critical component of code over numerous threads.
The libraries pthread.h and semaphore.h from POSIX were used.
*/


//#define HAVE_STRUCT_TIMESPEC
#include <pthread.h>
#include <semaphore.h>
#include <iostream>
#include <random>
#include <Windows.h>
using namespace std;

#define NUM_BUFFERS 7 //From assignment specification
//int buffer[NUM_BUFFERS] = { -1, -1, -1, -1, -1, -1, -1 };
int buffer[NUM_BUFFERS] = { 0, 0, 0, 0, 0, 0, 0 };


pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
sem_t empty, full;
int sizeTracker = 0;

//This random generation code was made with help from: https://stackoverflow.com/questions/4926622/how-to-generate-different-random-numbers-in-a-loop-in-c
random_device rd;
mt19937 gen(rd());

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
		sizeTracker = sizeTracker + 1;
	}
	else
	{
		cout << "buffer full" << endl;
	}
}

/*
Description: Removes the value in the parameter index from main buffer.
Pre: Called in the Consume function by a pthread.
Post: If the buffer was not empty, the value is removed in the main buffer.
*/
void removeFromBuffer(int index)
{
	if (sizeTracker > 0)
	{
		buffer[index] = -1;
		sizeTracker = sizeTracker - 1;
	}
	else
	{
		cout << "buffer empty" << endl;
	}
}

/*
Description: A producer thread executes this function endlessly, simply calls insertIntoBuffer if it acquires the lock.
Pre: A producer pthread must be created in the main.
Post: Endlessy produces random items for the buffer.
*/
void * Produce(void * thread)
{	
	//generate a random number 1 - 100 for the buffer
	uniform_int_distribution<> dis(1, 100);

	while (true)
	{
		int item = dis(gen);

		sem_wait(&empty);				//decrement empty sempahore 
		pthread_mutex_lock(&mutex);		//acquire lock
		insertIntoBuffer(item);			//function call
		cout << "Produced {" << item << "} into index ["
			 << sizeTracker - 1 << "] with Producer thread " 
			 << (int)thread << endl;
		sem_post(&full);				//increment full semaphore
		Sleep(5);
		pthread_mutex_unlock(&mutex);   //release lock
	} 
}

/*
Description: A consumer thread executes this function endlessly, simply calls removeFromBuffer if it acquires the lock.
Pre: A consumer pthread must be created in the main.
Post: Endlessy consumes items in the buffer.
*/
void * Consume(void * thread)
{
	while (true)
	{

		sem_wait(&full);						//decrement full sempahore 
		pthread_mutex_lock(&mutex);				//acquire lock
		cout << "Consumed {" << buffer[sizeTracker - 1] << "} from index ["
			<< sizeTracker - 1 << "] with Consumer thread "
			 << (int)thread << endl;
		removeFromBuffer(sizeTracker - 1);	//function call
		sem_post(&empty);						//increment empty semaphore
		Sleep(5);
		pthread_mutex_unlock(&mutex);			//release lock
	}
}

int main()
{
	//pthread_mutex_init(&mutex, NULL); //Mutex binary semaphore
	sem_init(&empty, 0, NUM_BUFFERS); //Semaphore for amount of empty slots in the buffer (initalized to 7)
	sem_init(&full, 0, 0); //Semaphore for the amount of full slots in the buffer (initalized to 0)

	//Create 10 producer/consumer pthreads
	for (int i = 0; i < 10; i++)
	{
		pthread_t Producer;
		pthread_create(&Producer, NULL, &Produce, (void*)(i + 1));

		pthread_t Consumer;
		pthread_create(&Consumer, NULL, &Consume, (void*)(i + 1));
	}


	system("pause"); //program terminates itself using any other method, we were forced to use system("pause"). Best way to observe output.
	return 0;
} 