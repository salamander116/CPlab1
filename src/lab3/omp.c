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
		#include "omp.h"
		#include <time.h>


		void main(int argc, char*argv[]){
			
			srand((unsigned)time(NULL));
			int numberOfThreads = atoi(argv[2]);
			pthread_t threads[numberOfThreads];
			int result= 0;

			int numberOfPoints = atoi(argv[1]);
			
			omp_set_num_threads(numberOfThreads);

			int shotsForEachThread = floor(numberOfPoints/numberOfThreads);

			//Delimeters the last thread number of points, used by first or last thread
			int halper = numberOfPoints - (shotsForEachThread * (numberOfThreads -1));

			long counter = 0;
			
			#pragma omp parallel
			{
			
			// if we have a strange number of threeads, firs thread processes like would be the last worker.

				if(omp_get_thread_num() == 0){

					for(int i = 0; i<halper; i++){
						
						//gerarpontos random

						float x = (float)rand()/RAND_MAX;

						float y = (float)rand()/RAND_MAX;

						if((x*x) + (y*y) <=1){
							counter++;
					
						}

					}

				}else{
					
					for(int i = 0; i<shotsForEachThread; i++){
						
						//gerarpontos random 

						float x = (float)rand()/RAND_MAX;

						float y = (float)rand()/RAND_MAX;

						if((x*x) + (y*y) <=1){
							counter++;
					
						}

					}
				}


				

			}

			
			float pi= (float)((float)counter/(float)numberOfPoints) * 4;

			printf("Total Number of poits: %d \n", numberOfPoints);
			printf("Total Number of threads: %d \n", numberOfThreads);
			printf("Points within the circle: %ld \n", counter);
			printf("Pi estimation: %.5f \n", pi);
			
		}

