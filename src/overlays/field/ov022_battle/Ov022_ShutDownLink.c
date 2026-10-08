/* Shut the link down: destroy the two objects whose handles are at +0x14, tear the four
 * subsystems down, release the frame slot and clear both root words.
 *
 * The handle loop counts UNSIGNED (blo), and the handle array is walked rather
 * than indexed. */

#include "game/engine.h"

extern void func_ov022_020831dc(void *ctx);
extern void VeneerTo_Obj_Destroy(int handle);
extern void Ov002_ReleaseAllSlotObjects(void);
extern void Ov002_RetirePendingSlotEntries(void);
extern void Ov002_TearDownContext(void);

typedef struct {
    int reserved;
    char *pCtx;     /* +4 */
} Ov022LinkRoot;

extern Ov022LinkRoot data_ov022_020b2e60;

void Ov022_ShutDownLink(void) {
    unsigned int i;
    char *ctx = data_ov022_020b2e60.pCtx;
    char *handle = *(char **)(ctx + 0x20);

    func_ov022_020831dc(ctx);

    for (i = 0; i < 2; i++) {
        if (*(int *)(handle + 0x14) != 0) {
            VeneerTo_Obj_Destroy(*(int *)(handle + 0x14));
        }
        handle += 4;
    }

    Ov002_ReleaseAllSlotObjects();
    Ov002_RetirePendingSlotEntries();
    EntityMgr_PopVramState();
    Ov002_TearDownContext();
    SoundMgr_SetListenersEnabled(0);

    data_ov022_020b2e60.pCtx = 0;
    data_ov022_020b2e60.reserved = 0;
}
