#include "vm/NativeFunctions.h"

#include "vm/VirtualMachine.h"
#include "vm/VMNativeCallStack.h"

#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>

/*****************************************************************************
 * Auxiliar functions
 *****************************************************************************/
static void _native_fprintf(FILE *fp, VirtualMachine & vm, VMNativeCallStack & stack);
static void _native_fscanf(FILE *fp, VirtualMachine & vm, VMNativeCallStack & stack);

static int print_int(FILE *fp, VMNativeCallStack & stack, bool l);
static int print_uint(FILE *fp, VMNativeCallStack & stack, bool l);
static int print_char(FILE *fp, VMNativeCallStack & stack, bool l);
static int print_float(FILE *fp, VMNativeCallStack & stack, bool l);
static int print_ptr(FILE *fp, VMNativeCallStack & stack, bool l);
static int print_hexa(FILE *fp, VMNativeCallStack & stack, bool l);
static int print_hexa_cap(FILE *fp, VMNativeCallStack & stack, bool l);
static int print_str(FILE *fp, VMNativeCallStack & stack, bool l);

static void scan_int(FILE *fp, VMNativeCallStack & stack, bool l);
static void scan_uint(FILE *fp, VMNativeCallStack & stack, bool l);
static void scan_char(FILE *fp, VMNativeCallStack & stack, bool l);
static void scan_float(FILE *fp, VMNativeCallStack & stack, bool l);
static void scan_ptr(FILE *fp, VMNativeCallStack & stack, bool l);
static void scan_hexa(FILE *fp, VMNativeCallStack & stack, bool l);
static void scan_hexa_cap(FILE *fp, VMNativeCallStack & stack, bool l);
static void scan_str(FILE *fp, VMNativeCallStack & stack, bool l);

/*****************************************************************************
 * extern void __assert_fail(const char *file, unsigned int line);
 *****************************************************************************/
void native___assert_fail(VirtualMachine & vm, VMNativeCallStack & stack) {
	const char *file = stack.readPtr<const char>();
	unsigned int line = stack.read<unsigned int>();
	
	fprintf(stderr, "%s:%u: Assertion failed.\n", file, line);
	abort();
}

/*****************************************************************************
 * extern double acos(double arg);
 *****************************************************************************/
void native_acos(VirtualMachine & vm, VMNativeCallStack & stack) {
	double arg = stack.read<double>();
	
	double ret = acos(arg);
	
	vm.pushValue(&ret, sizeof(double));
}

/*****************************************************************************
 * extern double asin(double arg);
 *****************************************************************************/
void native_asin(VirtualMachine & vm, VMNativeCallStack & stack) {
	double arg = stack.read<double>();
	
	double ret = asin(arg);
	
	vm.pushValue(&ret, sizeof(double));
}

/*****************************************************************************
 * extern double atan(double arg);
 *****************************************************************************/
void native_atan(VirtualMachine & vm, VMNativeCallStack & stack) {
	double arg = stack.read<double>();
	
	double ret = atan(arg);
	
	vm.pushValue(&ret, sizeof(double));
}

/*****************************************************************************
 * extern double atan2(double y, double x);
 *****************************************************************************/
void native_atan2(VirtualMachine & vm, VMNativeCallStack & stack) {
	double y = stack.read<double>();
	double x = stack.read<double>();
	
	double ret = atan2(y, x);
	
	vm.pushValue(&ret, sizeof(double));
}

/*****************************************************************************
 * extern double ceil(double arg);
 *****************************************************************************/
void native_ceil(VirtualMachine & vm, VMNativeCallStack & stack) {
	double arg = stack.read<double>();
	
	double ret = ceil(arg);
	
	vm.pushValue(&ret, sizeof(double));
}

/*****************************************************************************
 * extern double cos(double arg);
 *****************************************************************************/
void native_cos(VirtualMachine & vm, VMNativeCallStack & stack) {
	double arg = stack.read<double>();
	
	double ret = cos(arg);
	
	vm.pushValue(&ret, sizeof(double));
}

/*****************************************************************************
 * extern double cosh(double arg);
 *****************************************************************************/
void native_cosh(VirtualMachine & vm, VMNativeCallStack & stack) {
	double arg = stack.read<double>();
	
	double ret = cosh(arg);
	
	vm.pushValue(&ret, sizeof(double));
}

/*****************************************************************************
 * extern double fabs(double arg);
 *****************************************************************************/
