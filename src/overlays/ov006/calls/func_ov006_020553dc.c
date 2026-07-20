typedef unsigned char u8;
typedef unsigned int u32;

typedef struct {
    u8 pad_0000[8];
    u8 display_state;
    u8 pad_0009[0x94e3];
    int reset_value;
    u8 pad_94f0[4];
    int scene_state;
    u8 pad_94f8[0x10];
    int entry_count;
} Ov006RootContext;

extern Ov006RootContext *data_ov006_02056664;
extern u32 data_ov006_020565ac;

extern void func_ov006_02053734(int state);
extern void func_ov006_0205341c(int state);
extern void func_ov006_02053b24(int state);
extern void func_ov006_020538a4(int state);
extern void func_ov006_0204d4e4(void *display_state);
extern void func_ov006_0204d160(void *display_state, void *descriptor);
extern void func_ov006_02053cdc(int layer, int x, int y);
extern void func_ov006_0205227c(int state);
extern void func_ov006_02055560(void);
extern void func_ov006_020551a4(int state, int duration, int start, int end,
                                int payload);

void func_ov006_020553dc(void) {
    int i;
    volatile u32 *main_display_control = (volatile u32 *)0x04000000;
    volatile u32 *sub_display_control = (volatile u32 *)0x04001000;

    if (data_ov006_02056664 == 0) {
        return;
    }

    func_ov006_02053734(data_ov006_02056664->scene_state);
    func_ov006_0205341c(data_ov006_02056664->scene_state);
    func_ov006_02053b24(data_ov006_02056664->scene_state);
    func_ov006_020538a4(data_ov006_02056664->scene_state);
    func_ov006_0204d4e4(&data_ov006_02056664->display_state);
    func_ov006_0204d160(&data_ov006_02056664->display_state,
                        (void *)&data_ov006_020565ac);

    func_ov006_02053cdc(2, 0, 0);
    func_ov006_02053cdc(3, 0, 0);
    func_ov006_02053cdc(4, 0, 4);
    func_ov006_02053cdc(5, 0, 0x12);
    func_ov006_02053cdc(0, 0, 0);
    func_ov006_02053cdc(1, 0, 0x16);

    for (i = 0; i < data_ov006_02056664->entry_count; i++) {
        data_ov006_02056664->reset_value = -1;
    }

    func_ov006_0205227c(data_ov006_02056664->scene_state);
    func_ov006_02055560();

    *sub_display_control =
        (*sub_display_control & ~0x1f00) | 0x1e00;
    *main_display_control =
        (*main_display_control & ~0x1f00) | 0x1f00;

    func_ov006_02055560();
    func_ov006_020551a4(5, 0, 0, 0, 0);
}
