/* NONMATCHING: semantically complete, loop-body instruction-scheduling tie. The count read,
 * the array-of-Entry4 index (i*4 via lsl, not an induction pointer -- that crack IS applied),
 * the two follow-up allocs and the list teardown all match; residue is ~16 bytes inside the
 * 4-byte copy loop, where mwcc loads the second byte of each pair before the first (and picks
 * r2 vs the ROM's r3 for the entry pointer). Direct, temp-pair, and swapped-load forms all
 * leave the same scheduling. Behaviour: flatten a build-list of 4-byte entries into a packed
 * array at node+0x94, then alloc node+0x9c/+0xa0 and free the list at node+0xb0. */
typedef struct {
    unsigned char b0, b1, b2, b3;
} Entry4;

extern void *func_0203d15c(int size);
extern unsigned char *func_01fffd70(int list);
extern unsigned char *func_01fffd8c(int list);
extern void NNSi_FndDestroyDoubleList(void *list);
extern void func_0203d194(int object);

void func_ov107_020c9618(int node) {
    int count = *(int *)(*(int *)(node + 0xb0) + 0x20);
    int i;
    unsigned char *p;

    *(int *)(node + 0x98) = count;
    *(void **)(node + 0x94) = func_0203d15c(count << 2);
    i = 0;
    p = (unsigned char *)func_01fffd70(*(int *)(node + 0xb0));
    while (p != 0) {
        Entry4 *arr = (Entry4 *)*(int *)(node + 0x94);
        arr[i].b0 = p[0];
        arr[i].b1 = p[1];
        arr[i].b2 = p[2];
        arr[i].b3 = p[3];
        i++;
        p = (unsigned char *)func_01fffd8c(*(int *)(node + 0xb0));
    }
    *(void **)(node + 0x9c) = func_0203d15c(*(int *)(node + 0x98));
    *(void **)(node + 0xa0) = func_0203d15c(*(int *)(node + 0x98));
    NNSi_FndDestroyDoubleList(*(void **)(node + 0xb0));
    func_0203d194(*(int *)(node + 0xb0));
    *(int *)(node + 0xb0) = 0;
}
