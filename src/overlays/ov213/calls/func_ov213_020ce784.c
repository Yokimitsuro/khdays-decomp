/* Charge entry: re-acquires the lock-on target into +0x24; with none, pose request 2 is queued
 * and the node dispatches null. Otherwise the +0x38 orientation is built to look from the actor
 * (+0x74) at the target (+0x74) with the data_02042264 up vector, the +0x48 rate becomes 30/10
 * of the frame step, pose 8 plays on the actor and pose 0 on its +0x3dc partner, effect 9 is
 * spawned at the zero vector (data_02041dc8) and the node moves to 020ce88c. */
struct vec { int x, y, z; };
extern int  func_ov107_020cab14(int obj, int flag);
extern void func_0203cd7c(void *out, int a, int b, void *c);
extern void func_0202ea48(void *quat, void *mtx);
extern void func_ov107_020c9264(int a, int b, int c);
extern void func_ov107_020c0b90(int owner, int mode, struct vec v, int flag);
extern void func_0203c634(int self, int idx, void *cb);
extern void func_ov213_020ce88c(void);
extern int  data_02042264;
extern struct vec data_02041dc8;

void func_ov213_020ce784(int *self) {
    int *state = (int *)self[1];
    int mtx[9];
    int target;

    target = state[9] = func_ov107_020cab14(*state, 0);
    if (target == 0) {
        *(unsigned char *)(*state + 0x1c7) = 2;
        func_0203c634((int)self, *(signed char *)((int)self + 0x20), 0);
        return;
    }
    func_0203cd7c(mtx, target + 0x74, *state + 0x74, &data_02042264);
    func_0202ea48((void *)(state + 0xe), mtx);
    state[0x12] = *(int *)(self[0] + 0x2c) * 30 / 10;
    func_ov107_020c9264(*state, 8, 0);
    func_ov107_020c9264(*(int *)(*state + 0x3dc), 0, 0);
    func_ov107_020c0b90(*state, 9, data_02041dc8, 0);
    func_0203c634((int)self, *(signed char *)((int)self + 0x20), &func_ov213_020ce88c);
}
