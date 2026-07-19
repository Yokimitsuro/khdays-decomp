extern int func_ov002_0207285c(int slot);
extern void func_ov002_02076b68(void *node);
extern char data_ov002_0207fa20;

/* Walks all 24 spawn slots and tears down every object still queued on each live one. */
void func_ov002_02076534(void) {
    int i;
    char *node;
    char *next;
    for (i = 0; i < 0x18; i++) {
        if (func_ov002_0207285c(i) >= 0) {
            node = ((char **)*(char **)((char *)&data_ov002_0207fa20 + 4))[i];
            while (node != 0) {
                next = *(char **)(node + 4);
                func_ov002_02076b68(node);
                node = next;
            }
        }
    }
}
