typedef struct NNSG3dResFileHeader NNSG3dResFileHeader;
typedef struct NNSG3dResTex NNSG3dResTex;
typedef struct Ov005TextureResource {NNSG3dResFileHeader *resource;unsigned int textureKey,paletteKey;} Ov005TextureResource;
typedef struct Ov005Context {char pad0[0x61548];void *textureArchive;} Ov005Context;
extern Ov005Context *data_ov005_0205b80c;
extern void func_0201f390(int);
extern NNSG3dResFileHeader *func_020255d4(void *,int,int);
extern NNSG3dResTex *func_02017088(NNSG3dResFileHeader *);
extern void func_02014e70(NNSG3dResTex *,unsigned int,unsigned int);
extern void func_02014ee4(NNSG3dResTex *,unsigned int);
extern void func_02025364(NNSG3dResTex *);
extern void func_02025420(NNSG3dResTex *);
void func_ov005_02051efc(Ov005TextureResource *entry,int textureId) {
    NNSG3dResTex *texture;
    func_0201f390(0);
    entry->resource=func_020255d4(data_ov005_0205b80c->textureArchive,7,textureId);
    if(entry->resource) {
        texture=func_02017088(entry->resource);
        func_02014e70(texture,entry->textureKey,0);
        func_02014ee4(texture,entry->paletteKey);
        func_02025364(texture);
        func_02025420(texture);
    }
    func_0201f390(1);
}