void native_fabs(VirtualMachine & vm, VMNativeCallStack & stack) {
	double arg = stack.read<double>();
	
	double ret = fabs(arg);
	
	vm.pushValue(&ret, sizeof(double));
}

/*****************************************************************************
 * extern double floor(double arg);
 *****************************************************************************/
void native_floor(VirtualMachine & vm, VMNativeCallStack & stack) {
	double arg = stack.read<double>();
	
	double ret = floor(arg);
	
	vm.pushValue(&ret, sizeof(double));
}

/*****************************************************************************
 * extern double fmod(double x, double y);
 *****************************************************************************/
void native_fmod(VirtualMachine & vm, VMNativeCallStack & stack) {
	double x = stack.read<double>();
	double y = stack.read<double>();
	
	double ret = fmod(x, y);
	
	vm.pushValue(&ret, sizeof(double));
}

/*****************************************************************************
 * extern double log(double arg);
 *****************************************************************************/
void native_log(VirtualMachine & vm, VMNativeCallStack & stack) {
	double arg = stack.read<double>();
	
	double ret = log(arg);
	
	vm.pushValue(&ret, sizeof(double));
}

/*****************************************************************************
 * extern double log10(double arg);
 *****************************************************************************/
void native_log10(VirtualMachine & vm, VMNativeCallStack & stack) {
	double arg = stack.read<double>();
	
	double ret = log10(arg);
	
	vm.pushValue(&ret, sizeof(double));
}


/*****************************************************************************
 * extern double pow(double base, double e);
 *****************************************************************************/
void native_pow(VirtualMachine & vm, VMNativeCallStack & stack) {
	double base = stack.read<double>();
	double e = stack.read<double>();
	
	double ret = pow(base, e);
	
	vm.pushValue(&ret, sizeof(double));
}

/*****************************************************************************
 * extern double sin(double arg);
 *****************************************************************************/
void native_sin(VirtualMachine & vm, VMNativeCallStack & stack) {
	double arg = stack.read<double>();
	
	double ret = sin(arg);
	
	vm.pushValue(&ret, sizeof(double));
}

/*****************************************************************************
 * extern double sinh(double arg);
 *****************************************************************************/
void native_sinh(VirtualMachine & vm, VMNativeCallStack & stack) {
	double arg = stack.read<double>();
	
	double ret = sinh(arg);
	
	vm.pushValue(&ret, sizeof(double));
}

/*****************************************************************************
 * extern double sqrt(double arg);
 *****************************************************************************/
void native_sqrt(VirtualMachine & vm, VMNativeCallStack & stack) {
	double arg = stack.read<double>();
	
	double ret = sqrt(arg);
	
	vm.pushValue(&ret, sizeof(double));
}

/*****************************************************************************
 * extern double tan(double arg);
 *****************************************************************************/
void native_tan(VirtualMachine & vm, VMNativeCallStack & stack) {
	double arg = stack.read<double>();
	
	double ret = tan(arg);
	
	vm.pushValue(&ret, sizeof(double));
}

/*****************************************************************************
 * extern double tanh(double arg);
 *****************************************************************************/
void native_tanh(VirtualMachine & vm, VMNativeCallStack & stack) {
	double arg = stack.read<double>();
	
	double ret = tanh(arg);
	
	vm.pushValue(&ret, sizeof(double));
}

/*****************************************************************************
 * extern int printf(const char *format, ...);
 *****************************************************************************/
void native_printf(VirtualMachine & vm, VMNativeCallStack & stack) {
	_native_fprintf(stdout, vm, stack);
}

/*****************************************************************************
 * extern int fprintf(FILE *fp, const char *format, ...);
 *****************************************************************************/
void native_fprintf(VirtualMachine & vm, VMNativeCallStack & stack) {
	// the compiler think it's a pointer to int, but it's a pointer to FILE
	FILE *fp = stack.readPtr<FILE>();
	
	_native_fprintf(fp, vm, stack);
}

