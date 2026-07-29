typedef unsigned char u8;

typedef struct MenuContext {
    u8 pad0000[0x95c4];
    int transitionValue;
    u8 pad95c8[0x30];
    int transitionActive;
} MenuContext;

extern MenuContext *volatile data_ov009_020563e4[2];
extern int OS_IsThreadAvailable_0x0204ee00(void);
extern void func_ov009_0204cb6c(int mode);
extern void func_ov009_0204cd34(int brightness, int duration);
extern void func_ov009_0204cec0(int enabled);

void func_ov009_0204e328(int value, int duration)
{
    int state = OS_IsThreadAvailable_0x0204ee00();

    data_ov009_020563e4[1]->transitionValue = value;
    if (state == -1) {
        func_ov009_0204cb6c(1);
        data_ov009_020563e4[1]->transitionActive = 1;
        return;
    }

    if (duration < 0) {
        duration = 100;
    }
    func_ov009_0204cb6c(4);
    func_ov009_0204cd34(-0x10, duration);
    func_ov009_0204cec0(0);
    data_ov009_020563e4[1]->transitionActive = 0;
}
