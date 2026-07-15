/* func_ov006_02053b24 -- (re)bind the two title BG graphic layers per sub-state, ov006.
 * Tears down any previously-bound cell object for layer slot 0x976c (if +0x9798 set) and
 * slot 0x97b8 (if +0x97e4 set), then rebinds both from their loaded resources through
 * func_0202f834 with a shared placement rect { x=0, y=0, w=0x20, h=0x18, ..., alpha, .., 6 }:
 *   layer 3 <- resource at obj+0x9760 (data_ov006_02056540), object at obj+0x976c
 *   layer 7 <- resource at obj+0x97ac (data_ov006_0205655c), object at obj+0x97b8
 * Both layers are shown (alpha 0xf) for the normal title states {0-3,10,11,13,14}; in the
 * attract states {4-7} layer 7 is hidden (alpha 0). Other states leave the layers as-is. */
extern int *data_ov006_02056664;
extern void func_0202fa20(void *obj, int a);
extern void func_0202f9ec(void *obj);
extern void func_0202f834(unsigned int *obj, int layer, void *res, unsigned short *rect);

#define OBJ ((char *)data_ov006_02056664)

void func_ov006_02053b24(int state) {
    unsigned short p[8];
    if (*(int *)(OBJ + 0x9798) != 0) {
        func_0202fa20(OBJ + 0x976c, 0);
        func_0202f9ec(OBJ + 0x976c);
    }
    if (*(int *)(OBJ + 0x97e4) != 0) {
        func_0202fa20(OBJ + 0x97b8, 0);
        func_0202f9ec(OBJ + 0x97b8);
    }
    p[0] = 0;
    p[1] = 0;
    p[2] = 0x20;
    p[3] = 0x18;
    p[4] = 0;
    p[6] = 0;
    p[7] = 6;
    switch (state) {
    case 0:
    case 1:
    case 2:
    case 3:
    case 10:
    case 11:
    case 13:
    case 14:
        p[5] = 0xf;
        func_0202f834((unsigned int *)(OBJ + 0x976c), 3, OBJ + 0x9760, p);
        p[5] = 0xf;
        func_0202f834((unsigned int *)(OBJ + 0x97b8), 7, OBJ + 0x97ac, p);
        return;
    case 4:
    case 5:
    case 6:
    case 7:
        p[5] = 0xf;
        func_0202f834((unsigned int *)(OBJ + 0x976c), 3, OBJ + 0x9760, p);
        p[5] = 0;
        func_0202f834((unsigned int *)(OBJ + 0x97b8), 7, OBJ + 0x97ac, p);
        return;
    default:
        return;
    }
}
