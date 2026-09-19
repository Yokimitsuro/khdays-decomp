/* Sweep entry: raises bit 0 of the actor's +0x394, builds a yaw of 0xc91 about data_02042264 and
 * re-acquires the lock-on target into +0x60 (none: pose request 0, dispatch null). The +8 bone
 * pose is pushed into the actor's +0xa0 slot, the actor's +0x398 pose rotated by that yaw becomes
 * the +0x50 pose and is copied to +0x40, +0x20 and +0x30, the target's +0x74 position is kept at
 * +0x70, the +0x18 timer clears with a +0x1c range of 0.8, +0x7c/+0x80/+0x84 clear, effect 0x162
 * (kind 6) spawns at the +4 anchor from the +0x384 model and the node moves to 020d0d8c. */
typedef struct { int x, y, z; } Vec3;
struct m4 { int w[4]; };
struct blk11 { int w[11]; };
struct Bits394 { unsigned int b0 : 1; };
struct Ov273ActorPose { char pad[0xa0]; struct blk11 bones; };
extern void func_0202f188(void *dst, void *k, int angle);
extern int  func_ov107_020cab14(int obj, int flag);
extern void func_0203c634(int self, int idx, int cb);
extern void func_0202ef54(void *out, void *a, void *b);
extern void func_ov107_020c5af8(int actor, int id, int kind, void *anchor);
extern int  data_02042264;
extern void func_ov273_020d49cc(void);

void func_ov273_020d4868(int *self) {
    int *state = (int *)self[1];
    struct m4 yaw = {0};
    int target;

    ((struct Bits394 *)(*state + 0x394))->b0 = 1;
    func_0202f188(&yaw, &data_02042264, 0xc91);
    target = state[0x18] = func_ov107_020cab14(*state, 0);
    if (target == 0) {
        *(unsigned char *)(*state + 0x1c7) = 0;
        func_0203c634((int)self, *(signed char *)((int)self + 0x20), 0);
        return;
    }
    ((struct Ov273ActorPose *)*state)->bones = *(struct blk11 *)state[2];
    *(struct m4 *)(state + 0x14) = *(struct m4 *)(*state + 0x398);
    func_0202ef54(state + 0x14, state + 0x14, &yaw);
    *(struct m4 *)(state + 0x10) = *(struct m4 *)(state + 0x14);
    *(Vec3 *)(state + 0x1c) = *(Vec3 *)(state[0x18] + 0x74);
    *(struct m4 *)(state + 8) = *(struct m4 *)(state + 0x14);
    *(struct m4 *)(state + 0xc) = *(struct m4 *)(state + 8);
    state[6] = 0;
    state[7] = 0xccd;
    state[0x1f] = 0;
    state[0x20] = 0;
    func_ov107_020c5af8(*(int *)(*state + 0x384), 0x162, 6, (void *)state[1]);
    *((unsigned char *)state + 0x84) = 0;
    func_0203c634((int)self, *(signed char *)((int)self + 0x20), (int)&func_ov273_020d49cc);
}
