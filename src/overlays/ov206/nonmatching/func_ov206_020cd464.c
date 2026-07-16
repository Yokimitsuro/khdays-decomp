/* func_ov206_020cd464 -- enter the behaviour: reset the owner, wire up the context, arm three
 * handlers.
 * The owner's state pair is reset (+0x1c6 to 0, +0x1c7 to -1) and the context's cached pointers
 * are pointed at the owner's live data: the transform at +0xb0, the pose at +0x74, and the rig's
 * name field at +0x384+0xad. The counters at +0x40/+0x44/+0x10 start at zero.
 * Flag 6 is then set in the high byte of the owner's +0x60 halfword, and three handlers are armed
 * through func_0203c634: action 1, 0 and 2 in that order.
 *
 * The +0x60 update is written as the explicit extract/reassemble the ROM uses rather than as a
 * bitfield store -- a standalone `hi |= K` on a bitfield adds a redundant & 0xffff (+8 B). Note
 * `v & ~0xff00` for the low-byte keep, NOT `v & 0xff`: the former gives the ROM's `bic #0xff00`,
 * the latter an `and #0xff`. See codegen-cracks.md.
 *
 * NONMATCHING: 184/184 bytes, same instruction count, first diff at 0x15. The -1 store must be
 * through a `signed char *`: as `unsigned char *` the constant folds to 0xff and mwcc materialises
 * `mov ip,#0xff`, where the ROM derives it from the live zero (`sub r2,lr,#1`) exactly as the
 * "derive -1 from a live 0" note predicts. With that fixed the only residue is which register
 * holds the -1 (ROM r2, mwcc ip) and, as a knock-on, where the first callback's pool load is
 * scheduled (ROM 0x30, mwcc 0x20 -- it hoists it into the r2 that the ROM still needs).
 * Register-permutation class; blocks the ov206/207/274/275 family for this shape. */
extern void func_0203c634(int self, int action, void (*cb)(void));
extern void func_ov206_020cd818(void);
extern void func_ov206_020cd51c(void);
extern void func_ov206_020cd72c(void);

void func_ov206_020cd464(int self) {
    int *ctx;
    unsigned short v;

    ctx = *(int **)(self + 4);
    *(unsigned char *)(ctx[0] + 0x1c6) = 0;
    *(signed char *)(ctx[0] + 0x1c7) = -1;
    ctx[0x10] = 0;
    ctx[0x11] = 0;
    ctx[1] = ctx[0] + 0xb0;
    ctx[2] = ctx[0] + 0x74;
    ctx[4] = 0;
    ctx[3] = *(int *)(ctx[0] + 0x384) + 0xad;

    v = *(unsigned short *)(ctx[0] + 0x60);
    *(unsigned short *)(ctx[0] + 0x60) =
        (unsigned short)((v & ~0xff00) |
                         (((((unsigned int)v << 0x10) >> 0x18 | 6) << 0x18) >> 0x10));

    func_0203c634(self, 1, func_ov206_020cd818);
    func_0203c634(self, 0, func_ov206_020cd51c);
    func_0203c634(self, 2, func_ov206_020cd72c);
}
