extern void func_ov107_020cb100(int sub);
extern void func_ov107_020c7ca4(int obj);

// If flagged (this[0x1c4]&0xa) and idle (this[0x1c7]==-1) and the current
// sub-state isn't one of the reserved values, force sub-state 5. Then, unless the
// sub-state is 10, release the pending sub-object (this[0x398]) if present.
void func_ov114_020cc3c8(int *this)
{
    if ((*(unsigned char *)((int)this + 0x1c4) & 0xa) != 0 &&
        *(signed char *)((int)this + 0x1c7) == -1) {
        signed char cur = *(signed char *)((int)this + 0x1c6);
        if (cur != 0 && cur != 1 && cur != 3 && cur != 5 && cur != 0xb && cur != 7) {
            ((signed char *)this)[0x1c7] = 5;
        }
    }
    if (*(signed char *)((int)this + 0x1c6) != 10 && *(int *)((int)this + 0x398) != 0) {
        func_ov107_020cb100(*(int *)((int)this + 0x398));
        *(int *)((int)this + 0x398) = 0;
    }
    func_ov107_020c7ca4((int)this);
}
