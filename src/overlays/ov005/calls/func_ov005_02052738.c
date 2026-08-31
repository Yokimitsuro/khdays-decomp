typedef unsigned int u32;
typedef struct PaletteData {char pad0[8];u32 size;void *data;} PaletteData;
typedef struct CharacterData {char pad0[16];u32 size;void *data;} CharacterData;
typedef struct SpriteResSet {void *screen;CharacterData *character;PaletteData *palette;} SpriteResSet;
typedef struct Ov005Context {u32 resultArchive;} Ov005Context;
extern Ov005Context *data_ov005_0205b80c;
extern void *func_0201ef9c(u32,int);
extern void func_02024c94(SpriteResSet *,void *,int,int,int);
extern void GX_LoadBGPltt(void *,u32,u32);
extern void GX_LoadBG3Char(void *,u32,u32);
extern void GX_LoadBG1Char(void *,u32,u32);
extern void NNSi_FndFreeFromDefaultHeap(void *);
void func_ov005_02052738(void) {
    SpriteResSet resources;
    void *archive;
    archive=func_0201ef9c((((data_ov005_0205b80c->resultArchive+0x8000)&0xfffffc)<<7)|0x80000000,14);
    func_02024c94(&resources,archive,-1,2,0);
    GX_LoadBGPltt(resources.palette->data,0,resources.palette->size);
    GX_LoadBG3Char(resources.character->data,0,resources.character->size);
    func_02024c94(&resources,archive,-1,4,-1);
    GX_LoadBG1Char(resources.character->data,0,resources.character->size);
    if(archive)NNSi_FndFreeFromDefaultHeap(archive);
}
