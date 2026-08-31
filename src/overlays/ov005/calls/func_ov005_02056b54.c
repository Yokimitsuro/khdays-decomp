/* Initialize the result font and two text surfaces sharing the selected row buffer. */
typedef unsigned char u8;
typedef unsigned int u32;
typedef struct FontInfo { char data[12]; } FontInfo;
typedef struct TileSurface { char data[60]; } TileSurface;
typedef struct TileSurfaceCfg {
    int nUnk00, nUnk04, nWidthTiles, nHeightTiles, nRowTiles, nPaletteIndex;
    void *nVramTarget;
    int nUnk1c;
    FontInfo *pPixels;
    int nUnk24;
} TileSurfaceCfg;
typedef struct Ov005ResultContext {
    char unknown00[0x4ad4];
    FontInfo font;
    TileSurface textSurfaces[2];
    int activeTextBufferIndex;
} Ov005ResultContext;
extern Ov005ResultContext *data_ov005_0205b810;
extern char data_ov005_0205b5f4[];
extern void MI_CpuFill8(void *,u8,u32);
extern void func_0202ff58(FontInfo *,const char *);
extern void *func_ov005_0205708c(int,int *);
extern void func_0202ff98(TileSurface *,TileSurfaceCfg *);
extern void *G2_GetBG2ScrPtr(void),*G2S_GetBG2CharPtr(void);
extern void MIi_CpuClearFast(u32,void *,u32);
void func_ov005_02056b54(void) {
    TileSurfaceCfg config;
    u8 tileBase=1;
    MI_CpuFill8(&data_ov005_0205b810->font,0,12);
    MI_CpuFill8(&config,0,40);
    func_0202ff58(&data_ov005_0205b810->font,data_ov005_0205b5f4);
    config.nUnk04=13;
    config.nWidthTiles=19;
    config.nHeightTiles=2;
    config.nUnk00=0;
    config.nRowTiles=tileBase;
    config.nPaletteIndex=0;
    config.nVramTarget=func_ov005_0205708c(26,&data_ov005_0205b810->activeTextBufferIndex);
    config.nUnk1c=22;
    config.pPixels=&data_ov005_0205b810->font;
    config.nUnk24=32;
    func_0202ff98(&data_ov005_0205b810->textSurfaces[0],&config);
    tileBase+=config.nWidthTiles*config.nHeightTiles;
    config.nRowTiles=tileBase;
    config.nUnk00=6;
    config.nUnk04=9;
    config.nWidthTiles=20;
    config.nHeightTiles=2;
    func_0202ff98(&data_ov005_0205b810->textSurfaces[1],&config);
    MIi_CpuClearFast(0,G2_GetBG2ScrPtr(),0x800);
    MIi_CpuClearFast(0,G2S_GetBG2CharPtr(),32);
}
