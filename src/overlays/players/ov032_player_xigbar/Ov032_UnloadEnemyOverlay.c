#include "game/engine.h"

extern char *NNSi_FndGetCurrentRootHeap(void);
extern void Ov032_DisposeAndFreeChild(char *obj);
extern void Ov032_ReleaseChildFromGlobal(char *heap);
extern void VeneerTo_Obj_Destroy(int h);
extern void Ov022_DestroyRoot(char *heap);

/* Enemy overlay teardown: drops the model handle, the two animation blocks and the sound block,
 * then hands the heap back to the shared unloader. */
void Ov032_UnloadEnemyOverlay(void) {
    char *heap = NNSi_FndGetCurrentRootHeap();
    Ov032_DisposeAndFreeChild(heap);
    Ov032_ReleaseChildFromGlobal(heap);
    VeneerTo_Obj_Destroy(*(int *)(heap + 0x2c2c));
    ReleaseField74AndCleanup(heap + 0x2c34);
    ReleaseField74AndCleanup(heap + 0x2d3c);
    FreeAllResourceTables(heap + 0x2e44);
    Ov022_DestroyRoot(heap);
}
