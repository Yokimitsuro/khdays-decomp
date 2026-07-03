extern void func_0203c634(void *obj, int idx, void *value);
extern void func_ov149_020cfd84(void);
extern void func_ov149_020cfe6c(void);
void func_ov149_020cfcf4(int *node) {
    int *state = (int *)node[1];
    signed char c = *(signed char *)(*state + 0x1c7);
    if (c != -1) {
        *(signed char *)(*state + 0x1c6) = c;
        switch (*(signed char *)(*state + 0x1c6)) {
        case 0:
            func_0203c634(node, 1, func_ov149_020cfd84);
            break;
        case 1:
            func_0203c634(node, 1, func_ov149_020cfe6c);
            break;
        }
        *(signed char *)(*state + 0x1c7) = 0xff;
    }
}
