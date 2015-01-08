#include "68kCPU.h"
#include <stdlib.h>
#include <stdio.h>
#include <Windows.h>

void asl_cmd(CPU68K *cpu,short Opcode,InstructionPtr instrptr)
{
}
void asr_cmd(CPU68K *cpu,short Opcode,InstructionPtr instrptr)
{
}
void lsl_cmd(CPU68K *cpu,short Opcode,InstructionPtr instrptr)
{
}
void lsr_cmd(CPU68K *cpu,short Opcode,InstructionPtr instrptr)
{
}

void rod_cmd(CPU68K *cpu,short Opcode,InstructionPtr instrptr)
{
	wchar_t OutputString[100] = {0};
	//calculate extra data
	short InvMask = ~instrptr->Mask;
	short InstrData = Opcode&InvMask;

	short Cnt = (InstrData&0x0E00)>>9;
	short direction = (InstrData&0x0100)>8;
	short size = (InstrData&0x00C0)>>6;
	short ir = (InstrData&0x0020)>>5;
	short Reg = (InstrData&0x0003);



}
void roxl_cmd(CPU68K *cpu,short Opcode,InstructionPtr instrptr)
{
}
void roxr_cmd(CPU68K *cpu,short Opcode,InstructionPtr instrptr)
{
}


void swap_cmd(CPU68K *cpu,short Opcode,InstructionPtr instrptr)
{
	 wchar_t OutputString[100] = {0};
	//calculate extra data
	short InvMask = ~instrptr->Mask;
	short InstrData = Opcode&InvMask;

	short DestReg = (InstrData&0x0003);

	cpu->ClearCarryFlag();
	cpu->ClearOverflowFlag();
	cpu->ClearNegativeFlag();
	cpu->ClearZeroFlag();


	unsigned int Data = cpu->DataRegisterRead(DestReg);
	short tophalf = (Data&0xFF00)>>8;
	unsigned int Result = Data<<8 | tophalf;


	swprintf_s(OutputString,100,L"\tSWAP: 0x%X -> 0x%X\n",Data,Result);
	OutputDebugString(OutputString);

	cpu->DataRegisterWrite(DestReg,Result);
	if(Result == 0)
		cpu->SetZeroFlag();

	if(Result>0x7FFFFFFF)
		cpu->SetNegativeFlag();
}