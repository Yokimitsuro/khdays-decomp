typedef unsigned char u8;
typedef struct Ov000ResourceTracker {char opaque[76];} Ov000ResourceTracker;
typedef struct Ov005SpriteManager {char opaque[0x4a80];} Ov005SpriteManager;
typedef struct FontInfo {char opaque[12];} FontInfo;
typedef struct TileSurface {char opaque[60];} TileSurface;
typedef struct Ov005TextTable {char opaque[12];} Ov005TextTable;
typedef struct Ov005ResultContext {
    void *resultArchive,*localizedResultArchive;
    Ov000ResourceTracker resourceTracker;
    Ov005SpriteManager spriteManager;
    FontInfo font;
    TileSurface textSurfaces[2];
    char unknown4b58[12];
    void *rowBuffers[4];
    char unknown4b74[0xc4];
    Ov005TextTable menuText;
    char unknown4c44[32];
} Ov005ResultContext;
extern Ov005ResultContext *data_ov005_0205b810;
extern void func_ov005_020550e4(void);
extern void func_ov005_0204e4e8(Ov005TextTable *);
extern void func_ov005_0204d138(Ov000ResourceTracker *);
extern void func_ov005_0204dcec(Ov005SpriteManager *);
extern void func_0202ff7c(FontInfo *),func_0202ffbc(TileSurface *);
extern void func_02024fd4(void *),NNSi_FndFreeFromDefaultHeap(void *);
extern void func_0201e1d0(void);
void func_ov005_02056e24(void) {
    u8 i;
    func_ov005_020550e4();
    func_ov005_0204e4e8(&data_ov005_0205b810->menuText);
    func_ov005_0204d138(&data_ov005_0205b810->resourceTracker);
    func_ov005_0204dcec(&data_ov005_0205b810->spriteManager);
    func_0202ff7c(&data_ov005_0205b810->font);
    func_0202ffbc(&data_ov005_0205b810->textSurfaces[0]);
    func_0202ffbc(&data_ov005_0205b810->textSurfaces[1]);
    func_02024fd4(data_ov005_0205b810->localizedResultArchive);
    func_02024fd4(data_ov005_0205b810->resultArchive);
    for(i=0;i<4;i++) {
        if(data_ov005_0205b810->rowBuffers[i]) {
            NNSi_FndFreeFromDefaultHeap(data_ov005_0205b810->rowBuffers[i]);
            data_ov005_0205b810->rowBuffers[i]=0;
        }
    }
    func_0201e1d0();
    data_ov005_0205b810=0;
}
