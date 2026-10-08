/* Initialises the reward menu's sprites: loads the sprite set, disables the entries, creates the 14
 * new-item indicators and installs the touch callbacks. */

#include "nitro/types.h"

typedef void (*EntryCallback)(void);
typedef struct Ov005SpriteManager {char data[0x4a80];} Ov005SpriteManager;
typedef struct Ov005Context {u32 resultArchive,localizedResultArchive;char pad8[76];Ov005SpriteManager embeddedManager;Ov005SpriteManager *spriteManager;char pad4ad8[0x5d668];int indicatorSlots[2][7];} Ov005Context;
typedef struct SpriteDescriptor {u32 resourceId;int type,mode,variant;} SpriteDescriptor;
typedef struct EntryIds {int ids[4];} EntryIds;
typedef struct UiLayoutPos {int x,y;} UiLayoutPos;
extern Ov005Context *data_ov005_0205b80c;
extern EntryIds data_ov005_0205b358;
extern void Ov005_InitSubsystemObject(Ov005SpriteManager *,void *);
extern void Ov005_InitFromDescAndMark(Ov005SpriteManager *,SpriteDescriptor *);
extern void func_ov005_0204e0b0(Ov005SpriteManager *,u32);
extern void Ov005_LoadBlockProcessAndFree(Ov005SpriteManager *,u32,int);
extern void Ov005_SetControlBit0AtA7C(Ov005SpriteManager *,int);
extern void *Ov005_FindEntryById(Ov005SpriteManager *,int);
extern void Ov005_ReleaseTwoSlotsEx_2(Ov005SpriteManager *,void *,int);
extern void Ov005_ReleaseTwoSlots(Ov005SpriteManager *,void *);
extern void Ov005_ReleaseTwoSlots_2(Ov005SpriteManager *,void *);
extern int VeneerTo_SlotTable_AddEntry(Ov005SpriteManager *,int,int);
extern void SlotTable_SetEntryVelocity(Ov005SpriteManager *,int,int);
extern void Slot_SetPosition(Ov005SpriteManager *,int,UiLayoutPos *);
extern void Slot_ClearFlagBit1(Ov005SpriteManager *,int);
extern void Slot_SetVisible(Ov005SpriteManager *,int,int);
extern void Ov005_ResolveEntryStoreWord(Ov005SpriteManager *,int,EntryCallback);
extern void Ov005_ScrollFromTouch(void),Ov005_ResultSpriteCallbackNoOp(void),Ov005_ResultSpriteCallbackNoOp_2(void),Ov005_ResultSpriteCallbackNoOp_3(void),Ov005_ResultSpriteCallbackNoOp_4(void),Ov005_ConfirmExitFromTouch(void),Ov005_CancelExitFromTouch(void);
static inline void SetPixelPosition(UiLayoutPos *position,int x,int y) {position->y=y<<12;position->x=x<<12;}
void Ov005_InitializeResultSprites(void) {
    SpriteDescriptor descriptor;
    EntryIds entryIds;
    UiLayoutPos position;
    Ov005SpriteManager *manager=&data_ov005_0205b80c->embeddedManager;
    int x;
    int id,index,y;
    u32 i;
    Ov005_InitSubsystemObject(manager,0);
    descriptor.resourceId=(((data_ov005_0205b80c->resultArchive+0x8000)&0xfffffc)<<7)|0x80000001;
    descriptor.type=1;descriptor.mode=0;descriptor.variant=0;
    Ov005_InitFromDescAndMark(manager,&descriptor);
    func_ov005_0204e0b0(manager,(((data_ov005_0205b80c->localizedResultArchive+0x8000)&0xfffffc)<<7)|0x80000000);
    Ov005_LoadBlockProcessAndFree(manager,(((data_ov005_0205b80c->resultArchive+0x8000)&0xfffffc)<<7)|0x80000004,49);
    Ov005_SetControlBit0AtA7C(manager,0);
    data_ov005_0205b80c->spriteManager=manager;
    for(id=1;id<=49;id++) {
        Ov005_ReleaseTwoSlotsEx_2(&data_ov005_0205b80c->embeddedManager,Ov005_FindEntryById(&data_ov005_0205b80c->embeddedManager,id),0);
        Ov005_ReleaseTwoSlots(&data_ov005_0205b80c->embeddedManager,Ov005_FindEntryById(&data_ov005_0205b80c->embeddedManager,id));
    }
    entryIds=data_ov005_0205b358;
    for(i=0;i<4;i++)Ov005_ReleaseTwoSlots_2(&data_ov005_0205b80c->embeddedManager,Ov005_FindEntryById(&data_ov005_0205b80c->embeddedManager,entryIds.ids[i]));
    for(id=0;id<2;id++) {
        x=17+id*112;
        for(index=0;index<7;index++) {
            y=49+index*16;
            data_ov005_0205b80c->indicatorSlots[id][index]=VeneerTo_SlotTable_AddEntry(data_ov005_0205b80c->spriteManager,0,1);
            SetPixelPosition(&position,x,y);
            SlotTable_SetEntryVelocity(data_ov005_0205b80c->spriteManager,data_ov005_0205b80c->indicatorSlots[id][index],120);
            Slot_SetPosition(data_ov005_0205b80c->spriteManager,data_ov005_0205b80c->indicatorSlots[id][index],&position);
            Slot_ClearFlagBit1(data_ov005_0205b80c->spriteManager,data_ov005_0205b80c->indicatorSlots[id][index]);
            Slot_SetVisible(data_ov005_0205b80c->spriteManager,data_ov005_0205b80c->indicatorSlots[id][index],0);
        }
    }
    Ov005_ResolveEntryStoreWord(manager,4,Ov005_ScrollFromTouch);
    Ov005_ResolveEntryStoreWord(manager,18,Ov005_ResultSpriteCallbackNoOp);
    Ov005_ResolveEntryStoreWord(manager,19,Ov005_ResultSpriteCallbackNoOp_2);
    Ov005_ResolveEntryStoreWord(manager,20,Ov005_ResultSpriteCallbackNoOp_3);
    Ov005_ResolveEntryStoreWord(manager,21,Ov005_ResultSpriteCallbackNoOp_4);
    Ov005_ResolveEntryStoreWord(manager,25,Ov005_ConfirmExitFromTouch);
    Ov005_ResolveEntryStoreWord(manager,26,Ov005_CancelExitFromTouch);
}