static void _native_fprintf(FILE *fp, VirtualMachine & vm, VMNativeCallStack & stack) {
	int printed = 0;
	
	const char *arg1 = stack.readPtr<const char>();
	
	for (const char *p = arg1; *p; ++p) {
		if (*p != '%') {
			fputc(*p, fp);
			++printed;
		}
		else {
			++p;
			if (!*p) break;
			
			bool l = false;
			bool done = false;
			
			while (!done) {
				switch (*p) {
					case '%':
						fputc('%', fp);
						++printed;
						done = true;
						break;
					case 'l':
					case 'L':
						l = true;
						break;
					case 'd':
						printed += print_int(fp, stack, l);
						done = true;
						break;
					case 'u':
						printed += print_uint(fp, stack, l);
						done = true;
						break;
					case 'f':
						printed += print_float(fp, stack, l);
						done = true;
						break;
					case 'c':
						printed += print_char(fp, stack, l);
						done = true;
						break;
					case 'p':
						printed += print_ptr(fp, stack, l);
						done = true;
						break;
					case 'x':
						printed += print_hexa(fp, stack, l);
						done = true;
						break;
					case 'X':
						printed += print_hexa_cap(fp, stack, l);
						done = true;
						break;
					case 's':
						printed += print_str(fp, stack, l);
						done = true;
						break;
				}
				
				if (!done) {
					++p;
					if (!*p) break;
				}
			}
		}
	}
	
	// set the return value
	vm.pushValue(&printed, sizeof(int));
}

/*****************************************************************************
 * extern int scanf(const char *format, ...);
 *****************************************************************************/
void native_scanf(VirtualMachine & vm, VMNativeCallStack & stack) {
	_native_fscanf(stdin, vm, stack);
}

/*****************************************************************************
 * extern int fscanf(FILE *fp, const char *format, ...);
 *****************************************************************************/
void native_fscanf(VirtualMachine & vm, VMNativeCallStack & stack) {
	// the compiler think it's a pointer to int, but it's a pointer to FILE
	FILE *fp = stack.readPtr<FILE>();
	
	_native_fscanf(fp, vm, stack);
}

static void _native_fscanf(FILE *fp, VirtualMachine & vm, VMNativeCallStack & stack) {
	int readed = 0;
	
	const char *arg1 = stack.readPtr<const char>();
	
	for (const char *p = arg1; *p; ++p) {
		if (*p != '%') continue;
		++p;
		if (!*p) break;
		
		bool l = false;
		bool done = false;
		
		while (!done) {
			switch (*p) {
				case '%':
					done = true;
					break;
				case 'l':
				case 'L':
					l = true;
					break;
				case 'd':
					scan_int(fp, stack, l); 
					++readed;
					done = true;
					break;
				case 'u':
					scan_uint(fp, stack, l); 
					++readed;
					done = true;
					break;
				case 'f':
					scan_float(fp, stack, l); 
					++readed;
					done = true;
					break;
				case 'c':
					scan_char(fp, stack, l); 
					++readed;
					done = true;
					break;
				case 'p':
					scan_ptr(fp, stack, l);
					++readed;
					done = true;
					break;
				case 'x':
					scan_hexa(fp, stack, l);
					++readed;
					done = true;
					break;
				case 'X':
					scan_hexa_cap(fp, stack, l); 
					++readed;
					done = true;
					break;
				case 's':
					scan_str(fp, stack, l);
					++readed;
					done = true;
					break;
			}
			
			if (!done) {
				++p;
				if (!*p) break;
			}
		}
	}
	
	// set the return value
	vm.pushValue(&readed, sizeof(int));
}

/*****************************************************************************
 * extern int fgetc (FILE *fp);
 *****************************************************************************/
void native_fgetc (VirtualMachine & vm, VMNativeCallStack & stack) {
	// the compiler think it's a pointer to int, but it's a pointer to FILE
	FILE *fp = stack.readPtr<FILE>();
	
	int ret = fgetc(fp);
	
	// set the return value
	vm.pushValue(&ret, sizeof(int));
}

/*****************************************************************************
 * extern int getc (FILE *fp);
 *****************************************************************************/
void native_getc (VirtualMachine & vm, VMNativeCallStack & stack) {
	native_fgetc(vm, stack);
}

/*****************************************************************************
 * extern int getchar(void);
 *****************************************************************************/
void native_getchar(VirtualMachine & vm, VMNativeCallStack & stack) {
	int ret = getchar();
	vm.pushValue(&ret, sizeof(int));
}

/*****************************************************************************
 * extern FILE *fopen(const char *path, const char *mode);
 *****************************************************************************/
void native_fopen(VirtualMachine & vm, VMNativeCallStack & stack) {
	const char *path = stack.readPtr<const char>();
	const char *mode = stack.readPtr<const char>();
	
	FILE *fp = fopen(path, mode);
	
	RegisterInt ret = reinterpret_cast<RegisterInt>(fp);
	vm.pushValue(&ret, sizeof(RegisterInt));
}

/*****************************************************************************
 * extern int fclose(FILE *fp);
 *****************************************************************************/
