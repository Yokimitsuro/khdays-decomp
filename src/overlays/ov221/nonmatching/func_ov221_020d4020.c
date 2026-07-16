/* func_ov221_020d4020 -- construct the object: install its four handlers, set up its flags, build
 * the two sub-objects and claim a palette slot.
 *
 * The handler table goes in first (+0x8, +0xc, +0x1c, +0x30), then the hw60 flags get 0x20 and
 * then 0x4e -- two separate writes, and the value at data_ov221_020d4ddc is read BETWEEN them, so
 * the order matters and they cannot be folded into one.
 *
 * The main sub-object is func_0203b898(func_ov107_020c9440(owner, 0x1a)), cached at +0x384 and
 * then configured three times (modes 0, 2, 4). data_ov221_020d4e54 is a rolling palette/slot
 * counter: this object takes the current value, then bumps it and wraps back to 3 at 0x1f -- so
 * slots 0..2 are reserved and the rest cycle.
 *
 * The second sub-object is only built when the saved value is non-negative; it is keyed off that
 * value rather than a constant.
 *
 * Both hw60 writes take the explicit extract/reassemble form (no `lsl#0x10 ; lsr#0x10` trunc pair
 * in the ROM), and the field at +8 of the last sub-object is a byte-in-word. See
 * codegen-cracks.md.
 *
 * ------------------------------------------------------------------------------------------
 * ★ UNFINISHED, NOT a tie: 500 vs 504 bytes -- ONE instruction, and it is a spill decision.
 *
 *   ROM:  push {r3,r4,r5,lr} ; ... str r2,[sp] ... ldr r1,[sp]     (r4=owner, r5=self,
 *                                                                   `saved` SPILLED into the
 *                                                                   pushed r3's slot)
 *   mine: push {r4,r5,r6,lr}                                       (r4=owner, r5=saved, r6=self)
 *
 * Both push four registers, so the frames cost the same; mwcc simply chose to keep `saved` in a
 * callee-saved register where the ROM parked it on the stack, and the missing instruction is that
 * `str r2,[sp]`. Everything else -- including the whole counter block and both hw60 writes --
 * is byte-identical.
 *
 * Tried and rejected: declaring `saved` last (the decl-order lever governs WHICH callee-saved
 * register a local gets, not whether it gets one at all). The value is read early, between the two
 * hw60 writes, and used once at the very end, so the source order is not in question either.
 *
 * Semantics are settled. This needs a way to make mwcc spill rather than allocate. */

typedef struct {
    unsigned f : 8;
} B8;

extern int func_ov107_020c9440(int owner, int kind);
extern int func_0203b898(int a);
extern void func_0203b9fc(int obj, int mode, int a, int b);
extern void func_02016b60(int a, int b, int slot);
extern void func_0203bfb4(int a, int obj);
extern void func_0203c7ac(int obj, int a);
extern void func_ov107_020c9074(int self, int obj);
extern int func_01fffca8(int a, int b, int c);
extern int func_ov107_020c319c(int a);
extern void func_ov221_020d4218(void);
extern void func_ov221_020d424c(void);
extern void func_ov221_020d42b0(void);
extern void func_ov221_020d443c(void);
extern int data_ov221_020d4ddc;
extern unsigned char data_ov221_020d4e54;

void func_ov221_020d4020(int self) {
    int owner;
    unsigned short v;
    int saved;

    owner = *(int *)(self + 0x390);
    *(void **)(self + 8) = (void *)func_ov221_020d4218;
    *(void **)(self + 0xc) = (void *)func_ov221_020d424c;
    *(void **)(self + 0x1c) = (void *)func_ov221_020d42b0;
    *(void **)(self + 0x30) = (void *)func_ov221_020d443c;

    v = *(unsigned short *)(self + 0x60);
    *(unsigned short *)(self + 0x60) =
        (unsigned short)((v & ~0xff00)
                         | (((((unsigned int)v << 0x10) >> 0x18 | 0x20) << 0x18) >> 0x10));

    saved = data_ov221_020d4ddc;

    v = *(unsigned short *)(self + 0x60);
    *(unsigned short *)(self + 0x60) =
        (unsigned short)((v & ~0xff00)
                         | (((((unsigned int)v << 0x10) >> 0x18 | 0x4e) << 0x18) >> 0x10));

    *(unsigned short *)(self + 0x1ae) |= 4;
    *(int *)(self + 0x70) = 1;
    *(int *)(self + 0x54) = 0;
    *(int *)(self + 0x58) = 0;
    *(int *)(*(int *)(self + 0x9c) + 0x5c) |= 4;

    *(int *)(self + 0x384) = func_0203b898(func_ov107_020c9440(owner, 0x1a));
    func_0203b9fc(*(int *)(self + 0x384), 0, 0, 1);
    func_0203b9fc(*(int *)(self + 0x384), 2, 0, 1);
    func_0203b9fc(*(int *)(self + 0x384), 4, 0, 1);
    func_02016b60(*(int *)(*(int *)(*(int *)(self + 0x384) + 0x88) + 0x78), 0,
                  data_ov221_020d4e54);

    /* Stored, then re-read through the byte for the wrap test -- that is what pins the store
     * ahead of the compare, which is where the ROM puts it. */
    data_ov221_020d4e54 = data_ov221_020d4e54 + 1;
    if (data_ov221_020d4e54 >= 0x1f) {
        data_ov221_020d4e54 = 3;
    }

    if (*(int *)(self + 0x384) != 0) {
        func_0203bfb4(*(int *)(self + 0x9c), *(int *)(self + 0x384));
        func_0203c7ac(*(int *)(self + 0x384), 0);
    }

    if (saved >= 0) {
        *(int *)(self + 0x394) = func_0203b898(func_ov107_020c9440(owner, saved));
        func_ov107_020c9074(self, *(int *)(self + 0x394));
        *(int *)(*(int *)(self + 0x394) + 0x5c) |= 2;
    }

    *(int *)(self + 0x388) = func_01fffca8(self + 0x22c, 0x10, 0x64);
    **(int **)(self + 0x388) = func_ov107_020c319c(self + 0x64);
    ((B8 *)(*(int *)(self + 0x388) + 8))->f |= 2;
    *(int *)(self + 0x38c) = 0;
}
