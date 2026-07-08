extern void func_0203c634(void *obj, int idx, void *value);
extern void func_ov299_020d3b18(void);
extern void func_ov299_020d3b54(void);

void func_ov299_020d3a9c(int *node)
{
    int *state = (int *)node[1];
    signed char next = *(signed char *)(*state + 0x1c7);

    if (next == -1) {
        return;
    }
    *(signed char *)(*state + 0x1c6) = next;
    switch (*(signed char *)(*state + 0x1c6)) {
    case 0:
        func_0203c634(node, 1, func_ov299_020d3b18);
        break;
    case 2:
        func_0203c634(node, 1, func_ov299_020d3b54);
        break;
    }
    *(signed char *)(*state + 0x1c7) = -1;
}
