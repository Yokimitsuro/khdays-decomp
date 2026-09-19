/* Rider presence hook: with only the second rider counter (+0x3be) left, both rider items
 * (+0x384 / +0x38c) get channel 1 bound with (0, 0) and bit 0 of the +0x398 mode byte's high
 * nibble clears; with only the first (+0x3bc) left they get (1, 0) and the +0x39c byte clears;
 * with none left both items suspend (bit 1 of +0x5c) and both bytes clear; with both left the
 * items resume, get (2, 0) and both bytes set bit 0. */
typedef struct {
    unsigned char lo : 4;
    unsigned char hi : 4;
} Nib;
extern void func_0203b9fc(int item, int channel, int a, int b);

void func_ov278_020cda7c(char *self) {
    if (*(short *)(self + 0x300 + 0xbc) == 0 && *(short *)(self + 0x300 + 0xbe) > 0) {
        func_0203b9fc(*(int *)(self + 0x384), 1, 0, 0);
        func_0203b9fc(*(int *)(self + 0x38c), 1, 0, 0);
        ((Nib *)*(char **)(self + 0x398))->hi &= ~1;
        return;
    }
    if (*(short *)(self + 0x300 + 0xbc) > 0 && *(short *)(self + 0x300 + 0xbe) == 0) {
        func_0203b9fc(*(int *)(self + 0x384), 1, 1, 0);
        func_0203b9fc(*(int *)(self + 0x38c), 1, 1, 0);
        ((Nib *)*(char **)(self + 0x39c))->hi &= ~1;
        return;
    }
    if (*(short *)(self + 0x300 + 0xbc) == 0 && *(short *)(self + 0x300 + 0xbe) == 0) {
        *(int *)(*(char **)(self + 0x384) + 0x5c) |= 2;
        *(int *)(*(char **)(self + 0x38c) + 0x5c) |= 2;
        ((Nib *)*(char **)(self + 0x398))->hi &= ~1;
        ((Nib *)*(char **)(self + 0x39c))->hi &= ~1;
        return;
    }
    *(int *)(*(char **)(self + 0x384) + 0x5c) &= ~2;
    *(int *)(*(char **)(self + 0x38c) + 0x5c) &= ~2;
    func_0203b9fc(*(int *)(self + 0x384), 1, 2, 0);
    func_0203b9fc(*(int *)(self + 0x38c), 1, 2, 0);
    ((Nib *)*(char **)(self + 0x398))->hi |= 1;
    ((Nib *)*(char **)(self + 0x39c))->hi |= 1;
}
