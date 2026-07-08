extern int func_0202a818(int arg0, int arg1);
extern void func_0203c640(void *node);

void func_ov284_020cd55c(int *node) {
    if ((func_0202a818(*(int *)(*(int *)(node[1] + 4) + 0x88), *(int *)(*node + 0x2c) * 0x1e) & 1) != 0) {
        func_0203c640(node);
    }
}
