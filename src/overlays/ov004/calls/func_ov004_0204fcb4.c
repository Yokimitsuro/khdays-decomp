typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct BootModeState {
    u8 flags;
    u8 state;
    u16 elapsed;
    u16 resetWord;
} BootModeState;

typedef struct Ov004SceneState {
    void *task;
    int selectedDay;
} Ov004SceneState;

extern Ov004SceneState *data_ov004_02051380;
extern BootModeState data_0204c240;

extern int func_ov004_0205102c(void);
extern void func_020235bc(int handlerId);
extern void func_020235e8(u32 field, int width, u32 value);
extern void func_020352cc(void);
extern void func_ov004_0204f278(int arg, int unused);
extern void func_02020a78(int scene, int arg);

int func_ov004_0204fcb4(void) {
    if (func_ov004_0205102c() != 0) {
        func_020235bc(0x18ae);
        func_020235e8(0, 9, (u16)data_ov004_02051380->selectedDay);

        data_0204c240.elapsed =
            data_ov004_02051380->selectedDay == 0x165 ? 0x2711 : 0x2710;
        data_0204c240.resetWord = 0;
        data_0204c240.state = 0;

        func_020352cc();
        func_ov004_0204f278(0, 0);
        func_02020a78(2, 0);
        return -2;
    }
    return 0;
}
