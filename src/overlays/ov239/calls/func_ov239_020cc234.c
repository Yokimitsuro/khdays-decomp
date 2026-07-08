struct row8 { int a, b; };

extern void func_0203c7e8(int instance);
extern void func_ov107_020c9eac(int p);
extern void func_ov107_020c68ec(int obj);

// Teardown: destroy the primary sub-object (this[0x388]), release the channel
// (this[0x398]), free the 4 optional slot instances (this + i*8 + 0x39c), then
// notify the owner.
void func_ov239_020cc234(int *this)
{
    int i;
    func_0203c7e8(*(int *)((int)this + 0x388));
    func_ov107_020c9eac(*(int *)((int)this + 0x398));
    for (i = 0; i < 4; i++) {
        int slot = ((struct row8 *)this)[i + 0x73].b;
        if (slot != 0) {
            func_0203c7e8(slot);
        }
    }
    func_ov107_020c68ec((int)this);
}
