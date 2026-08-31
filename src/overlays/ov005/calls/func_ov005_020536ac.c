typedef unsigned short u16;
typedef struct MenuLimitHeader { u16 inputMask; short limits[2]; char opaque[20]; } MenuLimitHeader;
typedef struct Ov005Context { char opaque00[0x4c12]; MenuLimitHeader menuLimitHeader; } Ov005Context;
extern Ov005Context *data_ov005_0205b80c;
extern u16 func_020362fc(MenuLimitHeader *);
extern int func_ov005_020533d8(int);
extern void func_02033b78(int,int);
extern void func_ov005_020535c8(void);
int func_ov005_020536ac(void) {
    int direction;
    int changed;
    /* The target leaves r4 unchanged when none of these direction bits is set. */
    if(func_020362fc(&data_ov005_0205b80c->menuLimitHeader)&0x40)direction=0x40;
    if(func_020362fc(&data_ov005_0205b80c->menuLimitHeader)&0x80)direction=0x80;
    if(func_020362fc(&data_ov005_0205b80c->menuLimitHeader)&0x20)direction=0x20;
    if(func_020362fc(&data_ov005_0205b80c->menuLimitHeader)&0x10)direction=0x10;
    changed=func_ov005_020533d8(direction);
    if(changed)func_02033b78(0,0);
    func_ov005_020535c8();
    return changed;
}
