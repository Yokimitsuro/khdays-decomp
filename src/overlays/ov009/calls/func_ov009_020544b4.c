typedef unsigned char u8;

typedef struct Ov009SaveContext {
    u8 pad000[0x68];
    int pending;
} Ov009SaveContext;

typedef struct Ov009SlotReleaseConfig {
    int targetValue;
    int currentValue;
} Ov009SlotReleaseConfig;

extern const int data_ov009_02056008[2];
extern int func_ov009_0204e440(void);
extern int func_ov009_020518fc(int manager, int id);
extern int *func_ov009_02051978(int manager, int entry);
extern void func_ov009_020519b0(
    int manager,
    int entry,
    Ov009SlotReleaseConfig *config
);

void func_ov009_020544b4(Ov009SaveContext *ctx)
{
    Ov009SlotReleaseConfig config;
    unsigned int i;
    int manager = func_ov009_0204e440();

    for (i = 0; i < 2; i++) {
        int entry;
        int id = data_ov009_02056008[i];
        entry = func_ov009_020518fc(manager, id);
        int *slot = func_ov009_02051978(manager, entry);

        config.currentValue = slot[1];
        if (ctx->pending != 0) {
            if (id == 0x15) {
                config.targetValue = 0x28000;
            } else {
                config.targetValue = 0x88000;
            }
        } else {
            if (id == 0x15) {
                config.targetValue = 0x88000;
            } else {
                config.targetValue = 0x28000;
            }
        }
        func_ov009_020519b0(manager, entry, &config);
    }
}
