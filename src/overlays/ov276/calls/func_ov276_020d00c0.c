struct row8 { int a, b; };

extern void func_0202a440(int a, int b, int c, int d);
extern void func_0203c7e8(int instance);
extern void func_ov107_020c9eac(int p);
extern void func_ov107_020c68ec(int obj);

// Full teardown: run the base cleanup (this+0x384, forwarded args), clear the
// active channel (this[0x390]), destroy the primary sub-object (this[0x3a8]) and
// the aux channel (this[0x470]), free the 6 optional slot instances
// (this + i*8 + 0x488), then notify the owner.
void func_ov276_020d00c0(int *this, int p2, int p3, int p4)
{
    int i;
    func_0202a440((int)this + 0x384, p2, p3, p4);
    *(int *)((int)this + 0x390) = 0;
    func_0203c7e8(*(int *)((int)this + 0x3a8));
    func_ov107_020c9eac(*(int *)((int)this + 0x470));
    for (i = 0; i < 6; i++) {
        int slot = ((struct row8 *)this)[i + 0x91].a;
        if (slot != 0) {
            func_0203c7e8(slot);
        }
    }
    func_ov107_020c68ec((int)this);
}
