#include "sstack.h"
#include "processor.h"
#include "trap.h"
#include <stdio.h>
#include <stdlib.h>


#define SSTACK_ASSERT() printf("SSTACK_ASSERT FAILED!\n"); abort();

sstack_t::sstack_t()
{

	stack_selector = 0;
	
	for(int i = 0; i < SHADOW_STACK_COUNT; i++)
	{
		ss_banks[i].sp = 0;
		
		for(int p = 0; p < SHADOW_STACK_SIZE; p++)
		{
			ss_banks[i].SSTACK[p] = 0;
		}
	}

}


void sstack_t::push(int ra)
{

	shadow_stack* ss = &ss_banks[stack_selector];

	if(ss->sp >= SHADOW_STACK_SIZE)
	{
		SSTACK_ASSERT();
	}

	else	
	{
		ss->SSTACK[ss->sp++] = ra;

/* 		printf("in push, stack_sel:%d\t sp:%d\t dataout:%x	datain:%x\n",
			stack_selector,
			ss->sp-1,
			ss->SSTACK[ss->sp-1],
			ra
		); */

		printf("ssst sp:%d ra:%x\n", ss->sp-1, ss->SSTACK[ss->sp-1]);
	}
}

int sstack_t::pop(void)
{
	shadow_stack* ss = &ss_banks[stack_selector];
	int pop_val = 0x33;

	if(ss->sp < 1)
	{
		SSTACK_ASSERT();
	}

	else	
	{
		pop_val = ss->SSTACK[--ss->sp];

		printf("ssld sp:%d ra:%x\n", ss->sp, pop_val);

/* 		printf("in pop, stack_sel:%d\t sp:%d\t dataout:%x\n",
			stack_selector,
			ss->sp,
			pop_val
		); */
	}

	return pop_val;
}

int sstack_t::authenticate(int ra, int din)
{
	
	int result = din ^ ra;
	
/* 	printf("in authenticate, stack_sel:%d	dout:%x		result:%x 	ra:%x\n",
		stack_selector,
		din,
		result,
		ra
	); */

	// throw interrupt here
	if(result != 0)
	{
		//PAC_ASSERT();
	}

	return result;

}

void sstack_t::select(int selector)
{
	if(selector >= 0 && selector < SHADOW_STACK_COUNT)
	{
		stack_selector = selector;
	}
	
	// throw interrupt here maybe
	else
	{
		SSTACK_ASSERT();
	}
}

void sstack_t::clear(void)
{

	for(int i = 0; i < SHADOW_STACK_COUNT; i++)
	{
		shadow_stack* ss = &ss_banks[i];

		for(int p = 0; p < SHADOW_STACK_SIZE; p++)
		{
			ss->SSTACK[p] = 0;
		}
		ss->sp = 0;
	}
}

