/* Redraws one of the reward menu's text surfaces: the header message, the item names and
 * quantities, the column labels or the selected item's description. */

#include "nitro/types.h"

typedef struct FontInfo { int opaque[3]; } FontInfo;
typedef struct TileSurface {
    void *pixels;
    int width,height,totalBytes,rowBytes,unknown14;
    void *current,*currentData;
    FontInfo *font;
    int textMetricArg,unknown28,unknown2c,unknown30,unknown34,is8bpp;
} TileSurface;
typedef struct Ov005MenuItemHeader {
    u16 itemId,textureResourceId,name[32],description[256];
    int indicatorState;
    u8 quantities[2];
    u16 quantityLimit;
} Ov005MenuItemHeader;
typedef struct Ov005SelectionState {
    signed char selectedItem,activeRow,firstVisibleItem,unknown03;
    int maxFirstVisibleItem,cachedRowItemCounts[2],scrollThumbHeight;
} Ov005SelectionState;
typedef struct Ov005TextTable { int unknown,count; void *records; } Ov005TextTable;
typedef struct Ov005Context {
    char opaque00[0x4ad8];
    FontInfo fonts[2];
    TileSurface textSurfaces[4];
    int activeBufferIndex;
    void *rowBuffers[3];
    int menuState;
    long long startTick;
    Ov005SelectionState selection;
    char opaque4c10[0x2c];
    u8 dirtyTextBuffers;
    char opaque4c3d[0x4f];
    u8 statusStep;
    char opaque4c8d[3];
    int rowItemCounts[2];
    Ov005MenuItemHeader items[636];
    Ov005MenuItemHeader *firstItemSlot[2][636];
    char opaque61548[0xc34];
    Ov005TextTable menuText;
} Ov005Context;
typedef struct Ov005Config { char opaque[0x68]; u8 resultCode; } Ov005Config;
extern Ov005Context *data_ov005_0205b80c;
extern Ov005Config data_ov005_0205b85c;
extern const u16 data_ov005_0205b504[];
extern void Obj_InvokeInnerVtable4(TileSurface *);
extern u16 *Ov005_GetVarRecordByIndex(Ov005TextTable *,unsigned int);
extern void Ov005_DrawShadowedText(TileSurface *,const u16 *,int,int,int,unsigned int,int);
extern void Text_FormatUtf16(u16 *dst, unsigned int len, const u16 *fmt, ...);
extern int NNSi_G2dFontGetTextWidth(FontInfo *,int,const u16 *);
extern void TextCanvas_DrawShadowedAt(TileSurface *,int,int,int,int,const u16 *);
extern void EnqueueObjGfxCommand(TileSurface *);
void Ov005_RenderTextSurface(int surfaceIndex) {
    u8 row;
    TileSurface *surface=&data_ov005_0205b80c->textSurfaces[surfaceIndex];
    Ov005SelectionState *selection=&data_ov005_0205b80c->selection;
    Ov005Config *config=&data_ov005_0205b85c;
    u16 *text=0;
    u8 line,index;
    u16 quantityText[8];
    Ov005MenuItemHeader *item;
    int narrow;
    Obj_InvokeInnerVtable4(surface);
    switch(surfaceIndex) {
    case 0:
        if(data_ov005_0205b80c->menuState==2) {
            if(data_ov005_0205b80c->statusStep>=3) {
                u8 messageId=config->resultCode==2?3:4;
                text=Ov005_GetVarRecordByIndex(&data_ov005_0205b80c->menuText,messageId);
            }
        } else text=Ov005_GetVarRecordByIndex(&data_ov005_0205b80c->menuText,2);
        Ov005_DrawShadowedText(surface,text,6,6,1,0x209,1);
        break;
    case 1:
        for(line=0;line<7;line++) {
            for(row=0;row<2;row++) {
                index=line+selection->firstVisibleItem;
                if(index>=data_ov005_0205b80c->rowItemCounts[row]) continue;
                item=data_ov005_0205b80c->firstItemSlot[row][index];
                if(item->itemId==0)continue;
                Text_FormatUtf16(quantityText,8,data_ov005_0205b504,item->quantities[row]);
                narrow=NNSi_G2dFontGetTextWidth(surface->font,surface->textMetricArg,item->name)>=72;
                if(narrow)surface->font=&data_ov005_0205b80c->fonts[1];
                Ov005_DrawShadowedText(surface,item->name,row*112+20,line*16+3,1,0x209,1);
                if(narrow)surface->font=&data_ov005_0205b80c->fonts[0];
                Ov005_DrawShadowedText(surface,quantityText,row*112+106,line*16+3,3,0x821,1);
            }
        }
        break;
    case 2:
        text=Ov005_GetVarRecordByIndex(&data_ov005_0205b80c->menuText,5);
        Ov005_DrawShadowedText(surface,text,56,5,1,0x412,1);
        text=Ov005_GetVarRecordByIndex(&data_ov005_0205b80c->menuText,6);
        Ov005_DrawShadowedText(surface,text,168,5,1,0x412,1);
        break;
    case 3:
        item=data_ov005_0205b80c->firstItemSlot[selection->activeRow][(u8)(selection->selectedItem+selection->firstVisibleItem)];
        if(item)TextCanvas_DrawShadowedAt(surface,3,4,1,3,item->description);
        break;
    }
    EnqueueObjGfxCommand(surface);
    data_ov005_0205b80c->dirtyTextBuffers|=1<<data_ov005_0205b80c->activeBufferIndex;
}
