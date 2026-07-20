/* UNFINISHED. 176/176 bytes, structurally identical -- register choice only.
 *
 * ov107 root teardown: run the four step callbacks at +0x2c (each fires only if
 * its ->f4 is 0 and its ->f8 is non-null), release the four handles at
 * +0x7c..+0x88, run the root vtable's own teardown, walk the node list at +0x4c
 * freeing each node's two pointers, destroy both lists, release +0x48, then the
 * module-level cleanup and the two 02030d10 releases.
 *
 * +0x7c..+0x88 are one array of four handles.  The first is reached with a plain
 * [r6,#0x7c] and the rest need an address computation ONLY because 0x7c is the
 * largest word-load immediate offset in THUMB -- a codegen artefact, not a
 * source difference.  Do not read it as four unrelated fields.
 *
 * WHAT DIFFERS: which register holds the step pointer.
 *   ROM   ldr r0,[r5,#0x2c] ; ldr r1,[r0,#4] ; ... ; ldr r1,[r0,#8] ; blx r1
 *   ours  ldr r1,[r4,#0x2c] ; ldr r0,[r1,#4] ; ... ; ldr r0,[r1,#8] ; blx r0
 * The ROM keeps the struct pointer in r0 and the loaded values in r1; we do the
 * opposite.  Both are valid colourings and the instruction stream is otherwise
 * identical, byte for byte.
 *
 * RULED OUT:
 *   index-scaled loop (`p[i*4]`) instead of a walking pointer -- 180 B, 4 over.
 *     The walking pointer is what the ROM does and it fixes the size.
 *   `s` declared inside the loop vs at function scope
 *   ALL 120 declaration-order permutations of the five locals
 * Same class as func_ov010_0204cac0: a two-colouring the compiler picks the
 * other way round, with no source-level lever found.
 */
/* +0x7c..+0x88 are four consecutive handles, so they are one array; the first is
 * reached with a plain [r6,#0x7c] and the rest need an address computation only
 * because 0x7c is THUMB's largest word-load immediate offset -- a codegen
 * artefact, not a source difference. */
typedef struct {
    void *vtable;               /* +0x00, ->f8 is a teardown callback */
    char pad04[0x28];
    void *step[4];              /* +0x2c: each ->f4 must be 0 before ->f8 runs */
    char pad3c[0xc];
    int f48;                    /* +0x48 */
    char pad4c_[0];             /* +0x4c is the node list */
} Ov107Root;

extern void *NNSi_FndGetCurrentRootHeap(void);
extern void func_02024fd4(void *p);
extern void func_0203d194(void *p);
extern void *func_01fffd70(void *list);
extern void *func_01fffd8c(void *list);
extern void NNSi_FndDestroyDoubleList(void *list);
extern void func_ov107_020c2f40(void);
extern void func_02030d10(int a);

extern void *data_ov107_020cbf1c;

void func_ov107_020c9a10(void) {
    char *root;
    char *p;
    int i;
    void **node;

    root = (char *)NNSi_FndGetCurrentRootHeap();
    p = root;
    for (i = 0; i < 4; i++) {
        int *s = *(int **)(p + 0x2c);
        if (s[1] == 0 && s[2] != 0) {
            ((void (*)(void))s[2])();
        }
        p += 4;
    }
    func_02024fd4(*(void **)(root + 0x7c));
    func_02024fd4(*(void **)(root + 0x80));
    func_02024fd4(*(void **)(root + 0x84));
    func_02024fd4(*(void **)(root + 0x88));
    {
        int *v = *(int **)root;
        if (v[2] != 0) {
            ((void (*)(void))v[2])();
        }
    }
    node = (void **)func_01fffd70(root + 0x4c);
    while (node != 0) {
        func_02024fd4(node[0]);
        func_0203d194(node[1]);
        node = (void **)func_01fffd8c(root + 0x4c);
    }
    NNSi_FndDestroyDoubleList(root + 0x4c);
    NNSi_FndDestroyDoubleList(root + 4);
    if (*(void **)(root + 0x48) != 0) {
        func_0203d194(*(void **)(root + 0x48));
    }
    *(int *)(root + 0x48) = 0;
    func_ov107_020c2f40();
    func_02030d10(1);
    func_02030d10(4);
    data_ov107_020cbf1c = 0;
}
