/*
 * vector_util.h
 *
 *  Created on: Oct 2, 2016
 *      Author: srikanth
 */

#ifndef VECTOR_UTIL_H_
#define VECTOR_UTIL_H_


/* Usage:
 * 1. Use the set bit/ clear bit macros to set the corresponding
 *    vector bits in the bitmap.
 * 2. Each data plane thread will copy the bitmaps at the beginning
 *    of the packet processing cycle. Hence no more lb_barriers required.
 * 3. The bitmap walk macros below will be used to call the vectors one by one.
 *    We can directly use the global vector tables present in the vector_table.c.
 *    There is no need for per dispatcher memory allocation.
 * 4. To increase performance we can unroll the vector table in the dispatcher by using a
 *    simple switch case. This will be done based on performance runs.
 */

#define VECTOR_SET_BIT(bm, bit_idx) (bm |= (1UL << bit_idx))
#define VECTOR_CLEAR_BIT(bm, bit_idx) (bm &= ~(1UL << bit_idx))

/*Will get the index of the first bit set.
 * Return:
 * 	0 for word = 0
 * 	0 for word = 1
 * 	1 for word = 2
 * 	3 for word = 8
 * 	4 for word = 16*/
static inline unsigned long vector_ffs(unsigned long word)
{
    __asm__("bsf %1,%0"
            :"=r"(word)
            :"rm"(word));
    return word;
}

/* The below MACROs together form the basic dispatcher.
 * The input bitmap must be temporary variable as it will
 * be modified within the macro. We get each bit set in the
 * bitmap and calculate the corresponding index. This index
 * will be used to access the vector table.*/
#define VECTOR_BITMAP_WALK_START(bitmap, v_tbl, ret)  {      \
    unsigned long tmp_bitmap = (bitmap);                     \
    unsigned long offset = 0;                                \
    for (;tmp_bitmap;) {                                     \
        offset = vector_ffs(tmp_bitmap);                     \
        VECTOR_CLEAR_BIT(tmp_bitmap, offset);                \


/*
 * We can write the dispatcher specific logic here.
 * Handle the return codes. Debug code will also reduce as
 * we dont need to lookup the function name by comparison.
 * Its direct lookup in the global table for the function name.
 */


#define VECTOR_BITMAP_WALK_END()\
            }                   \
    }



void test_vector_dispatch();

#endif /* VECTOR_UTIL_H_ */
