unsigned short *func_02005738(unsigned short *p, int v)
{
	if (v == 0) {
		*p = 0;
		return p;
	}
	if (v > 0) {
		v |= 0x4000;
		*p = (unsigned short)v;
	} else {
		v = -v;
		v |= 0x8000;
		*p = (unsigned short)v;
	}
	return p;
}
