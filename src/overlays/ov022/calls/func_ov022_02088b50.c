#pragma opt_propagation off

typedef unsigned char u8;
typedef unsigned short u16;

struct Ov022ColorVector {
    int x;
    int y;
    int z;
};

struct Ov022ColorBuffer {
    u8 channel[6];
};

struct Ov022ColorWork {
    struct Ov022ColorBuffer color;
    char _pad06[2];
    struct Ov022ColorVector vector;
};

struct Ov022ActiveState {
    int _unk00;
    void *activeBase;
};

extern struct Ov022ColorVector *func_ov022_020881f8(int kind);
extern int func_ov022_02088474(int kind);
extern int func_ov002_02072754(int state);
extern void func_ov002_02077cec(u8 *color, u16 id, int *vector);
extern struct Ov022ActiveState data_ov022_020b2e78;

void func_ov022_02088b50(int kind, int channel, int intensity) {
    struct Ov022ColorWork work;
    u8 *color;
    void *activeBase;
    int zero;

    color = work.color.channel;
    zero = 0;
    activeBase = data_ov022_020b2e78.activeBase;
    color[0] = zero;
    color[1] = 0;
    color[2] = 0;
    color[3] = 0;
    color[4] = 0;
    color[5] = 0;
    if (activeBase == 0) {
        return;
    }
    if (intensity > 100) {
        intensity = 100;
    }
    work.color.channel[channel] = (u8)intensity;
    work.vector = *func_ov022_020881f8(kind);
    work.vector.y += 0x800;
    func_ov002_02077cec(
        work.color.channel,
        (u16)func_ov002_02072754(func_ov022_02088474(kind)),
        (int *)&work.vector);
}
