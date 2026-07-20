typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct {
    u32 field_0;
    u32 raw_keys;
    u16 packed_keys;
} MissionKeyBlock;

typedef struct {
    u32 mode;
    u32 keycode;
    u32 raw_keys;
    u16 packed_keys;
} MissionDisplayConfig;

typedef struct {
    u8 pad_000[0x28];
    u32 transition_requested;
    u8 pad_02c[0x3e8];
    u8 selection_block[0x18];
    MissionKeyBlock key_block;
    u8 pad_438[0x68];
    u32 active_value;
    u8 pad_4a4[0x44];
    u32 exit_requested;
} MissionContext;

extern MissionContext *data_ov006_020565e4;

extern void func_ov105_020bf8c8(void *callback);
extern void func_02030610(void);
extern void func_02031600(void *config);
extern void func_020305d8(void);
extern int OS_IsTickAvailable(void);
extern void func_ov006_0204e0c4(void);
extern void func_02030cf8(int slot, void *callback);
extern void func_ov006_0204e3ec(void);

void func_ov006_0204e114(void) {
    MissionDisplayConfig exit_config;
    MissionDisplayConfig key_config;
    MissionKeyBlock *key_block;

    data_ov006_020565e4->transition_requested = 0;
    if (data_ov006_020565e4->exit_requested == 0) {
        func_ov105_020bf8c8(0);
    }
    func_02030610();

    if (data_ov006_020565e4->exit_requested != 0) {
        exit_config.mode = 1;
        exit_config.keycode = 1;
        func_02031600(&exit_config);
        func_020305d8();
    } else {
        if (OS_IsTickAvailable() == 0) {
            func_ov006_0204e0c4();
        } else {
            key_block = &data_ov006_020565e4->key_block;
            func_ov006_0204e0c4();
            key_config.mode = 3;
            key_config.raw_keys = key_block->raw_keys;
            key_config.packed_keys = key_block->packed_keys;
            func_02031600(&key_config);
        }
        func_020305d8();
        func_02030cf8(0xd, func_ov006_0204e3ec);
    }

    data_ov006_020565e4->active_value = 1;
}
