/* func_ov245_020d2118 -- arm a straight-line move: latch the caller's distance into both +0x10 and
 * +0x14, clear the elapsed counter at +0x1c, reset the owner's velocity at +0x3bc to the shared
 * zero constant and put it in state 1. */
extern int data_02041dc8;

typedef struct { int x, y, z; } Vec3;

void func_ov245_020d2118(int *node, int v) {
    node[5] = v;
    node[4] = v;
    node[7] = 0;
    *(Vec3 *)(node[0] + 0x3bc) = *(Vec3 *)&data_02041dc8;
    *(unsigned char *)(node[0] + 0x1c7) = 1;
}
