typedef unsigned char u8;

typedef struct Ov009SaveContext {
    u8 pad000[0x64];
    int pending;
} Ov009SaveContext;

typedef struct Ov009SlotReleaseConfig {
    int targetValue;
    int currentValue;
} Ov009SlotReleaseConfig;

extern const int data_ov025_020b4048[2];
extern int func_ov025_02084a7c(void);
extern int func_ov025_0208843c(int manager, int id);
extern int *func_ov025_020884c8(int manager, int entry);
extern void func_ov025_02088500(
    int manager,
    int entry,
    Ov009SlotReleaseConfig *config
);

void func_ov025_0209b560(Ov009SaveContext *ctx)
{
    Ov009SlotReleaseConfig config;
    unsigned int i;
    int manager = func_ov025_02084a7c();

    for (i = 0; i < 2; i++) {
        int entry;
        int id = data_ov025_020b4048[i];
        entry = func_ov025_0208843c(manager, id);
        int *slot = func_ov025_020884c8(manager, entry);

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
        func_ov025_02088500(manager, entry, &config);
    }
}
