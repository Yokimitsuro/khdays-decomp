typedef unsigned char u8;
typedef unsigned short u16;
/* Codegen view of the existing Ov002DayClock global; +2 is set for the next scene. */
typedef struct SceneTransition {u8 flags,submode;u16 transitionValue,parameter;} SceneTransition;
typedef struct ModeSource {char opaque[8];int mode;} ModeSource;
extern u16 data_0204c190;
extern SceneTransition data_0204c240;
extern u8 data_0204c300[];
extern ModeSource *data_ov005_0205b808;
extern int func_ov005_02057a90(void);
extern int func_ov005_02057a6c(void);
extern int func_ov005_02057ab4(void);
extern int func_ov005_02054fb8(void);
extern int func_ov005_02054fdc(void);
extern void func_ov005_02054f9c(int);
extern void func_ov005_02057a34(void);
extern void func_ov005_02057a18(void);
extern void func_ov005_02057a50(void);
extern void func_ov005_02054f7c(void);
extern void func_ov005_02051328(void);
extern void func_020352cc(void);
extern void func_ov005_02050cb0(int,int);
extern void func_02020a78(int,int);
extern void func_020235bc(int);
extern void func_020235a8(int);
extern unsigned int func_020235d0(unsigned int,unsigned int);
int func_ov005_02051724(void) {
    int result=0;
    if(func_ov005_02057a90())func_ov005_02054f9c(0);
    else func_ov005_02054f9c(1);
    if(func_ov005_02057a90() && ((data_0204c190&1)||(data_0204c190&2)))func_ov005_02057a34();
    if(func_ov005_02057a90() && (data_0204c190&8))func_ov005_02057a18();
    if(func_ov005_02057a6c() && func_ov005_02054fb8()) {
        func_ov005_02057a50();
        func_ov005_02054f7c();
    }
    if(func_ov005_02057ab4() && func_ov005_02054fdc()) {
        func_ov005_02051328();
        func_020352cc();
        func_ov005_02050cb0(0,0);
        if(data_0204c240.flags&4)func_02020a78(0x13,0);
        else if((data_0204c240.flags&2)||(data_0204c240.flags&1)||(data_0204c300[0x4c]&1)) {
            func_020235bc(0x18ae);
            if(data_0204c240.flags&2)func_020235a8(0x18c9);
            else if(data_0204c240.flags&1)func_020235a8(0x18bd);
            data_0204c240.transitionValue=func_020235d0(0,9)==0x165?10001:10000;
            data_0204c240.parameter=0;
            data_0204c240.submode=0;
            data_0204c240.flags=0;
            func_02020a78(2,0);
        } else {
            int mode=data_ov005_0205b808->mode;
            if(mode!=999) {
                int day=func_020235d0(0,9);
                if(day>=7 && day<=13)func_02020a78(10,mode);
                else func_02020a78(5,mode);
            } else func_02020a78(13,0);
        }
        result=-2;
    }
    return result;
}
