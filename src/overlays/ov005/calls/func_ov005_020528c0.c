typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef struct Ov005MenuItemHeader {char data[0x24c];} Ov005MenuItemHeader;
typedef struct PlayerItemLimit {u16 itemId;short limit;} PlayerItemLimit;
typedef struct Ov005Config {
    u16 sceneId,missionIndex;
    char pad4[8];u16 rewardMode;char pade[6];int specialQuantity;
    char pad18[0x48];PlayerItemLimit *itemQuantities;int nOption64;
    u8 pad68,specialItemMask;short specialQuantities[4];
} Ov005Config;
extern Ov005Config data_ov005_0205b85c;
extern char *data_ov005_0205b80c;
extern void MI_CpuFill8(void *,u8,u32);
extern void func_ov005_0205192c(Ov005MenuItemHeader *,u32,int,int);
extern void func_ov005_02051cd4(int);
extern void func_ov005_02052800(void *);
void func_ov005_020528c0(void) {
    u32 i;
    Ov005Config *config=&data_ov005_0205b85c;
    int itemId;
    int specialIndex;
    int quantity;
    for(i=0;i<0x27c;i++)MI_CpuFill8((Ov005MenuItemHeader *)(data_ov005_0205b80c+0x4c98)+i,0,0x24c);
    if(config->itemQuantities)for(i=0;i<32;i++) {
        if(config->itemQuantities[i].itemId)func_ov005_0205192c((Ov005MenuItemHeader *)(data_ov005_0205b80c+0x4c98)+config->itemQuantities[i].itemId,config->itemQuantities[i].itemId,config->itemQuantities[i].limit,1);
    }
    if(!config->nOption64)func_ov005_02051cd4(config->sceneId);
    for(specialIndex=0;specialIndex<4;specialIndex++) {
        if(config->specialItemMask & (1<<specialIndex)) {
            itemId=specialIndex<2?specialIndex+0x277:0x279;
            func_ov005_0205192c((Ov005MenuItemHeader *)(data_ov005_0205b80c+0x4c98)+itemId,(u16)itemId,config->specialQuantities[specialIndex],1);
        }
    }
    itemId=-1;
    switch(config->rewardMode) {
    case 8:if(config->missionIndex!=94 && config->missionIndex!=37)itemId=0x27a;break;
    case 255:break;
    default:itemId=0x27b;break;
    }
    quantity=config->specialQuantity;
    if(itemId>0 && quantity>0)func_ov005_0205192c((Ov005MenuItemHeader *)(data_ov005_0205b80c+0x4c98)+itemId,(u16)itemId,(short)quantity,0);
    func_ov005_02052800(data_ov005_0205b80c+0x4c90);
}
