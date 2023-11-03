#ifndef NATIVE_FUNCTIONS_H
#define NATIVE_FUNCTIONS_H

class VirtualMachine;
class VMNativeCallStack;

/*****************************************************************************
 * assert.h
 *****************************************************************************/
void native___assert_fail(VirtualMachine & vm, VMNativeCallStack & stack);

/*****************************************************************************
 * math.h
 *****************************************************************************/
void native_acos(VirtualMachine & vm, VMNativeCallStack & stack);
void native_asin(VirtualMachine & vm, VMNativeCallStack & stack);
void native_atan(VirtualMachine & vm, VMNativeCallStack & stack);
void native_atan2(VirtualMachine & vm, VMNativeCallStack & stack);
void native_ceil(VirtualMachine & vm, VMNativeCallStack & stack);
void native_cos(VirtualMachine & vm, VMNativeCallStack & stack);
void native_cosh(VirtualMachine & vm, VMNativeCallStack & stack);
void native_fabs(VirtualMachine & vm, VMNativeCallStack & stack);
void native_floor(VirtualMachine & vm, VMNativeCallStack & stack);
void native_fmod(VirtualMachine & vm, VMNativeCallStack & stack);
void native_log(VirtualMachine & vm, VMNativeCallStack & stack);
void native_log10(VirtualMachine & vm, VMNativeCallStack & stack);
void native_pow(VirtualMachine & vm, VMNativeCallStack & stack);
void native_sin(VirtualMachine & vm, VMNativeCallStack & stack);
void native_sinh(VirtualMachine & vm, VMNativeCallStack & stack);
void native_sqrt(VirtualMachine & vm, VMNativeCallStack & stack);
void native_tan(VirtualMachine & vm, VMNativeCallStack & stack);
void native_tanh(VirtualMachine & vm, VMNativeCallStack & stack);

/*****************************************************************************
 * stdio.h
 *****************************************************************************/
void native_printf(VirtualMachine & vm, VMNativeCallStack & stack);
void native_fprintf(VirtualMachine & vm, VMNativeCallStack & stack);

void native_scanf(VirtualMachine & vm, VMNativeCallStack & stack);
void native_fscanf(VirtualMachine & vm, VMNativeCallStack & stack);

void native_fgetc (VirtualMachine & vm, VMNativeCallStack & stack);
void native_getc (VirtualMachine & vm, VMNativeCallStack & stack);

void native_getchar(VirtualMachine & vm, VMNativeCallStack & stack);

void native_fopen(VirtualMachine & vm, VMNativeCallStack & stack);
void native_fclose(VirtualMachine & vm, VMNativeCallStack & stack);

void native_fflush(VirtualMachine & vm, VMNativeCallStack & stack);

void native___get_stdin(VirtualMachine & vm, VMNativeCallStack & stack);
void native___get_stdout(VirtualMachine & vm, VMNativeCallStack & stack);
void native___get_stderr(VirtualMachine & vm, VMNativeCallStack & stack);

/*****************************************************************************
 * stdlib.h
 *****************************************************************************/
void native_calloc(VirtualMachine & vm, VMNativeCallStack & stack);
void native_malloc(VirtualMachine & vm, VMNativeCallStack & stack);
void native_free(VirtualMachine & vm, VMNativeCallStack & stack);
void native_realloc(VirtualMachine & vm, VMNativeCallStack & stack);
void native_abort(VirtualMachine & vm, VMNativeCallStack & stack);

/*****************************************************************************
 * string.h
 *****************************************************************************/
void native_memcpy(VirtualMachine & vm, VMNativeCallStack & stack);
void native_strcpy(VirtualMachine & vm, VMNativeCallStack & stack);
void native_strncpy(VirtualMachine & vm, VMNativeCallStack & stack);
void native_strcat(VirtualMachine & vm, VMNativeCallStack & stack);
void native_strncat(VirtualMachine & vm, VMNativeCallStack & stack);
void native_strlen(VirtualMachine & vm, VMNativeCallStack & stack);

#endif
