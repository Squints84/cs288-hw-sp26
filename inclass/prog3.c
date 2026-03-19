#include <stdio.h>

// GDB does not allow you to see function instructions in memory. In other words, you can't directly see function sitting in memory as a contigious block.
// But, you can trace and manipulate the stack and memory during runtime in C program.


int depth=0;
void func(){
	char func_data[20];
	if(depth++>5) return;
	sprintf(func_data, "*#*#*#*# %d *#*#*#*#", depth);
	printf("func_data (layer %d) @ %p \n", depth, (void *)func_data);
	func();
	}

int main(){
	printf("func @ %p \n", (void *)func);
	func();
}

