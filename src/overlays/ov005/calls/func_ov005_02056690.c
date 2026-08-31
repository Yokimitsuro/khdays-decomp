/* Ov005_InitializeMissionResultSprites: load the result-screen sprite sets,
 * reset their entries, select reward indicators, and initialize progress bars.
 * The progress numerator at config+0x20 is signed; mode 255 alone maps a zero
 * percentage to 100. Pixel widths use 183*percent/100 narrowed to signed 16 bits.
 * ARM: 1220 bytes, 46 relocations, byte-exact.
 */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef struct Ov005SpriteManager {char data[0x4a80];} Ov005SpriteManager;
typedef struct Ov005ResultContext {u32 resultArchive,localizedResultArchive;char unknown08[76];Ov005SpriteManager spriteManager;} Ov005ResultContext;
typedef struct Ov005Config {u16 sceneId,missionIndex;char unknown04[8];u16 rewardMode;char unknown0e[18];int missionProgressValue;char unknown24[12];int missionTargetValue;} Ov005Config;
typedef struct SpriteDescriptor {u32 resourceId;int type,mode,variant;} SpriteDescriptor;
extern Ov005ResultContext *data_ov005_0205b810;
extern Ov005Config data_ov005_0205b85c;
extern void *G2_GetBG0ScrPtr(void),*G2_GetBG3ScrPtr(void);
extern void MIi_CpuClearFast(u32,void *,u32);
extern void func_ov005_0204dc64(Ov005SpriteManager *,void *);
extern void func_ov005_0204e098(Ov005SpriteManager *,SpriteDescriptor *);
extern void func_ov005_0204e0b0(Ov005SpriteManager *,u32);
extern void func_ov005_0204dff0(Ov005SpriteManager *,u32,int);
extern void *func_ov005_0204e0d0(Ov005SpriteManager *,int);
extern void func_ov005_0204e3bc(Ov005SpriteManager *,void *,int);
extern void func_ov005_0204e300(Ov005SpriteManager *,void *);
extern void func_ov005_0204e29c(Ov005SpriteManager *,void *,int);
extern void func_ov005_02055480(int,int,int,int);
extern void func_ov005_02055528(int,int);
extern void func_ov005_02055594(int,int,int);
extern int func_02023588(u32);
extern int func_02020400(int,int);
static inline void ShowEntry(int id) {
    func_ov005_0204e29c(&data_ov005_0205b810->spriteManager,
        func_ov005_0204e0d0(&data_ov005_0205b810->spriteManager,id),1);
}
void func_ov005_02056690(void) {
    SpriteDescriptor descriptor;
    Ov005ResultContext *context=data_ov005_0205b810;
    Ov005Config *config=&data_ov005_0205b85c;
    u8 index;
    int number;
    int icon;
    MIi_CpuClearFast(0,G2_GetBG0ScrPtr(),0x800);
    MIi_CpuClearFast(0,G2_GetBG3ScrPtr(),0x800);
    func_ov005_0204dc64(&context->spriteManager,0);
    descriptor.resourceId=(((data_ov005_0205b810->resultArchive+0x8000)&0xfffffc)<<7)|0x80000002;
    descriptor.type=2;descriptor.mode=0;descriptor.variant=0;
    func_ov005_0204e098(&context->spriteManager,&descriptor);
    func_ov005_0204e0b0(&context->spriteManager,(((data_ov005_0205b810->localizedResultArchive+0x8000)&0xfffffc)<<7)|0x80000001);
    func_ov005_0204dff0(&context->spriteManager,(((data_ov005_0205b810->resultArchive+0x8000)&0xfffffc)<<7)|0x80000005,111);
    for(index=1;index<=111;index++) {
        void *entry=func_ov005_0204e0d0(&context->spriteManager,index);
        func_ov005_0204e3bc(&context->spriteManager,entry,0);
        func_ov005_0204e300(&context->spriteManager,entry);
    }
    number=(int)config->missionIndex%100;
    if(number==94)number=0;
    func_ov005_02055480(number,3,2,2);
    if(config->missionIndex>=100)ShowEntry(5);
    func_ov005_02055528(33,0);func_ov005_02055528(39,0);
    func_ov005_02055528(48,0);func_ov005_02055528(54,0);
    func_ov005_02055528(63,0);func_ov005_02055528(69,0);
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
    func_ov005_02055528(icon,0);
    if(func_02023588(0x2087)) {
        func_ov005_02055528(107,0);
        switch(config->rewardMode) {
        case 255:func_ov005_02055528(8,0);break;
        case 8:func_ov005_02055528(8,2);break;
        default:func_ov005_02055528(8,1);break;
        }
    } else if(config->rewardMode==255) {
        int percent=func_02020400(config->missionProgressValue*100,config->missionTargetValue);
        if(percent==0)percent=100;
        func_ov005_02055528(8,0);
        ShowEntry(10);
        func_ov005_02055594(10,(short)(183*percent/100),0);
    } else {
        if(config->rewardMode==8)func_ov005_02055528(8,2);
        else func_ov005_02055528(8,1);
        switch(config->rewardMode) {
        case 2: {
            int percent=func_02020400(config->missionProgressValue*100,config->missionTargetValue);
            ShowEntry(10);
            func_ov005_02055594(10,(short)(183*percent/100),0);
            break;
        }
        case 0: {
            int id;
            func_ov005_02055528(11,0);
            for(id=22;id<=29;id++)if(id!=24 && id!=27)func_ov005_02055528(id,0);
            ShowEntry(20);ShowEntry(21);
            break;
        }
        default:func_ov005_02055528(22,0);break;
        }
    }
}
