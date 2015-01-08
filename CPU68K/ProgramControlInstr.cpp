#include "68kCPU.h"
#include <stdlib.h>
#include <stdio.h>
#include <Windows.h>


//Test Operand instructions
void tst_cmd(CPU68K *cpu,short Opcode,InstructionPtr instrptr)
{
	wchar_t OutputString[100] = {0};
	//calculate extra data
	short InvMask = ~instrptr->Mask;
	short InstrData = Opcode&InvMask;

	short size = (InstrData & 0x00C0)>>6;
	short SrcAddrMode = (InstrData&0x0038)>>3;
	short SrcXn =		(InstrData&0x0003);


	cpu->ClearCarryFlag();
	cpu->ClearOverflowFlag();
	cpu->ClearNegativeFlag();
	cpu->ClearZeroFlag();

	unsigned int Operand = cpu->GetOperandUsingEffectiveAddress(SrcAddrMode,SrcXn,size);
	swprintf_s(OutputString,100,L"\tTST: Testing if Operand 0x%X == 0\n",Operand);
	OutputDebugString(OutputString);
	if(Operand == 0)
	{
		//This test did pass so set the CCR accordingly
		cpu->SetZeroFlag();
	}
	else if(Operand&0x80000000 ==0x80000000) 
	{
		//The operand is negative
		cpu->SetNegativeFlag();
	}


}

void ftst_cmd(CPU68K *cpu,short Opcode,InstructionPtr instrptr)
{

}


//Integer and floating point Conditional

void bcc_cmd(CPU68K *cpu,short Opcode,InstructionPtr instrptr)
{
	wchar_t OutputString[100] = {0};
	//calculate extra data
	short InvMask = ~instrptr->Mask;
	short InstrData = Opcode & InvMask;

	char Condition = (InstrData&0x0F00)>>8;
	unsigned char DisplacementType = (InstrData&0x00FF);
	int Displacement = 0;

	if(DisplacementType == 0)
		Displacement = cpu->FetchWord()-2;
	else if(DisplacementType == 0xff)
		Displacement = cpu->FetchLong()-4;
	else
		Displacement = DisplacementType;

	bool ConditionResult = false;
	unsigned short Status = cpu->StatusRegisterRead();

	//Now lets determine what happens based on the condition
	switch(Condition)
	{
		case 0:	//TRUE
		case 1:	//FALSE
		case 2: //Higher
		case 3: //lower or same
		case 4:	//Carry Clear
			//Lets check the condition code register to see if the C bit is not set
				swprintf_s(OutputString,100,L"\tBcc: checking if Carry bit is clear \n");
				OutputDebugString(OutputString);
				ConditionResult = (((Status&0x0001)) == 0);
				break;
		case 5: //Carry Set
				//Lets check the condition code register to see if the C bit is set
				swprintf_s(OutputString,100,L"\tBcs: checking if Carry bit is set \n");
				OutputDebugString(OutputString);
				ConditionResult = (((Status&0x0001)) == 1);
			break;
		case 6: //Not Equal
				//Lets check the condition code register to see if the Z bit is not set
				swprintf_s(OutputString,100,L"\tBne: checking if Equal bit is clear \n");
				OutputDebugString(OutputString);
				ConditionResult = (((Status&0x0004)>>2) == 0);
			break;
		case 7: //Equal
				//Lets check the condition code register to see if the Z bit is set
				swprintf_s(OutputString,100,L"\tBe: checking if Z bit is set \n");
				OutputDebugString(OutputString);
				ConditionResult = (((Status&0x0004)>>2) == 1);
			break;
		case 8: //Overflow Clear
				//Lets check the condition code register to see if the V bit is not set
				swprintf_s(OutputString,100,L"\tBvc: checking if Overflow bit is clear \n");
				OutputDebugString(OutputString);
				ConditionResult = (((Status&0x0002)>>1) == 0);
				break;
		case 9: //Overflow Set
			//Lets check the condition code register to see if the V bit is set
				swprintf_s(OutputString,100,L"\tBvs: checking if Overflow bit is set \n");
				OutputDebugString(OutputString);
				ConditionResult = (((Status&0x0002)>>1) == 1);
				break;
		case 10: //Plus
			//Lets check the condition code register to see if the N bit is not set
				swprintf_s(OutputString,100,L"\tBpl: checking if Negative bit is clear \n");
				OutputDebugString(OutputString);
				ConditionResult = (((Status&0x0008)>>3) == 0);
				break;
		case 11: //Minus
			//Lets check the condition code register to see if the N bit is set
				swprintf_s(OutputString,100,L"\tBmi: checking if Negative bit is set \n");
				OutputDebugString(OutputString);
				ConditionResult = (((Status&0x0008)>>3) == 1);
				break;
		case 12: //Greater or Equal
		case 13: //Less tham
		case 14: //greater than
		case 15: //less or Equal
			break;
		
	}

	if(ConditionResult)
	{
		//Branch condition passed
		int NewAddress =cpu->ProgramCounterRead() + Displacement;
		swprintf_s(OutputString,100,L"\tBranching to Address 0x%X\n",NewAddress);
		OutputDebugString(OutputString);
		cpu->ProgramCounterWrite(NewAddress);
	}

	//
}

