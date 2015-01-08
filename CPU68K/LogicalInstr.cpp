#include "68kCPU.h"
#include <stdlib.h>
#include <stdio.h>
#include <Windows.h>

void and_cmd(CPU68K *cpu,short Opcode,InstructionPtr instrptr)
{
	wchar_t OutputString[100] = {0};
	//calculate extra data
	short InvMask = ~instrptr->Mask;
	short InstrData = Opcode&InvMask;

	short Reg = (InstrData & 0x0E00)>>9;
	short Opmode = (InstrData & 0x01C0)>>6;
	short AddrMode	= (InstrData&0x0038)>>3;
	short Xn		= (InstrData&0x0003);

	short size = Opmode & 0x3;
	short direction = (Opmode & 0x4)>>2;

	cpu->ClearCarryFlag();
	cpu->ClearOverflowFlag();
	cpu->ClearNegativeFlag();
	cpu->ClearZeroFlag();


	unsigned int SrcData;
	unsigned int DestData;
	unsigned int Result;

	if(direction == 0)
	{
		SrcData = cpu->GetOperandUsingEffectiveAddress(AddrMode,Xn,size);
		DestData = cpu->DataRegisterRead(Reg);
	}
	else
	{
		SrcData = cpu->DataRegisterRead(Reg);
		DestData = cpu->GetOperandUsingEffectiveAddress(AddrMode,Xn,size);
	}
	
	Result = SrcData & DestData;


	swprintf_s(OutputString,100,L"\tAND: 0x%X & 0x%X = 0x%X \n", SrcData,DestData,Result);
	OutputDebugString(OutputString);

	if(direction == 0)
		cpu->DataRegisterWrite(Reg,Result);
	else
		cpu->SetOperandUsingEffectiveAddress(AddrMode,Xn,size,Result);

	if(Result == 0)
		cpu->SetZeroFlag();

	if(Result>0x7FFFFFFF)
		cpu->SetNegativeFlag();
}
void andi_cmd(CPU68K *cpu,short Opcode,InstructionPtr instrptr)
{
	wchar_t OutputString[100] = {0};
	//calculate extra data
	short InvMask = ~instrptr->Mask;
	short InstrData = Opcode&InvMask;

	short size = (InstrData & 0x00C0)>>6;
	short DestAddrMode	= (InstrData&0x0038)>>3;
	short DestXn		=		(InstrData&0x0003);
	unsigned int ImmediateData = 0;

	if(size == 0)
		ImmediateData = cpu->FetchWord()&0x00FF;
	else if(size == 1)
		ImmediateData = cpu->FetchWord();
	else
		ImmediateData = cpu->FetchLong();


	cpu->ClearCarryFlag();
	cpu->ClearOverflowFlag();
	cpu->ClearNegativeFlag();
	cpu->ClearZeroFlag();


	unsigned int DestData = cpu->GetOperandUsingEffectiveAddress(DestAddrMode,DestXn,size);

	unsigned int Result =  DestData & ImmediateData;

	swprintf_s(OutputString,100,L"\tANDI: AND of 0x%X and 0x%x = 0x%X \n", ImmediateData,DestData,Result);
	OutputDebugString(OutputString);

	cpu->SetOperandUsingEffectiveAddress(DestAddrMode,DestXn,size,Result);

	if(Result == 0)
		cpu->SetZeroFlag();

	if(Result>0x7FFFFFFF)
		cpu->SetNegativeFlag();
}
void eor_cmd(CPU68K *cpu,short Opcode,InstructionPtr instrptr)
{
}
void eori_cmd(CPU68K *cpu,short Opcode,InstructionPtr instrptr)
{

	wchar_t OutputString[100] = {0};
	//calculate extra data
	short InvMask = ~instrptr->Mask;
	short InstrData = Opcode&InvMask;

	short size = (InstrData & 0x00C0)>>6;
	short DestAddrMode	= (InstrData&0x0038)>>3;
	short DestXn		=		(InstrData&0x0003);
	unsigned int ImmediateData = 0;

	if(size == 0)
		ImmediateData = cpu->FetchWord()&0x00FF;
	else if(size == 1)
		ImmediateData = cpu->FetchWord();
	else
		ImmediateData = cpu->FetchLong();


	cpu->ClearCarryFlag();
	cpu->ClearOverflowFlag();
	cpu->ClearNegativeFlag();
	cpu->ClearZeroFlag();


	unsigned int DestData = cpu->GetOperandUsingEffectiveAddress(DestAddrMode,DestXn,size);

	unsigned int Result =  DestData ^ ImmediateData;

	swprintf_s(OutputString,100,L"\tEORI: Eclusive or of 0x%X and 0x%x = 0x%X \n", ImmediateData,DestData,Result);
	OutputDebugString(OutputString);

	cpu->SetOperandUsingEffectiveAddress(DestAddrMode,DestXn,size,Result);

	if(Result == 0)
		cpu->SetZeroFlag();

	if(Result>0x7FFFFFFF)
		cpu->SetNegativeFlag();
	
}
void not_cmd(CPU68K *cpu,short Opcode,InstructionPtr instrptr)
{
	wchar_t OutputString[100] = {0};
	//calculate extra data
	short InvMask = ~instrptr->Mask;
	short InstrData = Opcode&InvMask;

	short size = (InstrData & 0x00C0)>>6;
	short DestAddrMode	= (InstrData&0x0038)>>3;
	short DestXn		= (InstrData&0x0003);

	cpu->ClearCarryFlag();
	cpu->ClearOverflowFlag();
	cpu->ClearNegativeFlag();
	cpu->ClearZeroFlag();


	unsigned int DestData = cpu->GetOperandUsingEffectiveAddress(DestAddrMode,DestXn,size);

	unsigned int Result =  ~DestData;

	swprintf_s(OutputString,100,L"\tNOT: NOT 0x%X = 0x%X \n", DestData,Result);
	OutputDebugString(OutputString);

	cpu->SetOperandUsingEffectiveAddress(DestAddrMode,DestXn,size,Result);

	if(Result == 0)
		cpu->SetZeroFlag();

	if(Result>0x7FFFFFFF)
		cpu->SetNegativeFlag();
}
void or_cmd(CPU68K *cpu,short Opcode,InstructionPtr instrptr)
{
	wchar_t OutputString[100] = {0};
	//calculate extra data
	short InvMask = ~instrptr->Mask;
	short InstrData = Opcode&InvMask;

	short Reg = (InstrData & 0x0E00)>>9;
	short Opmode = (InstrData & 0x01C0)>>6;
	short AddrMode	= (InstrData&0x0038)>>3;
	short Xn		= (InstrData&0x0003);

	short size = Opmode & 0x3;
	short direction = (Opmode & 0x4)>>2;

	cpu->ClearCarryFlag();
	cpu->ClearOverflowFlag();
	cpu->ClearNegativeFlag();
	cpu->ClearZeroFlag();


	unsigned int SrcData;
	unsigned int DestData;
	unsigned int Result;

	if(direction == 0)
	{
		SrcData = cpu->GetOperandUsingEffectiveAddress(AddrMode,Xn,size);
		DestData = cpu->DataRegisterRead(Reg);
	}
	else
	{
		SrcData = cpu->DataRegisterRead(Reg);
		DestData = cpu->GetOperandUsingEffectiveAddress(AddrMode,Xn,size);
	}
	
	Result = SrcData | DestData;


	swprintf_s(OutputString,100,L"\tOR: 0x%X | 0x%X = 0x%X \n", SrcData,DestData,Result);
	OutputDebugString(OutputString);

	if(direction == 0)
		cpu->DataRegisterWrite(Reg,Result);
	else
		cpu->SetOperandUsingEffectiveAddress(AddrMode,Xn,size,Result);

	if(Result == 0)
		cpu->SetZeroFlag();

	if(Result>0x7FFFFFFF)
		cpu->SetNegativeFlag();
}
void ori_cmd(CPU68K *cpu,short Opcode,InstructionPtr instrptr)
{
	wchar_t OutputString[100] = {0};
	//calculate extra data
	short InvMask = ~instrptr->Mask;
	short InstrData = Opcode&InvMask;

	short size = (InstrData & 0x00C0)>>6;
	short DestAddrMode	= (InstrData&0x0038)>>3;
	short DestXn		=		(InstrData&0x0003);
	unsigned int ImmediateData = 0;

	if(size == 0)
		ImmediateData = cpu->FetchWord()&0x00FF;
	else if(size == 1)
		ImmediateData = cpu->FetchWord();
	else
		ImmediateData = cpu->FetchLong();


	cpu->ClearCarryFlag();
	cpu->ClearOverflowFlag();
	cpu->ClearNegativeFlag();
	cpu->ClearZeroFlag();


	unsigned int DestData = cpu->GetOperandUsingEffectiveAddress(DestAddrMode,DestXn,size);

	unsigned int Result =  DestData | ImmediateData;

	swprintf_s(OutputString,100,L"\tORI: OR of 0x%X and 0x%x = 0x%X \n", ImmediateData,DestData,Result);
	OutputDebugString(OutputString);

	cpu->SetOperandUsingEffectiveAddress(DestAddrMode,DestXn,size,Result);

	if(Result == 0)
		cpu->SetZeroFlag();

	if(Result>0x7FFFFFFF)
		cpu->SetNegativeFlag();
}