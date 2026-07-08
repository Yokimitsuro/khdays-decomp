extern void func_0203c650(int owner, int instance);
extern void func_ov107_020c7ca4(int obj);

// Release the pending sub-objects unless their sub-state is active: free this[0x3d0]
// (unless sub-state 5) and this[0x3d8] (unless sub-state 3), clearing each slot;
// then run the shared advance handler.
void func_ov219_020cfff0(int *this)
{
    if (((signed char *)this)[0x1c6] != 5 && *(int *)((int)this + 0x3d0) != 0) {
        func_0203c650(*(int *)((int)this + 0x3c), *(int *)((int)this + 0x3d0));
        *(int *)((int)this + 0x3d0) = 0;
    }
    if (((signed char *)this)[0x1c6] != 3 && *(int *)((int)this + 0x3d8) != 0) {
        func_0203c650(*(int *)((int)this + 0x3c), *(int *)((int)this + 0x3d8));
        *(int *)((int)this + 0x3d8) = 0;
    }
    func_ov107_020c7ca4((int)this);
}
