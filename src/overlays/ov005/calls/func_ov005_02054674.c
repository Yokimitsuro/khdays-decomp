typedef unsigned char u8;
typedef unsigned short u16;
typedef struct Tween {
    int mode,duration,from,to;
    long long startTick;
    unsigned int unknownBit0:1,unknownBit1:1,complete:1;
} Tween;
typedef struct Ov005MenuItemHeader {
    u16 itemId,textureResourceId,name[32],description[256];
    int indicatorState;
    u8 quantities[2];
    u16 quantityLimit;
} Ov005MenuItemHeader;
typedef struct Ov005Context {
    char opaque00[0x4bf0];
    int menuState;
    char opaque4bf4[0x7c];
    Tween statusTween;
    u8 statusStep;
    char opaque4c8d[11];
    Ov005MenuItemHeader items[636];
} Ov005Context;
typedef struct Ov005Config { char opaque00[0x68]; u8 rewardMultiplier; } Ov005Config;
extern Ov005Context *data_ov005_0205b80c;
extern Ov005Config data_ov005_0205b85c;
extern void func_ov005_02053994(void);
extern void func_ov005_020538ec(int);
extern void func_02033b78(int,int);
extern void func_ov005_020523f8(int);
static inline int IsTweenDone(Tween *tween) {return tween->complete;}
static inline int AdvanceStatusStep(void) {
    int changed=0;
    if(IsTweenDone(&data_ov005_0205b80c->statusTween)) {
        int next=data_ov005_0205b80c->statusStep+1;
        if(next!=5) {
            data_ov005_0205b80c->statusStep=next;
            func_ov005_020538ec(data_ov005_0205b80c->statusStep);
            changed=1;
        }
    }
    return changed;
}
void func_ov005_02054674(void) {
    Ov005Config *config=&data_ov005_0205b85c;
    u16 i;
    func_ov005_02053994();
    if(AdvanceStatusStep()) {
        switch(data_ov005_0205b80c->statusStep) {
        case 3:
            for(i=0;i<0x277;i++)data_ov005_0205b80c->items[i].quantities[0]*=config->rewardMultiplier;
            func_02033b78(0,17);
            break;
        case 4:break;
        }
    }
    if(IsTweenDone(&data_ov005_0205b80c->statusTween)) data_ov005_0205b80c->menuState=3;
    func_ov005_020523f8(1);
    func_ov005_020523f8(0);
}
