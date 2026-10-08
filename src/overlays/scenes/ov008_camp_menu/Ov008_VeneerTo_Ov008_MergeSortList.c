/* Interworking tail-call veneer (`ldr ip,[pc] ; bx ip`): forwards to Ov008_MergeSortList. */

#include "nnsys/fnd.h"

extern void *Ov008_MergeSortList(NNSFndList * list, int compare);

void *Ov008_VeneerTo_Ov008_MergeSortList(NNSFndList * list, int compare)
{
    return Ov008_MergeSortList(list, compare);
}
