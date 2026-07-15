/* func_0202099c -- scene dispatcher / "advance to pending scene" step.
 * Runs every frame as the BootTask steady-state helper (called from the object
 * state fn @0x02020978, whose return is ignored). Drives the scene-control record
 * @0x0204bda4:
 *   +0x04 obj      current scene task object (from InstantiateClass) [== data_0204bda8]
 *   +0x08 entry    &g_SceneTable[curId]
 *   +0x0c curId    active scene id
 *   +0x10 pendId   pending scene id  (0x0204bdb4; set by StoreGlobalPairAt10 @0x02020a78)
 *   +0x14 pendArg  pending scene arg (0x0204bdb8)
 * Step 1 (teardown): if a scene object exists and func_02023bbc() reports it ended,
 *   unload its overlay (func_0201e4a8, unless the entry has none) and clear obj/curId.
 * Step 2 (load): when no scene object is live and a pending id is set, look it up in
 *   g_SceneTable (@0x02042548, {overlayId, classDesc} per scene id): FS_LoadOverlay the
 *   scene's overlay (func_0201e470) unless overlayId==-1, then InstantiateClass its
 *   class descriptor with pendArg; latch curId=pendId and clear the pending pair.
 * Scene 1 (boot/logo) -> overlayId 0 (ov000), classDesc @0x0205a9c0. */

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

extern int  data_0204bda4;           /* record base; +4 aliases data_0204bda8 (obj) */
extern char data_0204bda8[];         /* SceneCtl (obj..pendArg); cleared by func_02020988 */
extern SceneEntry data_02042548[];   /* g_SceneTable, indexed by scene id */
extern void *data_0204c02c;

extern int  func_02023bbc(void *obj);
extern void func_0201e4a8(int);
extern void func_02020834(void);
extern void func_02023604(void *);
extern void func_0201e470(int module, int overlayId);
extern void *func_02023930(void *classDesc, int arg);   /* InstantiateClass */
extern void func_02023a3c(void *obj, int);

int func_0202099c(void) {
    SceneCtl *s = (SceneCtl *)data_0204bda8;

    if (*(void **)((char *)&data_0204bda4 + 4) != 0) {
        if (func_02023bbc(s->obj) != 0) {
            if (s->entry->overlayId != -1) {
                func_0201e4a8(0);
            }
            func_02020834();
            func_02023604(data_0204c02c);
            s->obj = 0;
            s->curId = 0;
        }
    }

    if (s->obj == 0) {
        int id = s->pendId;
        if (id != 0) {
            SceneEntry *ent = &data_02042548[id];
            int ov = ent->overlayId;
            if (ov != -1) {
                func_0201e470(0, ov);
            }
            {
                void *obj = func_02023930(ent->classDesc, s->pendArg);
                s->obj = obj;
                s->entry = ent;
                func_02023a3c(obj, 1);
            }
            s->curId = s->pendId;
            s->pendId = 0;
            s->pendArg = 0;
        }
    }
    return 1;
}
