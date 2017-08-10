#include<stdio.h>
#include<math.h>

inline void cpuid(unsigned int eax_p, unsigned int ebx_p, unsigned int ecx_p, unsigned int edx_p) {
	register unsigned int eax asm("eax");
	register unsigned int ebx asm("ebx");
	register unsigned int ecx asm("ecx");
	register unsigned int edx asm("edx");

	eax = eax_p;
	ebx = ebx_p;
	ecx = ecx_p;
	edx = edx_p;

	__asm__ (
		"CPUID"
	);
}

void print_binary(unsigned int value) {
	char result[32];
	unsigned int bit;
	int nth_bit;
	result[31] = 0;

	for (bit = 1, nth_bit = 31; nth_bit > -1; nth_bit--, bit*=2) {
		if (value & bit)
			result[nth_bit] = '1';
		else
			result[nth_bit] = '0';
	}

	for (nth_bit = 0; nth_bit < 32; nth_bit++) {
		if (nth_bit > 0 && nth_bit % 8 == 0)
			printf("%c", ' ');
		printf("%c", result[nth_bit]);
	}
	
	printf("\n", &result);
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

	cpuid(0x80000002, 0, 0, 0);

	eax2 = eax;
	ebx2 = ebx;
	ecx2 = ecx;
	edx2 = edx;
	
	print_letters(eax2);
	print_letters(ebx2);
	print_letters(ecx2);
	print_letters(edx2);

	cpuid(0x80000003, 0, 0, 0);

	eax2 = eax;
	ebx2 = ebx;
	ecx2 = ecx;
	edx2 = edx;

	print_letters(eax2);
	print_letters(ebx2);
	print_letters(ecx2);
	print_letters(edx2);

	cpuid(0x80000004, 0, 0, 0);

	eax2 = eax;
	ebx2 = ebx;
	ecx2 = ecx;
	edx2 = edx;

	print_letters(eax2);
	print_letters(ebx2);
	print_letters(ecx2);
	print_letters(edx2);
	
	printf("\n");
}

void print_vendor_id() {
	register unsigned int ebx asm("ebx");
	register unsigned int ecx asm("ecx");
	register unsigned int edx asm("edx");
	unsigned int ebx2, ecx2, edx2;

	cpuid(0, 0, 0, 0);

	ebx2 = ebx;
	ecx2 = ecx;
	edx2 = edx;
	
	print_letters(ebx2);
	print_letters(edx2);
	print_letters(ecx2);
	
	printf("\n");
}

inline void print_support_enabled_disabled(unsigned int enabled, char *str) {
	if (enabled) {
		printf("CPU supports '%s'\n", str);
	} else {
		printf("CPU does not support '%s'\n", str);
	}
}

inline unsigned int uint_pow(unsigned int base, unsigned int exp) {
	unsigned int result = 1;
	while (exp > 0) {
		result *= base;
		exp--;
	}
	return result;
}

