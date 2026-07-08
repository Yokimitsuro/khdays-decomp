extern int func_ov302_020cc410(int this_, int list, int arg);
extern int func_ov302_020cc424(int this_, int list, int arg);
extern int func_ov302_020cc4d4(int this_, int list, int arg);
extern int func_ov302_020cc4c0(int this_, int list, int arg);
extern int func_ov302_020cc4e8(int this_, int list, int arg);
extern int func_ov302_020cc4fc(int this_, int list, int arg);
extern int func_ov302_020cc510(int this_, int list, int arg);
extern int func_ov302_020cc524(int this_, int list, int arg);

void func_ov302_020cc598(int this_, unsigned int mode, int arg) {
    switch (mode) {
        case 0:
            *(unsigned short *)(this_ + 0x10) = func_ov302_020cc410(this_, *(int *)(this_ + 0x14), arg);
            break;
        case 1:
            *(unsigned short *)(this_ + 0x10) = func_ov302_020cc424(this_, *(int *)(this_ + 0x14), arg);
            break;
        case 2:
            *(unsigned short *)(this_ + 0x10) = func_ov302_020cc4d4(this_, *(int *)(this_ + 0x14), arg);
            break;
        case 3:
            *(unsigned short *)(this_ + 0x10) = func_ov302_020cc4c0(this_, *(int *)(this_ + 0x14), arg);
            break;
        case 4:
            *(unsigned short *)(this_ + 0x10) = func_ov302_020cc4e8(this_, *(int *)(this_ + 0x14), arg);
            break;
        case 5:
            *(unsigned short *)(this_ + 0x10) = func_ov302_020cc4fc(this_, *(int *)(this_ + 0x14), arg);
            break;
        case 6:
            *(unsigned short *)(this_ + 0x10) = func_ov302_020cc510(this_, *(int *)(this_ + 0x14), arg);
            break;
        case 7:
            *(unsigned short *)(this_ + 0x10) = func_ov302_020cc524(this_, *(int *)(this_ + 0x14), arg);
            break;
    }
}
