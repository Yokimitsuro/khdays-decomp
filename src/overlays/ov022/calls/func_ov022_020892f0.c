extern void func_0202accc(int anim, unsigned short slot, int block, short binding);
extern int *func_01fff774(unsigned short *anim, unsigned int slot, int frame);

struct Ov022TrackTable5 {
    unsigned int values[5];
};

extern struct Ov022TrackTable5 data_ov022_020b236c;

void func_ov022_020892f0(unsigned short *anim, int bindingIndex) {
    struct Ov022TrackTable5 table = data_ov022_020b236c;
    int i = 0;

    do {
        unsigned int raw = table.values[i];
        if (0 < (short)anim[(unsigned short)raw + 0x70]) {
            func_0202accc((int)anim, raw, (int)(anim + 0x70),
                          (short)bindingIndex);
            func_01fff774(anim, raw & 0xffff, 0);
        }
        i = i + 1;
    } while (i < 5);
}
