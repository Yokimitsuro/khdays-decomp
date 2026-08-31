typedef unsigned int u32;
typedef void (*EntryCallback)(void);
typedef struct Ov005SpriteManager {char data[0x4a80];} Ov005SpriteManager;
typedef struct Ov005Context {u32 resultArchive,localizedResultArchive;char pad8[76];Ov005SpriteManager embeddedManager;Ov005SpriteManager *spriteManager;char pad4ad8[0x5d668];int indicatorSlots[2][7];} Ov005Context;
typedef struct SpriteDescriptor {u32 resourceId;int type,mode,variant;} SpriteDescriptor;
typedef struct EntryIds {int ids[4];} EntryIds;
typedef struct UiLayoutPos {int x,y;} UiLayoutPos;
extern Ov005Context *data_ov005_0205b80c;
extern EntryIds data_ov005_0205b358;
extern void func_ov005_0204dc64(Ov005SpriteManager *,void *);
extern void func_ov005_0204e098(Ov005SpriteManager *,SpriteDescriptor *);
extern void func_ov005_0204e0b0(Ov005SpriteManager *,u32);
extern void func_ov005_0204dff0(Ov005SpriteManager *,u32,int);
extern void func_ov005_0204e478(Ov005SpriteManager *,int);
extern void *func_ov005_0204e0d0(Ov005SpriteManager *,int);
extern void func_ov005_0204e3bc(Ov005SpriteManager *,void *,int);
extern void func_ov005_0204e300(Ov005SpriteManager *,void *);
extern void func_ov005_0204e33c(Ov005SpriteManager *,void *);
extern int WM_EndKeySharing_0x02032444(Ov005SpriteManager *,int,int);
extern void func_020325b8(Ov005SpriteManager *,int,int);
extern void func_0203257c(Ov005SpriteManager *,int,UiLayoutPos *);
extern void func_020326cc(Ov005SpriteManager *,int);
extern void func_02032710(Ov005SpriteManager *,int,int);
extern void func_ov005_0204e0c0(Ov005SpriteManager *,int,EntryCallback);
extern void func_ov005_02054dcc(void),func_ov005_02054eb8(void),func_ov005_02054ebc(void),func_ov005_02054ec0(void),func_ov005_02054ec4(void),func_ov005_02054ec8(void),func_ov005_02054f18(void);
static inline void SetPixelPosition(UiLayoutPos *position,int x,int y) {position->y=y<<12;position->x=x<<12;}
void func_ov005_02052ca4(void) {
    SpriteDescriptor descriptor;
    EntryIds entryIds;
    UiLayoutPos position;
    Ov005SpriteManager *manager=&data_ov005_0205b80c->embeddedManager;
    int x;
    int id,index,y;
    u32 i;
    func_ov005_0204dc64(manager,0);
    descriptor.resourceId=(((data_ov005_0205b80c->resultArchive+0x8000)&0xfffffc)<<7)|0x80000001;
    descriptor.type=1;descriptor.mode=0;descriptor.variant=0;
    func_ov005_0204e098(manager,&descriptor);
    func_ov005_0204e0b0(manager,(((data_ov005_0205b80c->localizedResultArchive+0x8000)&0xfffffc)<<7)|0x80000000);
    func_ov005_0204dff0(manager,(((data_ov005_0205b80c->resultArchive+0x8000)&0xfffffc)<<7)|0x80000004,49);
    func_ov005_0204e478(manager,0);
    data_ov005_0205b80c->spriteManager=manager;
    for(id=1;id<=49;id++) {
        func_ov005_0204e3bc(&data_ov005_0205b80c->embeddedManager,func_ov005_0204e0d0(&data_ov005_0205b80c->embeddedManager,id),0);
        func_ov005_0204e300(&data_ov005_0205b80c->embeddedManager,func_ov005_0204e0d0(&data_ov005_0205b80c->embeddedManager,id));
    }
    entryIds=data_ov005_0205b358;
    for(i=0;i<4;i++)func_ov005_0204e33c(&data_ov005_0205b80c->embeddedManager,func_ov005_0204e0d0(&data_ov005_0205b80c->embeddedManager,entryIds.ids[i]));
    for(id=0;id<2;id++) {
        x=17+id*112;
        for(index=0;index<7;index++) {
            y=49+index*16;
            data_ov005_0205b80c->indicatorSlots[id][index]=WM_EndKeySharing_0x02032444(data_ov005_0205b80c->spriteManager,0,1);
            SetPixelPosition(&position,x,y);
            func_020325b8(data_ov005_0205b80c->spriteManager,data_ov005_0205b80c->indicatorSlots[id][index],120);
            func_0203257c(data_ov005_0205b80c->spriteManager,data_ov005_0205b80c->indicatorSlots[id][index],&position);
            func_020326cc(data_ov005_0205b80c->spriteManager,data_ov005_0205b80c->indicatorSlots[id][index]);
            func_02032710(data_ov005_0205b80c->spriteManager,data_ov005_0205b80c->indicatorSlots[id][index],0);
        }
    }
    func_ov005_0204e0c0(manager,4,func_ov005_02054dcc);
    func_ov005_0204e0c0(manager,18,func_ov005_02054eb8);
    func_ov005_0204e0c0(manager,19,func_ov005_02054ebc);
    func_ov005_0204e0c0(manager,20,func_ov005_02054ec0);
    func_ov005_0204e0c0(manager,21,func_ov005_02054ec4);
    func_ov005_0204e0c0(manager,25,func_ov005_02054ec8);
    func_ov005_0204e0c0(manager,26,func_ov005_02054f18);
}
