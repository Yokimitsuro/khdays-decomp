/* Ov005_InitializeMissionResultSprites: load the result-screen sprite sets,
 * reset their entries, select reward indicators, and initialize progress bars.
 * The progress numerator at config+0x20 is signed; mode 255 alone maps a zero
 * percentage to 100. Pixel widths use 183*percent/100 narrowed to signed 16 bits.
 * ARM: 1220 bytes, 46 relocations, byte-exact.
 */

#include "nitro/types.h"
#include "game/engine.h"
#include "game/archive.h"

typedef struct Ov005SpriteManager {char data[0x4a80];} Ov005SpriteManager;
typedef struct Ov005ResultContext {u32 resultArchive,localizedResultArchive;char unknown08[76];Ov005SpriteManager spriteManager;} Ov005ResultContext;
typedef struct Ov005Config {u16 sceneId,missionIndex;char unknown04[8];u16 rewardMode;char unknown0e[18];int missionProgressValue;char unknown24[12];int missionTargetValue;} Ov005Config;
typedef struct SpriteDescriptor {u32 resourceId;int type,mode,variant;} SpriteDescriptor;
extern Ov005ResultContext *data_ov005_0205b810;
extern Ov005Config data_ov005_0205b85c;
extern void *G2_GetBG0ScrPtr(void),*G2_GetBG3ScrPtr(void);
extern void MIi_CpuClearFast(u32,void *,u32);
extern void Ov005_InitSubsystemObject(Ov005SpriteManager *,void *);
extern void Ov005_InitFromDescAndMark(Ov005SpriteManager *,SpriteDescriptor *);
extern void func_ov005_0204e0b0(Ov005SpriteManager *,u32);
extern void Ov005_LoadBlockProcessAndFree(Ov005SpriteManager *,u32,int);
extern void *Ov005_FindEntryById(Ov005SpriteManager *,int);
extern void Ov005_ReleaseTwoSlotsEx_2(Ov005SpriteManager *,void *,int);
extern void Ov005_ReleaseTwoSlots(Ov005SpriteManager *,void *);
extern void Ov005_SetEntrySlotsVisible(Ov005SpriteManager *,void *,int);
extern void Ov005_DrawResultNumber(int,int,int,int);
extern void Ov005_SelectAndShowResultSprite(int,int);
extern void Ov005_SetResultSpritePixelOffset(int,int,int);
extern int func_02020400(int,int);
static inline void ShowEntry(int id) {
    Ov005_SetEntrySlotsVisible(&data_ov005_0205b810->spriteManager,
        Ov005_FindEntryById(&data_ov005_0205b810->spriteManager,id),1);
}
void Ov005_InitializeMissionResultSprites(void) {
    SpriteDescriptor descriptor;
    Ov005ResultContext *context=data_ov005_0205b810;
    Ov005Config *config=&data_ov005_0205b85c;
    u8 index;
    int number;
    int icon;
    MIi_CpuClearFast(0,G2_GetBG0ScrPtr(),0x800);
    MIi_CpuClearFast(0,G2_GetBG3ScrPtr(),0x800);
    Ov005_InitSubsystemObject(&context->spriteManager,0);
    descriptor.resourceId=ARCHIVE_HANDLE(data_ov005_0205b810->resultArchive, 2);
    descriptor.type=2;descriptor.mode=0;descriptor.variant=0;
    Ov005_InitFromDescAndMark(&context->spriteManager,&descriptor);
    func_ov005_0204e0b0(&context->spriteManager,ARCHIVE_HANDLE(data_ov005_0205b810->localizedResultArchive, 1));
    Ov005_LoadBlockProcessAndFree(&context->spriteManager,ARCHIVE_HANDLE(data_ov005_0205b810->resultArchive, 5),111);
    for(index=1;index<=111;index++) {
        void *entry=Ov005_FindEntryById(&context->spriteManager,index);
        Ov005_ReleaseTwoSlotsEx_2(&context->spriteManager,entry,0);
        Ov005_ReleaseTwoSlots(&context->spriteManager,entry);
    }
    number=(int)config->missionIndex%100;
    if(number==94)number=0;
    Ov005_DrawResultNumber(number,3,2,2);
    if(config->missionIndex>=100)ShowEntry(5);
    Ov005_SelectAndShowResultSprite(33,0);Ov005_SelectAndShowResultSprite(39,0);
    Ov005_SelectAndShowResultSprite(48,0);Ov005_SelectAndShowResultSprite(54,0);
    Ov005_SelectAndShowResultSprite(63,0);Ov005_SelectAndShowResultSprite(69,0);
    switch(config->rewardMode) {
    case 0:icon=99;break;
    case 1:icon=100;break;
    case 3:icon=111;break;
    case 4:icon=102;break;
    case 5:icon=103;break;
    case 6:icon=104;break;
    case 7:icon=105;break;
    case 8:icon=106;break;
    default:icon=9;break;
    }
    Ov005_SelectAndShowResultSprite(icon,0);
    if(GameState_IsFlagSet(0x2087)) {
        Ov005_SelectAndShowResultSprite(107,0);
        switch(config->rewardMode) {
        case 255:Ov005_SelectAndShowResultSprite(8,0);break;
        case 8:Ov005_SelectAndShowResultSprite(8,2);break;
        default:Ov005_SelectAndShowResultSprite(8,1);break;
        }
    } else if(config->rewardMode==255) {
        int percent=func_02020400(config->missionProgressValue*100,config->missionTargetValue);
        if(percent==0)percent=100;
        Ov005_SelectAndShowResultSprite(8,0);
        ShowEntry(10);
        Ov005_SetResultSpritePixelOffset(10,(short)(183*percent/100),0);
    } else {
        if(config->rewardMode==8)Ov005_SelectAndShowResultSprite(8,2);
        else Ov005_SelectAndShowResultSprite(8,1);
        switch(config->rewardMode) {
        case 2: {
            int percent=func_02020400(config->missionProgressValue*100,config->missionTargetValue);
            ShowEntry(10);
            Ov005_SetResultSpritePixelOffset(10,(short)(183*percent/100),0);
            break;
        }
        case 0: {
            int id;
            Ov005_SelectAndShowResultSprite(11,0);
            for(id=22;id<=29;id++)if(id!=24 && id!=27)Ov005_SelectAndShowResultSprite(id,0);
            ShowEntry(20);ShowEntry(21);
            break;
        }
        default:Ov005_SelectAndShowResultSprite(22,0);break;
        }
    }
}
