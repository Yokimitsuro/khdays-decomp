/* Sets up the result screen's texture VRAM, loads the icon archive and reserves texture and palette
 * space for every icon, and places the reward list quads. */

#include "nitro/types.h"

typedef struct Ov005TextureResource {void *resource;u32 textureKey,paletteKey;} Ov005TextureResource;
typedef struct Ov005MenuQuad {char data[36];} Ov005MenuQuad;
typedef struct Ov005TextureSet {void *archive;Ov005TextureResource textures[213];Ov005MenuQuad quads[2][7];} Ov005TextureSet;
typedef struct Ov005Context {char pad0[0x61548];Ov005TextureSet textureSet;} Ov005Context;
extern Ov005Context *data_ov005_0205b80c;
extern char gOv005UiPnl3DPackPath[];
extern void NNS_GfdInitFrmTexVramManager(int,int);
extern void NNS_GfdInitFrmPlttVramManager(int,int);
extern void *Archive_LoadFile(const char *,int);
extern void Obj_RelocateSections(void *,int);
extern u32 NNS_GfdAllocFrmTexVram(int,int,int);
extern u32 func_020111c0(int,int,int);
extern void Ov005_InitializeMenuQuad(Ov005MenuQuad *,short,short,short,short);
void Ov005_AllocateResultTextures(void) {
    int i;
    Ov005Context *context=data_ov005_0205b80c;
    Ov005TextureSet *set=&context->textureSet;
    int x,y;
    Ov005TextureResource *texture;
    Ov005MenuQuad *row,*quad;
    int j;
    NNS_GfdInitFrmTexVramManager(1,1);
    NNS_GfdInitFrmPlttVramManager(0x8000,1);
    context->textureSet.archive=Archive_LoadFile(gOv005UiPnl3DPackPath,14);
    Obj_RelocateSections(context->textureSet.archive,0);
    for(i=0,texture=set->textures;i<213;i++,texture++) {
        texture->textureKey=NNS_GfdAllocFrmTexVram(0x80,0,0);
        texture->paletteKey=func_020111c0(0x20,0,1);
    }
    for(i=0,x=10,row=set->quads[0];i<2;i++,x+=112,row+=7) {
        for(j=0,y=40,quad=row;j<7;j++,y+=16,quad++)Ov005_InitializeMenuQuad(quad,(short)x,(short)y,0,31);
    }
}
