void MTX_Rot22_(int *mtx, int sinv, int cosv)
{
    mtx[0] = cosv;
    mtx[1] = sinv;
    mtx[2] = -sinv;
    mtx[3] = cosv;
}
