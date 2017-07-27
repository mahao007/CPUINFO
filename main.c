#include<stdio.h>

inline void cpuid(unsigned int value) {
	register unsigned int eax asm("eax");

	eax = value;

	__asm__ (
		"CPUID"
	);
}

void print_binary(unsigned int value) {
	char result[33];
	result[32] = 0;
	unsigned int bit;
	int nth_bit;

	for (bit = 1, nth_bit = 31; nth_bit > -1; nth_bit--, bit*=2) {
		if (value & bit)
			result[nth_bit] = '1';
		else
			result[nth_bit] = '0';
	}

	printf("%s\n", &result);
}

void print_letters(unsigned int value) {
    char letter = value;
    if (letter)
	    printf("%c", letter);
	letter = value>>8;
    if (letter)
	    printf("%c", letter);
	letter = value>>16;
    if (letter)
	    printf("%c", letter);
	letter = value>>24;
    if (letter)
	    printf("%c", letter);
}

inline char get_letter_from_register_value(unsigned int register_value, unsigned int index) {
	return register_value >> index * 8;
}

void print_processor_brand_string() {
	register unsigned int eax asm("eax");
	register unsigned int ebx asm("ebx");
	register unsigned int ecx asm("ecx");
	register unsigned int edx asm("edx");
	unsigned int eax2, ebx2, ecx2, edx2;

	cpuid(0x80000002);

	eax2 = eax;
	ebx2 = ebx;
	ecx2 = ecx;
	edx2 = edx;
	
	print_letters(eax2);
	print_letters(ebx2);
	print_letters(ecx2);
	print_letters(edx2);

	cpuid(0x80000003);

	eax2 = eax;
	ebx2 = ebx;
	ecx2 = ecx;
	edx2 = edx;

	print_letters(eax2);
	print_letters(ebx2);
	print_letters(ecx2);
	print_letters(edx2);

	cpuid(0x80000004);

	eax2 = eax;
	ebx2 = ebx;
	ecx2 = ecx;
	edx2 = edx;

	print_letters(eax2);
	print_letters(ebx2);
	print_letters(ecx2);
	print_letters(edx2);
}

int main(int argc, char **argv) {

	print_processor_brand_string();
    printf("\n");
    
	return 0;
}
