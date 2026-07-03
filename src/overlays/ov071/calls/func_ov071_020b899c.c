extern int func_02030788();
extern int func_02023c40();
extern int func_ov022_020ad114();
extern void *func_ov022_020ad0c0();
extern void VEC_Subtract();
extern int VEC_Mag();
extern void func_01ff8d18();
extern int FX_Atan2();
extern void func_ov022_020a35f4();

void func_ov071_020b899c(void *this)
{
    int buf[3];
    if (!func_02030788()) {
        *(unsigned long long *)((char *)this + 0x464) |= 0x10000;
    }
    if (!func_02030788()) {
        *(unsigned long long *)((char *)this + 0x46c) |= 0x10000;
    }
    *(int *)((char *)this + 0x4b0) = (func_02023c40() == 1) ? 0x240 : 0x180;
    if (func_ov022_020ad114(this) != 0) {
        int t;
        void *r = func_ov022_020ad0c0(this);
        VEC_Subtract(r, (char *)this + 0x48c, buf);
        if (VEC_Mag(buf) != 0) {
            func_01ff8d18(buf, buf);
        }
        t = (unsigned short)FX_Atan2(-buf[0], -buf[2]);
        {
            int *disp = *(int **)((char *)this + 0x20);
            if ((*disp & 0x20) == 0) {
                *(short *)((char *)disp + 0x80) = (short)(t + 0x8000);
                *(unsigned short *)((char *)disp + 4) |= 0x20;
            }
        }
    }
    func_ov022_020a35f4(this, 0x21);
}
