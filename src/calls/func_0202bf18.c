/* func_0202bf18 -- start or stop an object's interpolated transition.
 *
 * Enabling starts the transition from pObj+0xb4 into pObj+0x168 via func_0202df00 and sets
 * bit4 of the object's flag byte at pObj+8; disabling just clears that bit and does nothing
 * else. A caller passing a duration of 0 means "use the default": the object's own base
 * duration at pObj+0x154 scaled by 1.5 in 20.12 fixed point. That scale is written as the
 * project's usual widened form, `(s64)v * 0x1800 + 0x800 >> 12`, which is what produces the
 * umull/asr/mla/adc sequence -- the same idiom already matched in
 * src/overlays/ov022/calls/func_ov022_02086688.c. */
typedef unsigned char u8;
typedef signed int s32;
typedef signed long long s64;
typedef unsigned int u32;

extern int func_0202df00(u32 *pDst, u32 *pSrc, u32 nDuration, int nMode);

void func_0202bf18(u8 *pObj, int bEnable, int nDuration)
{
    if (bEnable != 0) {
        if (nDuration == 0) {
            nDuration = (s32)(((s64)*(s32 *)(pObj + 0x154) * 0x1800 + 0x800) >> 12);
        }
        func_0202df00((u32 *)(pObj + 0x168), (u32 *)(pObj + 0xb4), nDuration, 0);
        pObj[8] |= 0x10;
        return;
    }
    pObj[8] &= ~0x10;
}
