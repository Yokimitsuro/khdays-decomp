/* Display rank awards and mark awards added beyond the saved record. */
typedef unsigned int u32;
typedef struct Ov005SpriteManager { char data[0x4a80]; } Ov005SpriteManager;
typedef struct Ov005ResultContext { char unknown00[0x54]; Ov005SpriteManager spriteManager; } Ov005ResultContext;
typedef struct Ov005Config { unsigned short sceneId, missionIndex; char unknown04[8]; unsigned short rewardMode; char unknown0e[2]; int resultRank; } Ov005Config;
extern Ov005ResultContext *data_ov005_0205b810;
extern Ov005Config data_ov005_0205b85c;
extern u32 func_020235d0(u32, u32);
extern void func_ov005_02055528(int, u32);
extern void *func_ov005_0204e0d0(Ov005SpriteManager *, int);
extern void func_ov005_0204e33c(Ov005SpriteManager *, void *);
void func_ov005_020557a8(void) {
    Ov005Config *config = &data_ov005_0205b85c;
    int index;
    int firstEntryId = config->rewardMode == 2 ? 14 : 17;
    int currentAwards;
    int previousAwards = func_020235d0(config->missionIndex * 3 + 0x2a4c, 3);
    currentAwards = config->resultRank >= 0 && config->resultRank <= 2 ? 3 - config->resultRank : 0;
    index = 0;
    if (currentAwards <= previousAwards) {
        for (; index < currentAwards; index++) func_ov005_02055528(firstEntryId + index, 0);
    } else {
        for (; index < previousAwards; index++) func_ov005_02055528(firstEntryId + index, 0);
        if (config->resultRank >= 0 && config->resultRank <= 2) {
            for (; index < currentAwards; index++) {
                func_ov005_02055528(firstEntryId + index, 0);
                func_ov005_0204e33c(&data_ov005_0205b810->spriteManager,
                    func_ov005_0204e0d0(&data_ov005_0205b810->spriteManager, firstEntryId + index));
            }
        }
    }
}
