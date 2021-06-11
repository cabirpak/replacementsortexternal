/*
============================================================================
Name        : replacementselectionsort.c
Author      :
 Version     :
Copyright   : Your copyright notice
Description : Hello World in C, Ansi-style
============================================================================
*/

 

#include <stdio.h>

#include <stdlib.h>

 

#define ELEMENT_COUNT 15 //bunu dosyadan okunan eleman sayısına cevirmek lazim. dinamik allocation olacak yani.

#define HEAP_SIZE 3

#define MAX_BUFFER_SIZE 15

 

int elements[ELEMENT_COUNT] = {5,2,9,11,7,2,0,1,6,10,3,8,4,13,14};

 

int main(void) {

       puts("Sort begin");

 

       //her bir buffer'da maximum MAX_BUFFER_SIZE tane eleman olabilir.

       //maximum ELEMENT_COUNT kadar heap olabilir.

       int buffers[ELEMENT_COUNT][MAX_BUFFER_SIZE];

 

       int buffer_counter = 0;

       int in_buffer_counter = 0;

       int element_counter = 0;

 

       int current_heap[HEAP_SIZE];//values

       int current_heap_active_status[HEAP_SIZE];//bu aslinda bool ya da unsigned char olabilirdi, daha az yer kaplardi.

       //int min_of_current_buffer = 0x7FFFFFFF;// min bulunurken buraya cok buyuk sayi yazilir. (4 bayt icin boyle)

       int last_sent_to_buffer = -100000;// buraya, olmayacak kadar kucuk sayi yazilacak

 

       int finished = 0, first_iteration = 1;

 

       int i = 0;

 

       for(i=0; i<HEAP_SIZE; i++){

             current_heap_active_status[i] = 0;

       }

 

       for(;!finished;){

 

             //look if all heap elements inactive

             int all_inactive = 1;

             for(i=0; i<HEAP_SIZE; i++){

                    if(current_heap_active_status[i] == 1){

                           all_inactive = 0;

                           break;

                    }

             }

 

             if(all_inactive){

                    if(first_iteration){

                           //construct the initial heap

                           for(i = 0; i < HEAP_SIZE; i++){

                                  current_heap[i] = elements[element_counter];

                                  current_heap_active_status[i] = 1;

                                  element_counter ++;

                           }

                           first_iteration = 0;

                    }

                    else{

                           // all heap elements turned into active (at not first iteration)

                           /*if(element_counter >= ELEMENT_COUNT)
                                  finished = 1;
                           else*/{

                                  //bir sonraki buffer'a gondermeye baslanmak uzere heap'teki elemanlar active yapilir.

                                  buffers[buffer_counter][in_buffer_counter] = -1;//bir onceki buffer sonlandirilir.


                                  in_buffer_counter = 0;
                                  
                                  int some_actives_exist = 0;

                                  for(i = 0; i < HEAP_SIZE; i++){

                                    if(current_heap_active_status[i] != -1)
                                        current_heap_active_status[i] = 1;
                                    else
                                        some_actives_exist = 1;

                                  }
                                  //if(some_actives_exist)
                                    buffer_counter++;

                                  last_sent_to_buffer = -100000;

                                  //min_of_current_buffer = 0x7FFFFFFF;

                           }

                    }

                    all_inactive = 0;

             }//end of all_inactive

 

 

             // find and select the minimum of the heap

 

             int min_of_heap = 0x7fffffff;

             int min_of_heap_index = -1;

             for(i = 0; i < HEAP_SIZE; i++){

                    if(current_heap_active_status[i] == 1 && current_heap[i] < min_of_heap){

                           min_of_heap = current_heap[i];

                           min_of_heap_index = i;

                    }

             }

 
            printf("heap: %d (active:%d), %d (active:%d), %d (active:%d) min: %d\n", current_heap[0], current_heap_active_status[0], current_heap[1], current_heap_active_status[1], current_heap[2], current_heap_active_status[2], min_of_heap);


            if(min_of_heap_index == -1){
                finished = 1;
                //buffer_counter++;
                continue;
            }
 

             // if the selected element is less than all of the values in the current buffer

 

             printf("last_sent_to_buffer: %d\n", last_sent_to_buffer);

             printf("min_of_heap <= min_of_current_buffer -> %d\n", min_of_heap <= last_sent_to_buffer);

             if(min_of_heap <= last_sent_to_buffer /*&& min_of_current_buffer != 0x7fffffff*/){

 

                           current_heap_active_status[min_of_heap_index] = 0;

             }

             //otherwise

             else{

                    buffers[buffer_counter][in_buffer_counter] = current_heap[min_of_heap_index];

 

                    //buffer'in en kucuk elemani guncel tutulur.

                    //if(buffers[buffer_counter][in_buffer_counter] < min_of_current_buffer)

                    last_sent_to_buffer = buffers[buffer_counter][in_buffer_counter];

 

                    printf("(%d, %d) : %d\n", buffer_counter, in_buffer_counter, buffers[buffer_counter][in_buffer_counter]);

 

                    in_buffer_counter++;

 

 

 

 

                    //take the next element

                    if(element_counter < ELEMENT_COUNT){

                           printf("element_counter: %d\n", element_counter);

                           printf("heap: %d (active:%d), %d (active:%d), %d (active:%d) min: %d\n", current_heap[0], current_heap_active_status[0], current_heap[1], current_heap_active_status[1], current_heap[2], current_heap_active_status[2], min_of_heap);

 

                           current_heap[min_of_heap_index] = elements[element_counter];

                           element_counter ++;

 

                    }

                    else{

                           //buffers[buffer_counter][in_buffer_counter] = -1;//bir onceki buffer sonlandirilir.

                           //finished = 1;

                           //buffer_counter++;

 

                           current_heap_active_status[min_of_heap_index] = -1;

                    }

             }

       }

 

       int tmp_buf_counter = 0;

       for(tmp_buf_counter = 0; tmp_buf_counter < buffer_counter; tmp_buf_counter++){

             puts("\nSIRADAKI BUFFER:");

 

             int tmp_in_buf_counter = 0;

             for(tmp_in_buf_counter = 0; buffers[tmp_buf_counter][tmp_in_buf_counter] != -1; tmp_in_buf_counter++){

                    printf("%d ", buffers[tmp_buf_counter][tmp_in_buf_counter]);

             }

       }

 

       return EXIT_SUCCESS;

}
