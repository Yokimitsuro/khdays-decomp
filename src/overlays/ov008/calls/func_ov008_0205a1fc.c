/*
 * Ov008_Menu_BindScenePanels - bind the menu scene's named panel resources, called
 * from Ov008_Menu_InitSceneObject.
 *
 * The per-scene parameter table entry carries up to three resource names (name1/2/3,
 * 0x10 bytes each after the leading value word). For each non-empty name it looks the
 * name up in the scene's resource dictionary (obj+0x5c, +0x40 to reach the dict), stores
 * the found index at obj+0x148/+0x14c (with the "valid" flag at obj+0x140/+0x144), then
 * initialises the matching panel sub-object (obj+0x1b8 for names 1 and 3, obj+0x31c for
 * name 2) via ov008 sub-object clear + func_02059c88 (loading it from the message handle
 * at obj+0x1b4 for this scene id / character byte obj+0x4d4, slot 1/2/3) and builds its
 * panel-id summary; if the sub-object's byte[1] is set it ORs bit0 into byte[0].
 *
 * name1 and name3 share the same panel slot/fields (0x1b8, 0x148, 0x140), name2 uses its
 * own (0x31c, 0x14c, 0x144). A dict of 0 yields index 0xffffffff (not found).
 * The `obj+0x5c != 0 ? +0x40 : 0` test is written non-zero-branch-first so mwcc emits
 * `addne; moveq` (the zero-branch-first spelling gives `moveq; addne`).
 */

typedef struct {
    int  value;
    char name1[0x10];
    char name2[0x10];
    char name3[0x10];
} SceneParam;

extern int  func_02016f10(void *dict, void *name);
extern void func_ov008_02059c78(int subobj);
extern void func_ov008_02059c88(int subobj, int msg, int b, int sceneId, int chr, int slot);
extern void func_ov008_02059eb0(int subobj, char *out, int src);
extern SceneParam data_ov008_0208e9c4[];

void func_ov008_0205a1fc(int obj, int *pSceneId)
{
    SceneParam *e = &data_ov008_0208e9c4[*pSceneId];
    int dict;
    unsigned int idx;

    if (e->name1[0] != 0) {
        if (*(int *)(obj + 0x5c) != 0) dict = *(int *)(obj + 0x5c) + 0x40;
        else dict = 0;
        if (dict == 0) idx = 0xffffffff;
        else idx = func_02016f10((void *)dict, e->name1);
        *(unsigned int *)(obj + 0x148) = idx;
        *(int *)(obj + 0x140) = 1;
        func_ov008_02059c78(obj + 0x1b8);
        func_ov008_02059c88(obj + 0x1b8, *(int *)(obj + 0x1b4), 0, *pSceneId,
                            *(unsigned char *)(obj + 0x4d4), 1);
        func_ov008_02059eb0(obj + 0x1b8, (char *)(obj + 0x480), 0);
        if (*(char *)(obj + 0x1b9) != 0) *(unsigned char *)(obj + 0x1b8) |= 1;
    }
    if (e->name2[0] != 0) {
        if (*(int *)(obj + 0x5c) != 0) dict = *(int *)(obj + 0x5c) + 0x40;
        else dict = 0;
        if (dict == 0) idx = 0xffffffff;
        else idx = func_02016f10((void *)dict, e->name2);
        *(unsigned int *)(obj + 0x14c) = idx;
        *(int *)(obj + 0x144) = 1;
        func_ov008_02059c78(obj + 0x31c);
        func_ov008_02059c88(obj + 0x31c, *(int *)(obj + 0x1b4), 0, *pSceneId,
                            *(unsigned char *)(obj + 0x4d4), 2);
        func_ov008_02059eb0(obj + 0x31c, (char *)(obj + 0x480), 0);
        if (*(char *)(obj + 0x31d) != 0) *(unsigned char *)(obj + 0x31c) |= 1;
    }
    if (e->name3[0] != 0) {
        if (*(int *)(obj + 0x5c) != 0) dict = *(int *)(obj + 0x5c) + 0x40;
        else dict = 0;
        if (dict == 0) idx = 0xffffffff;
        else idx = func_02016f10((void *)dict, e->name3);
        *(unsigned int *)(obj + 0x148) = idx;
        *(int *)(obj + 0x140) = 1;
        func_ov008_02059c78(obj + 0x1b8);
        func_ov008_02059c88(obj + 0x1b8, *(int *)(obj + 0x1b4), 0, *pSceneId,
                            *(unsigned char *)(obj + 0x4d4), 3);
        func_ov008_02059eb0(obj + 0x1b8, (char *)(obj + 0x480), 0);
        if (*(char *)(obj + 0x1b9) != 0) *(unsigned char *)(obj + 0x1b8) |= 1;
    }
}
