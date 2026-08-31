typedef unsigned short u16;
typedef struct MsgDbItemRecord {char pad0[32];u16 icon;} MsgDbItemRecord;
typedef struct Ov005TextureResource {void *resource;unsigned int textureKey,paletteKey;} Ov005TextureResource;
typedef struct Ov005Context {char pad0[0x6154c];Ov005TextureResource textures[213];} Ov005Context;
extern Ov005Context *data_ov005_0205b80c;
extern void func_020342e8(MsgDbItemRecord **,int,unsigned int,int);
extern void func_020343cc(MsgDbItemRecord **);
extern void func_ov005_02051efc(Ov005TextureResource *,int);
static inline int GetIconIndex(MsgDbItemRecord *record) {
    if(!record || !record->icon)return 0;
    return record->icon-1;
}
void func_ov005_02051f78(void) {
    MsgDbItemRecord *record=0;
    int itemId;
    int textureId;
    for(itemId=1;itemId<0x277;itemId++) {
        func_020342e8(&record,0x15,itemId,14);
        textureId=GetIconIndex(record);
        func_ov005_02051efc(&data_ov005_0205b80c->textures[textureId],textureId);
        if(record)func_020343cc(&record);
    }
    for(itemId=0xd1;itemId<0xd5;itemId++)func_ov005_02051efc(&data_ov005_0205b80c->textures[itemId],itemId);
}
