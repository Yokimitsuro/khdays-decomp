#include "game/engine.h"

extern char *NNSi_FndGetCurrentRootHeap(void);
extern void Ov052_DisposeAndFreeChild(char *obj);
extern void Ov052_ReleaseChildFromGlobal(char *heap);
extern void VeneerTo_Obj_Destroy(int h);
extern void Ov022_DestroyRoot(char *heap);

/* Enemy overlay teardown: drops the model handle, the two animation blocks and the sound block,
 * then hands the heap back to the shared unloader. */
void Ov052_UnloadEnemyOverlay(void) {
    char *heap = NNSi_FndGetCurrentRootHeap();
    Ov052_DisposeAndFreeChild(heap);
    Ov052_ReleaseChildFromGlobal(heap);
    VeneerTo_Obj_Destroy(*(int *)(heap + 0x2c2c));
    ReleaseField74AndCleanup(heap + 0x2c34);
    ReleaseField74AndCleanup(heap + 0x2d3c);
    FreeAllResourceTables(heap + 0x2e44);
    Ov022_DestroyRoot(heap);
}
