reg_t ra = READ_REG(1);
sstack_t *ss;
ss = p->get_mmu()->get_sstack();
ss->push(ra);