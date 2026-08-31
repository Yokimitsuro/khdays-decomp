typedef unsigned char u8;
typedef struct NNSG3dResFileHeader NNSG3dResFileHeader;
typedef struct Ov005TextureParams {unsigned int texImageParam,texPlttBase;} Ov005TextureParams;
typedef struct Ov005MenuQuad {Ov005TextureParams texture;char opaque[0x1c];} Ov005MenuQuad;
typedef struct Ov005MenuItemHeader {short unknown;unsigned short textureResourceId;} Ov005MenuItemHeader;
typedef struct Ov005TextureResource {NNSG3dResFileHeader *resource;char opaque[8];} Ov005TextureResource;
typedef struct Ov005ListWindow {char opaque[2];signed char firstVisible;} Ov005ListWindow;
extern char *data_ov005_0205b80c;
extern signed char func_ov005_02053370(int rowIndex);
extern void func_ov005_02050d64(Ov005TextureParams *params,const NNSG3dResFileHeader *resource);
void func_ov005_02052048(void) {
    u8 i;
    Ov005TextureResource *resources;
    Ov005ListWindow *window=(Ov005ListWindow *)(data_ov005_0205b80c+0x4bfc);
    int itemRowOffset;
    int quadRowOffset;
    u8 row;
    for (row=0;row<2;row++) {
        signed char count=func_ov005_02053370(row);
        resources=(Ov005TextureResource *)(data_ov005_0205b80c+0x6154c);
        for (i=0;i<count;i++) {
            itemRowOffset=row*0x9f0;
            quadRowOffset=row*0xfc;
            func_ov005_02050d64((Ov005TextureParams *)(data_ov005_0205b80c+0x61f48+quadRowOffset+i*0x24),
                resources[(*(Ov005MenuItemHeader **)((char *)itemRowOffset+(int)data_ov005_0205b80c+(window->firstVisible+i)*4+0x60168))->textureResourceId].resource);
        }
    }
}
