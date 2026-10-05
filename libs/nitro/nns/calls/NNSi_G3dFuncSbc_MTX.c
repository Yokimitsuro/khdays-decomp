/* NitroSystem G3D SBC: forwards the command's byte as a geometry command (0x14) when enabled, then
 * advances 2 bytes. */

extern void NNSi_G3dGeBufferCommand1(int arg0, unsigned int arg1);

void NNSi_G3dFuncSbc_MTX(int *ptr) {
    int flags = ptr[2];

    if ((flags & 0x200) == 0 && (flags & 1) != 0 && (flags & 0x100) == 0) {
        NNSi_G3dGeBufferCommand1(0x14, *(unsigned char *)(ptr[0] + 1));
    }

    ptr[0] += 2;
}
