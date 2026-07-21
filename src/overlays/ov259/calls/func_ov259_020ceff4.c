/* Enter the lunge reaction: snapshot the current velocity (node[8..10] -> node[5..7]), scale the
 * live velocity by 0xb00 (Fx12), set the reaction state to 2, and re-register the think callback. */
typedef struct { int x, y, z; } Vec3;
extern void func_01ffa724(int scale, void *dst, void *src);
extern void func_0203c634(int self, int idx, int cb);

void func_ov259_020ceff4(int param_1) {
    int *node = *(int **)(param_1 + 4);
    *(Vec3 *)(node + 5) = *(Vec3 *)(node + 8);
    func_01ffa724(0xb00, node + 8, node + 8);
    *(char *)(*node + 0x1c7) = 2;
    func_0203c634(param_1, *(signed char *)((char *)param_1 + 0x20), 0);
}
