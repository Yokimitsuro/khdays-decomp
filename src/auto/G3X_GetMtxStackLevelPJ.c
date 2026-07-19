/* Reads the matrix-stack level out of GXSTAT; -1 if the stack-error bit is set. */
int G3X_GetMtxStackLevelPJ(int *level) {
    if ((*(volatile unsigned *)0x04000600 & 0x4000) != 0) {
        return -1;
    }
    *level = (*(volatile unsigned *)0x04000600 & 0x2000) >> 13;
    return 0;
}
