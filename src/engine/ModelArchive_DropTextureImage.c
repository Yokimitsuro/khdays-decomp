/* Drops the texture image data of a model archive from main memory once it is in VRAM: the
 * archive's block is shrunk to end where its texture member's images start (texInfo.ofsTex, +0x14
 * of the texture block). */


extern int Archive_GetMember(int a, int b, int c);
extern int NNS_G3dGetTex(int entry);
extern void ExpHeap_ResizeBlock(int a, int b, int c, int d);

void ModelArchive_DropTextureImage(int archive, int heap, int arg3) {
    int entry = Archive_GetMember(archive, 7, 0);
    int base;
    if (entry == 0) return;
    base = NNS_G3dGetTex(entry);
    if (base == 0) return;
    ExpHeap_ResizeBlock(heap, archive, base + *(int *)(base + 0x14) - archive, arg3);
}
