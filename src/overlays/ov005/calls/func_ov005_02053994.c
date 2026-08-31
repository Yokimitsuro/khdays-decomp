typedef unsigned char u8;
typedef struct Tween {int mode,duration,from,to;long long startTick;unsigned int flags;} Tween;
typedef struct Ov005Context {char header[0x54];char embeddedManager[0x4a80];char opaque4ad4[0x19c];Tween statusTween;} Ov005Context;
typedef struct Ov005Config {char opaque00[0x68];u8 rewardMultiplier;} Ov005Config;
extern Ov005Context *data_ov005_0205b80c;
extern Ov005Config data_ov005_0205b85c;
extern void func_0203602c(Tween *,int *);
extern void func_ov005_020522fc(int,short,short);
extern int func_ov005_0204e0d0(void *,int);
extern unsigned int func_ov005_0204e14c(void *,int);
extern void func_ov005_0204e3bc(void *,int,unsigned int);
extern void func_ov005_0204e29c(void *,int,int);
void func_ov005_02053994(void) {
    int position;
    Ov005Config *config=&data_ov005_0205b85c;
    int slot;
    func_0203602c(&data_ov005_0205b80c->statusTween,&position);
    func_ov005_020522fc(47,0,position>>12);
    slot=func_ov005_0204e0d0(data_ov005_0205b80c->embeddedManager,47);
    if(func_ov005_0204e14c(data_ov005_0205b80c->embeddedManager,slot))return;
    slot=func_ov005_0204e0d0(data_ov005_0205b80c->embeddedManager,47);
    func_ov005_0204e3bc(data_ov005_0205b80c->embeddedManager,slot,(u8)(config->rewardMultiplier-2));
    slot=func_ov005_0204e0d0(data_ov005_0205b80c->embeddedManager,47);
    func_ov005_0204e29c(data_ov005_0205b80c->embeddedManager,slot,1);
}
