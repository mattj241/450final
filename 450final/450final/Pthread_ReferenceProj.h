////#define HAVE_STRUCT_TIMESPEC
//#include <pthread.h>
//#include <iostream>
//using namespace std;
//
//int buffers[7];
//
//void *MakeBuffers(void *thread)
//{
//	for (int i = 0; i < 7; i++)
//	{
//		buffers[i] = i + 1;
//		cout << "buffer #" << i + 1 << " has a value of: " << buffers[i] << endl;
//	}
//	return 0;
//}
//
//void *ClearBuffers(void *thread)
//{
//	for (int i = 0; i < 7; i++)
//	{
//		buffers[i] = 0;
//		cout << "buffer #" << i + 1 << " has been cleared to: " << buffers[i] << endl;
//	}
//	return 0;
//}
//
//int main()
//{
//	pthread_t producerThread, consumerThread;
//	pthread_create(&producerThread, NULL, &MakeBuffers, NULL);
//	pthread_create(&consumerThread, NULL, &ClearBuffers, NULL);
//
//	pthread_exit(NULL);
//	return 0;
//}


//void wait(semaphore * inputSemaphore, pthread_t * thread)
//{
//	inputSemaphore->value--;
//	if (inputSemaphore->value < 0)
//	{
//		//inputSemaphore->list.add(process)
//		//pthreadCancelableWait(thread);
//	}
//}
//
//void signal(semaphore * inputSemaphore)
//{
//	inputSemaphore->value++;
//	if (inputSemaphore->value <= 0)
//	{
//		//inputSemaphore->list.add(process)
//
//	}
//}