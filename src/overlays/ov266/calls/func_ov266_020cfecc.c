/* func_ov266_020cfecc -- reset the tracking block and re-point the emitter.
 *
 * One of a 3-member shape family; the twins live in ov212/ov267 and are byte-identical modulo
 * relocs (matched here, fanned out with dedupprop).
 *
 * Zeroes the counter at +0x5dc and the two flag
 * bytes at +0x5e0/+0x5e1, parks the vector at +0x4e4 back on the constant data_02041dc8, and pushes
 * the (16-bit) id through func_0203b9fc against the thing at +0x388.
 *
 * `(short)id` is the ROM's `lsl #0x10 ; asr #0x10` sign-extend, so the parameter really is a signed
 * 16-bit value widened at the call -- not an int the compiler happened to truncate. (Declaring the
 * param `short` outright is NOT the same thing and loses 4 bytes.)
 *
 * ★ func_0203b9fc takes FOUR arguments, not three. Declaring it with three silently drops the
 * trailing 0 -- and that 0 is the ROM's `mov r3, #0`, which is ALSO the value the three zero-stores
 * share. With the argument present mwcc must put it in r3 and everything falls into place; without
 * it, the 0 is a free scratch value and lands in ip instead, which reads as an unbreakable
 * allocator coin-flip. It is not: it is a dropped argument (SKILL.md's phantom-args trap). */

typedef struct {
    int x;
    int y;
    int z;
} VecFx32;

extern void func_0203b9fc(int a, int b, int c, int d);
extern VecFx32 data_02041dc8;

void func_ov266_020cfecc(int obj, int id) {
    *(int *)(obj + 0x5dc) = 0;
    *(signed char *)(obj + 0x5e0) = 0;
    *(signed char *)(obj + 0x5e1) = 0;
    *(VecFx32 *)(obj + 0x4e4) = data_02041dc8;
    func_0203b9fc(*(int *)(obj + 0x388), 0, (short)id, 0);
}
