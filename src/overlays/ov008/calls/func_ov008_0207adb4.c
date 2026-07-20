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

extern MissionContext *data_ov008_02090f24;

extern int func_02001030(void);
extern void func_02003a20(MissionSelectionBuffer *buffer);
extern void func_020200e4(void *selection_block, void *payload);
extern int func_ov008_02079980(int value);
extern void func_ov008_02079868(int mode, void *send_block, u32 size);
extern void func_ov008_02079f80(void);
extern void func_020307b8(int value);
extern int func_ov008_0207994c(void);
extern int func_ov008_020798a8(const void *payload, u32 payload_size);
extern void func_ov008_0207b56c(void);
extern void func_ov008_0207aad0(void);

void *func_ov008_0207adb4(void) {
    MissionSelectionBuffer buffer;
    void *next = 0;

    switch (func_02001030()) {
    case 3:
        break;
    case 4:
        func_02003a20(&buffer);
        func_020200e4(data_ov008_02090f24->selection_block, buffer.payload);
        if (func_ov008_02079980(0) != 0) {
            func_ov008_02079868(0, &data_ov008_02090f24->flags, 0x68);
            if (data_ov008_02090f24->flags.bits.send_started != 0) {
                func_ov008_02079f80();
                func_020307b8(0);
                next = (void *)func_ov008_0207b56c;
                break;
            }
        }
        if (func_ov008_0207994c() != 0) {
            func_ov008_020798a8(data_ov008_02090f24->selection_block, 0x18);
        }
        break;
    default:
        data_ov008_02090f24->state = 0;
        next = (void *)func_ov008_0207aad0;
        break;
    }

    return next;
}