void fbcc_cmd(CPU68K *cpu,short Opcode,InstructionPtr instrptr)
{
}
void dbcc_cmd(CPU68K *cpu,short Opcode,InstructionPtr instrptr)
{
	wchar_t OutputString[100] = {0};
	//calculate extra data
	short InvMask = ~instrptr->Mask;
	short InstrData = Opcode & InvMask;

	char Condition = (InstrData&0x0F00)>>8;
	unsigned char DataReg = (InstrData&0x0003);
	int Displacement = 0;
	Displacement = cpu->FetchWord()-2;

	bool ConditionResult = true;
	unsigned short Status = cpu->StatusRegisterRead();

	//Now lets determine what happens based on the condition
	switch(Condition)
	{
		case 0:	//TRUE
		case 1:	//FALSE
				swprintf_s(OutputString,100,L"\tDBra: \n");
				OutputDebugString(OutputString);
				ConditionResult = false;
				break;
		case 2: //Higher
		case 3: //lower or same
		case 4:	//Carry Clear
			//Lets check the condition code register to see if the C bit is not set
				swprintf_s(OutputString,100,L"\tDBcc: checking if Carry bit is clear \n");
				OutputDebugString(OutputString);
				ConditionResult = (((Status&0x0001)) == 0);
				break;
		case 5: //Carry Set
				//Lets check the condition code register to see if the C bit is set
				swprintf_s(OutputString,100,L"\tDBcs: checking if Carry bit is set \n");
				OutputDebugString(OutputString);
				ConditionResult = (((Status&0x0001)) == 1);
			break;
		case 6: //Not Equal
				//Lets check the condition code register to see if the Z bit is not set
				swprintf_s(OutputString,100,L"\tDBne: checking if Equal bit is clear \n");
				OutputDebugString(OutputString);
				ConditionResult = (((Status&0x0004)>>2) == 0);
			break;
		case 7: //Equal
				//Lets check the condition code register to see if the Z bit is set
				swprintf_s(OutputString,100,L"\tDBe: checking if Z bit is set \n");
				OutputDebugString(OutputString);
				ConditionResult = (((Status&0x0004)>>2) == 1);
			break;
		case 8: //Overflow Clear
				//Lets check the condition code register to see if the V bit is not set
				swprintf_s(OutputString,100,L"\tDBvc: checking if Overflow bit is clear \n");
				OutputDebugString(OutputString);
				ConditionResult = (((Status&0x0002)>>1) == 0);
				break;
		case 9: //Overflow Set
			//Lets check the condition code register to see if the V bit is set
				swprintf_s(OutputString,100,L"\tDBvs: checking if Overflow bit is set \n");
				OutputDebugString(OutputString);
				ConditionResult = (((Status&0x0002)>>1) == 1);
				break;
		case 10: //Plus
			//Lets check the condition code register to see if the N bit is not set
				swprintf_s(OutputString,100,L"\tDBpl: checking if Negative bit is clear \n");
				OutputDebugString(OutputString);
				ConditionResult = (((Status&0x0008)>>3) == 0);
				break;
		case 11: //Minus
			//Lets check the condition code register to see if the N bit is set
				swprintf_s(OutputString,100,L"\tDBmi: checking if Negative bit is set \n");
				OutputDebugString(OutputString);
				ConditionResult = (((Status&0x0008)>>3) == 1);
				break;
		case 12: //Greater or Equal
		case 13: //Less tham
		case 14: //greater than
		case 15: //less or Equal
			break;
		
	}

	if(!ConditionResult)
	{
		//Branch condition passed
		
		//Decrement the data register
		int Data = cpu->DataRegisterRead(DataReg) - 1;
		cpu->DataRegisterWrite(DataReg,Data);

		if(Data != -1)
		{
			int NewAddress =cpu->ProgramCounterRead() + Displacement;
			swprintf_s(OutputString,100,L"\tBranching to Address 0x%X , DataReg : %d,0x%X\n",NewAddress,DataReg,Data);
			OutputDebugString(OutputString);
			cpu->ProgramCounterWrite(NewAddress);
		}
	}
}
void fdbcc_cmd(CPU68K *cpu,short Opcode,InstructionPtr instrptr)
{
}
void scc_cmd(CPU68K *cpu,short Opcode,InstructionPtr instrptr)
{
}
void fscc_cmd(CPU68K *cpu,short Opcode,InstructionPtr instrptr)
{
}

