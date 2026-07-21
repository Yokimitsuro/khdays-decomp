extern void func_ov025_020a7264(int obj, unsigned int flag);
extern void func_ov025_020a6d4c(int *obj, int dir);
extern unsigned short data_0204c18c;

void func_ov025_020a91a4(int *obj) {
    if (obj[0x1a] == 0 && obj[0xc] == 0 && obj[0xd] == 0) {
        if ((data_0204c18c & 0xf0) == 0x10) {
            if (obj[0x13e] != 0) {
                func_ov025_020a7264((int)obj, obj[0x13f] == 0);
            } else {
                func_ov025_020a6d4c(obj, 1);
            }
        }
    }
}
