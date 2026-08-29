typedef unsigned char u8;
typedef unsigned short u16;

typedef struct Ov002ObjInfo {
    char pad000[0x4c];
    u16 nKind;                  /* 0x4c */
} Ov002ObjInfo;

typedef struct Ov002Obj {
    char pad000[8];
    Ov002ObjInfo *pInfo;        /* 0x08 */
    char pad00c[0xb];
    u8 bArmed;                  /* 0x17 */
} Ov002Obj;

extern int func_ov002_0206b7d4(int nSlot);
extern int func_ov002_0207c490(Ov002Obj *pObj);

/* Say whether an object is free to act right now.
 *
 * An object that is not armed always is.  Otherwise it depends on the kind:
 * most kinds are free, the handful that follow a roster slot are only free
 * while that slot is not busy, and one kind answers for itself.
 */
int func_ov002_02076c24(Ov002Obj *pObj, int nSlot)
{
    if (pObj->bArmed == 0) {
        return 1;
    }

    switch (pObj->pInfo->nKind) {
    case 8:
    case 14:
    case 16:
    case 17:
    case 0x1d:
    case 0x1e:
        return func_ov002_0206b7d4(nSlot) == 0;

    case 0x21:
        return func_ov002_0207c490(pObj);
    }

    return 1;
}
