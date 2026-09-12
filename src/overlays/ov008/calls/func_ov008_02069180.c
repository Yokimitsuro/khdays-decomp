typedef unsigned char u8;

typedef struct Ov009SaveContext {
    u8 pad000[0x64];
    int pending;
} Ov009SaveContext;

typedef struct Ov009SlotReleaseConfig {
    int targetValue;
    int currentValue;
} Ov009SlotReleaseConfig;

extern const int data_ov008_0208f4e8[2];
extern int func_ov008_02050c54(void);
extern int func_ov008_02054788(int manager, int id);
extern int *func_ov008_02054820(int manager, int entry);
extern void func_ov008_02054858(
    int manager,
    int entry,
    Ov009SlotReleaseConfig *config
);

void func_ov008_02069180(Ov009SaveContext *ctx)
{
    Ov009SlotReleaseConfig config;
    unsigned int i;
    int manager = func_ov008_02050c54();

    for (i = 0; i < 2; i++) {
        int entry;
        int id = data_ov008_0208f4e8[i];
        entry = func_ov008_02054788(manager, id);
        int *slot = func_ov008_02054820(manager, entry);

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
        func_ov008_02054858(manager, entry, &config);
    }
}
