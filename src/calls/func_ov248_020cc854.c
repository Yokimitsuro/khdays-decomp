extern int func_0203c650();
extern int func_ov107_020c7ca4();
extern int func_ov107_020cb100();

struct Blob {
    int words[11];
};

struct Obj {
    int field3c_word;       /* placeholder, real layout via offsets below */
};

#define U8(p, o)  (*(unsigned char *)((char *)(p) + (o)))
#define S8(p, o)  (*(signed char *)((char *)(p) + (o)))
#define I32(p, o) (*(int *)((char *)(p) + (o)))
#define PTR(p, o) (*(void **)((char *)(p) + (o)))

void func_ov248_020cc854(void *this) {
    int flag;

    flag = (S8(this, 0x1c6) == 8 || S8(this, 0x1c6) == 9);

    if ((U8(this, 0x1c4) & 0xa) && S8(this, 0x1c7) == -1) {
        if (flag) {
            U8(this, 0x1c7) = 2;
        }
    }

    if (U8(this, 0x1c4) & 0xa) {
        if (S8(this, 0x1c7) == -1 && S8(this, 0x1c6) == 6) {
            U8(this, 0x1c7) = 2;
        }
    }

    if (S8(this, 0x1c6) != 6 && !flag) {
        if (I32(this, 0x4c4)) {
            func_0203c650(I32(this, 0x3c), I32(this, 0x4c4));
            I32(this, 0x4c4) = 0;
        }
        if (I32(this, 0x4f4)) {
            func_0203c650(I32(this, 0x3c), I32(this, 0x4f4));
            I32(this, 0x4f4) = 0;
        }
        if (!flag) {
            if (I32(this, 0x4cc)) {
                func_0203c650(I32(this, 0x3c), I32(this, 0x4cc));
                I32(this, 0x4cc) = 0;
            }
            if (I32(this, 0x4d4)) {
                func_0203c650(I32(this, 0x3c), I32(this, 0x4d4));
                I32(this, 0x4d4) = 0;
            }
        }
    }

    if (S8(this, 0x1c6) != 8 && I32(this, 0x4a4) != 0) {
        func_ov107_020cb100();
        I32(this, 0x4a4) = 0;
    }

    *(struct Blob *)((char *)PTR(this, 0x3b0) + 0x10) =
        *(struct Blob *)((char *)this + 0x3e0);
    *(struct Blob *)((char *)PTR(PTR(this, 0x3ac), 0) + 0x10) =
        *(struct Blob *)((char *)PTR(this, 0x3b0) + 0x10);

    func_ov107_020c7ca4(this);
}
