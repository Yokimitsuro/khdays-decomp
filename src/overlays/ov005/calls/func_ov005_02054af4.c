/* Commit menu item quantities and mission flags, then cap the mode-specific reward total. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef struct GameState {
    char opaque00[0x810];
    u8 itemCounts[1024];
    char opaqueC10[0xd58];
    u16 mode8RewardTotal,otherRewardTotal;
} GameState;
typedef struct Ov005MenuItemHeader {
    u16 itemId;
    char opaque02[0x242];
    int indicatorState;
    u8 quantities[2];
    u16 quantityLimit;
} Ov005MenuItemHeader;
typedef struct Ov005Context {
    char opaque00[0x4c98];
    Ov005MenuItemHeader items[636];
    char opaque60168[0x2010];
    u8 bonusItemCount;
} Ov005Context;
typedef struct Ov005Config {
    u16 sceneId,missionIndex;
    char opaque04[8];
    u16 rewardMode;
    char opaque0e[2];
    int suppressMode8Reward;
    int specialQuantity;
    char opaque18[0x51];
    u8 specialItemMask;
} Ov005Config;
extern GameState *data_0204be18;
extern Ov005Context *data_ov005_0205b80c;
extern Ov005Config data_ov005_0205b85c;
extern u32 OVERLAY_28_ID[1];
extern void func_020235a8(u32);
extern u32 func_020235d0(u32,u32);
extern void func_020235e8(u32,u32,u32);
extern void func_0201e470(int,int);
extern void func_0201e4a8(int,int);
extern int func_ov005_02054164(void);
extern int func_ov028_0208b3c0(int (*)(void));
extern int func_ov028_0208b040(int (*)(void));
extern int func_ov028_0208b200(int (*)(void));
void func_ov005_02054af4(void) {
    Ov005Config *config=&data_ov005_0205b85c;
    int row,index,itemId;
    u16 count;
    u8 flags;
    for(row=0;row<2;row++) {
        for(index=0;index<631;index++) {
            for(itemId=0;itemId<1024;itemId++) {
                if(itemId==data_ov005_0205b80c->items[index].itemId) {
                    if(data_ov005_0205b80c->items[index].quantities[row]!=0) {
                        count=data_0204be18->itemCounts[itemId]+data_ov005_0205b80c->items[index].quantities[row];
                        func_020235a8(itemId+0x4db);
                        if(data_ov005_0205b80c->items[index].indicatorState==2)func_020235a8(itemId+0x37c9);
                        if(count>data_ov005_0205b80c->items[index].quantityLimit)count=data_ov005_0205b80c->items[index].quantityLimit;
                        data_0204be18->itemCounts[itemId]=count;
                    }
                    break;
                }
            }
        }
    }
    if(data_ov005_0205b80c->bonusItemCount) {
        data_0204be18->itemCounts[63]+=data_ov005_0205b80c->bonusItemCount;
        func_020235a8(0x51a);
        if(data_0204be18->itemCounts[63]>99)data_0204be18->itemCounts[63]=99;
    }
    func_0201e470(0,(u32)OVERLAY_28_ID);
    if(func_ov028_0208b3c0(0)) {
        flags=func_020235d0(config->missionIndex*4+0x92b,4)|config->specialItemMask;
        func_020235e8(config->missionIndex*4+0x92b,4,flags);
    } else {
        flags=func_020235d0(config->missionIndex*4+0x92b,4)|config->specialItemMask;
        if(!func_ov028_0208b040(func_ov005_02054164))func_ov028_0208b200(func_ov005_02054164);
        func_020235e8(config->missionIndex*4+0x92b,4,flags);
    }
    func_0201e4a8(0,(u32)OVERLAY_28_ID);
    switch(config->rewardMode) {
    case 8: {
        int total;
        if(config->suppressMode8Reward!=0)return;
        if(config->missionIndex==94 || config->missionIndex==37)return;
        total=data_0204be18->mode8RewardTotal+config->specialQuantity;
        if(total>999)total=999;
        data_0204be18->mode8RewardTotal=total;
        break;
    }
    case 255:break;
    default: {
        int total;
        if(config->specialQuantity>0) {
            total=data_0204be18->otherRewardTotal+config->specialQuantity;
            if(total>999)total=999;
            data_0204be18->otherRewardTotal=total;
        }
    }
    }
}
