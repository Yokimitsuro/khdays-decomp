typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct {
    u8 pad_0000[8];
    u8 display_state[0x94ec];
    void *scene_resources;
} Ov006RootContext;

extern Ov006RootContext *data_ov006_02056664;

extern void func_ov006_02053734(void *resources);
extern void func_ov006_0205341c(void *resources);
extern void func_ov006_02053b24(void *resources);
extern void func_ov006_020538a4(void *resources);
extern void func_ov006_0204d4e4(void *display_state);
extern void func_ov006_0205227c(void *resources);
extern void func_0201e374(int brightness);
extern void func_0201e3cc(int brightness);
extern void func_ov006_020551a4(int state, int arg1, int arg2, int arg3, int arg4);

static inline void SetMainVisiblePlanes(int planes) {
    volatile u32 *display_control = (volatile u32 *)0x04000000;
    *display_control = (*display_control & ~0x1f00) | (planes << 8);
}

static inline void SetSubVisiblePlanes(int planes) {
    volatile u32 *display_control = (volatile u32 *)0x04001000;
    *display_control = (*display_control & ~0x1f00) | (planes << 8);
}

void func_ov006_02055804(void) {
    volatile u16 *main_palette = (volatile u16 *)0x05000000;

    SetMainVisiblePlanes(0);
    SetSubVisiblePlanes(0);
    func_ov006_02053734(data_ov006_02056664->scene_resources);
    func_ov006_0205341c(data_ov006_02056664->scene_resources);
    func_ov006_02053b24(data_ov006_02056664->scene_resources);
    func_ov006_020538a4(data_ov006_02056664->scene_resources);
    func_ov006_0204d4e4(data_ov006_02056664->display_state);
    func_ov006_0205227c(data_ov006_02056664->scene_resources);

    main_palette[0] = 0;
    main_palette[0x200] = 0;
    func_0201e374(-16);
    func_0201e3cc(-16);
    func_ov006_020551a4(0xe, 0, 0, 0, 0);
}
