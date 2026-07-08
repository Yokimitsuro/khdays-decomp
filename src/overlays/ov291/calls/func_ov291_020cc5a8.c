extern int func_ov107_020c9848(void);

// When idle (this[0x1c7]==-1) and the current sub-state is neither 0 nor 6,
// request sub-state 6 and latch the active target's field (query[0x2c], or 0 if
// no target) into this[0x3ac].
void func_ov291_020cc5a8(int *this)
{
    if (*(signed char *)((int)this + 0x1c7) != -1) {
        return;
    }
    if (*(signed char *)((int)this + 0x1c6) != 0 && *(signed char *)((int)this + 0x1c6) != 6) {
        ((signed char *)this)[0x1c7] = 6;
        {
            int target = func_ov107_020c9848();
            *(int *)((int)this + 0x3ac) = (target != 0) ? *(int *)(target + 0x2c) : 0;
        }
    }
}
