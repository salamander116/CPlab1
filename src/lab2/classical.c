		#include <stdio.h>
		#include <stdlib.h>
		#include <math.h>
		#include <string.h>
		#include <pthread.h>
		#include <sys/mman.h>
		#include <fcntl.h>
		#include <unistd.h>
		#include <sys/types.h>
		#include <sys/stat.h>
		#include <sys/time.h>
		#include <time.h>


		void * worker(void*arg){

			
			long counter = 0;
			int totalShots =  (int )(long) arg;
		
			for(int i = 0; i<totalShots; i++){
				//gerarpontos

				float x = (float)rand()/RAND_MAX;

				float y = (float)rand()/RAND_MAX;

				if((x*x) + (y*y) <=1){
					counter++;
				}

			}

				return  (void*)counter;
		}



		

		int main(int argc, char*argv[]){
			
			srand((unsigned)time(NULL));
			int numberOfThreads = atoi(argv[2]);
			pthread_t threads[numberOfThreads];
			int result= 0;

			int numberOfPoints = atoi(argv[1]);
			int shotsForEachThread = floor(numberOfPoints/numberOfThreads);
			int halper = 0;

			/* All threads created */ 
			for(int i = 0; i< numberOfThreads; i++){
				if(i == numberOfThreads){
					
					pthread_create(&threads[i], NULL, worker, ((void*)(long)(numberOfPoints - halper)));
				
				}else{

					pthread_create(&threads[i], NULL, worker, (void*)(long)shotsForEachThread);
					halper = halper + shotsForEachThread;
				
				}
			}

			/* Waits for all threads */
			for(int i = 0; i< numberOfThreads; i++){
				
				void* counterPtr = 0;
				pthread_join(threads[i], &counterPtr);
				int a = (int)(long)counterPtr;
				result += a;
			}
			
			float pi= (float)((float)result/(float)numberOfPoints) * 4;

			printf("Total Number of poits: %d \n", numberOfPoints);
			printf("Total Number of threads: %d \n", numberOfThreads);
			printf("Points within the circle: %d \n", result);
			printf("Pi estimation: %.5f \n", pi);
			
			return 0;

		}

