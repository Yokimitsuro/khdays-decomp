typedef struct Ov005Context {
    char opaque00[0x4bf0];
    int menuState;
    char opaque4bf4[0x1c];
    unsigned char dialogChoice;
} Ov005Context;
extern Ov005Context *data_ov005_0205b80c;
extern void func_ov005_020544f4(void);
extern void func_02033b78(unsigned int,unsigned int);
void func_ov005_02054ec8(void) {
    if(data_ov005_0205b80c->menuState>=6)return;
    data_ov005_0205b80c->dialogChoice=1;
    func_ov005_020544f4();
    data_ov005_0205b80c->menuState=6;
    func_02033b78(0,1);
}
