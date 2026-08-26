/* Preserve the original unit's predicated-store scheduling in the point loop. */
#pragma opt_repositioncode on

typedef struct Ov022Point {
    int x;
    int y;
} Ov022Point;

typedef struct Ov022CornerTable {
    Ov022Point corners[4];
} Ov022CornerTable;

typedef struct Ov022DisplayObject {
    char padding000[0x10];
    int pointX;
    int pointY;
    char padding018[0x18];
} Ov022DisplayObject;

extern const Ov022CornerTable data_ov022_020b227c;
extern void func_ov002_02050e64(void);
extern int func_ov002_0205127c(Ov022DisplayObject *object);

void func_ov022_02086264(Ov022DisplayObject *object, int amount,
                         const Ov022Point *center)
{
    Ov022CornerTable cornerTable = data_ov022_020b227c;
    Ov022Point position;
    int negativeAmount;
    int index;

    func_ov002_02050e64();
    negativeAmount = -amount;
    for (index = 0; index < 4; index++, object++) {
        int cornerX = cornerTable.corners[index].x;
        int cornerY;

        if (cornerX > 0) {
            *(volatile int *)&position.x = amount;
        } else {
            *(volatile int *)&position.x = negativeAmount;
        }
        cornerY = cornerTable.corners[index].y;
        if (cornerY > 0) {
            *(volatile int *)&position.y = amount;
        } else {
            *(volatile int *)&position.y = negativeAmount;
        }
        position.x += center->x + cornerX;
        position.y += center->y + cornerY;
        object->pointX = position.x;
        object->pointY = position.y;
        func_ov002_0205127c(object);
    }
}
