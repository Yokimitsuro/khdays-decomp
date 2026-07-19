typedef struct { int x, y, z; } Vec3;

/* Arms the slot: clears the timer, marks it active, flags the node dirty, drops the pending
 * target and snapshots the base pose into the working one. */
void func_ov255_020d27cc(int *self) {
    char *node;
    self[2] = 0;
    *((char *)self + 0xc) = 1;
    node = (char *)self[1];
    *(int *)(node + 0x5c) |= 2;
    *(int *)(*self + 0x3cc) = 0;
    *(Vec3 *)(*self + 0x39c) = *(Vec3 *)(*self + 0xb0);
}
