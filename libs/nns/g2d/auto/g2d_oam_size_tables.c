/* NitroSystem g2d (g2d_Oam_data.h, instantiated by g2d_CellAnimation.c): the OBJ height / width
 * tables indexed by [shape][size] (NNS_G2D_DEFINE_NNSI_OBJSIZEHTBL / ...WTBL). */
typedef unsigned short u16;

/* NNSi_objSizeHTbl */
const u16 data_020419c4[3][4] = {
    {  8, 16, 32, 64 },
    {  8,  8, 16, 32 },
    { 16, 32, 32, 64 }
};

/* NNSi_objSizeWTbl */
const u16 data_020419dc[3][4] = {
    {  8, 16, 32, 64 },
    { 16, 32, 32, 64 },
    {  8,  8, 16, 32 }
};
