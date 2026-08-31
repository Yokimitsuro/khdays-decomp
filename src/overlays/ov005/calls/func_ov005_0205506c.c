typedef unsigned int u32;
extern u32 func_020235d0(u32,u32);
extern void func_020235e8(u32,u32,u32);
static inline int IsMissionComplete(int mission) {return func_020235d0(mission*3+0x28e4,3)==3;}
void func_ov005_0205506c(void) {
    int mission;
    if(func_020235d0(0x1913,2)!=0)return;
    for(mission=1;mission<=93;mission++) {
        if(!IsMissionComplete(mission))return;
    }
    func_020235e8(0x1913,2,1);
}
