//#include "box.h"
//
//#define DOWN 32
//#define UP 32
//
//PVOID GrabSSN
//(
//	IN PVOID FuncAddr,
//	OUT DWORD64* SyscallNumber,
//	OUT INT_PTR* SyscallInstr
//)
//
//{
//
//	// mov r10, rcx
//	// mov rcx, [SSN]
//	if (*((PBYTE)FuncAddr) == 0x4c
//		&& *((PBYTE)FuncAddr + 1) == 0x8b
//		&& *((PBYTE)FuncAddr + 2) == 0xd1
//		&& *((PBYTE)FuncAddr + 3) == 0xb8
//		&& *((PBYTE)FuncAddr + 6) == 0x00
//		&& *((PBYTE)FuncAddr + 7) == 0x00)
//	{
//		BYTE high = *((PBYTE)FuncAddr + 5);
//		BYTE low = *((PBYTE)FuncAddr + 4);
//
//		DWORD64 SSN = (high << 8) | low;
//		*SyscallNumber = SSN;
//		for (DWORD i = 0; i < 32; i++)
//		{
//			if (*((PBYTE)FuncAddr + i) == 0x0F &&
//				*((PBYTE)FuncAddr + i + 1) == 0x05)
//			{
//				*SyscallInstr = (INT_PTR)FuncAddr + i;
//				return FuncAddr;
//			}
//		}
//	}
//
//	return NULL;
//
//}
//
//PVOID SSNUnhook
//(
//	IN PVOID FuncAddr,
//	IN DWORD64* SyscallNumber,
//	IN INT_PTR* SyscallInstr
//)
//
//{
//
//	for (DWORD x = 0; x < 500; x++)
//	{
//		if (*((PBYTE)FuncAddr + x * DOWN) == 0x4c
//			&& *((PBYTE)FuncAddr + 1 + x * DOWN) == 0x8b
//			&& *((PBYTE)FuncAddr + 2 + x * DOWN) == 0xd1
//			&& *((PBYTE)FuncAddr + 3 + x * DOWN) == 0xb8
//			&& *((PBYTE)FuncAddr + 6 + x * DOWN) == 0x00
//			&& *((PBYTE)FuncAddr + 7 + x * DOWN) == 0x00)
//		{
//			BYTE high = *((PBYTE)FuncAddr + 5 + x * DOWN);
//			BYTE low = *((PBYTE)FuncAddr + 4 + x * DOWN);
//
//			DWORD64 SSN = ((high << 8) | low) - x;
//			*SyscallNumber = SSN;
//			for (DWORD i = 0; i < 32; i++)
//			{
//				if (*((PBYTE)FuncAddr + i) == 0x0F &&
//					*((PBYTE)FuncAddr + i + 1) == 0x05)
//				{
//					*SyscallInstr = (INT_PTR)FuncAddr + i;
//					return FuncAddr;
//				}
//			}
//		}
//
//		if (*((PBYTE)FuncAddr + x * UP) == 0x4c
//			&& *((PBYTE)FuncAddr + 1 + x * UP) == 0x8b
//			&& *((PBYTE)FuncAddr + 2 + x * UP) == 0xd1
//			&& *((PBYTE)FuncAddr + 3 + x * UP) == 0xb8
//			&& *((PBYTE)FuncAddr + 6 + x * UP) == 0x00
//			&& *((PBYTE)FuncAddr + 7 + x * UP) == 0x00)
//		{
//			BYTE high = *((PBYTE)FuncAddr + 5 + x * UP);
//			BYTE low = *((PBYTE)FuncAddr + 4 + x * UP);
//
//			DWORD64 SSN = ((high << 8) | low) + x;
//			*SyscallNumber = SSN;
//			for (DWORD i = 0; i < 32; i++)
//			{
//				if (*((PBYTE)FuncAddr + i) == 0x0F &&
//					*((PBYTE)FuncAddr + i + 1) == 0x05)
//				{
//					*SyscallInstr = (INT_PTR)FuncAddr + i;
//					return FuncAddr;
//				}
//			}
//		}
//	}
//
//	return NULL;
//
//}
//
//BOOL relative_jmp(IN PVOID FuncAddr)
//{
//
//		for (DWORD i = 0; i < 32; i++)
//		{
//			if (*((PBYTE)FuncAddr + i) == 0xe9)
//				return TRUE; // found jmp instruction
//		}
//
//	return FALSE;
//}
//
//BOOL absolute_jmp(IN PVOID FuncAddr)
//{
//
//	unsigned char jmp_stub[] = {
//	0xFF, 0x25 // jmp qword ptr...
//	};
//
//	if (memcmp(FuncAddr, jmp_stub, sizeof(jmp_stub)) != 0)
//		return FALSE; // no absolute_jmp
//
//	INT32 Hookadr = *(INT32*)((PBYTE)FuncAddr + 2);
//	PBYTE ptr = (PBYTE)FuncAddr + 6 + Hookadr;
//
//	PVOID target = *(PVOID*)ptr;
//
//	return TRUE;
//}