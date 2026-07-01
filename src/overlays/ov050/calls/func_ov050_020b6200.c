extern void func_ov050_020b6238();

struct S { int f0; int f4; };

void func_ov050_020b6200(struct S *p)
{
    func_ov050_020b6238(p, 0, 0);
    p->f4 = 1;
}
