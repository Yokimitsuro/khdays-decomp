struct Obj_020a7018;
extern _Bool func_ov022_020ad114(struct Obj_020a7018 *obj);
struct Vec3_020a7018;
extern struct Vec3_020a7018 *func_ov022_020ad0c0(struct Obj_020a7018 *obj);
extern int func_ov022_020a35f4(struct Obj_020a7018 *obj, int mode);

struct Vec3_020a7018 {
    int a;
    int b;
    int c;
};

struct TailState_020a7018 {
    signed char pad0[2];
    signed char state;
};

struct Obj_020a7018 {
    unsigned char pad0000[0x490];
    int target490;
    unsigned char pad0494[0x320];
    unsigned char state7b4;
    unsigned char pad07b5[0x23fb];
    struct TailState_020a7018 tail2bb0;
};

int func_ov022_020a7018(struct Obj_020a7018 *obj) {
    int r = 0;
    int ok = 0;
    {
        struct TailState_020a7018 *tail = &obj->tail2bb0;
        if (obj->state7b4 != 3) {
            return 0;
        }
        if (func_ov022_020ad114(obj)) {
            struct Vec3_020a7018 buf =
                *func_ov022_020ad0c0(obj);
            int target = obj->target490;
            int v = buf.b;
            if (v >= target) {
                if (v < target + 0xc00) {
                    ok = 1;
                }
            } else if (v > target - 0xc00) {
                ok = 1;
            }
        }
        if (tail->state == 2) {
            ok = 1;
        }
    }
    if (ok) {
        r = func_ov022_020a35f4(obj, 0xf);
        obj->state7b4 = 0;
    }
    return r;
}
