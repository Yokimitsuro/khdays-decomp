/* func_ov000_02054c50 -- set up the screen's work area and register everything it draws.
 *
 * The work area starts 0x18 into the block at data_0204be14; that pointer is cached at
 * data_0204be18 and the whole 0x1cac of it is zeroed. Two sub-regions get a second clear as
 * halfwords (+0xee0 for 0xf0, +0xc10 for 0x2d0) and one as words with -1 (+0x198c for 0x320) --
 * different fill values, so they are different kinds of table, not one big buffer.
 *
 * `slot` is clamped to 0..3 before being passed on as a halfword: it selects which of the four
 * save slots this screen shows.
 *
 * The rest is a flat registration table, func_020235e8(id, kind, flag), for the resources the
 * screen needs. The ids cluster in three runs (0x35bf-0x37c7, 0x3c15-0x3c29, and the pair
 * 0xab3/0x95b registered with kind 4), which is why they are written out rather than looped.
 *
 * THUMB -- verify with --thumb. */

extern void *data_0204be14;
extern void *data_0204be18;

extern void *MI_CpuFill8(void *dst, unsigned char v, unsigned int n);
extern void MIi_CpuClear16(unsigned short v, void *dst, unsigned int n);
extern void INITi_CpuClear32_0x01ff86fc(unsigned int v, void *dst, unsigned int n);
extern void func_020235e8(int id, int kind, int flag);

void func_ov000_02054c50(int slot) {
    data_0204be18 = (char *)data_0204be14 + 0x18;
    MI_CpuFill8(data_0204be18, 0, 0x1cac);
    func_020235e8(0, 9, 0x191);

    if (slot < 0) {
        slot = 0;
    }
    if (slot > 3) {
        slot = 3;
    }
    func_020235e8(0x40a, 2, (unsigned short)slot);

    MIi_CpuClear16(0, (char *)data_0204be18 + 0xee0, 0xf0);
    MIi_CpuClear16(0, (char *)data_0204be18 + 0xc10, 0x2d0);

    func_020235e8(0x37c4, 1, 0);
    func_020235e8(0x37bf, 1, 0);
    func_020235e8(0x37c0, 2, 1);
    func_020235e8(0x37c3, 1, 0);
    func_020235e8(0x37c2, 1, 0);
    func_020235e8(0x37c5, 1, 0);
    func_020235e8(0x37c6, 1, 1);
    func_020235e8(0x37c7, 2, 0);
    func_020235e8(0x35bf, 2, 0);
    func_020235e8(0x3c15, 1, 1);
    func_020235e8(0x3c16, 1, 1);
    func_020235e8(0x3c17, 2, 0);
    func_020235e8(0x3c19, 2, 0);
    func_020235e8(0x3c1b, 2, 2);
    func_020235e8(0x3c1d, 2, 1);
    func_020235e8(0x3c26, 1, 1);
    func_020235e8(0x3c1f, 1, 0);
    func_020235e8(0x3c20, 1, 1);
    func_020235e8(0x35c1, 2, 1);
    func_020235e8(0x3c23, 2, 1);
    func_020235e8(0x3c21, 2, 1);
    func_020235e8(0x3c25, 1, 0);
    func_020235e8(0x3c27, 2, 1);
    func_020235e8(0x3c29, 2, 1);
    func_020235e8(0xab3, 4, 8);
    func_020235e8(0x95b, 4, 8);

    INITi_CpuClear32_0x01ff86fc(-1, (char *)data_0204be18 + 0x198c, 0x320);
}
