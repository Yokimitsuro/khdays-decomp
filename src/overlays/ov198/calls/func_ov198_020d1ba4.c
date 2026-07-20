/* Command handler: place one of the two attached nodes from a packed transform.
 *
 * Only acts on command 5 targeting slot 0 or 1.  The command carries three 24-bit
 * BIG-ENDIAN fixed-point components at +5, +8 and +0xb; each is reassembled by writing its
 * three bytes REVERSED into the high end of a stack word and taking `>> 8`, which both
 * swaps the byte order and sign-extends from bit 23 in one go.  Those become a Vec3, an
 * identity transform is built and translated by it, and the result is handed to the
 * placement helper; the returned handle replaces the slot at owner + slot*8 + 0x398.
 * Everything else in the command stream falls through to the shared tail.
 *
 * TWO CODEGEN POINTS:
 *  - the slot guard must be written as `!(slot != 0 && slot != 1)`.  Spelled as
 *    `slot == 0 || slot == 1` mwcc folds it into an unsigned range test (`cmp #1 ; bhi`)
 *    and the function comes out 4 bytes short; the De Morgan form gives the ROM's
 *    `cmp #0 ; cmpne #1 ; bne` chain.  Reversing the operands or going through an int
 *    local does not help -- only the negation does.  (A three-or-more-value chain, as in
 *    Ov*_ReleaseByStateAndSyncSrt, has no range to fold into and needs no such care.)
 *  - declaration order sets the frame: the 0x2c-byte transform is at the TOP of the frame
 *    and the byte-assembly buffer at the bottom, so they are declared in that order --
 *    mwcc gives the lower address to the later declaration.
 */
typedef struct { int w[11]; } SrtTransform;
typedef struct { int x, y, z; } Vec3;

extern void func_0203c960(SrtTransform *m);
extern void func_0203ca30(SrtTransform *m, const Vec3 *v);
extern int func_ov107_020c0794(int a, int node, int kind, int z, SrtTransform *m);
extern void func_ov107_020c7500(int owner, unsigned char *cmd, int arg);

void func_ov198_020d1ba4(int owner, unsigned char *cmd, int arg) {
    SrtTransform m;
    Vec3 v;
    union { int w[3]; unsigned char b[12]; } t;

    if (cmd[2] == 5 && !(cmd[3] != 0 && cmd[3] != 1)) {
        t.b[3] = cmd[5];
        t.b[2] = cmd[6];
        t.b[1] = cmd[7];
        v.x = t.w[0] >> 8;
        t.b[7] = cmd[8];
        t.b[6] = cmd[9];
        t.b[5] = cmd[0xa];
        v.y = t.w[1] >> 8;
        t.b[11] = cmd[0xb];
        t.b[10] = cmd[0xc];
        t.b[9] = cmd[0xd];
        v.z = t.w[2] >> 8;

        func_0203c960(&m);
        func_0203ca30(&m, &v);
        *(int *)((char *)owner + cmd[3] * 8 + 0x398) =
            func_ov107_020c0794(*(int *)(owner + 0x3c),
                                *(int *)((char *)owner + cmd[3] * 8 + 0x394), 0x17, 0, &m);
    }
    func_ov107_020c7500(owner, cmd, arg);
}
