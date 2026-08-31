typedef unsigned int u32;
typedef unsigned short u16;
typedef struct Ov005MenuItemHeader {char data[0x24c];} Ov005MenuItemHeader;
typedef struct ItemWeight {u32 itemId;int weight;} ItemWeight;
typedef struct WeightedItemRecord {char header[0x14];ItemWeight items[8];} WeightedItemRecord;
extern char *data_ov005_0205b80c;
extern int func_020342e8(WeightedItemRecord **,int,u32,int);
extern void func_020343cc(WeightedItemRecord **);
extern u32 func_02023eb4(u32);
extern void func_ov005_0205192c(Ov005MenuItemHeader *,u32,int,int);
void func_ov005_02051be4(u32 tableId) {
    WeightedItemRecord *record=0;
    int total,count,i;
    if(!func_020342e8(&record,0x1a,tableId,0xe))return;
    total=0;
    count=0;
    for(i=0;i<8;i++) {
        total+=record->items[i].weight;
        count++;
    }
    total=func_02023eb4(total);
    for(i=0;i<count;i++) {
        int weight=record->items[i].weight;
        if(weight!=0 && total>=0 && total<=weight) {
            u32 itemId=record->items[i].itemId;
            if(itemId!=0)func_ov005_0205192c((Ov005MenuItemHeader *)(data_ov005_0205b80c+0x4c98)+itemId,(u16)itemId,1,0);
            break;
        }
        total-=weight;
    }
    func_020343cc(&record);
}
