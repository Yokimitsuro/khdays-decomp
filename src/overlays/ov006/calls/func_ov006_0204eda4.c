typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct {
    u32 field_00[0xf];
    u16 item_count;
    u16 field_3e;
    u16 ready;
    u16 field_42;
    u32 field_44[0x1f];
} MissionRecord;

typedef struct {
    u8 pad_000[0x100];
    volatile u8 row_count;
    u8 pad_101[3];
    MissionRecord rows[4];
    u32 row_states[4];
} MissionContext;

typedef struct {
    MissionContext *context;
    void *controller_instance;
} MissionGlobals;

extern MissionGlobals data_ov006_020565e4;
extern u8 data_ov006_020561c8[];
extern int func_02001030(void);
extern void func_ov105_020bf1e4(u32 value);
extern void func_ov105_020be900(void (*callback)(const MissionRecord *),
                                void *data, int value);
extern void OS_IsThreadAvailable(void);
extern void func_ov006_0204d800(const MissionRecord *record);
extern void func_ov006_0204db2c(void);

void *func_ov006_0204eda4(void) {
    switch (func_02001030()) {
    case 1:
        func_ov105_020bf1e4(0x800356);
        func_ov105_020be900(func_ov006_0204d800,
                            data_ov006_020561c8, 0);
        break;

    case 2: {
        u8 i;

        OS_IsThreadAvailable();
        for (i = 0; i < data_ov006_020565e4.context->row_count; i++) {
            u8 j;

            if (data_ov006_020565e4.context->row_states[i] < 600) {
                data_ov006_020565e4.context->row_states[i]++;
            }

            if (data_ov006_020565e4.context->row_states[i] >= 600) {
                for (j = i;
                     j < data_ov006_020565e4.context->row_count - 1;
                     j++) {
                    data_ov006_020565e4.context->rows[j] =
                        data_ov006_020565e4.context->rows[j + 1];
                }
                data_ov006_020565e4.context->row_count--;
                i--;
            }
        }
        break;
    }

    case 3:
        break;

    default:
        func_ov006_0204db2c();
        break;
    }

    return 0;
}
