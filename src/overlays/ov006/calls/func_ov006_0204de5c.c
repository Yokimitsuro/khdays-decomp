typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct {
    u8 pad_000[0x28];
    u32 transition_requested;
    u8 pad_02c[0x14];
    u8 option;
    u8 pad_041;
    u16 selection;
} MissionContext;

extern MissionContext *volatile data_ov006_020565e4;
extern char data_ov006_02056600[];

extern int func_ov105_020bf4a0(void);
extern int func_ov105_020bd978(void);
extern void func_ov105_020bf22c(void *resource, int size);
extern int func_ov105_020bf704(int mode, int selection, int value, int count, int option);
extern void func_ov105_020bf8c8(void (*callback)(void));
extern void func_ov105_020bf8b8(void (*callback)(void));
extern void func_ov006_0204d914(void);
extern void func_ov006_0204de18(void);

void func_ov006_0204de5c(void) {
    int value = func_ov105_020bf4a0();

    data_ov006_020565e4->selection = (u16)func_ov105_020bd978();
    func_ov105_020bf22c(data_ov006_02056600, 0x18);

    if (func_ov105_020bf704(0, data_ov006_020565e4->selection, value, 2,
                            data_ov006_020565e4->option) == 0) {
        return;
    }

    func_ov105_020bf8c8(func_ov006_0204d914);
    func_ov105_020bf8b8(func_ov006_0204de18);
    data_ov006_020565e4->transition_requested = 1;
}
