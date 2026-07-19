/* NONMATCHING -- size-exact (176/176), one 3-instruction scheduling window off.
 *
 * WHAT IT IS (fully decoded, this part is solid): begin a save write for `slot`.
 *   - CARD_UnlockBackup, bump the sequence counter (func_02020904)
 *   - Ov008_EmitCommandAndStoreHandle(0, &local, 1); non-zero result -> abort
 *     with the shared error tail, return 0
 *   - accumulate PLAY TIME: ((now - data_0204be1c) << 6) / 0x1ff6210 added to
 *     *data_0204be18.  0x1ff6210 = 33,513,488 is the DS system clock, and the
 *     <<6 is because OS tick is clock/64 -- so this converts elapsed ticks to
 *     SECONDS.
 *   - MATH_CalcSHA1(buf+4, buf+0x18, 0x1cac) -- digest of the payload into the
 *     header - and then the magic 0xc8f592a6 at buf[0]
 *   - seed ctx (counter=0, slot) and issue block (slot*2)*0x2018 + 0x20
 *
 * ★ Because this function writes a magic + SHA1 into the buffer and then hands
 * it to func_ov008_0208ba70, that callee is the WRITE issuer -- which also makes
 * the Ov008/Ov009/Ov025_CardTransferStep family (same callee) the write stepper.
 * The x4 family at 0208bcdc calls a DIFFERENT issuer (0208b9e8, which allocates
 * 0x2d0 and runs another helper chain), so those two paths are not the same
 * operation.  Worth confirming before naming either one read/write.
 *
 * ★ func_02020368 is the 64-bit signed division runtime: writing the divide a
 * slightly different way made mwcc emit `_ll_sdiv` in that exact reloc slot.
 *
 * WHAT DIFFERS: only where `*data_0204be18` is loaded.
 *   ROM   ldr r0,[pc] ; lsls r1,r1,#6 ; ldr r4,[r0] ; lsrs r0,r3,#0x1a
 *   ours  ldr r2,[pc] ; lsrs r0,r3,#0x1a ; lsls r1,r1,#6 ; ldr r4,[r2]
 * The ROM interleaves the pointer deref between the two shifts; mwcc puts it
 * after both.  Everything before and after is byte-identical.
 *
 * RULED OUT (each still diffs, at 0x34 or 0x3D):
 *   - `*p += expr` vs `*p = *p + expr` vs a temp for the seconds (+4 bytes)
 *   - splitting the delta and the <<6 into separate statements (moves 0x34->0x3D,
 *     i.e. closer -- that form is the one kept here)
 *   - dropping the (int) cast on the quotient
 *   - a local pointer for data_0204be18 (hand-CSE, and it hoists the load even
 *     earlier)
 * NOT ruled out: arity is confirmed correct (Ov008_EmitCommandAndStoreHandle
 * takes 3, verified in Ghidra), mode is THUMB and was verified as such.
 * This is a scheduling window, not a wrong-C problem -- but per the project's
 * own record, "scheduling tie" has been wrong more often than right, so re-test
 * it rather than trusting this note.  Two twins ride on it:
 * func_ov009_02055e18 and func_ov025_020b0d00.
 */
extern void CARD_UnlockBackup(unsigned short lock);
extern int func_02020904(void);
extern int func_ov008_0208b930(int a, void *b, int c);
extern void func_0200e164(int id);
extern void func_020208f0(void);
extern long long func_020031d4(void);
extern void MATH_CalcSHA1(void *digest, const void *data, unsigned int len);
extern void func_ov008_0208ba70(int arg0, int arg1, int arg2);

extern unsigned short data_0204be10;
extern long long data_0204be1c;
extern int *data_0204be18;
extern unsigned int *data_0204be14;
extern unsigned char data_ov008_02090fb4[];

int func_ov008_0208bd9c(int slot) {
    int local;
    long long delta;

    CARD_UnlockBackup(data_0204be10);
    func_02020904();
    if (func_ov008_0208b930(0, &local, 1) != 0) {
        func_0200e164(data_0204be10);
        func_020208f0();
        return 0;
    }
    delta = (func_020031d4() - data_0204be1c) << 6;
    *data_0204be18 += (int)(delta / 0x1ff6210);
    MATH_CalcSHA1((char *)data_0204be14 + 4, (char *)data_0204be14 + 0x18, 0x1cac);
    *data_0204be14 = 0xc8f592a6;
    data_ov008_02090fb4[0] = 0;
    data_ov008_02090fb4[1] = (unsigned char)slot;
    func_ov008_0208ba70((data_ov008_02090fb4[1] << 1) * 0x2018 + 0x20,
                        (int)data_0204be14, 0x2018);
    return 1;
}
