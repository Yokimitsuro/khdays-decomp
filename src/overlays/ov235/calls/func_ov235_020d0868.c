extern void func_ov235_020cccc0(int node, int arg, void *outVec, int *outScale);
extern void func_01ffa724(int scale, void *src, void *dst);
extern void func_0203c634(int self, int idx, int cb);

void func_ov235_020d0868(int param_1) {
    int *node = *(int **)(param_1 + 4);
    int scale;
    int aim[3];
    func_ov235_020cccc0((int)node, node[0x17], aim, &scale);
    func_01ffa724(scale, aim, node + 4);
    if (*(unsigned char *)node[3] == 0) {
        *(char *)(*node + 0x1c7) = 2;
        func_0203c634(param_1, *(signed char *)((char *)param_1 + 0x20), 0);
    }
}
