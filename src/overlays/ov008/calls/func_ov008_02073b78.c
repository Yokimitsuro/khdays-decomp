extern void func_ov008_02071d40(int obj, unsigned int flag);
extern void func_ov008_02071854(int *obj, int dir);
extern unsigned short data_0204c18c;

void func_ov008_02073b78(int *obj) {
    if (obj[0x1a] == 0 && obj[0xc] == 0 && obj[0xd] == 0) {
        if ((data_0204c18c & 0xf0) == 0x20) {
            if (obj[0x13e] != 0) {
                func_ov008_02071d40((int)obj, obj[0x13f] == 0);
            } else {
                func_ov008_02071854(obj, -1);
            }
        }
    }
}
