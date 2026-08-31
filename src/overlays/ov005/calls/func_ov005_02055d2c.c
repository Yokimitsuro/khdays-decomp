/* Show or hide the first reward multiplier; the original retains unused switch cases. */
#pragma opt_propagation off
typedef unsigned char u8;
typedef unsigned int u32;
typedef struct Ov005SpriteManager { char data[0x4a80]; } Ov005SpriteManager;
typedef struct Ov005ResultContext { char unknown00[0x54]; Ov005SpriteManager spriteManager; } Ov005ResultContext;
typedef struct Ov005Config { char unknown00[0x4c]; u32 rewardScales[3]; } Ov005Config;
extern Ov005ResultContext *data_ov005_0205b810;
extern Ov005Config data_ov005_0205b85c;
extern unsigned short func_ov005_02057acc(int);
extern void func_ov005_02055480(u32, int, int, int);
extern void *func_ov005_0204e0d0(Ov005SpriteManager *, int);
extern void func_ov005_0204e29c(Ov005SpriteManager *, void *, int);
void func_ov005_02055d2c(int rewardIndex, int visible) {
    u8 index;
    int firstEntryId = 0;
    Ov005Config *config = &data_ov005_0205b85c;
    if (rewardIndex != 0) return;
    switch (rewardIndex) {
    case 0: firstEntryId = 81; break;
    case 1: firstEntryId = 87; break;
    case 2: firstEntryId = 93; break;
    }
    if (visible) {
        func_ov005_02055480(func_ov005_02057acc(config->rewardScales[rewardIndex]), firstEntryId, 4, 3);
        func_ov005_0204e29c(&data_ov005_0205b810->spriteManager,
            func_ov005_0204e0d0(&data_ov005_0205b810->spriteManager, firstEntryId + 4), 1);
        func_ov005_0204e29c(&data_ov005_0205b810->spriteManager,
            func_ov005_0204e0d0(&data_ov005_0205b810->spriteManager, firstEntryId + 5), 1);
    } else {
        index = 0;
        do {
            func_ov005_0204e29c(&data_ov005_0205b810->spriteManager,
                func_ov005_0204e0d0(&data_ov005_0205b810->spriteManager, firstEntryId + index), 0);
            index++;
        } while (index < 6);
    }
}
