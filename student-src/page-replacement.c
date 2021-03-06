#include <stdlib.h>

#include "types.h"
#include "pagetable.h"
#include "global.h"
#include "process.h"

/*******************************************************************************
 * Finds a free physical frame. If none are available, uses a clock sweep
 * algorithm to find a used frame for eviction.
 *
 * @return The physical frame number of a free (or evictable) frame.
 */
pfn_t get_free_frame(void) {
    
   /* See if there are any free frames */
   for(int i = 0; i < CPU_NUM_FRAMES; ++i)
      if(rlt[i].pcb == NULL) return i;

   /* FIX ME : Problem 5 */
   /* IMPLEMENT A CLOCK SWEEP ALGORITHM HERE */
    for(int i = 0; i < CPU_NUM_FRAMES; ++i)
        if(rlt[i].pcb->pagetable[rlt[i].vpn].valid==0) return i;
    
    
    pte_t p;
    for(int i = 0; i < CPU_NUM_FRAMES; ++i){
        p = rlt[i].pcb->pagetable[rlt[i].vpn];
        if(p.used==0) return i;
        p.used = 0;
    }
   /* If all else fails, return a random frame */
   //return rand() % CPU_NUM_FRAMES;
    return 0;
}
