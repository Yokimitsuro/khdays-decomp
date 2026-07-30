/*
 * Res_LoadSpriteSet - load a 2D sprite resource set (screen / character / palette)
 * from an archive into a 3-pointer SpriteResSet.
 *
 * Opens the archive (func_02025464), then for each of the three slots looks up an
 * archive member by kind and index -- kind 6 (NRCS screen) at scrIdx, kind 1
 * (NCGR character) at charIdx, kind 0 (PLTT palette) at pltIdx -- and decodes it
 * into the matching output pointer. A negative index, a missing member, or a
 * decoder that returns 0 leaves that pointer NULL.
 */

extern void func_02025464(int *arc, int a, int b, int c);
extern int func_020255d4(int arc, int type, int idx);
extern int func_02011a6c(int member, void *out);
extern int func_020119d4(int member, void *out);
extern int func_02011a20(int member, void *out);

void func_02024c94(unsigned int *param_1, int *param_2, int param_3, int param_4, int param_5)
{
    int m;

    func_02025464(param_2, 0, param_3, param_4);
    param_1[0] = 0;
    if (param_3 >= 0 && (m = func_020255d4((int)param_2, 6, param_3)) != 0 && func_02011a6c(m, param_1) == 0)
        param_1[0] = 0;
    param_1[1] = 0;
    if (param_4 >= 0 && (m = func_020255d4((int)param_2, 1, param_4)) != 0 && func_020119d4(m, param_1 + 1) == 0)
        param_1[1] = 0;
    param_1[2] = 0;
    if (param_5 >= 0) {
        m = func_020255d4((int)param_2, 0, param_5);
        if (m != 0) {
            if (func_02011a20(m, param_1 + 2) == 0)
                param_1[2] = 0;
        }
    }
}
