/**
 * @file sstack.h
 * @author Andrew Belcher
 * @date 19 April 2020
 * @brief Header file for the shadow stack component
 */

#ifndef _RISCV_SSTACK_H
#define _RISCV_SSTACK_H

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
	bool verbose_mode;

public:

	/** @brief Pushes the return address to the Shadow Stack selected
	 *
	 *  @param int ra, the return address
	 *  @return void
	 */
	void push(int ra);

	/** @brief Pushes the return address to the Shadow Stack selected
	 *
	 *  @param void
	 *  @retrun int pop_val, the return address
	 */
	int pop(void);

	/** @brief Pushes the return address to the Shadow Stack selected
	 *
	 *  @param int ra, the return address to authenticate
	 *  @param int din, the data popped off the stack used to auhthenticate with
	 *  @retrun int result, the output from XORing the 2 inputs, needs to be 0 to be successful
	 */
	int authenticate(int ra, int din);

	/** @brief Changes the Shadow Stack selecter value
	 *
	 *  @param int selector, a value that represents which stack to use, 0-3(max is set by SHADOW_STACK_COUNT
	 *  @retrun void
	 */
	void select(int selector);

	/** @brief Clears all Shadow Stacks
	 *
	 *  @param void
	 *  @retrun void
	 */
	void clear(void);

	/** @brief Sets whether the Shadow Stack module prints internal info
	 *	
	 *  @param bool mode, true allows it, false denies it
	 *  @return void
	 */
	void set_verbose_mode(bool mode);

	/** @brief Shadow Stack Constructor
	 *
	 *  @param void
	 *  @return Shadow Stack Class instance
	 */
	sstack_t();

};

#endif