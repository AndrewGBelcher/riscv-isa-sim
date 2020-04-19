int thread_selector = insn.u_imm() >> 12;
printf("ssth 0x%lx pc=%lx\n", thread_selector, pc);
sstack_t *ss;
ss = p->get_mmu()->get_sstack();
ss->select(thread_selector);