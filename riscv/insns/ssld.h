sstack_t *ss;
ss = p->get_mmu()->get_sstack();
int dout = ss->pop();
int result = ss->authenticate(READ_REG(X_RA), dout);
printf("ssld ra=%lx pc=%lx\n", READ_REG(X_RA), pc);
if(result != 0)
{
	printf("dout:%x ra_reg:%x result:%x\n",dout, READ_REG(X_RA), result);
	WRITE_REG(X_RA, dout);
} 
