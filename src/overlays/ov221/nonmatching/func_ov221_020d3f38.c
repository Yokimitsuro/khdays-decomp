/* func_ov221_020d3f38 -- retune, notify, and (in mode 1) start the homing move.
 * VARIADIC -- the stmdb {r0,r1,r2,r3} prologue is the tell. Its own varargs are three Vec3 by
 * value: the first is handed to func_ov107_020c5c54 as a va_list, and the second and third are
 * forwarded BY VALUE to func_ov221_020d43a0 (itself variadic).
 *
 * Bit 1 of +0x40 is a SIGNED bitfield (the ROM extracts it with asr, not lsr) and gates the
 * owner's own notify hook (+0xc), which is loaded only if that bit is set. The rig at +0x384 is
 * reset when there is one, +0x38c is raised, and unless +0x50 is exactly 1 that is where it stops.
 *
 * The two forwarded Vec3 explain the whole tail. 020d43a0 takes (ctx, mode, Vec3, Vec3): the first
 * Vec3 goes in r2/r3 plus the outgoing slot at sp+0, so the SECOND lands at sp+4..0xc -- which is
 * why the frame is 0x10 and why the second is stored before the first. It looks like a dead local
 * at sp+4 until you notice 020d43a0 reads varargs past its Vec3 (its `add r2,sp,#0x24`).
 *
 * NONMATCHING: 180/180 bytes, byte-exact except ONE instruction at 0xc -- and it is the SAME tie
 * as its sibling func_ov221_020d43a0: the ROM caches the mode from its argument register
 * (`mov r4,r1`), mwcc reads it back from the block the variadic prologue spilled
 * (`ldr r4,[sp,#0x24]`), because va_start takes the parameter's address. Two independent
 * functions, one root cause -- that is now confirmed rather than suspected.
 *
 * FOUR knobs are solved here and must be kept; only the mode-register residue is open:
 * 1. The 4th argument. The apparent dead local at sp+4 is 020d43a0's SECOND by-value Vec3 -- it is
 *    variadic, so its first Vec3 takes r2/r3 + sp+0 and the second lands at sp+4..0xc. Reading it
 *    as a local costs 28 B and mwcc drops the store as dead.
 * 2. Bit 1 of +0x40 is a SIGNED bitfield -- `int b:1`, giving asrs. As unsigned you get lsrs.
 * 3. The hook must be captured INSIDE the condition (`(notify = *(...)) != 0`): as two separate
 *    expressions mwcc loads +0xc twice, once predicated for the test and again for the call.
 * 4. The varargs must be folded to their own frame offsets (va_at), not reached through a held
 *    va_list: a live `ap` gets parked in a callee-saved register and spills the mode. */

typedef struct {
    int x;
    int y;
    int z;
} Vec3;

#define va_start(ap, last) ((ap) = (char *)(&(last) + 1))
/* Reach a vararg by its offset without keeping a live va_list. Using a held `ap` for these two
 * makes mwcc park it in a callee-saved register (add r4,sp,#0x28 ; add r0,r4,#0xc) and spill the
 * mode; folding each one to its own frame offset gives the ROM's `add r0,sp,#0x34`. */
#define va_at(last, off) (*(Vec3 *)((char *)(&(last) + 1) + (off)))

extern void func_ov107_020c5c54(int self, char *ap);
extern void func_0203c7ac(int rig, int a);
extern void func_ov221_020d43a0(int ctx, int mode, Vec3 a, Vec3 b);

typedef struct {
    char pad[0x40];
    int b40_0 : 1;
    int b40_1 : 1;
    int b40_rest : 30;
} Ov221_Self;

void func_ov221_020d3f38(int self, int mode, ...) {
    int m;
    void (*notify)(int, int);

    m = mode;
    func_ov107_020c5c54(self, (char *)(&mode + 1));

    /* The hook is captured INSIDE the condition on purpose: as two separate expressions mwcc
     * loads +0xc twice (once predicated for the test, once again for the call). */
    if (((Ov221_Self *)self)->b40_1 && (notify = *(void (**)(int, int))(self + 0xc)) != 0) {
        notify(self, 0);
    }
    if (*(int *)(self + 0x384) != 0) {
        func_0203c7ac(*(int *)(self + 0x384), 0);
    }
    *(int *)(self + 0x38c) = 1;
    if (*(int *)(self + 0x50) != 1) {
        return;
    }

    func_ov221_020d43a0(*(int *)(self + 0x214), m, va_at(mode, 0xc), va_at(mode, 0x18));
}
