/* Frees every session buffer and releases both service instances. */

#include "nitro/types.h"
#include "game/heap.h"

extern void Session_ShutdownHookNoOp(void);
extern void VeneerTo_Obj_Destroy(void *p);

extern u32 **gMsgQueue;
extern GameHeap *gMainHeap;

void Session_Shutdown(void)
{
    u32 *r6;
    int j;
    char *r7;
    int r4;
    int r5;
    u32 *p;
    int k;

    r6 = (u32 *)gMsgQueue;
    if (r6 == 0) goto end;
    j = 0;
    if ((int)r6[2] > 0) {
        r7 = (char *)0;
        do {
            r4 = 0;
            r5 = 0;
            do {
                p = (u32 *)(r7 + r6[1] + r5);
                ExpHeap_Free((void *)p[1], gMainHeap);
                r4++;
                r5 += 0xc;
            } while (r4 < 2);
            r7 += 0x20;
            j++;
        } while (j < (int)r6[2]);
    }
    ExpHeap_Free((void *)r6[1], gMainHeap);
    Session_ShutdownHookNoOp();
    r5 = 0x758;
    r4 = 0;
    do {
        VeneerTo_Obj_Destroy((void *)*(u32 *)((char *)r6 + r5));
        r4++;
        r6 = (u32 *)((char *)r6 + 4);
    } while (r4 < 2);
end:
    gMsgQueue = 0;
}
