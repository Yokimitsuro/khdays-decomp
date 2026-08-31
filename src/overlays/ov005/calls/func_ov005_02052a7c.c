typedef unsigned int u32;
typedef struct Ov005TextureResource {void *resource;u32 textureKey,paletteKey;} Ov005TextureResource;
typedef struct Ov005MenuQuad {char data[36];} Ov005MenuQuad;
typedef struct Ov005TextureSet {void *archive;Ov005TextureResource textures[213];Ov005MenuQuad quads[2][7];} Ov005TextureSet;
typedef struct Ov005Context {char pad0[0x61548];Ov005TextureSet textureSet;} Ov005Context;
extern Ov005Context *data_ov005_0205b80c;
extern char data_ov005_0205b50c[];
extern void func_02010e80(int,int);
extern void func_02011174(int,int);
extern void *func_0201ef9c(const char *,int);
extern void func_02025464(void *,int);
extern u32 func_02010f7c(int,int,int);
extern u32 func_020111c0(int,int,int);
extern void func_ov005_02051eb8(Ov005MenuQuad *,short,short,short,short);
void func_ov005_02052a7c(void) {
    int i;
    Ov005Context *context=data_ov005_0205b80c;
    Ov005TextureSet *set=&context->textureSet;
    int x,y;
    Ov005TextureResource *texture;
    Ov005MenuQuad *row,*quad;
    int j;
    func_02010e80(1,1);
    func_02011174(0x8000,1);
    context->textureSet.archive=func_0201ef9c(data_ov005_0205b50c,14);
    func_02025464(context->textureSet.archive,0);
    for(i=0,texture=set->textures;i<213;i++,texture++) {
        texture->textureKey=func_02010f7c(0x80,0,0);
        texture->paletteKey=func_020111c0(0x20,0,1);
    }
    for(i=0,x=10,row=set->quads[0];i<2;i++,x+=112,row+=7) {
        for(j=0,y=40,quad=row;j<7;j++,y+=16,quad++)func_ov005_02051eb8(quad,(short)x,(short)y,0,31);
    }
}
