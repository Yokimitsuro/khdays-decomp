/* Tears an effect set down when it is active: releases its nine model instances and its service
 * (when loaded) and resets it. */

extern void ReleaseField74AndCleanup(int arg0);
extern void VeneerTo_Obj_Destroy(int arg0);
extern void Ov022_ResetBlock94c(unsigned char *arg0);

void func_ov022_02092e4c(unsigned char *arg0, int arg1, int arg2, int arg3) {
    int f = *arg0;
    if ((f & 1) != 0) {
        if ((f & 4) != 0) {
            int i = 0;
            int p = (int)arg0 + 4;
            do {
                ReleaseField74AndCleanup(p);
                i = i + 1;
                p = p + 0x108;
            } while (i < 9);
            if (*(int *)((char *)arg0 + 0x94c) != 0) {
                VeneerTo_Obj_Destroy(*(int *)((char *)arg0 + 0x94c));
            }
        }
        Ov022_ResetBlock94c(arg0);
    }
}
