/* Aim and launch a homing move: compute the aim vector and speed toward the target
 * (func_ov257_020ccf98 with node[0x18]) into stack buffers, scale it into the velocity (node[4]),
 * then if the target is still valid (*node[3] == 0) enter the move state (2) and register the
 * callback. */
extern void func_ov257_020ccf98(int node, int arg, void *outVec, int *outScale);
extern void func_01ffa724(int scale, void *src, void *dst);
extern void func_0203c634(int self, int idx, int cb);

void func_ov257_020d0900(int param_1) {
    int *node = *(int **)(param_1 + 4);
    int scale;
    int aim[3];
    func_ov257_020ccf98((int)node, node[0x18], aim, &scale);
    func_01ffa724(scale, aim, node + 4);
    if (*(unsigned char *)node[3] == 0) {
        *(char *)(*node + 0x1c7) = 2;
        func_0203c634(param_1, *(signed char *)((char *)param_1 + 0x20), 0);
    }
}
