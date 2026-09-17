/* NitroSystem g3d anm.c: the animation-object init dispatch table NNS_G3dInitAnmObj (02014abc)
 * searches by the animation resource's category bytes -- 'M' 'AM' (material animation),
 * 'M' 'PT' (texture pattern), 'M' 'AT' (texture SRT), 'V' 'AV' (visibility), 'J' 'AC' (joint) --
 * with room for five user-registered entries (the count in use, data_02042490, sits apart).
 */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef void (*NNSG3dAnimInitFunc)(void *pAnmObj, void *pResAnm, const void *pResMdl);

typedef struct NNSG3dAnmObjInitFunc {
    u8 category0;
    u8 dummy;
    u16 category1;
    NNSG3dAnimInitFunc func;
} NNSG3dAnmObjInitFunc;

#define NNS_G3D_ANMOBJ_INITFUNC_MAX 10
#define CATEGORY1(a, b) ((u16)((a) | ((b) << 8)))

extern void func_0201891c(void *, void *, const void *);   /* NNSi_G3dAnmObjInitNsBma */
extern void func_02018f04(void *, void *, const void *);   /* NNSi_G3dAnmObjInitNsBtp */
extern void func_02018dec(void *, void *, const void *);   /* NNSi_G3dAnmObjInitNsBta */
extern void func_02019194(void *, void *, const void *);   /* NNSi_G3dAnmObjInitNsBva */
extern void func_02017224(void *, void *, const void *);   /* NNSi_G3dAnmObjInitNsBca */

/* NNSi_G3dAnmObjInitFuncArray */
NNSG3dAnmObjInitFunc data_020424b4[NNS_G3D_ANMOBJ_INITFUNC_MAX] = {
    { 'M', 0, CATEGORY1('A', 'M'), func_0201891c },
    { 'M', 0, CATEGORY1('P', 'T'), func_02018f04 },
    { 'M', 0, CATEGORY1('A', 'T'), func_02018dec },
    { 'V', 0, CATEGORY1('A', 'V'), func_02019194 },
    { 'J', 0, CATEGORY1('A', 'C'), func_02017224 },
    { 0, 0, 0, 0 },
    { 0, 0, 0, 0 },
    { 0, 0, 0, 0 },
    { 0, 0, 0, 0 },
    { 0, 0, 0, 0 },
};
