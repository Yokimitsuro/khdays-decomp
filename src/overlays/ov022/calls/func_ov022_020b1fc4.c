/* func_ov022_020b1fc4 -- tear down the four 0xc-byte sub-lists hanging off a battle
 * resource header and clear this slot's registry entry.
 * For each of the four entries: release arg0[1] sub-objects of stride 0x30 from the
 * block at +0xc, then free the block itself. Finally clear the registry word selected
 * by the header's kind byte (0 -> word 0, 1 -> word 1).
 *
 * arg0 is UNSIGNED char *: both the count at +1 and the kind at +0 come back with a
 * plain ldrb. The tail is a switch, not an if/else chain -- the ROM puts BOTH bodies
 * out of line and falls through to the default return. */
extern void func_ov002_02050cf4(int arg0);
extern void NNSi_FndFreeFromDefaultHeap(int arg0);
extern int data_ov022_020b2ec0;

void func_ov022_020b1fc4(unsigned char *arg0) {
    int outer = 0;
    unsigned char *pc = arg0;
    do {
        int i = 0;
        if ((int)arg0[1] > 0) {
            int off = 0;
            do {
                func_ov002_02050cf4(*(int *)(pc + 0xc) + off);
                i = i + 1;
                off = off + 0x30;
            } while (i < (int)arg0[1]);
        }
        NNSi_FndFreeFromDefaultHeap(*(int *)(pc + 0xc));
        pc = pc + 0xc;
        outer = outer + 1;
    } while (outer < 4);
    switch (*arg0) {
    case 0:
        *(int *)&data_ov022_020b2ec0 = 0;
        break;
    case 1:
        ((int *)&data_ov022_020b2ec0)[1] = 0;
        break;
    }
}
