/* Opens a model group from a resource: an 'HPAK' pack yields all its kind-5 entries
 * (func_020255bc count, func_020255d4 entry), any other resource is a single model; the model
 * pointers (+4, count at +2) are allocated from the default heap and each one is prepared
 * (func_02028bb4). Returns 1. */
#pragma thumb on
typedef unsigned short u16;

typedef struct {
    u16 flags;          /* 0x00 */
    u16 count;          /* 0x02 */
    void **models;      /* 0x04 */
} ModelGroup;

extern int func_020255bc(void *pack, int kind);
extern void *func_020255d4(void *pack, int kind, int index);
extern void *NNSi_FndAllocFromDefaultExpHeap(unsigned int size);
extern void func_02028bb4(void *model);

int func_0202aff4(ModelGroup *g, void *res)
{
    int i;

    g->flags = 0;
    if (*(unsigned int *)res == 0x4850414b) {
        g->count = func_020255bc(res, 5);
        g->models = NNSi_FndAllocFromDefaultExpHeap(g->count << 2);
        for (i = 0; i < g->count; i++) {
            g->models[i] = func_020255d4(res, 5, i);
            func_02028bb4(g->models[i]);
        }
    } else {
        g->count = 1;
        g->models = NNSi_FndAllocFromDefaultExpHeap(4);
        g->models[0] = res;
        func_02028bb4(g->models[0]);
    }
    return 1;
}
