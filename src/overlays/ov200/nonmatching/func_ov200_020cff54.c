/*
 * NONMATCHING -- 180/180 size-exact, diff @0x10-0x14: the `state = self[1]` load slot. The ROM loads
 * it in the gap BETWEEN the two config `ldrh`s and the two `strh`s (`ldrh;ldrh;ldr r4;strh;strh`);
 * mwcc schedules it either one slot too early (state decl at top) or after both strh (decl moved down)
 * -- neither hits the ROM's exact slot. Same blx/pt-scheduling residue class as func_ov200_020cfcfc.
 * Everything else (020ce8f0 refresh, delta*30/30, attack 6, the +0x1ae |= 8, the blx, the handoff) is
 * byte-exact. Attack only the state-load slot.
 *
 * func_ov200_020cff54 -- x3 (ov200/201/271). AI-state enter: refresh, fire, flag, and notify.
 * Load the two config halfwords (data_ov200_020d182c +0xc/+0xe) into a scratch point. Refresh the
 * owner (020ce8f0), set state[0x18] = owner_delta*30/30, fire attack 6 (flag 1), OR flag 8 into the
 * owner halfword at *state+0x1ae. If the owner has a callback at *state+0x24, invoke it
 * (fp(*state, &pt, 4)). Clear the timer state[0x14] and hand off to the 020d0008 state.
 */
struct pt { unsigned short a, b; };
extern void func_ov200_020ce8f0(int self);
extern void func_ov107_020c9264(int a, int b, int c);
extern void func_0203c634(int self, int idx, int cb);
extern unsigned short data_ov200_020d182c[];
extern void func_ov200_020d0008(void);

void func_ov200_020cff54(int *self) {
    struct pt pt;
    void (*fp)(int, void *, int);
    int *state;

    pt.a = data_ov200_020d182c[6];
    pt.b = data_ov200_020d182c[7];
    state = (int *)self[1];
    func_ov200_020ce8f0((int)self);
    state[0x18] = *(int *)(*self + 0x2c) * 0x1e / 30;
    func_ov107_020c9264(*state, 6, 1);
    *(unsigned short *)(*state + 0x1ae) |= 8;
    fp = *(void (**)(int, void *, int))(*state + 0x24);
    if (fp != 0) {
        fp(*state, &pt, 4);
    }
    state[0x14] = 0;
    func_0203c634((int)self, *(signed char *)((int)self + 0x20), (int)&func_ov200_020d0008);
}
