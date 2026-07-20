typedef unsigned int u32;

typedef struct {
    u32 field_0;
    void *volatile instance;
} MissionControllerState;

extern MissionControllerState data_ov006_020565e4;
extern unsigned char data_ov006_020563c0;
extern void *func_02023930(void *class_desc, int arg);

void func_ov006_0204faf0(int arg) {
    if (data_ov006_020565e4.instance != 0) {
        return;
    }

    data_ov006_020565e4.instance = func_02023930(&data_ov006_020563c0, arg);
}
