/* Recall entry: once both riders' +0xad bytes (+4 / +8 children) are clear, the two children
 * get their four channels (0, 1, 2, 4) bound with (1, 1) and the node moves to 020d615c. */
extern void func_0203b9fc(void *child, int cmd, int arg, int flag);
extern void func_0203c634(void *obj, int idx, void *value);
extern void func_ov236_020d615c(void);

void func_ov236_020d6094(int *node) {
    int *state = (int *)node[1];
    int i;
    if (*(unsigned char *)(state[1] + 0xad) != 0) return;
    if (*(unsigned char *)(state[2] + 0xad) != 0) return;
    for (i = 0; i < 2; i++) {
        func_0203b9fc((void *)state[i + 1], 0, 1, 1);
        func_0203b9fc((void *)state[i + 1], 1, 1, 1);
        func_0203b9fc((void *)state[i + 1], 2, 1, 1);
        func_0203b9fc((void *)state[i + 1], 4, 1, 1);
    }
    func_0203c634(node, *(signed char *)(node + 8), func_ov236_020d615c);
}
