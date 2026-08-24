#pragma opt_propagation off
#pragma opt_common_subs off
#pragma opt_dead_assignments off
#pragma opt_lifetimes on

extern int func_01fffde0(int player);
extern void func_ov002_0206bbb8(int slot, int kind, int value);
extern unsigned char data_0204be04;

struct PlayerScale020889cc {
    unsigned char _pad0000[0x2ab3];
    unsigned char step;
};

void func_ov022_020889cc(int player, int value) {
    struct PlayerScale020889cc *base;
    register int quotient;
    int step;
    unsigned int scaled;
    register unsigned int packedHigh;

    if (data_0204be04 != 0) {
        return;
    }
    base = (struct PlayerScale020889cc *)func_01fffde0(player);
    if (base == 0) {
        return;
    }
    if (value <= 0) {
        return;
    }

    quotient = (value << 12) / 100;
    step = base->step - 1;
    if (step < 0) {
        step = 0;
    }
    if (step >= 10) {
        step = 100;
        quotient *= step;
        packedHigh = value << 16;
    } else {
        step = step * 5;
        quotient *= step;
        packedHigh = value << 16;
    }
    scaled = quotient + 0xfff;
    scaled <<= 4;
    func_ov002_0206bbb8(0, 2, packedHigh | (scaled >> 16));
}
