/* Rider presence hook for the second rider set (items +0x388 / +0x390, counters +0x3d0 / +0x3d2):
 * with only the second counter left both items resume, get channel 1 = (0, 0), the +0x398 / +0x39c
 * mode bytes clear bit 0 of their high nibble and the +0x3a0 / +0x3a4 ones set it; with only the
 * first left the channel is (1, 0) and the byte pairs swap; with none left both items suspend
 * (bit 1 of +0x5c) and all four bytes clear; with both left the items resume, get (2, 0) and all
 * four bytes set bit 0. */
typedef struct {
    unsigned char lo : 4;
    unsigned char hi : 4;
} Nib;
extern void func_0203b9fc(int item, int channel, int a, int b);

void func_ov278_020ce984(char *self) {
    if (*(short *)(self + 0x300 + 0xd0) == 0 && *(short *)(self + 0x300 + 0xd2) > 0) {
        *(int *)(*(char **)(self + 0x388) + 0x5c) &= ~2;
        *(int *)(*(char **)(self + 0x390) + 0x5c) &= ~2;
        func_0203b9fc(*(int *)(self + 0x388), 1, 0, 0);
        func_0203b9fc(*(int *)(self + 0x390), 1, 0, 0);
        ((Nib *)*(char **)(self + 0x398))->hi &= ~1;
        ((Nib *)*(char **)(self + 0x39c))->hi &= ~1;
        ((Nib *)*(char **)(self + 0x3a0))->hi |= 1;
        ((Nib *)*(char **)(self + 0x3a4))->hi |= 1;
        return;
    }
    if (*(short *)(self + 0x300 + 0xd0) > 0 && *(short *)(self + 0x300 + 0xd2) == 0) {
        *(int *)(*(char **)(self + 0x388) + 0x5c) &= ~2;
        *(int *)(*(char **)(self + 0x390) + 0x5c) &= ~2;
        func_0203b9fc(*(int *)(self + 0x388), 1, 1, 0);
        func_0203b9fc(*(int *)(self + 0x390), 1, 1, 0);
        ((Nib *)*(char **)(self + 0x398))->hi |= 1;
        ((Nib *)*(char **)(self + 0x39c))->hi |= 1;
        ((Nib *)*(char **)(self + 0x3a0))->hi &= ~1;
        ((Nib *)*(char **)(self + 0x3a4))->hi &= ~1;
        return;
    }
    if (*(short *)(self + 0x300 + 0xd0) == 0 && *(short *)(self + 0x300 + 0xd2) == 0) {
        *(int *)(*(char **)(self + 0x388) + 0x5c) |= 2;
        *(int *)(*(char **)(self + 0x390) + 0x5c) |= 2;
        ((Nib *)*(char **)(self + 0x398))->hi &= ~1;
        ((Nib *)*(char **)(self + 0x39c))->hi &= ~1;
        ((Nib *)*(char **)(self + 0x3a0))->hi &= ~1;
        ((Nib *)*(char **)(self + 0x3a4))->hi &= ~1;
        return;
    }
    *(int *)(*(char **)(self + 0x388) + 0x5c) &= ~2;
    *(int *)(*(char **)(self + 0x390) + 0x5c) &= ~2;
    func_0203b9fc(*(int *)(self + 0x388), 1, 2, 0);
    func_0203b9fc(*(int *)(self + 0x390), 1, 2, 0);
    ((Nib *)*(char **)(self + 0x398))->hi |= 1;
    ((Nib *)*(char **)(self + 0x39c))->hi |= 1;
    ((Nib *)*(char **)(self + 0x3a0))->hi |= 1;
    ((Nib *)*(char **)(self + 0x3a4))->hi |= 1;
}
