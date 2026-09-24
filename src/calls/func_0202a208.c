/* func_0202a208 -- bind a model instance's animations, MAIN. The model file holds five animation
 * groups (archive members 0..4, counted by func_0202a1b8); one default-heap block holds a pointer
 * slot per animation, handed out group by group (a group without animations gets NULL; with none
 * at all the set is cleared). Every animation is then allocated as an animation object for the
 * instance's resource model (func_02016948 with the default allocator) and initialised
 * (func_02014abc); group 3 (texture pattern) also gets the texture set of the instance's
 * resource list. The per-group counts and `texSrc` are recorded in the set. Codegen: each loop
 * keeps its own block-scoped count `n`; one function-scope `n` swaps the third loop's n/anm registers. */
typedef unsigned short u16;
typedef int BOOL;

typedef struct ModelResList {
    char pad00[0xc];
    void *texFile;                      /* +0x0c */
} ModelResList;

typedef struct ModelInst {
    char pad00[0x74];
    ModelResList *resList;              /* +0x74 */
    void *resMdl;                       /* +0x78 */
} ModelInst;

typedef struct ModelAnimSet {
    u16 count[5];                       /* +0x00 */
    u16 texSrc;                         /* +0x0a */
    int pad0c;
    void **objs[5];                     /* +0x10 */
} ModelAnimSet;

extern void *func_020255d4(void *file, int nMember, int nSub);
extern int func_0202a1b8(void *anmSet);
extern void *NNSi_FndAllocFromDefaultExpHeap(unsigned int size);
extern void MI_CpuFill8(void *dest, int data, unsigned int size);
extern void *func_020170c8(void *anmSet, int idx);                          /* NNS_G3dGetAnmByIdx */
extern void *NNSi_FndGetAllocatorForDefaultHeap(int idx);
extern void *func_02016948(void *allocator, void *anm, void *resMdl);       /* NNS_G3dAllocAnmObj */
extern void *func_02017088(void *file);                                     /* NNS_G3dGetTex */
extern void func_02014abc(void *anmObj, void *anm, void *resMdl, void *tex); /* NNS_G3dAnmObjInit */

void func_0202a208(ModelAnimSet *set, ModelInst *inst, void *file, int texSrc)
{
    int i;
    int total = 0;
    int j;

    for (i = 0; i < 5; i++) {
        total += func_0202a1b8(func_020255d4(file, i, 0));
    }
    if (total > 0) {
        void **slot = NNSi_FndAllocFromDefaultExpHeap(total * 4);

        for (i = 0; i < 5; i++) {
            int n = func_0202a1b8(func_020255d4(file, i, 0));
            if (n > 0) {
                set->objs[i] = slot;
                slot += n;
            } else {
                set->objs[i] = 0;
            }
        }
    } else {
        MI_CpuFill8(set, 0, sizeof(ModelAnimSet));
    }
    for (i = 0; i < 5; i++) {
        void *anmSet = func_020255d4(file, i, 0);
        int n = func_0202a1b8(anmSet);

        for (j = 0; j < n; j++) {
            void *anm = func_020170c8(anmSet, j);

            set->objs[i][j] = func_02016948(NNSi_FndGetAllocatorForDefaultHeap(0), anm, inst->resMdl);
            func_02014abc(set->objs[i][j], anm, inst->resMdl,
                          i == 3 ? func_02017088(func_020255d4(inst->resList->texFile, 7, 0)) : 0);
        }
        set->count[i] = n;
    }
    set->texSrc = texSrc;
}
