reg_t ra = READ_REG(1);
printf("ssst ra=%lx pc=%lx\n", ra, pc);
sstack_t *ss;
ss = p->get_mmu()->get_sstack();
ss->push(ra);