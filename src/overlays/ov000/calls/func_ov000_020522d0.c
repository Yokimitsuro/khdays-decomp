typedef unsigned char u8;
typedef unsigned int u32;
typedef unsigned long long u64;

typedef struct {
    u8 pad_0000[0x4ad0];
    int active_state;
    u8 pad_4ad4[0x2c0];
    int transition_flag;
} OverlayContext;

extern OverlayContext *volatile data_ov000_0205ac24;
extern u64 func_020031d4(void);
extern int func_02020368(u64 value, u32 divisor, int mode);
extern void func_0201e3cc(int value);

void func_ov000_020522d0(void) {
    u64 elapsed =
        func_020031d4() - *(u64 *)((u8 *)data_ov000_0205ac24 + 0x4ae4);

    func_0201e3cc(func_02020368(elapsed, 0x4cb5, 0) - 16);
    if (elapsed <= 0x4cb51) {
        return;
    }

    *(u64 *)((u8 *)data_ov000_0205ac24 + 0x4ae4) = func_020031d4();
    func_0201e3cc(0);
    data_ov000_0205ac24->active_state = 2;
    data_ov000_0205ac24->transition_flag = 0;
}
