typedef unsigned short u16;
typedef struct MenuLimitHeader { u16 inputMask; short limits[2]; char opaque[20]; } MenuLimitHeader;
typedef struct Ov005Context {
    char opaque00[0x4bf0];
    int menuState;
    char opaque4bf4[0x1c];
    unsigned char dialogChoice,unknown4c11;
    MenuLimitHeader menuLimitHeader;
    char opaque4c2c[0x5d568];
    void *exitTaskHandle;
} Ov005Context;
extern Ov005Context *data_ov005_0205b80c;
extern u16 data_0204c190;
extern const char data_ov005_0205b7cc[];
extern u16 func_020362fc(MenuLimitHeader *);
extern void func_ov005_020544f4(void),func_ov005_02054184(void);
extern void func_02033b78(int,int);
extern int func_02030670(void);
extern void *func_02023930(const void *,void *);
void func_ov005_020547e4(void) {
    int action;
    u16 held;
    /* The original leaves r4 unchanged if none of these input bits is set. */
    if(func_020362fc(&data_ov005_0205b80c->menuLimitHeader)&0x20)action=0x20;
    if(func_020362fc(&data_ov005_0205b80c->menuLimitHeader)&0x10)action=0x10;
    held=data_0204c190;
    if(held&1)action=1;
    if(held&2)action=2;
    switch(action) {
    case 0x20:
        if(data_ov005_0205b80c->dialogChoice==0) {
            data_ov005_0205b80c->dialogChoice=1;
            func_ov005_020544f4();
            func_02033b78(0,0);
        }
        break;
    case 0x10:
        if(data_ov005_0205b80c->dialogChoice==1) {
            data_ov005_0205b80c->dialogChoice=0;
            func_ov005_020544f4();
            func_02033b78(0,0);
        }
        break;
    case 1:
        if(data_ov005_0205b80c->dialogChoice==0) {
            data_ov005_0205b80c->menuState=3;
            func_ov005_02054184();
            data_ov005_0205b80c->dialogChoice=0;
            func_02033b78(0,3);
        } else {
            if(func_02030670()) {
                data_ov005_0205b80c->exitTaskHandle=func_02023930(data_ov005_0205b7cc,0);
                data_ov005_0205b80c->menuState=5;
            } else data_ov005_0205b80c->menuState=6;
            func_02033b78(0,1);
        }
        break;
    case 2:
        data_ov005_0205b80c->menuState=3;
        func_ov005_02054184();
        data_ov005_0205b80c->dialogChoice=0;
        func_02033b78(0,3);
        break;
    }
}
