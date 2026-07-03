extern void func_0203c634(void *obj, int idx, void *value);
extern void func_ov178_020ceb74(void);
extern void func_ov178_020cec18(void);
void func_ov178_020ceaf8(int *node) {
    int *state = (int *)node[1];
    signed char c = *(signed char *)(*state + 0x1c7);
    if (c != -1) {
        *(signed char *)(*state + 0x1c6) = c;
        switch (*(signed char *)(*state + 0x1c6)) {
        case 0:
            func_0203c634(node, 1, func_ov178_020ceb74);
            break;
        case 1:
            func_0203c634(node, 1, func_ov178_020cec18);
            break;
        }
    }
    *(signed char *)(*state + 0x1c7) = 0xff;
}
