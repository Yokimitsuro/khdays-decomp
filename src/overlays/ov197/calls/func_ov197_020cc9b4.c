struct vec3 { int x, y, z; };

extern int data_02041dc8; /* const initial pose vector */
extern void func_0203b9fc(int subitem, int a, int b, int c);

// Seed the node pose: copy the default vector into both this[+0x3a4] and
// this[+0x3b0], raise the two ready flags, then push sub-state via SetSubitemState.
void func_ov197_020cc9b4(int *this, int arg1)
{
    struct vec3 tmp = *(struct vec3 *)&data_02041dc8;
    *(struct vec3 *)((int)this + 0x3a4) = tmp;
    *(struct vec3 *)((int)this + 0x3b0) = tmp;
    *(int *)((int)this + 0x3e4) = 1;
    *(int *)((int)this + 0x3e8) = 1;
    func_0203b9fc(*(int *)((int)this + 0x388), 0, (short)arg1, 0);
}
