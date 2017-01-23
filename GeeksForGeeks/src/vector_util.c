/*
 * vector_util.c
 *
 *  Created on: Oct 2, 2016
 *      Author: srikanth
 */
#include <stdio.h>
#include <stdlib.h>
#include "vector_util.h"


void test_vector_dispatch()
{
   unsigned long bitmap = 0;
   unsigned long input_arr[10] = {1,2,3,4,5,6,7,8,9,10};
   int idx;

   for(;bitmap < 32;) {
       bitmap = ((bitmap << 1) | (1UL));
       printf("Input bitmap:%lu\n", bitmap);
       /*-----------------------------------------------------------------*/
       VECTOR_BITMAP_WALK_START(bitmap, NULL, ret)

       /*Add dispatcher logic.*/
       /* Use global vector table directly
        * or unroll the table into a switch case
        * where each case is a vector.*/
       printf("\tbitmap: %lu vector_index: %lu\n", bitmap, offset);


       VECTOR_BITMAP_WALK_END()
       /*-----------------------------------------------------------------*/

   }

   printf("\nInput random bits\n\n");

   for(idx = 0; idx < 10; idx++) {
       bitmap = input_arr[idx];
       printf("Input bitmap:%lu\n", bitmap);
       /*-----------------------------------------------------------------*/
       VECTOR_BITMAP_WALK_START(bitmap, NULL, ret)

       printf("\tbitmap: %lu vector index: %lu\n", bitmap, offset); \


       VECTOR_BITMAP_WALK_END()
	   /*-----------------------------------------------------------------*/

   }

}

