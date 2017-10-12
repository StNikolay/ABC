#include <stdio.h>
#include <math.h>
#include <sys/time.h>
#include <stdlib.h>

int a = 2, b = 30, tmp;

double wtime()
{
	struct timeval t;
	gettimeofday(&t, NULL);
	return (double)t.tv_sec + (double)t.tv_usec * 1E-6;
}

int asm_pow(int a, int b)
{
	//int tmp;
	__asm__ (
		//	".intel_syntax noprefix\n"
			"mov r0, %1\n"
			"mov r1, %2\n"
			"mov r2, #1\n"
			//"dec ecx\n"
			"metka:\n"
			"sub r1, r1, #1\n"
			"mul r2, r0, r2\n"
			"cmp r1, #0\n"
			"bne metka\n"
			"mov %0, r2\n"
			//"mov tmp, eax"
			: "=r"(tmp)
			: "r"(a), "r"(b)
			: "r0", "r1", "r2"
	);
	return tmp;
}

int main()
{
	//int a = 32, b = 5, c;
	int c;
	double t;

	t = wtime();
	c = pow(a, b);
	printf("row = %d\n", c);
	t = wtime() - t;
	printf("Elapsed time row's: %.6f sec.\n", t);

	t = wtime();
	c = asm_pow(a, b);
	printf("asm_row = %d\n", c);
	t = wtime() - t;
	printf("Elapsed time asm_row's: %.6f sec.\n", t);
	return 0;
}