//Unconditional program control instructions
void bra_cmd(CPU68K *cpu,short Opcode,InstructionPtr instrptr)
{
	wchar_t OutputString[100] = {0};
	//calculate extra data
	short InvMask = ~instrptr->Mask;
	short InstrData = Opcode & InvMask;

	char Condition = (InstrData&0x0F00)>>8;
	unsigned char DisplacementType = (InstrData&0x00FF);
	int Displacement = 0;

	if(DisplacementType == 0)
		Displacement = cpu->FetchWord()-2;
	else if(DisplacementType == 0xff)
		Displacement = cpu->FetchLong()-4;
	else
		Displacement = DisplacementType;

	
	
	int NewAddress =cpu->ProgramCounterRead() + Displacement;
	swprintf_s(OutputString,100,L"\tBRA: Branching to Address 0x%X\n",NewAddress);
	OutputDebugString(OutputString);
	cpu->ProgramCounterWrite(NewAddress);
	
}
void bsr_cmd(CPU68K *cpu,short Opcode,InstructionPtr instrptr)
{
	wchar_t OutputString[100] = {0};
	//calculate extra data
	short InvMask = ~instrptr->Mask;
	short InstrData = Opcode & InvMask;

	char Condition = (InstrData&0x0F00)>>8;
	unsigned char DisplacementType = (InstrData&0x00FF);
	int Displacement = 0;

	if(DisplacementType == 0)
		Displacement = cpu->FetchWord()-2;
	else if(DisplacementType == 0xff)
		Displacement = cpu->FetchLong()-4;
	else
		Displacement = DisplacementType;

	
	//Increment the stack pointer
	cpu->StackPointerWrite(cpu->StackPointerRead() - 4);

	//Save the Current Program Counter in the stack
	cpu->MemoryWriteLong(cpu->StackPointerRead(),cpu->ProgramCounterRead());

	//Branch to the New Address
	int NewAddress =cpu->ProgramCounterRead() + Displacement;
	swprintf_s(OutputString,100,L"\tBSR: Branching to Address 0x%X\n",NewAddress);
	OutputDebugString(OutputString);
	cpu->ProgramCounterWrite(NewAddress);
}
void jmp_cmd(CPU68K *cpu,short Opcode,InstructionPtr instrptr)
{
	wchar_t OutputString[100] = {0};
	//calculate extra data
	short InvMask = ~instrptr->Mask;
	short InstrData = Opcode&InvMask;

	short size = (InstrData & 0x00C0)>>6;
	short SrcAddrMode = (InstrData&0x0038)>>3;
	short SrcXn =		(InstrData&0x0003);

	unsigned int EA = cpu->GetEffectiveAddress(SrcAddrMode,SrcXn,2);
	swprintf_s(OutputString,100,L"\tJMP: Jumping to Address 0x%X\n",EA);
	OutputDebugString(OutputString);
	cpu->ProgramCounterWrite(EA);

}
void jsr_cmd(CPU68K *cpu,short Opcode,InstructionPtr instrptr)
{
	wchar_t OutputString[100] = {0};
	//calculate extra data
	short InvMask = ~instrptr->Mask;
	short InstrData = Opcode&InvMask;

	short size = (InstrData & 0x00C0)>>6;
	short SrcAddrMode = (InstrData&0x0038)>>3;
	short SrcXn =		(InstrData&0x0003);


	//Increment the stack pointer
	cpu->StackPointerWrite(cpu->StackPointerRead() - 4);

	//Save the Current Program Counter in the stack
	cpu->MemoryWriteLong(cpu->StackPointerRead(),cpu->ProgramCounterRead());

	//Set The Program counter to the effective
	unsigned int EA = cpu->GetEffectiveAddress(SrcAddrMode,SrcXn,2);
	swprintf_s(OutputString,100,L"\tJSR: Jumping to Address 0x%X\n",EA);
	OutputDebugString(OutputString);
	cpu->ProgramCounterWrite(EA);
}
void nop_cmd(CPU68K *cpu,short Opcode,InstructionPtr instrptr)
{
	//PC + 2 -> PC (integer pipeline sychronized)

}
void fnop_cmd(CPU68K *cpu,short Opcode,InstructionPtr instrptr)
{
	//PC + 4 -> PC (FPU pipeline sync)
	cpu->FetchWord();
}


