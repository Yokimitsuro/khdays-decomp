/* Tick result resources, dispatch the active phase, and flush pending buffers. */
typedef void (*Ov005ResultPhaseHandler)(void);
typedef struct Ov005ResultPhaseTable { Ov005ResultPhaseHandler states[5]; } Ov005ResultPhaseTable;
typedef struct Ov000ResourceTracker { char opaque[76]; } Ov000ResourceTracker;
typedef struct Ov005SpriteManager { char opaque[0x4a80]; } Ov005SpriteManager;
typedef struct Ov005ResultContext {
    char unknown00[8];
    Ov000ResourceTracker resourceTracker;
    Ov005SpriteManager spriteManager;
    char unknown4ad4[0xa0];
    int resultPhase;
} Ov005ResultContext;
extern Ov005ResultContext *data_ov005_0205b810;
extern const Ov005ResultPhaseTable data_ov005_0205b39c;
extern int func_02030670(void);
extern unsigned short func_ov105_020bd7c4(void);
extern void func_ov005_02055528(int, unsigned int);
extern void func_ov005_0204d110(Ov000ResourceTracker *);
extern void func_ov005_0204dd18(Ov005SpriteManager *, int);
extern void func_ov005_02056fd0(void);
void *func_ov005_02056f1c(void) {
    Ov005ResultPhaseTable handlers = data_ov005_0205b39c;
    if (func_02030670()) func_ov005_02055528(108, (unsigned char)func_ov105_020bd7c4());
    func_ov005_0204d110(&data_ov005_0205b810->resourceTracker);
    func_ov005_0204dd18(&data_ov005_0205b810->spriteManager, 0);
    handlers.states[data_ov005_0205b810->resultPhase]();
    func_ov005_02056fd0();
    return 0;
}
