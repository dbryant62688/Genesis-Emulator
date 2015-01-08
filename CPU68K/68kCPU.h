#ifndef __68KCPU_H_
#define __68KCPU_H_

#include "MemoryRegion.h"

class CPU68K;

#define NULL 0
typedef struct Instruction
{
	wchar_t Name[16];
	short Opcode;
	short Mask;
	void (*ExecutionPtr)(CPU68K *cpu,short Op,Instruction* instrptr);
}Instruction,*InstructionPtr;




bool CheckOpcode(short Op,Instruction instr);

class CPU68K
{
public:
	void Initialize(unsigned int romaddr);
	void Reset();
	short FetchInstruction();
	InstructionPtr DecodeInstruction(short opcode);
	void ExecuteInstruction(short Op,InstructionPtr instruction);


	unsigned char  MemoryReadByte(unsigned int Address);
	unsigned short MemoryReadWord(unsigned int Address);
	unsigned int   MemoryReadLong(unsigned int Address);

	void MemoryWriteByte(unsigned int Address, unsigned char Value);
	void MemoryWriteWord(unsigned int Address, unsigned short Value);
	void MemoryWriteLong(unsigned int Address, unsigned int Value);

	void DataRegisterWrite(int n, unsigned int value);
	unsigned int DataRegisterRead(int n);

	void AddressRegisterWrite(int n,unsigned int value);
	unsigned int AddressRegisterRead(int n);

	void StatusRegisterWrite(unsigned short value,unsigned short flag = 0x00FF);
	unsigned short StatusRegisterRead();

	void ProgramCounterWrite(unsigned int value);
	unsigned int ProgramCounterRead();
	void ProgramCounterIncrement();
	void ProgramCounterDecrement();

	void StackPointerWrite(unsigned int value);
	unsigned int StackPointerRead();
	
	char FetchByte();
	short FetchWord();
	unsigned int FetchLong();
	unsigned int GetOperandUsingEffectiveAddress(char AddrMode,char AddrReg,char OpSize,bool SignExtend = false);
	unsigned int GetEffectiveAddress(char AddrMode,char AddrReg,char OpSize);
	void SetOperandUsingEffectiveAddress(char AddrMode,char AddrReg,char OpSize,unsigned int Operand);



	void SetZeroFlag();
	void ClearZeroFlag();
	void SetCarryFlag();
	void ClearCarryFlag();
	void SetNegativeFlag();
	void ClearNegativeFlag();
	void SetExtendFlag();
	void ClearExtendFlag();
	void SetOverflowFlag();
	void ClearOverflowFlag();

protected:
	void IntializeInstructionSet();
	

protected:
	unsigned int DataRegisterBank[8];
	unsigned int AddressRegisterBank[7];
	unsigned int StackPointer;
	unsigned int ProgramCounter;
	unsigned short ConditionCodeRegister;
	unsigned char internalramaddr[0xFFFF];
	InstructionPtr InstructionList;

	unsigned int BaseAddress;

	MemoryMap Memory;
};
#endif
