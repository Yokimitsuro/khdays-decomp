/*
 * func_ov125_020ce5b0 -- AI-state entry: wire up the sub-nodes and their hit regions, register
 * two handlers. Mark bit1 of *(node+0x5c) on each sub-node state[1..5]. On the first sub-node
 * state[1] also install the physics callback func_ov125_020ce45c at +0x6c, back-link the state
 * at +0x84, scale its placement to 0x1000/0/0x1000 and arm its region 0 (0203b9fc). Arm state[2] and
 * state[3] regions 0/2/4 (state[3] scaled 0x2000/0x1000/0x2000), flag state[4], and arm
 * state[5] regions 0/2/4. Set the hi nibble of state[0xd] to 0xf and clear its lo nibble.
 * Register handlers 0 and 1 via 0203c634 -> 020ce75c, 020ce84c.
 */
struct nib { unsigned lo : 4, hi : 4; };
extern void func_0203ca50(void *placement, int x, int y, int z);
extern void func_0203b9fc(int a, int b, int c, int d);
extern void func_0203c634(int self, int idx, int cb);
extern void func_ov125_020ce45c(void);
extern void func_ov125_020ce75c(void);
extern void func_ov125_020ce84c(void);

void func_ov125_020ce5b0(int *self) {
    int *state = (int *)self[1];

    *(int *)(state[1] + 0x5c) |= 2;
    *(int *)(state[1] + 0x6c) = (int)&func_ov125_020ce45c;
    *(int *)(state[1] + 0x84) = (int)state;
    func_0203ca50((void *)(state[1] + 4), 0x1000, 0, 0x1000);
    func_0203b9fc(state[1], 0, 0, 1);
    *(int *)(state[2] + 0x5c) |= 2;
    func_0203b9fc(state[2], 0, 0, 1);
    func_0203b9fc(state[2], 2, 0, 1);
    func_0203b9fc(state[2], 4, 0, 1);
    *(int *)(state[3] + 0x5c) |= 2;
    func_0203b9fc(state[3], 0, 0, 1);
    func_0203b9fc(state[3], 2, 0, 1);
    func_0203b9fc(state[3], 4, 0, 1);
    func_0203ca50((void *)(state[3] + 4), 0x2000, 0x1000, 0x2000);
    *(int *)(state[4] + 0x5c) |= 2;
    *(int *)(state[5] + 0x5c) |= 2;
    func_0203b9fc(state[5], 0, 0, 1);
    func_0203b9fc(state[5], 2, 0, 1);
    func_0203b9fc(state[5], 4, 0, 1);
    ((struct nib *)(state + 0xd))->hi = 0xf;
    ((struct nib *)(state + 0xd))->lo = 0;
    func_0203c634((int)self, 0, (int)&func_ov125_020ce75c);
    func_0203c634((int)self, 1, (int)&func_ov125_020ce84c);
}
