/* Copy or erase a clipped result-screen tilemap rectangle and mark its buffer dirty. */
#pragma opt_strength_reduction off
typedef unsigned short u16;
typedef struct NNSG2dScreenData {
    u16 screenWidth,screenHeight,colorMode,screenFormat;
    unsigned int szByte;
    unsigned int rawData[1];
} NNSG2dScreenData;
typedef struct Ov000ResourceTrackerAux { char opaque[8]; NNSG2dScreenData *screen; int active; } Ov000ResourceTrackerAux;
typedef struct Ov000TileBlitRequest {
    u16 id;
    short destinationX,destinationY;
    u16 sourceX,sourceY;
    short width,height;
    char unknown0e[2];
    int bufferHandle,active;
    Ov000ResourceTrackerAux *asset;
    char unknown1c[0x1c];
} Ov000TileBlitRequest;
typedef struct Ov005ResultContext { char opaque[0x4b80]; unsigned char dirtyTextBuffers; } Ov005ResultContext;
extern Ov005ResultContext *data_ov005_0205b810;
extern void *func_ov005_0205708c(int, int *);
extern void MIi_CpuCopy16(const void *, void *, unsigned int);
extern void MIi_CpuClear16(u16, void *, unsigned int);
void func_ov005_020570f0(int entryAddress,int draw) {
    NNSG2dScreenData *screen;
    int row;
    unsigned int sourceX;
    unsigned int sourceWidth;
    unsigned int sourceY;
    Ov000TileBlitRequest *entry=(Ov000TileBlitRequest *)entryAddress;
    u16 *destination;
    unsigned int x;
    int extent;
    int width;
    unsigned int y;
    {
    int height;
    int bufferIndex;
    destination=func_ov005_0205708c(entry->bufferHandle,&bufferIndex);
    screen=entry->asset->screen;
    width=entry->width;
    height=entry->height;
    sourceWidth=(unsigned int)screen->screenWidth>>3;
    if(width==-1)width=sourceWidth;
    if(height==-1)height=(unsigned int)screen->screenHeight>>3;
    sourceX=entry->sourceX;
    sourceY=entry->sourceY;
    if(entry->destinationX<0){sourceX-=entry->destinationX;width+=entry->destinationX;x=0;}
    else x=(u16)entry->destinationX;
    extent=x+width;
    if(extent>32){extent-=32;width-=extent;}
    if(entry->destinationY<0){sourceY-=entry->destinationY;height+=entry->destinationY;y=0;}
    else y=(u16)entry->destinationY;
    extent=y+height;
    if(extent>24){extent-=24;height-=extent;}
    if(draw) {
        for(row=0;row<height;row++) {
            MIi_CpuCopy16((u16 *)entry->asset->screen->rawData+(sourceWidth*(sourceY+row)+sourceX),
                destination+(x+(y<<5)),width*2);
            y++;
        }
    } else {
        for(entryAddress=0;entryAddress<height;entryAddress++) {
            MIi_CpuClear16(0,destination+(x+(y<<5)),width*2);
            y++;
        }
    }
    data_ov005_0205b810->dirtyTextBuffers|=1<<bufferIndex;
    }
}
