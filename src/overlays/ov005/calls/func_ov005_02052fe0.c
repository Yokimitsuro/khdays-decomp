typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef struct FontInfo {char data[12];} FontInfo;
typedef struct TileSurface {char pad0[40];int nUnk28;char pad2c[16];} TileSurface;
typedef struct TileSurfaceCfg {int nUnk00,nUnk04,nWidthTiles,nHeightTiles,nRowTiles,nPaletteIndex;void *nVramTarget;int nUnk1c;FontInfo *pPixels;int nUnk24;} TileSurfaceCfg;
typedef struct Ov005Context {char pad0[0x4ad8];FontInfo fonts[2];TileSurface surfaces[4];int activeBufferIndex;} Ov005Context;
extern Ov005Context *data_ov005_0205b80c;
extern char data_ov005_0205b558[],data_ov005_0205b570[];
extern void MI_CpuFill8(void *,u8,u32);
extern void func_0202ff58(FontInfo *,const char *);
extern void *func_ov005_02053ef0(int,int *);
extern void func_0202ff8c(TileSurface *,TileSurfaceCfg *);
extern void *G2S_GetBG2ScrPtr(void);
extern void *G2S_GetBG2CharPtr(void);
extern void MIi_CpuClearFast(u32,void *,u32);
void func_ov005_02052fe0(void) {
    TileSurfaceCfg config;
    TileSurface *surface;
    u8 i;
    u16 tileBase=1;
    MI_CpuFill8(&data_ov005_0205b80c->fonts[0],0,12);
    MI_CpuFill8(&config,0,40);
    func_0202ff58(&data_ov005_0205b80c->fonts[0],data_ov005_0205b558);
    func_0202ff58(&data_ov005_0205b80c->fonts[1],data_ov005_0205b570);
    config.nPaletteIndex=15;
    config.nVramTarget=func_ov005_02053ef0(10,&data_ov005_0205b80c->activeBufferIndex);
    config.nUnk1c=6;
    config.pPixels=&data_ov005_0205b80c->fonts[0];
    config.nUnk24=32;
    for(i=0;i<4;i++) {
        switch(i) {
        case 0:config.nUnk00=0;config.nUnk04=0;config.nWidthTiles=24;config.nHeightTiles=2;break;
        case 1:config.nUnk00=5;config.nUnk04=1;config.nWidthTiles=28;config.nHeightTiles=16;break;
        case 2:config.nUnk00=3;config.nUnk04=1;config.nWidthTiles=32;config.nHeightTiles=2;break;
        case 3:config.nUnk00=20;config.nUnk04=1;config.nWidthTiles=30;config.nHeightTiles=4;break;
        }
        config.nRowTiles=tileBase;
        surface=&data_ov005_0205b80c->surfaces[i];
        func_0202ff8c(surface,&config);
        if(i==3)surface->nUnk28=3;
        tileBase+=config.nWidthTiles*config.nHeightTiles;
    }
    MIi_CpuClearFast(0,G2S_GetBG2ScrPtr(),0x800);
    MIi_CpuClearFast(0,G2S_GetBG2CharPtr(),32);
}
