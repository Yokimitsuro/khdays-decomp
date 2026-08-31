typedef unsigned char u8;
typedef unsigned short u16;
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
extern void func_02030158(TileSurface *);
extern u16 *func_ov005_0204e4f8(Ov005TextTable *,unsigned int);
extern void func_ov005_02052384(TileSurface *,const u16 *,int,int,int,unsigned int,int);
extern void func_020262a0(u16 *,unsigned int,const u16 *,...);
extern int func_02013814(FontInfo *,int,const u16 *);
extern void func_0203031c(TileSurface *,int,int,int,int,const u16 *);
extern void func_020300f8(TileSurface *);
void func_ov005_020523f8(int surfaceIndex) {
    u8 row;
    TileSurface *surface=&data_ov005_0205b80c->textSurfaces[surfaceIndex];
    Ov005SelectionState *selection=&data_ov005_0205b80c->selection;
    Ov005Config *config=&data_ov005_0205b85c;
    u16 *text=0;
    u8 line,index;
    u16 quantityText[8];
    Ov005MenuItemHeader *item;
    int narrow;
    func_02030158(surface);
    switch(surfaceIndex) {
    case 0:
        if(data_ov005_0205b80c->menuState==2) {
            if(data_ov005_0205b80c->statusStep>=3) {
                u8 messageId=config->resultCode==2?3:4;
                text=func_ov005_0204e4f8(&data_ov005_0205b80c->menuText,messageId);
            }
        } else text=func_ov005_0204e4f8(&data_ov005_0205b80c->menuText,2);
        func_ov005_02052384(surface,text,6,6,1,0x209,1);
        break;
    case 1:
        for(line=0;line<7;line++) {
            for(row=0;row<2;row++) {
                index=line+selection->firstVisibleItem;
                if(index>=data_ov005_0205b80c->rowItemCounts[row]) continue;
                item=data_ov005_0205b80c->firstItemSlot[row][index];
                if(item->itemId==0)continue;
                func_020262a0(quantityText,8,data_ov005_0205b504,item->quantities[row]);
                narrow=func_02013814(surface->font,surface->textMetricArg,item->name)>=72;
                if(narrow)surface->font=&data_ov005_0205b80c->fonts[1];
                func_ov005_02052384(surface,item->name,row*112+20,line*16+3,1,0x209,1);
                if(narrow)surface->font=&data_ov005_0205b80c->fonts[0];
                func_ov005_02052384(surface,quantityText,row*112+106,line*16+3,3,0x821,1);
            }
        }
        break;
    case 2:
        text=func_ov005_0204e4f8(&data_ov005_0205b80c->menuText,5);
        func_ov005_02052384(surface,text,56,5,1,0x412,1);
        text=func_ov005_0204e4f8(&data_ov005_0205b80c->menuText,6);
        func_ov005_02052384(surface,text,168,5,1,0x412,1);
        break;
    case 3:
        item=data_ov005_0205b80c->firstItemSlot[selection->activeRow][(u8)(selection->selectedItem+selection->firstVisibleItem)];
        if(item)func_0203031c(surface,3,4,1,3,item->description);
        break;
    }
    func_020300f8(surface);
    data_ov005_0205b80c->dirtyTextBuffers|=1<<data_ov005_0205b80c->activeBufferIndex;
}
