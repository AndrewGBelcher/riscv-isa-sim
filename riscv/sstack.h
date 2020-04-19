#ifndef _RISCV_SSTACK_H
#define _RISCV_SSTACK_H

#define SHADOW_STACK_SIZE 0x100
#define SHADOW_STACK_COUNT 4


#define SHADOW_STACK_SIZE 0x100
#define SHADOW_STACK_COUNT 4


struct shadow_stack {

	int sp;
	int SSTACK[SHADOW_STACK_SIZE];
};

class sstack_t {
private:

	shadow_stack ss_banks[SHADOW_STACK_COUNT];
	int stack_selector;

public:


	void push(int ra);
	int pop(void);
	int authenticate(int ra, int din);
	void select(int selector);
	void clear(void);
	

	sstack_t();

};

#endif