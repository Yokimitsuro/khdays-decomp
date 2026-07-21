typedef unsigned short u16;

int func_ov025_02094618(u16 *pTileX, u16 *pTileY, unsigned int px, unsigned int py) {
    int ret = 0;
    if (px < 0x60 && py >= 0x10 && py < 0xa0) {
        int cx = px - 8;
        u16 tx;
        int cy;
        u16 ty;
        *pTileX = cx / 16;
        tx = *pTileX;
        if (tx > 4) tx = 4;
        *pTileX = tx;
        cy = py - 0x18;
        *pTileY = cy / 16;
        ty = *pTileY;
        ret = 1;
        if (ty > 7) ty = 7;
        *pTileY = ty;
    }
    return ret;
}
