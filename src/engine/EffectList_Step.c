/* Runs every entry of the current effect list (data_0204c22c): with the list's +0x6c request clear
 * the +0x68 state resets; inside the effect arena (gSubHeap, Heap_SetCurrent) each of the +8
 * entries (+4 array, 12 bytes each) is stepped by CmdPacket_Dispatch; the request is then consumed. */

#include "game/engine.h"

typedef struct {
    char data[0xc];
} EffectEntry;

typedef struct {
    int pad00;
    EffectEntry *entries;   /* 0x04 */
    int count;              /* 0x08 */
    char pad0c[0x68 - 0xc];
    int state;              /* 0x68 */
    int request;            /* 0x6c */
} EffectList;

extern EffectList *data_0204c22c;
extern GameHeap *gSubHeap;
extern void CmdPacket_Dispatch(EffectEntry *entry);

void EffectList_Step(void)
{
    EffectList *list = data_0204c22c;
    int i;
    GameHeap *old;

    if (list == 0) {
        return;
    }
    if (list->request == 0) {
        list->state = 0;
    }
    old = Heap_SetCurrent(gSubHeap);
    for (i = 0; i < list->count; i++) {
        CmdPacket_Dispatch(&list->entries[i]);
    }
    list->request = 0;
    Heap_SetCurrent(old);
}
