/* Samples a joint matrix of the owner's model; when it is available, copies its translation into
 * the tracked position (+0x3d8). */

extern int NNS_G3dGetResultMtx();

struct w3 { int a, b, c; };

void Ov147_QueryAndCopyVecIfHit(int arg0, int arg1) {
    int buf[12];
    if (NNS_G3dGetResultMtx(*(int *)(arg0 + 0x88) + 0x20, buf, 0, *(int *)(arg1 + 0x3d4)) == 0) return;
    *(struct w3 *)(arg1 + 0x3d8) = *(struct w3 *)((char *)buf + 0x24);
}
