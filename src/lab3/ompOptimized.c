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
			
			int result= 0;

			int numberOfPoints = atoi(argv[1]);
			
			//Let omp use the best number of threads for the job
			int systemNThreads = omp_get_num_threads();

			int shotsForEachThread = floor(numberOfPoints/systemNThreads);

			//Delimeters the last thread number of points, used by first or last thread
			int halper = numberOfPoints - (shotsForEachThread * (systemNThreads -1));

			long counter = 0;
			int i;
			
			#pragma omp parallel for 

				for(i=0; i< shotsForEachThread; i++){

					if(omp_get_thread_num() == 0){
						
						if(i < halper){

							//gerarpontos random -> same logic

							float x = (float)rand()/RAND_MAX;

							float y = (float)rand()/RAND_MAX;

							if((x*x) + (y*y) <=1){
								
								counter++;
					
							}

						}

					}else{
						
						//gerarpontos random

						float x = (float)rand()/RAND_MAX;

						float y = (float)rand()/RAND_MAX;

						if((x*x) + (y*y) <=1){
							
							counter++;
					
						}

					}

				}
			
			

			
			float pi= (float)((float)counter/(float)numberOfPoints) * 4;

			printf("Total Number of poits: %d \n", numberOfPoints);
			printf("Total Number of threads: %d \n", systemNThreads);
			printf("Points within the circle: %ld \n", counter);
			printf("Pi estimation: %.5f \n", pi);
			
		}

