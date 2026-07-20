typedef unsigned char u8;
typedef unsigned int u32;
typedef unsigned long long u64;

typedef struct {
    u8 pad_0000[0x4bc4];
    int active_state;
    int next_state;
} OverlayContext;

extern OverlayContext *volatile data_ov000_0205ac28;
extern u64 func_020031d4(void);
extern int func_02020368(u64 value, u32 divisor, int mode);
extern void func_0201e3cc(int value);

void func_ov000_02054170(void) {
    u64 elapsed =
        func_020031d4() - *(u64 *)((u8 *)data_ov000_0205ac28 + 0x14);

    func_0201e3cc(-func_02020368(elapsed, 0x4cb5, 0));
    if (elapsed <= 0x4cb51) {
        return;
    }

    *(u64 *)((u8 *)data_ov000_0205ac28 + 0x14) = func_020031d4();
    func_0201e3cc(-16);
    {
        OverlayContext *context = data_ov000_0205ac28;
        context->active_state = context->next_state;
    }
}
