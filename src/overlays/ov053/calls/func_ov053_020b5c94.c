/*
 * Bind the actor's two UI channels and build the rig's slot maps. Channel 0 (+0xda8, config
 * +0x2c2c, 3 tracks) and channel 1 (+0xf0c, config +0x2c80, 4 tracks) are opened, flagged
 * (bit 0 when their +1 byte is set) and bound to the actor's +0x910 block; channel 0 is then
 * driven with tag 0x78. Channel 1 drops its bit 3 before the rig's two 13-entry maps are
 * built: +0x2cd4 (kind -> slot) and +0x2c88 (slot -> id) start at -1, then every kind in the
 * +0x2c34 list (up to the first negative) that maps to an id -- 2, 5, 8, 9, 11 -> 0..4 -- gets
 * the next slot. Channel 1 is finally driven with tag 0xbe.
 *
 * THUMB. The table accesses are spelled `base + i + 0x2cd4` (index first): with the constant
 * first mwcc hoists `base + 0x2cd4` out of the loops and spills `base`. `n = 0` sits before the
 * first loop (its zero seeds `i` and the -1), and `id = -1` precedes the kind load so the load's
 * address temp takes r2, not r1.
 */
extern void func_ov022_0209fb60(int a, int b, int c);
extern void func_ov022_0209fb98(int a, int b, int c);
extern void func_ov002_02051d6c(int a, int b, int c);
extern void func_ov002_02051eec(int a, int b, int c, int d, int e);
extern int data_ov053_020b7e60;

void func_ov053_020b5c94(int self) {
    int base = *(int *)&data_ov053_020b7e60;

    func_ov022_0209fb60(self, 0, 3);
    func_ov022_0209fb98(self, 0, 1);
    if (*(signed char *)(self + 0xda9) != 0) {
        *(unsigned char *)(self + 0xda8) |= 1;
    }
    func_ov002_02051d6c(self + 0xda8, base + 0x2c2c, self + 0x910);
    func_ov002_02051eec(self + 0xda8, base + 0x2c2c, *(int *)(self + 0x2bd0),
                        *(unsigned char *)(self + 9), 0x78);
    func_ov022_0209fb60(self, 1, 4);
    func_ov022_0209fb98(self, 1, 1);
    if (*(signed char *)(self + 0xf0d) != 0) {
        *(unsigned char *)(self + 0xf0c) |= 1;
    }
    func_ov002_02051d6c(self + 0xf0c, base + 0x2c80, self + 0x910);
    *(unsigned char *)(self + 0xf0c) &= ~8;
    {
        int i;
        int n;
        int id;
        int kind;

        n = 0;
        for (i = 0; i < 13; i++) {
            *(signed char *)(base + i + 0x2cd4) = -1;
            *(signed char *)(base + i + 0x2c88) = -1;
        }
        for (i = 0; i < 13; i++) {
            id = -1;
            kind = *(signed char *)(base + i + 0x2c34);
            if (kind < 0) {
                break;
            }
            switch (kind) {
            case 2: id = 0; break;
            case 5: id = 1; break;
            case 8: id = 2; break;
            case 9: id = 3; break;
            case 11: id = 4; break;
            }
            if (id >= 0) {
                *(signed char *)(base + kind + 0x2cd4) = n;
                *(signed char *)(base + n + 0x2c88) = id;
                n++;
            }
        }
    }
    func_ov002_02051eec(self + 0xf0c, base + 0x2c80, *(int *)(self + 0x2bd0),
                        *(unsigned char *)(self + 9), 0xbe);
}
