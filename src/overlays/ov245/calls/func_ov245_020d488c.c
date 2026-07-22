/* func_ov245_020d488c -- reset the velocity vector at +0x3a0 to the shared zero constant, and if
 * the object is in mode 1 hand its context (+0x214) to the follow-up. */
extern void func_ov245_020d4e14(int a);
extern int data_02041dc8;

typedef struct { int x, y, z; } Vec3;

void func_ov245_020d488c(int self) {
    *(Vec3 *)(self + 0x3a0) = *(Vec3 *)&data_02041dc8;
    if (*(int *)(self + 0x50) != 1) {
        return;
    }
    func_ov245_020d4e14(*(int *)(self + 0x214));
}
