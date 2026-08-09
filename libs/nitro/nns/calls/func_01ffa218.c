typedef unsigned long u32;
typedef signed long fx32;
typedef int BOOL;

typedef struct VecFx32 {
    fx32 x;
    fx32 y;
    fx32 z;
} VecFx32;

typedef struct MtxFx43 {
    fx32 _00, _01, _02;
    fx32 _10, _11, _12;
    fx32 _20, _21, _22;
    fx32 _30, _31, _32;
} MtxFx43;

typedef struct NNSG3dJntAnmResult {
    u32 flag;
    VecFx32 scale;
    VecFx32 scaleEx0;
    VecFx32 scaleEx1;
    MtxFx43 mtx;
} NNSG3dJntAnmResult;

enum {
    JNT_SCALE_ONE = 0x01,
    JNT_ROT_ZERO = 0x02,
    JNT_TRANS_ZERO = 0x04,
    JNT_SCALEEX0_ONE = 0x08,
    JNT_MAYA_SSC = 0x20
};

extern void func_01ff9f00(u32 op, const void *args, u32 numWords);

void func_01ffa218(const NNSG3dJntAnmResult *result)
{
    BOOL sendTranslation = 0;
    u32 flag = result->flag;

    if (!(flag & JNT_TRANS_ZERO)) {
        sendTranslation = 1;
    }

    if ((flag & JNT_MAYA_SSC) && !(flag & JNT_SCALEEX0_ONE)) {
        if (sendTranslation) {
            func_01ff9f00(0x1c, &result->mtx._30, 3);
            sendTranslation = 0;
        }
        func_01ff9f00(0x1b, &result->scaleEx0, 3);
    }

    if (!(result->flag & JNT_ROT_ZERO)) {
        if (sendTranslation) {
            func_01ff9f00(0x19, &result->mtx, 12);
        } else {
            func_01ff9f00(0x1a, &result->mtx, 9);
        }
    } else if (sendTranslation) {
        func_01ff9f00(0x1c, &result->mtx._30, 3);
    }

    if (result->flag & JNT_SCALE_ONE) {
        return;
    }
    func_01ff9f00(0x1b, &result->scale, 3);
}
