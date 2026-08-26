typedef unsigned int u32;

typedef struct VecFx32 {
    int x;
    int y;
    int z;
} VecFx32;

typedef struct Ov022SelectionPoint {
    int x;
    int y;
} Ov022SelectionPoint;

extern int func_0201653c(const VecFx32 *world, int *screenX, int *screenY);
extern void VEC_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern int VEC_Mag(const VecFx32 *vector);
extern void func_01ff8d18(const VecFx32 *source, VecFx32 *destination);
extern int VEC_DotProduct(const VecFx32 *a, const VecFx32 *b);
extern VecFx32 data_020475ac[];
extern VecFx32 data_020475c4;

int func_ov022_02085ec4(const VecFx32 *position, Ov022SelectionPoint *point)
{
    int projectionResult;
    int screenX;
    int screenY;
    VecFx32 toPosition;
    VecFx32 viewDirection;
    u32 cameraAddress = (u32)data_020475ac;
    u32 cameraTargetAddress = (u32)&data_020475c4;

    projectionResult = func_0201653c(position, &screenX, &screenY);
    screenY -= 8;
    if (projectionResult != -1) {
        VEC_Subtract(position, (const VecFx32 *)cameraAddress, &toPosition);
        VEC_Subtract((const VecFx32 *)cameraTargetAddress,
                     (const VecFx32 *)cameraAddress, &viewDirection);
        if (VEC_Mag(&toPosition) != 0) {
            func_01ff8d18(&toPosition, &toPosition);
        }
        if (VEC_Mag(&viewDirection) != 0) {
            func_01ff8d18(&viewDirection, &viewDirection);
        }
        if (VEC_DotProduct(&viewDirection, &toPosition) < 0) {
            projectionResult = -1;
        }
    }

    point->x = screenX << 12;
    point->y = screenY << 12;
    return projectionResult;
}