void print_processor_features_support() {
	register unsigned int eax asm("eax");
	register unsigned int ebx asm("ebx");
	register unsigned int ecx asm("ecx");
	register unsigned int edx asm("edx");
	unsigned int eax2, ebx2, ecx2, edx2;

	//CPUID EAX = 1; Result = EDX
	const unsigned int FPU = uint_pow(2,0);
	const unsigned int VME = uint_pow(2,1);
	const unsigned int DE = uint_pow(2,2);
	const unsigned int PSE = uint_pow(2,3);
	const unsigned int TSC = uint_pow(2,4);
	const unsigned int MSR = uint_pow(2,5);
	const unsigned int PAE = uint_pow(2,6);
	const unsigned int MCE = uint_pow(2,7);
	const unsigned int CMPXCHG8 = uint_pow(2,8);
	const unsigned int APIC = uint_pow(2,9);
	const unsigned int SEP = uint_pow(2,11);
	const unsigned int PGE = uint_pow(2,12);
	const unsigned int MCA = uint_pow(2,13);
	const unsigned int MTRR = uint_pow(2,14);
	const unsigned int CMOV = uint_pow(2,15);
	const unsigned int PAT = uint_pow(2,16);
	const unsigned int PSE36 = uint_pow(2,17);
	const unsigned int PSN = uint_pow(2,18);
	const unsigned int CLFSH = uint_pow(2,19);
	const unsigned int DS = uint_pow(2,21);
	const unsigned int ACPI = uint_pow(2,22);
	const unsigned int MMX = uint_pow(2,23);
	const unsigned int FXSR = uint_pow(2,24);
	const unsigned int SSE = uint_pow(2,25);
	const unsigned int SSE2 = uint_pow(2,26);
	const unsigned int SS = uint_pow(2,27);
	const unsigned int HTT = uint_pow(2,28);
	const unsigned int TM = uint_pow(2,29);
	const unsigned int IA64 = uint_pow(2,30);
	const unsigned int PBE = uint_pow(2,31);

	//CPUID EAX = 1; Result = ECX
	const unsigned int SSE3 = uint_pow(2,0);
	const unsigned int PCLMULQDQ = uint_pow(2,1);
	const unsigned int DTES64 = uint_pow(2,2);
	const unsigned int MONITOR = uint_pow(2,3);
	const unsigned int DSCPL = uint_pow(2,4);
	const unsigned int VMX = uint_pow(2,5);
	const unsigned int SMX = uint_pow(2,6);
	const unsigned int EST = uint_pow(2,7);
	const unsigned int TM2 = uint_pow(2,8);
	const unsigned int SSSE3 = uint_pow(2,9);
	const unsigned int CNXTID = uint_pow(2,10);
	const unsigned int SDBG = uint_pow(2,11);
	const unsigned int FMA = uint_pow(2,12);
	const unsigned int CX16 = uint_pow(2,13);
	const unsigned int XTPR = uint_pow(2,14);
	const unsigned int PDCM = uint_pow(2,15);
	const unsigned int PCID = uint_pow(2,17);
	const unsigned int DCA = uint_pow(2,18);
	const unsigned int SSE4_1 = uint_pow(2,19);
	const unsigned int SSE4_2 = uint_pow(2,20);
	const unsigned int X2APIC = uint_pow(2,21);
	const unsigned int MOVBE = uint_pow(2,22);
	const unsigned int POPCNT = uint_pow(2,23);
	const unsigned int TSC_DEADLINE = uint_pow(2,24);
	const unsigned int AES = uint_pow(2,25);
	const unsigned int XSAVE = uint_pow(2,26);
	const unsigned int OSXSAVE = uint_pow(2,27);
	const unsigned int AVX = uint_pow(2,28);
	const unsigned int F16C = uint_pow(2,29);
	const unsigned int RDMD = uint_pow(2,30);
	const unsigned int HYPERVISOR = uint_pow(2,31);

	//CPUID EAX = 7 ECX = 0; Result = EBX
	const unsigned int FSGSBASE = uint_pow(2,0);
	const unsigned int IA32_TSC_ADJUST = uint_pow(2,1);
	const unsigned int SGX = uint_pow(2,2);
	const unsigned int BMI1 = uint_pow(2,3);
	const unsigned int HLE = uint_pow(2,4);
	const unsigned int AVX2 = uint_pow(2,5);
	const unsigned int SMEP = uint_pow(2,7);
	const unsigned int BMI2 = uint_pow(2,8);
	const unsigned int ERMS = uint_pow(2,9);
	const unsigned int INVPCID = uint_pow(2,10);
	const unsigned int RTM = uint_pow(2,11);
	const unsigned int PQM = uint_pow(2,12);
	const unsigned int FPU_CS_FPU_DS = uint_pow(2,13);
	const unsigned int MPX = uint_pow(2,14);
	const unsigned int PQE = uint_pow(2,15);
	const unsigned int AVX512F = uint_pow(2,16);
	const unsigned int AVX512DQ = uint_pow(2,17);
	const unsigned int RDSEED = uint_pow(2,18);
	const unsigned int ADX = uint_pow(2,19);
	const unsigned int SMAP = uint_pow(2,20);
	const unsigned int AVX512IFMA = uint_pow(2,21);
	const unsigned int PCOMMIT = uint_pow(2,22);
	const unsigned int CLFLUSHOPT = uint_pow(2,23);
	const unsigned int CLWB = uint_pow(2,24);
	const unsigned int INTEL_PT = uint_pow(2,25);
	const unsigned int AVX512PF = uint_pow(2,26);
	const unsigned int AVX512ER = uint_pow(2,27);
	const unsigned int AVX512CD = uint_pow(2,28);
	const unsigned int SHA = uint_pow(2,29);
	const unsigned int AVX512BW = uint_pow(2,30);
	const unsigned int AVX512VL = uint_pow(2,31);

	//CPUID EAX = 7 ECX = 0; Result = ECX
	const unsigned int PREFETCHWT1 = uint_pow(2,0);
	const unsigned int AVX512VBMI = uint_pow(2,1);
	const unsigned int UMIP = uint_pow(2,2);
	const unsigned int PKU = uint_pow(2,3);
	const unsigned int OSPKE = uint_pow(2,4);
	const unsigned int AVX512VPOPCNTDQ = uint_pow(2,14);
	const unsigned int RDPID = uint_pow(2,22);
	const unsigned int SGXLC = uint_pow(2,30);

	//CPUID EAX = 7 ECX = 0; Result = EDX
	const unsigned int AVX5124VNNIW = uint_pow(2,2);
	const unsigned int AVX5124FMAPS = uint_pow(2,3);
	
	cpuid(1, 0, 0, 0);

	ecx2 = ecx;
	edx2 = edx;

	//EDX
	print_support_enabled_disabled(edx2 & FPU, "x87 FPU");
	print_support_enabled_disabled(edx2 & VME, "Virtual 8086 mode extensions (such as VIF, VIP, PIV)");
	print_support_enabled_disabled(edx2 & DE, "Debugging extensions (CR4 bit 3)");
	print_support_enabled_disabled(edx2 & PSE, "Page Size Extension");
	print_support_enabled_disabled(edx2 & TSC, "Time Stamp Counter");
	print_support_enabled_disabled(edx2 & MSR, "Model-specific registers");
	print_support_enabled_disabled(edx2 & PAE, "Physical Address Extension");
	print_support_enabled_disabled(edx2 & MCE, "Machine Check Exception");
	print_support_enabled_disabled(edx2 & CMPXCHG8, "CMPXCHG8 (compare-and-swap) instruction");
	print_support_enabled_disabled(edx2 & APIC, "Onboard Advanced Programmable Interrupt Controller");
	print_support_enabled_disabled(edx2 & SEP, "SYSENTER and SYSEXIT instructions");
	print_support_enabled_disabled(edx2 & MTRR, "Memory Type Range Registers");
	print_support_enabled_disabled(edx2 & PGE, "Page Global Enable bit in CR4");
	print_support_enabled_disabled(edx2 & MCA, "Machine check architecture");
	print_support_enabled_disabled(edx2 & CMOV, "Conditional move and FCMOV instructions");
	print_support_enabled_disabled(edx2 & PAT, "Page Attribute Table");
	print_support_enabled_disabled(edx2 & PSE36, "36-bit page size extension");
	print_support_enabled_disabled(edx2 & PSN, "Processor Serial Number");
	print_support_enabled_disabled(edx2 & CLFSH, "CLFLUSH instruction (SSE2)");
	print_support_enabled_disabled(edx2 & DS, "Debug store: save trace of executed jumps");
	print_support_enabled_disabled(edx2 & ACPI, "Onboard thermal control MSRs for ACPI");
	print_support_enabled_disabled(edx2 & MMX, "MMX instructions");
	print_support_enabled_disabled(edx2 & FXSR, "FXSAVE, FXRESTOR instructions, CR4 bit 9");
	print_support_enabled_disabled(edx2 & SSE, "SSE instructions (a.k.a. Katmai New Instructions)");
	print_support_enabled_disabled(edx2 & SSE2, "SSE2 instructions");
	print_support_enabled_disabled(edx2 & SS, "CPU cache supports self-snoop");
	print_support_enabled_disabled(edx2 & HTT, "Hyper-threading");
	print_support_enabled_disabled(edx2 & TM, "Thermal monitor automatically limits temperature");
	print_support_enabled_disabled(edx2 & IA64, "IA64 processor emulating x86");
	print_support_enabled_disabled(edx2 & PBE, "Pending Break Enable (PBE# pin) wakeup support");

	//ECX
	print_support_enabled_disabled(ecx2 & SSE3, "Prescott New Instructions-SSE3 (PNI)");
	print_support_enabled_disabled(ecx2 & PCLMULQDQ, "PCLMULQDQ support");
	print_support_enabled_disabled(ecx2 & DTES64, "64-bit debug store (edx bit 21)");
	print_support_enabled_disabled(ecx2 & MONITOR, "MONITOR and MWAIT instructions (SSE3)");
	print_support_enabled_disabled(ecx2 & DSCPL, "CPL qualified debug store");
	print_support_enabled_disabled(ecx2 & VMX, "Virtual Machine eXtensions");
	print_support_enabled_disabled(ecx2 & SMX, "Safer Mode Extensions (LaGrande)");
	print_support_enabled_disabled(ecx2 & EST, "Enhanced SpeedStep");
	print_support_enabled_disabled(ecx2 & TM2, "Thermal Monitor 2");
	print_support_enabled_disabled(ecx2 & SSSE3, "Supplemental SSE3 instructions");
	print_support_enabled_disabled(ecx2 & CNXTID, "L1 Context ID");
	print_support_enabled_disabled(ecx2 & SDBG, "Silicon Debug interface");
	print_support_enabled_disabled(ecx2 & FMA, "Fused multiply-add (FMA3)");
	print_support_enabled_disabled(ecx2 & CX16, "CMPXCHG16B instruction");
	print_support_enabled_disabled(ecx2 & XTPR, "Can disable sending task priority messages");
	print_support_enabled_disabled(ecx2 & PDCM, "Perfmon & debug capability");
	print_support_enabled_disabled(ecx2 & PCID, "Process context identifiers (CR4 bit 17)");
	print_support_enabled_disabled(ecx2 & DCA, "Direct cache access for DMA writes");
	print_support_enabled_disabled(ecx2 & SSE4_1, "SSE4.1 instructions");
	print_support_enabled_disabled(ecx2 & SSE4_2, "SSE4.2 instructions");
	print_support_enabled_disabled(ecx2 & X2APIC, "x2APIC support");
	print_support_enabled_disabled(ecx2 & MOVBE, "MOVBE instruction (big-endian)");
	print_support_enabled_disabled(ecx2 & POPCNT, "POPCNT instruction");
	print_support_enabled_disabled(ecx2 & TSC_DEADLINE, "APIC supports one-shot operation using a TSC deadline value");
	print_support_enabled_disabled(ecx2 & AES, "AES instruction set");
	print_support_enabled_disabled(ecx2 & XSAVE, "XSAVE, XRESTOR, XSETBV, XGETBV");
	print_support_enabled_disabled(ecx2 & OSXSAVE, "XSAVE enabled by OS");
	print_support_enabled_disabled(ecx2 & AVX, "Advanced Vector Extensions");
	print_support_enabled_disabled(ecx2 & F16C, "F16C (half-precision) FP support");
	print_support_enabled_disabled(ecx2 & RDMD, "RDRAND (on-chip random number generator) support");
	print_support_enabled_disabled(ecx2 & HYPERVISOR, "Running on a hypervisor (always 0 on a real CPU, but also with some hypervisors)");

	cpuid(7, 0, 0, 0);

	ebx2 = ebx;
	ecx2 = ecx;
	edx2 = edx;

	print_support_enabled_disabled(ebx2 & FSGSBASE, "Access to base of %fs and %gs");
	print_support_enabled_disabled(ebx2 & IA32_TSC_ADJUST, "IA32_TSC_ADJUST");
	print_support_enabled_disabled(ebx2 & SGX, "Software Guard Extensions");
	print_support_enabled_disabled(ebx2 & BMI1, "Bit Manipulation Instruction Set 1");
	print_support_enabled_disabled(ebx2 & HLE, "Transactional Synchronization Extensions");
	print_support_enabled_disabled(ebx2 & AVX2, "Advanced Vector Extensions 2");
	print_support_enabled_disabled(ebx2 & SMEP, "Supervisor-Mode Execution Prevention");
	print_support_enabled_disabled(ebx2 & BMI2, "Bit Manipulation Instruction Set 2");
	print_support_enabled_disabled(ebx2 & ERMS, "Enhanced REP MOVSB/STOSB");
	print_support_enabled_disabled(ebx2 & INVPCID, "INVPCID instruction");
	print_support_enabled_disabled(ebx2 & RTM, "Transactional Synchronization Extensions");
	print_support_enabled_disabled(ebx2 & PQM, "Platform Quality of Service Monitoring");
	print_support_enabled_disabled(ebx2 & FPU_CS_FPU_DS, "FPU CS and FPU DS deprecated");
	print_support_enabled_disabled(ebx2 & MPX, "Intel MPX (Memory Protection Extensions)");
	print_support_enabled_disabled(ebx2 & PQE, "Platform Quality of Service Enforcement");
	print_support_enabled_disabled(ebx2 & AVX512F, "AVX-512 Foundation");
	print_support_enabled_disabled(ebx2 & AVX512DQ, "AVX-512 Doubleword and Quadword Instructions");
	print_support_enabled_disabled(ebx2 & RDSEED, "RDSEED instruction");
	print_support_enabled_disabled(ebx2 & ADX, "Intel ADX (Multi-Precision Add-Carry Instruction Extensions)");
	print_support_enabled_disabled(ebx2 & SMAP, "Supervisor Mode Access Prevention");
	print_support_enabled_disabled(ebx2 & AVX512IFMA, "AVX-512 Integer Fused Multiply-Add Instructions");
	print_support_enabled_disabled(ebx2 & PCOMMIT, "PCOMMIT instruction");
	print_support_enabled_disabled(ebx2 & CLFLUSHOPT, "CLFLUSHOPT instruction");
	print_support_enabled_disabled(ebx2 & CLWB, "CLWB instruction");
	print_support_enabled_disabled(ebx2 & INTEL_PT, "Intel Processor Trace");
	print_support_enabled_disabled(ebx2 & AVX512PF, "AVX-512 Prefetch Instructions");
	print_support_enabled_disabled(ebx2 & AVX512ER, "AVX-512 Exponential and Reciprocal Instructions");
	print_support_enabled_disabled(ebx2 & AVX512CD, "AVX-512 Conflict Detection Instructions");
	print_support_enabled_disabled(ebx2 & SHA, "Intel SHA extensions");
	print_support_enabled_disabled(ebx2 & AVX512BW, "AVX-512 Byte and Word Instructions");
	print_support_enabled_disabled(ebx2 & AVX512VL, "AVX-512 Vector Length Extensions");

	print_support_enabled_disabled(ecx2 & PREFETCHWT1, "PREFETCHWT1 instruction");
	print_support_enabled_disabled(ecx2 & AVX512VBMI, "AVX-512 Vector Bit Manipulation Instructions");
	print_support_enabled_disabled(ecx2 & UMIP, "User-mode Instruction Prevention");
	print_support_enabled_disabled(ecx2 & PKU, "Memory Protection Keys for User-mode pages");
	print_support_enabled_disabled(ecx2 & OSPKE, "PKU enabled by OS");
	print_support_enabled_disabled(ecx2 & AVX512VPOPCNTDQ, "AVX-512 Vector Population Count D/Q");
	print_support_enabled_disabled(ecx2 & RDPID, "	Read Processor ID");
	print_support_enabled_disabled(ecx2 & SGXLC, "SGX Launch Configuration");

	print_support_enabled_disabled(edx2 & AVX5124VNNIW, "AVX-512 Neural Network Instructions");
	print_support_enabled_disabled(edx2 & AVX5124FMAPS, "AVX-512 Multiply Accumulation Single precision");
}

void print_processor_serial_number() {
	const unsigned int PSN = uint_pow(2,18);
	register unsigned int eax asm("eax");
	register unsigned int ebx asm("ebx");
	register unsigned int ecx asm("ecx");
	register unsigned int edx asm("edx");
	unsigned int eax2, ebx2, ecx2, edx2;
	cpuid(1, 0, 0, 0);
	edx2 = edx;
	if (PSN & edx2) {
		cpuid(3, 0, 0, 0);
		//Transmetta Efficeon
		eax2 = eax;
		ebx2 = ebx;
		//Intel
		ecx2 = ecx;
		edx2 = edx;
		//Intel
		printf("ecx:");
		print_binary(ecx2);
		printf("edx:");
		print_binary(edx2);
		//Transmeta Efficeon
		printf("eax:");
		print_binary(eax2);
		printf("ebx:");
		print_binary(ebx2);
	} else {
		printf("Does not support Processor Serial Number(PSN)");
	}
}

int main(int argc, char **argv) {
	print_vendor_id();
	print_processor_brand_string();
	print_processor_features_support();
	//Missing cpuid eax=2 TLB
	print_processor_serial_number();
	return 0;
}