void native_fclose(VirtualMachine & vm, VMNativeCallStack & stack) {
	FILE *fp = stack.readPtr<FILE>();
	
	int ret = fclose(fp);
	
	vm.pushValue(&ret, sizeof(int));
}

/*****************************************************************************
 * extern int fflush(FILE *fp);
 *****************************************************************************/
void native_fflush(VirtualMachine & vm, VMNativeCallStack & stack) {
	FILE *fp = stack.readPtr<FILE>();
	
	int ret = fflush(fp);
	
	vm.pushValue(&ret, sizeof(int));
}

/*****************************************************************************
 * extern FILE *__get_stdin(void);
 *****************************************************************************/
void native___get_stdin(VirtualMachine & vm, VMNativeCallStack & stack) {
	vm.pushValue(&stdin, REGISTER_SIZE);
}

/*****************************************************************************
 * extern FILE *__get_stdout(void);
 *****************************************************************************/
void native___get_stdout(VirtualMachine & vm, VMNativeCallStack & stack) {
	vm.pushValue(&stdout, REGISTER_SIZE);
}

/*****************************************************************************
 * extern FILE *__get_stderr(void);
 *****************************************************************************/
void native___get_stderr(VirtualMachine & vm, VMNativeCallStack & stack) {
	vm.pushValue(&stderr, REGISTER_SIZE);
}

/*****************************************************************************
 * extern void *calloc(size_t nmemb, size_t size);
 *****************************************************************************/
void native_calloc(VirtualMachine & vm, VMNativeCallStack & stack) {
	unsigned int nmemb = stack.read<unsigned int>();
	unsigned int size = stack.read<unsigned int>();
	
	void *ret = calloc(nmemb, size);
	
	vm.pushValue(&ret, REGISTER_SIZE);
}

/*****************************************************************************
 * extern void *malloc(size_t size);
 *****************************************************************************/
void native_malloc(VirtualMachine & vm, VMNativeCallStack & stack) {
	unsigned int size = stack.read<unsigned int>();
	
	void *ret = malloc(size);
	
	vm.pushValue(&ret, REGISTER_SIZE);
}

/*****************************************************************************
 * extern void free(void *ptr);
 *****************************************************************************/
void native_free(VirtualMachine & vm, VMNativeCallStack & stack) {
	void *ptr = stack.readPtr<void>();
	
	free(ptr);
}


/*****************************************************************************
 * extern void *realloc(void *ptr, size_t size);
 *****************************************************************************/
void native_realloc(VirtualMachine & vm, VMNativeCallStack & stack) {
	void *ptr = stack.readPtr<void>();
	unsigned int size = stack.read<unsigned int>();
	
	void *ret = realloc(ptr, size);
	
	vm.pushValue(&ret, REGISTER_SIZE);
}


/*****************************************************************************
 * extern void abort(void);
 *****************************************************************************/
void native_abort(VirtualMachine & vm, VMNativeCallStack & stack) {
	abort();
}

/*****************************************************************************
 * extern void *memcpy(void *dest, const void *src, size_t n);
 *****************************************************************************/
void native_memcpy(VirtualMachine & vm, VMNativeCallStack & stack);


/*****************************************************************************
 * extern char *strcpy(char *dest, const char *src);
 *****************************************************************************/
void native_strcpy(VirtualMachine & vm, VMNativeCallStack & stack) {
	char *dest = stack.readPtr<char>();
	const char *src = stack.readPtr<const char>();
	
	char *ret = strcpy(dest, src);
	
	vm.pushValue(&ret, REGISTER_SIZE);
}

/*****************************************************************************
 * extern char *strncpy(char *dest, const char *src, size_t n);
 *****************************************************************************/
void native_strncpy(VirtualMachine & vm, VMNativeCallStack & stack) {
	char *dest = stack.readPtr<char>();
	const char *src = stack.readPtr<const char>();
	unsigned int size = stack.read<unsigned int>();
	
	char *ret = strncpy(dest, src, size);
	
	vm.pushValue(&ret, REGISTER_SIZE);
}

/*****************************************************************************
 * extern char *strcat(char *dest, const char *src);
 *****************************************************************************/
void native_strcat(VirtualMachine & vm, VMNativeCallStack & stack) {
	char *dest = stack.readPtr<char>();
	const char *src = stack.readPtr<const char>();
	
	char *ret = strcat(dest, src);
	
	vm.pushValue(&ret, REGISTER_SIZE);
}

/*****************************************************************************
 * extern char *strncat(char *dest, const char *src, size_t n);
 *****************************************************************************/
