/* Assign background priorities on the main and sub display engines. */
typedef unsigned short u16;
#define BG_CONTROL(address) (*(volatile u16 *)(address))
void func_ov005_020514ec(void) {
    BG_CONTROL(0x0400100a)=(BG_CONTROL(0x0400100a)&~3)|3;
    BG_CONTROL(0x0400100e)=(BG_CONTROL(0x0400100e)&~3)|2;
    BG_CONTROL(0x0400100c)=BG_CONTROL(0x0400100c)&~3;
    BG_CONTROL(0x0400000a)=(BG_CONTROL(0x0400000a)&~3)|3;
    BG_CONTROL(0x0400000e)=(BG_CONTROL(0x0400000e)&~3)|2;
    BG_CONTROL(0x0400000c)=BG_CONTROL(0x0400000c)&~3;
}
