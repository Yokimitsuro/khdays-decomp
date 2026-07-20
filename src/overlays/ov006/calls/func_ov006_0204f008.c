typedef unsigned char u8;
typedef unsigned int u32;

typedef union {
    u8 raw;
    struct {
        u8 send_started : 1;
        u8 unused : 7;
    } bits;
} MissionFlags;

typedef struct {
    u8 pad_000[0x2c];
    u32 state;
    u8 pad_030[0x3e4];
    u8 selection_block[0x18];
    MissionFlags flags;
    u8 send_block[0x67];
} MissionContext;

typedef struct {
    u32 header;
    u8 payload[0x50];
} MissionSelectionBuffer;

extern MissionContext *data_ov006_020565e4;

extern int func_02001030(void);
extern void func_02003a20(MissionSelectionBuffer *buffer);
extern void func_020200e4(void *selection_block, void *payload);
extern int func_ov006_0204db14(int value);
extern void func_ov006_0204d9fc(int mode, void *send_block, u32 size);
extern void func_ov006_0204e114(void);
extern void func_020307b8(int value);
extern int func_ov006_0204dae0(void);
extern int func_ov006_0204da3c(const void *payload, u32 payload_size);
extern void func_ov006_0204f810(void);
extern void func_ov006_0204ece4(void);

void *func_ov006_0204f008(void) {
    MissionSelectionBuffer buffer;
    void *next = 0;

    switch (func_02001030()) {
    case 3:
        break;
    case 4:
        func_02003a20(&buffer);
        func_020200e4(data_ov006_020565e4->selection_block, buffer.payload);
        if (func_ov006_0204db14(0) != 0) {
            func_ov006_0204d9fc(0, &data_ov006_020565e4->flags, 0x68);
            if (data_ov006_020565e4->flags.bits.send_started != 0) {
                func_ov006_0204e114();
                func_020307b8(0);
                next = (void *)func_ov006_0204f810;
                break;
            }
        }
        if (func_ov006_0204dae0() != 0) {
            func_ov006_0204da3c(data_ov006_020565e4->selection_block, 0x18);
        }
        break;
    default:
        data_ov006_020565e4->state = 0;
        next = (void *)func_ov006_0204ece4;
        break;
    }

    return next;
}