void native_strncat(VirtualMachine & vm, VMNativeCallStack & stack) {
	char *dest = stack.readPtr<char>();
	const char *src = stack.readPtr<const char>();
	unsigned int size = stack.read<unsigned int>();
	
	char *ret = strncat(dest, src, size);
	
	vm.pushValue(&ret, REGISTER_SIZE);
}

/*****************************************************************************
 * size_t strlen(const char *s);
 *****************************************************************************/
void native_strlen(VirtualMachine & vm, VMNativeCallStack & stack) {
	const char *s = stack.readPtr<const char>();
	
	unsigned int ret = strlen(s);
	
	vm.pushValue(&ret, sizeof(unsigned int));
}

/*****************************************************************************
 * Auxiliar functions
 *****************************************************************************/
static int print_int(FILE *fp, VMNativeCallStack & stack, bool l) {
	if (!l) return fprintf(fp, "%d", stack.read<int>());
	return fprintf(fp, "%Ld", stack.read<long long int>());
}

static int print_uint(FILE *fp, VMNativeCallStack & stack, bool l) {
	if (!l) return fprintf(fp, "%u", stack.read<unsigned int>());
	return fprintf(fp, "%Lu", stack.read<unsigned long long int>());
}

static int print_char(FILE *fp, VMNativeCallStack & stack, bool l) {
	return fprintf(fp, "%c", stack.read<char>());
}

static int print_float(FILE *fp, VMNativeCallStack & stack, bool l) {
	if (!l) return fprintf(fp, "%f", stack.read<float>());
	return fprintf(fp, "%lf", stack.read<double>());
}

static int print_ptr(FILE *fp, VMNativeCallStack & stack, bool l) {
	return fprintf(fp, "%p", stack.readPtr<void>());
}

static int print_hexa(FILE *fp, VMNativeCallStack & stack, bool l) {
	if (!l) return fprintf(fp, "%x", stack.read<int>());
	return fprintf(fp, "%Lx", stack.read<long long int>());
}

static int print_hexa_cap(FILE *fp, VMNativeCallStack & stack, bool l) {
	if (!l) return fprintf(fp, "%X", stack.read<int>());
	return fprintf(fp, "%LX", stack.read<long long int>());
}

static int print_str(FILE *fp, VMNativeCallStack & stack, bool l) {
	return fprintf(fp, "%s", stack.readPtr<const char>());
}

static void scan_int(FILE *fp, VMNativeCallStack & stack, bool l) {
	int x; // just make gcc happy
	
	if (!l) x = fscanf(fp, "%d", stack.readPtr<int>());
	else x = fscanf(fp, "%Ld", stack.readPtr<long long int>());
}

static void scan_uint(FILE *fp, VMNativeCallStack & stack, bool l) {
	int x; // just make gcc happy
	
	if (!l) x = fscanf(fp, "%u", stack.readPtr<unsigned int>());
	else x = fscanf(fp, "%Lu", stack.readPtr<unsigned long long int>());
}

static void scan_char(FILE *fp, VMNativeCallStack & stack, bool l) {
	int x; // just make gcc happy
	
	x = fscanf(fp, "%c", stack.readPtr<char>());
}

static void scan_float(FILE *fp, VMNativeCallStack & stack, bool l) {
	int x; // just make gcc happy
	
	if (!l) x = fscanf(fp, "%f", stack.readPtr<float>());
	else x = fscanf(fp, "%lf", stack.readPtr<double>());
}

static void scan_ptr(FILE *fp, VMNativeCallStack & stack, bool l) {
	int x; // just make gcc happy
	
	x = fscanf(fp, "%p", stack.readPtr<void *>());
}

static void scan_hexa(FILE *fp, VMNativeCallStack & stack, bool l) {
	int x; // just make gcc happy
	
	if (!l) x = fscanf(fp, "%x", stack.readPtr<int>());
	else x = fscanf(fp, "%Lx", stack.readPtr<long long int>());
}

static void scan_hexa_cap(FILE *fp, VMNativeCallStack & stack, bool l) {
	int x; // just make gcc happy
	
	if (!l) x = fscanf(fp, "%X", stack.readPtr<int>());
	else x = fscanf(fp, "%LX", stack.readPtr<long long int>());
}

static void scan_str(FILE *fp, VMNativeCallStack & stack, bool l) {
	int x; // just make gcc happy
	
	x = fscanf(fp, "%s", stack.readPtr<char>());
}
