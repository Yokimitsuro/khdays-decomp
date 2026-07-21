/* Begin the wind-up: set the two charge timers (node[10]=0x600, node[0xb]=0x300), clear node[9],
 * flag the owner's charging bit (*node+0x390), zero the aim vector (node[3..5]), and register the
 * wind-up think callback. */
typedef struct { int x, y, z; } Vec3;
extern Vec3 data_02041dc8;
extern void func_0203c634(int self, int idx, void *cb);
extern void func_ov245_020d18b0(void);

void func_ov245_020d1858(int param_1) {
    int *node = *(int **)(param_1 + 4);
    node[10] = 0x600;
    node[0xb] = 0x300;
    node[9] = 0;
    *(int *)(*node + 0x390) = 1;
    *(Vec3 *)(node + 3) = data_02041dc8;
    func_0203c634(param_1, *(signed char *)((char *)param_1 + 0x20), &func_ov245_020d18b0);
}
