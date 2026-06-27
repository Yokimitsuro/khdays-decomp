void func_01ff8ff4(int *mtx, int sinv, int cosv)
{
    mtx[0] = 0x1000;
    mtx[1] = 0;
    mtx[2] = 0;
    mtx[3] = 0;
    mtx[4] = cosv;
    mtx[5] = sinv;
    mtx[6] = 0;
    mtx[7] = -sinv;
    mtx[8] = cosv;
}
