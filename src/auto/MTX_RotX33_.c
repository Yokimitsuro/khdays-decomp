void MTX_RotX33_(int *p, int a, int b)
{
	p[0] = 0x1000;
	p[1] = 0;
	p[2] = 0;
	p[3] = 0;
	p[4] = b;
	p[5] = a;
	p[6] = 0;
	p[7] = -a;
	p[8] = b;
}
