/*
 * Bind the actor's two UI channels and build the rig's slot map. The rig's +0x2c2c "sequence
 * registered" flag is cleared, then channel 0 (+0xda8, config +0x2d38, 3 tracks) and channel 1
 * (+0xf0c, config +0x2d8c, 4 tracks) are opened, flagged (bit 0 when their +1 byte is set) and
 * bound to the actor's +0x910 block, channel 0 driven with tag 0x78 and channel 1 stripped of
 * its bit 3. The 13-entry kind -> slot map at +0x2de0 starts at -1; every kind 7..12 in the
 * +0x2d40 list (up to the first negative) gets the next slot, and the first of them also
 * registers the rig's +0x2c30 sequence under the packed identity key (the +0x2bd0 anchor bits
 * 2..23 shifted up 7, the +0x918 byte + 0xbe in 9 bits, bit 31), sets polygon id 0x3f on the
 * +0x2ca8 model, raises the node's flag 0x40 and marks the sequence registered.
 *
 * THUMB. `base + i` is a named `row` inside the loop (the ROM spills it across the calls and
 * re-reads the kind through it), `i = 0` precedes `n = 0` (n borrows i's zero) and the actor's
 * slot byte is `((unsigned char *)self)[9]` -- the `*(u8 *)(self + 9)` spelling lets mwcc hoist
 * `self + 9` out of the loop into a spill slot.
 */
extern void func_ov022_0209fb60(int a, int b, int c);
extern void func_ov022_0209fb98(int a, int b, int c);
extern void func_ov002_02051d6c(int a, int b, int c);
extern void func_ov002_02051eec(int a, int b, int c, int d, int e);
extern void func_0202a634(void *seq, unsigned int key, int a, int b);     /* RegisterSeqAndInit */
extern void func_02016cd0(void *model, int id);                           /* NNS_G3dMdlSetMdlPolygonIDAll */
extern void func_0202afc4(void *node, int on);                            /* SceneNode_SetFlag40 */
extern int data_ov064_020b7420;

void func_ov064_020b5c80(int self) {
    int base = *(int *)&data_ov064_020b7420;
    int i;
    int n;

    *(int *)(base + 0x2c2c) = 0;
    func_ov022_0209fb60(base, 0, 3);
    func_ov022_0209fb98(base, 0, 1);
    if (*(signed char *)(base + 0xda9) != 0) {
        *(unsigned char *)(base + 0xda8) |= 1;
    }
    func_ov002_02051d6c(base + 0xda8, base + 0x2d38, self + 0x910);
    func_ov002_02051eec(self + 0xda8, base + 0x2d38, *(int *)(self + 0x2bd0),
                        *(unsigned char *)(self + 9), 0x78);
    func_ov022_0209fb60(base, 1, 4);
    func_ov022_0209fb98(base, 1, 1);
    if (*(signed char *)(base + 0xf0d) != 0) {
        *(unsigned char *)(base + 0xf0c) |= 1;
    }
    *(unsigned char *)(self + 0xf0c) &= ~8;
    func_ov002_02051d6c(base + 0xf0c, base + 0x2d8c, self + 0x910);
    for (i = 0; i < 13; i++) {
        *(signed char *)(base + i + 0x2de0) = -1;
    }
    i = 0;
    n = 0;
    do {
        int row = base + i;
        if (*(signed char *)(row + 0x2d40) < 0) {
            break;
        }
        switch (*(signed char *)(row + 0x2d40)) {
        case 7:
        case 8:
        case 9:
        case 10:
        case 11:
        case 12:
            if (*(int *)(base + 0x2c2c) == 0) {
                func_0202a634((void *)(base + 0x2c30),
                              (((*(int *)(self + 0x2bd0) + 0x8000) & 0xfffffc) << 7) | 0x80000000
                                  | ((*(unsigned char *)(self + 0x918) + 0xbe) & 0x1ff),
                              1, ((unsigned char *)self)[9] + 7);
                func_02016cd0(*(void **)(base + 0x2ca8), 0x3f);
                func_0202afc4((void *)(base + 0x2c30), 1);
                *(int *)(base + 0x2c2c) = 1;
            }
            *(signed char *)(base + *(signed char *)(row + 0x2d40) + 0x2de0) = n;
            n++;
            break;
        }
        i++;
    } while (i < 13);
}
