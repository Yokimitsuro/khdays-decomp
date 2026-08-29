typedef unsigned short u16;

typedef struct Ov002Vec3 {
    int x, y, z;
} Ov002Vec3;

/* What a named place resolves to: its point and the heading that goes with
   it. */
typedef struct Ov002PlaceResult {
    char pad000[8];
    Ov002Vec3 place;
    int nExtra;
} Ov002PlaceResult;

extern int func_02021980(void *pCtx, int nArgs);
extern int func_02021994(void *pCtx, int nArgs);
extern char *func_02021948(void *pCtx, int nArgs);
extern int func_02020400(int a, int b);
extern Ov002PlaceResult *func_0202c3c4(u16 nSlot, const char *pKey);
extern void func_ov002_0206b6f8(int nIndex, void *pPlace, int nAngle);

/* Script VM command: put one roster slot at a place.
 *
 * Operand slots are eight bytes each and the leading halfword is the kind tag.
 * When the second operand is left out the command carries the place itself --
 * three fixed point coordinates and a heading in degrees, turned into a
 * rotation through the same 0x168 divisor the other place commands use.  When
 * it is present it names a place instead, and both the point and the heading
 * come from whatever that name resolves to.
 *
 * Always returns 1.
 */
int func_ov002_02074ac4(void *pCtx, int nArgs)
{
    Ov002Vec3 vPlace;
    int nIndex;
    int nAngle;
    Ov002PlaceResult *pFound;

    nIndex = func_02021980(pCtx, nArgs);
    if (*(short *)((char *)nArgs + 8) == 0) {
        vPlace.x = func_02021994(pCtx, nArgs + 0x10);
        vPlace.y = func_02021994(pCtx, nArgs + 0x18);
        vPlace.z = func_02021994(pCtx, nArgs + 0x20);
        nArgs += 0x28;
        nAngle = (u16)func_02020400(func_02021980(pCtx, nArgs) << 0x10,
                                    0x168);
    } else {
        nArgs += 8;
        pFound = func_0202c3c4(0, func_02021948(pCtx, nArgs));
        vPlace = pFound->place;
        nAngle = pFound->nExtra;
    }

    func_ov002_0206b6f8(nIndex, &vPlace, nAngle);
    return 1;
}
