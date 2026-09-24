/* Quadratic curve through three keys: for t in [0, 1] the parabola through p0 (t = 0), p1 (t = 1)
 * and p2 (t = 2) evaluated at t, for t beyond 1 the one through p1 at t = 1 continued with the p0..p2
 * slope and curvature (all fx32, func_02005418 = FX_Mul). Codegen: the curvature term of the second
 * branch is written inline in the final sum; as a named local the last add swaps its operands. */
#pragma thumb on
typedef int fx32;

extern fx32 func_02005418(fx32 a, fx32 b);   /* FX_Mul */

fx32 func_02021208(fx32 t, fx32 p0, fx32 p1, fx32 p2)
{
    if (t <= 0x1000) {
        fx32 a = func_02005418(-3 * p0 + p1 * 4 - p2, t);
        fx32 b = func_02005418(p2 + (p0 - (p1 << 1)), func_02005418(t, t));

        return func_02005418(0x800, p0 + p0 + a + b);
    } else {
        fx32 two = p1 << 1;
        fx32 c = func_02005418(p2 - p0, t - 0x1000);

        return func_02005418(0x800, two + c + func_02005418(p2 + (p0 - two), func_02005418(t - 0x1000, t - 0x1000)));
    }
}
