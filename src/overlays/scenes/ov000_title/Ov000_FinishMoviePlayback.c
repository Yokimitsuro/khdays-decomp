#include "game/engine.h"

extern char *NNSi_FndGetCurrentRootHeap(void);
extern int Ov000_List_GetState(void);
extern void VeneerTo_Obj_Destroy(int h);
extern int Ov000_FreshBootGfxSetup(int a);
extern int data_ov000_0205ac20;

/* Once the movie player reaches state 6, releases its handle and hands control back to the
 * title. Returns 1 when it acted, 0 while the movie is still running. */
int Ov000_FinishMoviePlayback(void) {
    char *heap = NNSi_FndGetCurrentRootHeap();
    if (Ov000_List_GetState() != 6) {
        return 0;
    }
    VeneerTo_Obj_Destroy(*(int *)(heap + 0x5000 + 0x74));
    data_ov000_0205ac20 = 0;
    Gfx_Reset2DEngines();
    return Ov000_FreshBootGfxSetup(1);
}
