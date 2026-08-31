typedef unsigned char u8;
typedef unsigned short u16;
typedef struct Ov005MenuItemHeader {
    u16 itemId,textureResourceId;
    u16 name[32];
    u16 description[256];
    int indicatorState;
    u8 quantities[2];
    u16 quantityLimit;
} Ov005MenuItemHeader;
typedef struct MsgDbItemRecord {
    char header[12];
    u16 *name,*description;
    int opaque14;
    int category;
    int opaque1c;
    u16 icon;
} MsgDbItemRecord;
extern char *data_ov005_0205b80c;
extern void func_020342e8(MsgDbItemRecord **,int,unsigned int,int);
extern void func_020343cc(MsgDbItemRecord **);
extern void func_02020104(u16 *,const u16 *,int);
extern u16 *func_ov005_0204e4f8(void *,unsigned int);
extern u16 *func_ov005_0205b100(void *,MsgDbItemRecord *);
extern int func_02023588(unsigned int);
static inline int GetIconIndex(MsgDbItemRecord *record) {
    if (record==0 || record->icon==0) return 0;
    return record->icon-1;
}
void func_ov005_0205192c(Ov005MenuItemHeader *item,unsigned int itemId,int quantity,int row) {
    MsgDbItemRecord *record=0;
    if(item==0)return;
    if(itemId==0 || quantity==0)return;
    item->name[31]=0;
    item->description[255]=0;
    if(itemId>=0x277) {
        item->itemId=itemId;
        switch(itemId) {
        case 0x277:case 0x278:case 0x279:
            item->textureResourceId=itemId==0x279?0xd2:0xd1;
            func_020342e8(&record,0x15,itemId-0xb5,0xe);
            func_02020104(item->name,record->name,31);
            func_02020104(item->description,record->description,255);
            func_020343cc(&record);
            item->quantities[row]=1;
            break;
        case 0x27a:
            item->textureResourceId=0xd3;
            func_02020104(item->name,func_ov005_0204e4f8(data_ov005_0205b80c+0x6217c,11),31);
            func_02020104(item->description,func_ov005_0204e4f8(data_ov005_0205b80c+0x6217c,12),255);
            item->quantities[row]=quantity;
            break;
        case 0x27b:
            item->textureResourceId=0xd4;
            func_02020104(item->name,func_ov005_0204e4f8(data_ov005_0205b80c+0x6217c,13),31);
            func_02020104(item->description,func_ov005_0204e4f8(data_ov005_0205b80c+0x6217c,14),255);
            item->quantities[row]=quantity;
            break;
        }
        item->indicatorState=1;
    } else {
        int icon;
        func_020342e8(&record,0x15,itemId,0xe);
        icon=GetIconIndex(record);
        item->itemId=itemId;
        item->textureResourceId=icon;
        func_02020104(item->name,record->name,31);
        func_02020104(item->description,func_ov005_0205b100(data_ov005_0205b80c+0x62188,record),255);
        item->quantities[row]+=quantity;
        if(func_02023588(itemId+0x37c9)) item->indicatorState=0;
        else item->indicatorState=1;
        item->quantityLimit=record->category==2 || itemId==1?255:99;
        func_020343cc(&record);
    }
}
