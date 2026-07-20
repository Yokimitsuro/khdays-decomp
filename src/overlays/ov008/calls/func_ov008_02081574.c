typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct {
    u8 pad_0000[8];
    u8 display_state[0x94ec];
    void *scene_resources;
} Ov006RootContext;

extern Ov006RootContext *data_ov008_02090fa4;

extern void func_ov008_0207f4a4(void *resources);
extern void func_ov008_0207f18c(void *resources);
extern void func_ov008_0207f894(void *resources);
extern void func_ov008_0207f614(void *resources);
extern void func_ov008_020559a8(void *display_state);
extern void func_ov008_0207dfec(void *resources);
extern void func_0201e374(int brightness);
extern void func_0201e3cc(int brightness);
extern void func_ov008_02080f14(int state, int arg1, int arg2, int arg3, int arg4);

static inline void SetMainVisiblePlanes(int planes) {
    volatile u32 *display_control = (volatile u32 *)0x04000000;
    *display_control = (*display_control & ~0x1f00) | (planes << 8);
}

static inline void SetSubVisiblePlanes(int planes) {
    volatile u32 *display_control = (volatile u32 *)0x04001000;
    *display_control = (*display_control & ~0x1f00) | (planes << 8);
}

void func_ov008_02081574(void) {
    volatile u16 *main_palette = (volatile u16 *)0x05000000;

    SetMainVisiblePlanes(0);
    SetSubVisiblePlanes(0);
    func_ov008_0207f4a4(data_ov008_02090fa4->scene_resources);
    func_ov008_0207f18c(data_ov008_02090fa4->scene_resources);
    func_ov008_0207f894(data_ov008_02090fa4->scene_resources);
    func_ov008_0207f614(data_ov008_02090fa4->scene_resources);
    func_ov008_020559a8(data_ov008_02090fa4->display_state);
    func_ov008_0207dfec(data_ov008_02090fa4->scene_resources);

    main_palette[0] = 0;
    main_palette[0x200] = 0;
    func_0201e374(-16);
    func_0201e3cc(-16);
    func_ov008_02080f14(0xe, 0, 0, 0, 0);
}
