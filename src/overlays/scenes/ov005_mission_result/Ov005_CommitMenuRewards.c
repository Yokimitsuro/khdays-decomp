/* Commit menu item quantities and mission flags, then cap the mode-specific reward total. */

#include "nitro/types.h"
#include "game/engine.h"

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
extern GameState *gGameState;
extern Ov005Context *data_ov005_0205b80c;
extern Ov005Config data_ov005_0205b85c;
extern u32 OVERLAY_28_ID[1];
extern int Ov005_StartTouchSampling(void);
extern int Ov028_DSProt_DetectDummy(int (*)(void));
extern int Ov028_DSProt_DetectFlashcart(int (*)(void));
extern int Ov028_DSProt_DetectEmulator(int (*)(void));
void Ov005_CommitMenuRewards(void) {
    Ov005Config *config=&data_ov005_0205b85c;
    int row,index,itemId;
    u16 count;
    u8 flags;
    for(row=0;row<2;row++) {
        for(index=0;index<631;index++) {
            for(itemId=0;itemId<1024;itemId++) {
                if(itemId==data_ov005_0205b80c->items[index].itemId) {
                    if(data_ov005_0205b80c->items[index].quantities[row]!=0) {
                        count=gGameState->itemCounts[itemId]+data_ov005_0205b80c->items[index].quantities[row];
                        GameState_SetFlag(itemId+0x4db);
                        if(data_ov005_0205b80c->items[index].indicatorState==2)GameState_SetFlag(itemId+0x37c9);
                        if(count>data_ov005_0205b80c->items[index].quantityLimit)count=data_ov005_0205b80c->items[index].quantityLimit;
                        gGameState->itemCounts[itemId]=count;
                    }
                    break;
                }
            }
        }
    }
    if(data_ov005_0205b80c->bonusItemCount) {
        gGameState->itemCounts[63]+=data_ov005_0205b80c->bonusItemCount;
        GameState_SetFlag(0x51a);
        if(gGameState->itemCounts[63]>99)gGameState->itemCounts[63]=99;
    }
    LoadOverlaySync(0,(u32)OVERLAY_28_ID);
    if(Ov028_DSProt_DetectDummy(0)) {
        flags=GameState_GetField(config->missionIndex*4+0x92b,4)|config->specialItemMask;
        GameState_SetField(config->missionIndex*4+0x92b,4,flags);
    } else {
        flags=GameState_GetField(config->missionIndex*4+0x92b,4)|config->specialItemMask;
        if(!Ov028_DSProt_DetectFlashcart(Ov005_StartTouchSampling))Ov028_DSProt_DetectEmulator(Ov005_StartTouchSampling);
        GameState_SetField(config->missionIndex*4+0x92b,4,flags);
    }
    UnloadOverlaySync(0,(u32)OVERLAY_28_ID);
    switch(config->rewardMode) {
    case 8: {
        int total;
        if(config->suppressMode8Reward!=0)return;
        if(config->missionIndex==94 || config->missionIndex==37)return;
        total=gGameState->mode8RewardTotal+config->specialQuantity;
        if(total>999)total=999;
        gGameState->mode8RewardTotal=total;
        break;
    }
    case 255:break;
    default: {
        int total;
        if(config->specialQuantity>0) {
            total=gGameState->otherRewardTotal+config->specialQuantity;
            if(total>999)total=999;
            gGameState->otherRewardTotal=total;
        }
    }
    }
}
