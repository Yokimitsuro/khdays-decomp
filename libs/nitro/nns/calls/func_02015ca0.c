typedef unsigned char u8;
typedef unsigned long u32;

typedef struct NNSG3dGlb {
    u8 pad00_8c[0x8c];
    u32 prmViewPort;
} NNSG3dGlb;

extern NNSG3dGlb data_02047394;

void func_02015ca0(int *px1, int *py1, int *px2, int *py2)
{
    if (px1)
        *px1 = (int)(data_02047394.prmViewPort & 0xff);
    if (py1)
        *py1 = (int)((data_02047394.prmViewPort >> 8) & 0xff);
    if (px2)
        *px2 = (int)((data_02047394.prmViewPort >> 16) & 0xff);
    if (py2)
        *py2 = (int)((data_02047394.prmViewPort >> 24) & 0xff);
}
