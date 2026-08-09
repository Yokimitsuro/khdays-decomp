typedef unsigned char u8;
typedef unsigned long u32;
typedef u32 NNSG3dTexKey;
typedef u32 NNSG3dPlttKey;

enum {
    NNS_G3D_SIGNATURE_NSBCA = 0x30414342,
    NNS_G3D_SIGNATURE_NSBVA = 0x30415642,
    NNS_G3D_SIGNATURE_NSBMA = 0x30414d42,
    NNS_G3D_SIGNATURE_NSBMD = 0x30444d42,
    NNS_G3D_SIGNATURE_NSBTA = 0x30415442,
    NNS_G3D_SIGNATURE_NSBTP = 0x30505442,
    NNS_G3D_SIGNATURE_NSBTX = 0x30585442
};

typedef struct NNSG3dResTex NNSG3dResTex;
typedef struct NNSG3dResMdlSet NNSG3dResMdlSet;

extern NNSG3dResMdlSet *func_02017078(void *pResData);
extern NNSG3dResTex *func_02017088(void *pResData);
extern void func_0201559c(NNSG3dResMdlSet *mdlSet);
extern NNSG3dPlttKey func_02014eec(NNSG3dResTex *tex);
extern void func_02014e84(NNSG3dResTex *tex, NNSG3dTexKey *texKey, NNSG3dTexKey *tex4x4Key);

extern int (*data_020423f8)(NNSG3dPlttKey key);
extern int (*data_020423f0)(NNSG3dTexKey key);

void func_020163f4(void *pResData)
{
    u8 *binFile = (u8 *)pResData;

    switch (*(u32 *)&binFile[0]) {
    case NNS_G3D_SIGNATURE_NSBMD:
    {
        NNSG3dResTex *tex;
        NNSG3dResMdlSet *mdlSet = func_02017078(pResData);
        tex = func_02017088(pResData);

        if (tex) {
            func_0201559c(mdlSet);
        }
    }

    case NNS_G3D_SIGNATURE_NSBTX:
    {
        NNSG3dResTex *tex;
        NNSG3dPlttKey plttKey;
        NNSG3dTexKey texKey, tex4x4Key;

        tex = func_02017088(pResData);

        if (tex) {
            plttKey = func_02014eec(tex);
            func_02014e84(tex, &texKey, &tex4x4Key);

            if (plttKey > 0) {
                data_020423f8(plttKey);
            }

            if (tex4x4Key > 0) {
                data_020423f0(tex4x4Key);
            }

            if (texKey > 0) {
                data_020423f0(texKey);
            }
        }
    }
    break;
    case NNS_G3D_SIGNATURE_NSBCA:
    case NNS_G3D_SIGNATURE_NSBVA:
    case NNS_G3D_SIGNATURE_NSBMA:
    case NNS_G3D_SIGNATURE_NSBTP:
    case NNS_G3D_SIGNATURE_NSBTA:
        break;
    default:
        break;
    }
}
