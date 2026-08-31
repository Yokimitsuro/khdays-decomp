/* Draw mission results, reward gauges, rank indicators and the current mode count. */
typedef unsigned char u8;
typedef unsigned int u32;
typedef struct Ov005SpriteManager { char data[0x4a80]; } Ov005SpriteManager;
typedef struct Ov005ResultTween { char tween[28]; int duration, currentValue, fromValue, toValue; } Ov005ResultTween;
typedef struct Ov005GaugeRange { int maximum, value; } Ov005GaugeRange;
typedef struct Ov005ResultGaugeRequest { int firstTileId; short column, row; int maximum, value, widthPixels; } Ov005ResultGaugeRequest;
typedef struct Ov005ResultContext {
    char unknown00[0x54]; Ov005SpriteManager spriteManager;
    char unknown4ad4[0xac]; u8 dirtyTextBuffers, unknown4b81[3];
    Ov005ResultTween resultTweens[4]; char unknown4c34[20];
    u8 modeSnapshot, unknown4c49[3]; Ov005GaugeRange gauge;
} Ov005ResultContext;
typedef struct Ov005Config {
    char unknown00[12]; unsigned short rewardMode; char unknown0e[2]; int resultRank;
    char unknown14[28]; int missionTargetValue; char unknown34[48]; int option64;
} Ov005Config;
extern Ov005ResultContext *data_ov005_0205b810;
extern Ov005Config data_ov005_0205b85c;
extern const u8 data_ov005_0205b588[];
extern void func_ov005_02055688(void), func_ov005_020570d0(int);
extern void GFXi_EnqueueCommand(int, int, const void *, int);
extern void func_ov005_020555e4(Ov005ResultGaugeRequest *);
extern void func_ov005_02057984(u32, u8 *, u8 *, u8 *);
extern void func_ov005_02055480(u32, int, int, int);
extern void func_ov005_02055528(int, u32);
extern void *func_ov005_0204e0d0(Ov005SpriteManager *, int);
extern void func_ov005_0204e29c(Ov005SpriteManager *, void *, int);
void func_ov005_020558c0(void) {
    Ov005GaugeRange *gauge = &data_ov005_0205b810->gauge;
    u8 *modeSnapshot = &data_ov005_0205b810->modeSnapshot;
    Ov005Config *config = &data_ov005_0205b85c;
    Ov005ResultGaugeRequest request;
    u8 minutes, seconds, centiseconds;
    func_ov005_02055688();
    func_ov005_020570d0(27);
    data_ov005_0205b810->dirtyTextBuffers |= 8;
    if (config->option64 == 0) {
        Ov005ResultTween *tweens = data_ov005_0205b810->resultTweens;
        switch (config->rewardMode) {
        case 2:
        case 255:
            request.firstTileId = config->resultRank > 0 && config->resultRank < 3 ? 0x3f3 : 0x3eb;
            request.column = 3;
            request.row = 14;
            request.maximum = config->missionTargetValue;
            request.value = tweens[0].currentValue;
            request.widthPixels = 183;
            if (config->resultRank == 0) GFXi_EnqueueCommand(31, 24, data_ov005_0205b588, 8);
            func_ov005_020555e4(&request);
            break;
        case 0:
            func_ov005_02057984(tweens[0].currentValue, &minutes, &seconds, &centiseconds);
            func_ov005_02055480(centiseconds, 22, 2, 2);
            func_ov005_02055480(seconds, 25, 2, 2);
            func_ov005_02055480(minutes, 28, 2, 2);
            break;
        default:
            func_ov005_02055480(tweens[0].currentValue, 22, 8, 0);
        }
    }
    request.firstTileId = 0x3fb;
    request.column = 3;
    request.row = 21;
    if (gauge->maximum == 0) request.maximum = request.value = 100;
    else { request.maximum = gauge->maximum; request.value = gauge->value; }
    request.widthPixels = 144;
    func_ov005_020555e4(&request);
    if (config->option64 == 0 && config->resultRank >= 0 && config->resultRank <= 2) {
        switch (config->rewardMode) {
        case 255: func_ov005_02055528(79, (u8)(config->resultRank != 0)); break;
        case 8: func_ov005_02055528(13, (u8)config->resultRank); break;
        }
    }
    if (config->option64 == 0 && config->rewardMode != 8 && config->resultRank < 3) {
        func_ov005_0204e29c(&data_ov005_0205b810->spriteManager,
            func_ov005_0204e0d0(&data_ov005_0205b810->spriteManager, 6), 1);
    }
    if (*modeSnapshot != 0) {
        func_ov005_0204e29c(&data_ov005_0205b810->spriteManager,
            func_ov005_0204e0d0(&data_ov005_0205b810->spriteManager, 76), 1);
        func_ov005_0204e29c(&data_ov005_0205b810->spriteManager,
            func_ov005_0204e0d0(&data_ov005_0205b810->spriteManager, 75), 1);
        func_ov005_02055480(*modeSnapshot, 77, 2, 0);
    }
}
