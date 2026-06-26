void *func_02010ccc(void **p)
{
	void *head = *p;
	if (head != 0) {
		*p = *(void **)head;
	}
	return head;
}
