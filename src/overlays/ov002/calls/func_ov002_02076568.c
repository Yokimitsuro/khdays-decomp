extern int func_ov002_0207285c(int slot);
extern void func_ov002_02076af0(void *node);
extern void func_ov002_02076b48(void *node);
extern void func_ov002_02077ef8(unsigned short slot);
extern char data_ov002_0207fa20;

/* Releases every object queued on each live spawn slot and then resets the slot's actor pose. */
void func_ov002_02076568(void) {
    int i;
    char *node;
    char *next;
    for (i = 0; i < 0x18; i++) {
        if (func_ov002_0207285c(i) >= 0) {
            node = ((char **)*(char **)((char *)&data_ov002_0207fa20 + 4))[i];
            while (node != 0) {
                next = *(char **)(node + 4);
                func_ov002_02076af0(node);
                func_ov002_02076b48(node);
                node = next;
            }
            func_ov002_02077ef8((unsigned short)i);
        }
    }
}
