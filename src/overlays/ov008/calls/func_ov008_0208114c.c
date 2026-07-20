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

extern Ov006RootContext *data_ov008_02090fa4;
extern u32 data_ov008_02090d9c;

extern void func_ov008_0207f4a4(int state);
extern void func_ov008_0207f18c(int state);
extern void func_ov008_0207f894(int state);
extern void func_ov008_0207f614(int state);
extern void func_ov008_020559a8(void *display_state);
extern void func_ov008_02055534(void *display_state, void *descriptor);
extern void func_ov008_0207fa4c(int layer, int x, int y);
extern void func_ov008_0207dfec(int state);
extern void func_ov008_020812d0(void);
extern void func_ov008_02080f14(int state, int duration, int start, int end,
                                int payload);

void func_ov008_0208114c(void) {
    int i;
    volatile u32 *main_display_control = (volatile u32 *)0x04000000;
    volatile u32 *sub_display_control = (volatile u32 *)0x04001000;

    if (data_ov008_02090fa4 == 0) {
        return;
    }

    func_ov008_0207f4a4(data_ov008_02090fa4->scene_state);
    func_ov008_0207f18c(data_ov008_02090fa4->scene_state);
    func_ov008_0207f894(data_ov008_02090fa4->scene_state);
    func_ov008_0207f614(data_ov008_02090fa4->scene_state);
    func_ov008_020559a8(&data_ov008_02090fa4->display_state);
    func_ov008_02055534(&data_ov008_02090fa4->display_state,
                        (void *)&data_ov008_02090d9c);

    func_ov008_0207fa4c(2, 0, 0);
    func_ov008_0207fa4c(3, 0, 0);
    func_ov008_0207fa4c(4, 0, 4);
    func_ov008_0207fa4c(5, 0, 0x12);
    func_ov008_0207fa4c(0, 0, 0);
    func_ov008_0207fa4c(1, 0, 0x16);

    for (i = 0; i < data_ov008_02090fa4->entry_count; i++) {
        data_ov008_02090fa4->reset_value = -1;
    }

    func_ov008_0207dfec(data_ov008_02090fa4->scene_state);
    func_ov008_020812d0();

    *sub_display_control =
        (*sub_display_control & ~0x1f00) | 0x1e00;
    *main_display_control =
        (*main_display_control & ~0x1f00) | 0x1f00;

    func_ov008_020812d0();
    func_ov008_02080f14(5, 0, 0, 0, 0);
}
