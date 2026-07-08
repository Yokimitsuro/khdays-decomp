struct vec3 { int x, y, z; };

extern void func_0203c9d0(int dst, int *src);
extern int data_02041dc8;

// If the object is in sub-state 1, derive the working vector at node+0x30 from
// node+0x20; otherwise seed it with the default (data_02041dc8). Either way,
// publish node+0x30 into the object's live vector (node[0]+0xf0).
void func_ov172_020d2394(int *this)
{
    int *node = (int *)this[1];
    if (*(signed char *)(node[0] + 0x1c6) == 1) {
        func_0203c9d0(node[0] + 0xa0, (int *)((int)node + 0x20));
    } else {
        *(struct vec3 *)((int)node + 0x30) = *(struct vec3 *)&data_02041dc8;
    }
    *(struct vec3 *)(node[0] + 0xf0) = *(struct vec3 *)((int)node + 0x30);
}
