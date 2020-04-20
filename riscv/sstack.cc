/**
 * @file sstack.cc
 * @author Andrew Belcher
 * @date 19 April 2020
 * @brief Source file for the shadow stack component
 */

#include "sstack.h"
#include "processor.h"
#include "trap.h"
#include <stdio.h>
#include <stdlib.h>

#define SSTACK_ASSERT(m) printf("SSTACK_ASSERT FAILED: " m  "\n"); abort();


/** @brief Shadow Stack Constructor
 *
 *  @param void
 *  @return Shadow Stack Class instance
 */
sstack_t::sstack_t(void)
{
	stack_selector = 0;
	verbose_mode = false;
	
	for(int i = 0; i < SHADOW_STACK_COUNT; i++)
	{
		ss_banks[i].sp = 0;
		
		for(int p = 0; p < SHADOW_STACK_SIZE; p++)
		{
			ss_banks[i].SSTACK[p] = 0;
		}
	}
}


/** @brief Sets whether the Shadow Stack module prints internal info
 *	
 *  @param bool mode, true allows it, false denies it
 *  @return void
 */
void sstack_t::set_verbose_mode(bool mode)
{
	verbose_mode = mode;
}


/** @brief Pushes the return address to the Shadow Stack selected
 *
 *  @param int ra, the return address
 *  @return void
 */
void sstack_t::push(int ra)
{
	shadow_stack* ss = &ss_banks[stack_selector];

	if(ss->sp >= SHADOW_STACK_SIZE)
	{
		SSTACK_ASSERT("stack is full!");
	}

	else	
	{
		ss->SSTACK[ss->sp++] = ra;

		if(verbose_mode)
		{
			printf("ssst sp:%d ra:%x\n", ss->sp-1, ss->SSTACK[ss->sp-1]);
		}
	}
}

/** @brief Pushes the return address to the Shadow Stack selected
 *
 *  @param void
 *  @retrun int pop_val, the return address
 */
int sstack_t::pop(void)
{
	shadow_stack* ss = &ss_banks[stack_selector];
	int pop_val = 0x33;

	if(ss->sp < 1)
	{
		SSTACK_ASSERT("stack is empty!");
	}

	else	
	{
		pop_val = ss->SSTACK[--ss->sp];

		if(verbose_mode)
		{
			printf("ssld sp:%d ra:%x\n", ss->sp, pop_val);
		}
	}

	return pop_val;
}

/** @brief Pushes the return address to the Shadow Stack selected
 *
 *  @param int ra, the return address to authenticate
 *  @param int din, the data popped off the stack used to auhthenticate with
 *  @retrun int result, the output from XORing the 2 inputs, needs to be 0 to be successful
 */
int sstack_t::authenticate(int ra, int din)
{
	int result = din ^ ra;

	if(verbose_mode)
	{
		printf("auth ra=%lx datain=%lx\n", ra, din);
	}

	return result;
}


/** @brief Changes the Shadow Stack selecter value
 *
 *  @param int selector, a value that represents which stack to use, 0-3(max is set by SHADOW_STACK_COUNT
 *  @retrun void
 */
void sstack_t::select(int selector)
{

	if(verbose_mode)
	{
		printf("ssth %d\n", selector);
	}

	if((selector < 0) || (selector >= SHADOW_STACK_COUNT))
	{
		SSTACK_ASSERT("selector is not valid!");
	}

	else
	{
		stack_selector = selector;
	}
}


/** @brief Clears all Shadow Stacks
 *
 *  @param void
 *  @retrun void
 */
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

