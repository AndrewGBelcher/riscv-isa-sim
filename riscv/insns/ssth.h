int thread_selector = insn.u_imm() >> 12;
sstack_t *ss;
ss = p->get_mmu()->get_sstack();
ss->select(thread_selector);