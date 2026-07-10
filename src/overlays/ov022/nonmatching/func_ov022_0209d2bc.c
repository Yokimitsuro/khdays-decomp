extern void func_ov022_020882bc(int e);
extern void func_ov002_0205766c(void);
extern int func_0202a818(unsigned short *p, int v);
extern int data_0204c240;

struct Obj0209d2bc {
    char pad464[0x464];
    unsigned long long flags464;
};

void func_ov022_0209d2bc(int obj, int param2) {
    if ((*(unsigned char *)&data_0204c240 & 4) == 0) return;
    func_ov022_020882bc(*(unsigned char *)(obj + 9));
    func_ov002_0205766c();
    if ((((struct Obj0209d2bc *)obj)->flags464 & 0x8000000000000LL) != 0) {
        *(unsigned short *)(obj + 0x8dc) = 0x6000;
        func_0202a818((unsigned short *)(obj + 0x7d4), param2);
        *(unsigned char *)(obj + 0x694) |= 0x10;
        return;
    }
    if (((short *)(obj + 0x800))[0x6e] > 0) {
        ((short *)(obj + 0x800))[0x6e] -= (short)param2;
        if (((short *)(obj + 0x800))[0x6e] <= 0) ((short *)(obj + 0x800))[0x6e] = 0;
    }
    if ((((unsigned int)*(unsigned char *)(obj + 0x694)) << 0x1b) >> 0x1f) {
        if (func_0202a818((unsigned short *)(obj + 0x7d4), param2) != 0) {
            if (*(short *)(obj + 0x8dc) == 0)
                *(unsigned char *)(obj + 0x694) &= ~0x10;
        }
    }
}
