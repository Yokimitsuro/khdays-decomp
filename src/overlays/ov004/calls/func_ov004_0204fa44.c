typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct Ov004SceneArgs {
    int currentDay;
    int selectedDay;
} Ov004SceneArgs;

extern const Ov004SceneArgs data_ov004_0205109c;
extern char *data_ov004_02051380;
extern u8 data_0204c300[];
extern char data_ov004_020512ec[];

extern u32 func_020235d0(u32 field, int width);
extern void func_020235e8(u32 field, int width, u32 value);
extern char *NNSi_FndGetCurrentRootHeap(void);
extern void *MI_CpuFill8(void *dst, int value, u32 size);
extern int func_ov004_0204f5a4(int value);
extern void func_ov004_0204f954(void);
extern void func_ov004_0204f9cc(void);
extern void func_ov004_0204f874(void);
extern void func_ov004_0204f32c(void);
extern void *func_02023930(void *config, void *args);
extern void *func_ov004_0204fcb4(void);

void *func_ov004_0204fa44(int requestedDay) {
    Ov004SceneArgs args;
    int currentDay;
    int index;
    int notify;
    u32 field;
    u32 value;
    int enabled;
    u8 playerFlag;
    u8 combinedFlag;

    currentDay = func_020235d0(0, 9);
    args = data_ov004_0205109c;

    NNSi_FndGetCurrentRootHeap();
    data_ov004_02051380 = NNSi_FndGetCurrentRootHeap();
    MI_CpuFill8(data_ov004_02051380, 0, 8);

    switch (requestedDay) {
    case 0x190:
        currentDay = 0x190;
        *(int *)(data_ov004_02051380 + 4) = currentDay;
        break;
    case 0x191:
        *(int *)(data_ov004_02051380 + 4) = 7;
        currentDay = 0xff;
        break;
    default:
        *(int *)(data_ov004_02051380 + 4) = requestedDay;
        break;
    case 0:
        *(int *)(data_ov004_02051380 + 4) = func_ov004_0204f5a4(currentDay);
        break;
    }

    if ((u32)(currentDay - 0x165) <= 1) {
        index = currentDay == 0x165 ? 0x5c : 0x5d;

        field = index * 4 + 0x92b;
        playerFlag = data_0204c300[0x4e];
        combinedFlag = playerFlag | func_020235d0(field, 4);
        notify = 0;
        func_020235e8(field, 4, combinedFlag);

        if (index == 0x5d) {
            enabled = func_020235d0(index * 3 + 0x28e4, 3) == 3;
            if (enabled == 0) {
                notify = 1;
            }
        }

        field = index * 3 + 0x28e4;
        value = (u16)func_020235d0(field, 3);
        if (value < 1) {
            func_020235e8(field, 3, 1);
        }
        value = (u16)func_020235d0(field, 3);
        if (value < 2) {
            func_020235e8(field, 3, 2);
        }
        func_020235d0(field, 3);
        func_020235e8(field, 3, 3);

        if (notify != 0) {
            func_ov004_0204f954();
            func_ov004_0204f9cc();
        }
    }

    if (currentDay == 0x165) {
        func_ov004_0204f874();
    }

    args.currentDay = currentDay;
    args.selectedDay = *(int *)(data_ov004_02051380 + 4);

    data_ov004_02051380 = NNSi_FndGetCurrentRootHeap();
    func_ov004_0204f32c();
    *(void **)data_ov004_02051380 = func_02023930(data_ov004_020512ec, &args);

    *(volatile u32 *)0x04000000 =
        (*(volatile u32 *)0x04000000 & ~0x1f00) | 0x1f00;

    return (void *)func_ov004_0204fcb4;
}
