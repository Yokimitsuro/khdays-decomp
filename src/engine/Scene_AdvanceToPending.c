/* Scene_AdvanceToPending -- scene dispatcher / "advance to pending scene" step.
 * Runs every frame as the BootTask steady-state helper (called from the object
 * state fn @0x02020978, whose return is ignored). Drives the scene-control record
 * @0x0204bda4:
 *   +0x04 obj      current scene task object (from InstantiateClass) [== gSceneCtl]
 *   +0x08 entry    &g_SceneTable[curId]
 *   +0x0c curId    active scene id
 *   +0x10 pendId   pending scene id  (0x0204bdb4; set by Scene_RequestPending @0x02020a78)
 *   +0x14 pendArg  pending scene arg (0x0204bdb8)
 * Step 1 (teardown): if a scene object exists and Instance_ReleaseIfDead() reports it ended,
 *   unload its overlay (UnloadOverlaySync, unless the entry has none) and clear obj/curId.
 * Step 2 (load): when no scene object is live and a pending id is set, look it up in
 *   g_SceneTable (@0x02042548, {overlayId, classDesc} per scene id): FS_LoadOverlay the
 *   scene's overlay (LoadOverlaySync) unless overlayId==-1, then InstantiateClass its
 *   class descriptor with pendArg; latch curId=pendId and clear the pending pair.
 * Scene 1 (boot/logo) -> overlayId 0 (ov000), classDesc @0x0205a9c0. */

#include "game/heap.h"

typedef struct SceneEntry {
    int   overlayId;   /* FS overlay index; -1 = scene has no overlay */
    void *classDesc;   /* InstantiateClass descriptor */
} SceneEntry;

typedef struct SceneCtl {
    void       *obj;      /* +0x00 (0x0204bda8) current scene task object */
    SceneEntry *entry;    /* +0x04 (0x0204bdac) current scene's table entry */
    int         curId;    /* +0x08 (0x0204bdb0) active scene id */
    int         pendId;   /* +0x0c (0x0204bdb4) pending scene id */
    int         pendArg;  /* +0x10 (0x0204bdb8) pending scene arg */
} SceneCtl;

extern int  data_0204bda4;           /* record base; +4 aliases gSceneCtl (obj) */
extern char gSceneCtl[];         /* SceneCtl (obj..pendArg); cleared by Scene_ClearPending */
extern SceneEntry gSceneTable[];   /* g_SceneTable, indexed by scene id */
extern GameHeap *gSubHeap;

extern int  Instance_ReleaseIfDead(void *obj);
extern void UnloadOverlaySync(int module, int overlayId);
extern void Callbacks_Init(void);
extern void HeapState_Recreate(GameHeap *heap);
extern void LoadOverlaySync(int module, int overlayId);
extern void *InstantiateClass(void *classDesc, int arg);   /* InstantiateClass */
extern void Word_Set(void *obj, int);

int Scene_AdvanceToPending(void) {
    SceneCtl *s = (SceneCtl *)gSceneCtl;

    if (*(void **)((char *)&data_0204bda4 + 4) != 0) {
        if (Instance_ReleaseIfDead(s->obj) != 0) {
            if (s->entry->overlayId != -1) {
                UnloadOverlaySync(0, s->entry->overlayId);
            }
            Callbacks_Init();
            HeapState_Recreate(gSubHeap);
            s->obj = 0;
            s->curId = 0;
        }
    }

    if (s->obj == 0) {
        int id = s->pendId;
        if (id != 0) {
            SceneEntry *ent = &gSceneTable[id];
            int ov = ent->overlayId;
            if (ov != -1) {
                LoadOverlaySync(0, ov);
            }
            {
                void *obj = InstantiateClass(ent->classDesc, s->pendArg);
                s->obj = obj;
                s->entry = ent;
                Word_Set(obj, 1);
            }
            s->curId = s->pendId;
            s->pendId = 0;
            s->pendArg = 0;
        }
    }
    return 1;
}
