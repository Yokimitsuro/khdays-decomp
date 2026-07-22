typedef struct Widget {
    char unk_00[0x10];
    unsigned short wFlags;
} Widget;

void func_ov002_02072b24(int arg0, Widget *widget, int hide) {
    if (hide) {
        widget->wFlags &= ~0x4000;
    } else {
        widget->wFlags |= 0x4000;
    }
}
