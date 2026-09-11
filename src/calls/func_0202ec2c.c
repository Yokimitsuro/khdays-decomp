typedef int fx32;

typedef struct Quat_0202ec2c {
    fx32 w;
    fx32 x;
    fx32 y;
    fx32 z;
} Quat_0202ec2c;

typedef struct MtxFx33_0202ec2c {
    fx32 m[3][3];
} MtxFx33_0202ec2c;

static inline fx32 FX_Mul_0202ec2c(fx32 a, fx32 b)
{
    return (fx32)(((long long)a * b + 0x800) >> 12);
}

/* Build a 3x3 rotation matrix from a unit quaternion (w,x,y,z order). */
void func_0202ec2c(MtxFx33_0202ec2c *mtx, const Quat_0202ec2c *q)
{
    fx32 x2 = q->x * 2;
    fx32 y2 = q->y * 2;
    fx32 z2 = q->z * 2;

    fx32 wx = FX_Mul_0202ec2c(x2, q->w);
    fx32 wy = FX_Mul_0202ec2c(y2, q->w);
    fx32 wz = FX_Mul_0202ec2c(z2, q->w);
    fx32 xx = FX_Mul_0202ec2c(x2, q->x);
    fx32 xy = FX_Mul_0202ec2c(y2, q->x);
    fx32 xz = FX_Mul_0202ec2c(z2, q->x);
    fx32 yy = FX_Mul_0202ec2c(y2, q->y);
    fx32 yz = FX_Mul_0202ec2c(z2, q->y);
    fx32 zz = FX_Mul_0202ec2c(z2, q->z);

    mtx->m[0][0] = 0x1000 - (yy + zz);
    mtx->m[1][0] = xy - wz;
    mtx->m[2][0] = xz + wy;

    mtx->m[0][1] = xy + wz;
    mtx->m[1][1] = 0x1000 - (xx + zz);
    mtx->m[2][1] = yz - wx;

    mtx->m[0][2] = xz - wy;
    mtx->m[1][2] = yz + wx;
    mtx->m[2][2] = 0x1000 - (xx + yy);
}
