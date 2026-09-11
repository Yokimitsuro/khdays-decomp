extern void func_0203c650(int owner, int instance);
extern void func_ov107_020c7ca4(int obj);

// Release the pending sub-objects at this+0x3b0 (+0x1c and +0xc) unless their
// sub-state (this+0x1c6) matches the held value; then run the shared advance handler.
void func_ov284_020cc53c(int *this)
{
    if (((signed char *)this)[0x1c6] != 5 && *(int *)(*(int *)((int)this + 0x3b0) + 0x1c) != 0) {
        func_0203c650(*(int *)((int)this + 0x3c), *(int *)(*(int *)((int)this + 0x3b0) + 0x1c));
        *(int *)(*(int *)((int)this + 0x3b0) + 0x1c) = 0;
    }
    if (((signed char *)this)[0x1c6] != 6 && *(int *)(*(int *)((int)this + 0x3b0) + 0xc) != 0) {
        func_0203c650(*(int *)((int)this + 0x3c), *(int *)(*(int *)((int)this + 0x3b0) + 0xc));
        *(int *)(*(int *)((int)this + 0x3b0) + 0xc) = 0;
    }
    func_ov107_020c7ca4((int)this);
}
