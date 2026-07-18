/*
 * func_ov271_020d23f0 -- x3. AI-state entry: wire up the sub-nodes and their hit regions, register two
 * handlers. Mark bit1 of *(node+0x5c) on each sub-node state[1..4]. On the first sub-node state[1] also
 * install the physics callback func_ov271_020d2158 at +0x6c and back-link the state at +0x84, then arm
 * its region 0 (0203b9fc). Arm state[2] regions 0/2/4 and state[4] regions 0/2 (state[3] is only
 * flagged). Set the hi nibble of state[0xe] to 0xf, clear state[0x14], clear the lo nibble of state[0xe].
 * Register handlers 0 and 1 via 0203c634 -> 020d06a4, 020d0764.
 */
struct nib { unsigned lo : 4, hi : 4; };
extern void func_0203b9fc(int a, int b, int c, int d);
extern void func_0203c634(int self, int idx, int cb);
extern void func_ov271_020d2158(void);
extern void func_ov271_020d2518(void);
extern void func_ov271_020d25d8(void);

void func_ov271_020d23f0(int *self) {
    int *state = (int *)self[1];

    *(int *)(state[1] + 0x5c) |= 2;
    *(int *)(state[1] + 0x6c) = (int)&func_ov271_020d2158;
    *(int *)(state[1] + 0x84) = (int)state;
    func_0203b9fc(state[1], 0, 0, 1);
    *(int *)(state[2] + 0x5c) |= 2;
    func_0203b9fc(state[2], 0, 0, 1);
    func_0203b9fc(state[2], 2, 0, 1);
    func_0203b9fc(state[2], 4, 0, 1);
    *(int *)(state[3] + 0x5c) |= 2;
    *(int *)(state[4] + 0x5c) |= 2;
    func_0203b9fc(state[4], 0, 0, 1);
    func_0203b9fc(state[4], 2, 0, 1);
    ((struct nib *)(state + 0xe))->hi = 0xf;
    state[0x14] = 0;
    ((struct nib *)(state + 0xe))->lo = 0;
    func_0203c634((int)self, 0, (int)&func_ov271_020d2518);
    func_0203c634((int)self, 1, (int)&func_ov271_020d25d8);
}