//Returns 
void rtd_cmd(CPU68K *cpu,short Opcode,InstructionPtr instrptr)
{
	wchar_t OutputString[100] = {0};
	//calculate extra data
	short InvMask = ~instrptr->Mask;
	short InstrData = Opcode & InvMask;

	//Set the Program Counter to the whats at the top of the stack
	cpu->ProgramCounterWrite(cpu->MemoryReadLong(cpu->StackPointerRead()));
	//Decrement the stack pointer by a displacement value
	cpu->StackPointerWrite(cpu->StackPointerRead() + 4 + cpu->FetchWord());

}
void rtr_cmd(CPU68K *cpu,short Opcode,InstructionPtr instrptr)
{
	wchar_t OutputString[100] = {0};
	//calculate extra data
	short InvMask = ~instrptr->Mask;
	short InstrData = Opcode & InvMask;

	
	//Decrement the stack pointer
	cpu->StackPointerWrite(cpu->StackPointerRead() + 2);

	//Set the Program Counter to the whats at the top of the stack
	cpu->ProgramCounterWrite(cpu->MemoryReadLong(cpu->StackPointerRead()));

	//Decrement the stack pointer
	cpu->StackPointerWrite(cpu->StackPointerRead() + 4);

}
void rts_cmd(CPU68K *cpu,short Opcode,InstructionPtr instrptr)
{
	wchar_t OutputString[100] = {0};
	//calculate extra data
	short InvMask = ~instrptr->Mask;
	short InstrData = Opcode & InvMask;

	//Set the Program Counter to the whats at the top of the stack
	cpu->ProgramCounterWrite(cpu->MemoryReadLong(cpu->StackPointerRead()));
	//Decrement the stack pointer
	cpu->StackPointerWrite(cpu->StackPointerRead() + 4);
}