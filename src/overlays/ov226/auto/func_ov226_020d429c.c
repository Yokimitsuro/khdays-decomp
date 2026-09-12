struct Vec3 { int x, y, z; };

extern struct Vec3 data_02041dc8;

void func_ov226_020d429c(void *this_, int val, int unused2, int unused3, int unused4, struct Vec3 vec) {
    void *owner = *(void **)this_;
    *((signed char *)owner + 0x1c7) = 1;
    *(int *)((char *)this_ + 0x44) = val;
    *(struct Vec3 *)((char *)this_ + 0x24) = vec;
    *(struct Vec3 *)((char *)this_ + 0x18) = data_02041dc8;
}
