/* Recount the +0x410 kind histogram (four words) of the actor's +0x404 slot table: each of the
 * six slots that holds a +0x390 item adds one to the bucket of that item's +0x1b4 kind. */
typedef unsigned int u32;
extern void MI_CpuFill8(void *dst, u32 data, u32 size);

void func_ov277_020cfb60(int *node) {
    int *state = (int *)node[1];
    int i;

    MI_CpuFill8((void *)(*state + 0x410), 0, 0x10);
    for (i = 0; i < 6; i++) {
        int item = *(int *)(((int *)*(int *)(*state + 0x404))[i] + 0x390);
        if (item != 0) {
            *(int *)(*state + *(unsigned char *)(item + 0x1b4) * 4 + 0x410) += 1;
        }
    }
}
