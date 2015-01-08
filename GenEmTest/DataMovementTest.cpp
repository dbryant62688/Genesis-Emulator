#include "stdafx.h"
#include "..\CPU68K\68KCPU.h"

using namespace System;
using namespace System::Text;
using namespace System::Collections::Generic;
using namespace	Microsoft::VisualStudio::TestTools::UnitTesting;

namespace GenEmTest
{
	[TestClass]
	public ref class DataMovementTest
	{
	public: 
		[TestMethod]
		void moveTest()
		{

			//test if the move command functions correctly

			CPU68K *mcpu = new CPU68K;
			//Create ROM Area
			unsigned char RomArea[] = {0x20,0x01};	//Move.b (A1)+ to D0 
			unsigned int ExpectedValue = 0x1234;
			
			
			//Initialize the CPU with a specific rom area
			mcpu->Initialize((unsigned int)&RomArea[0]);

			//Set up Registers to Known values
			mcpu->DataRegisterWrite(0,0x555);
			mcpu->DataRegisterWrite(1,0x1234);

			//Run the Test Instruction
			short Opcode = mcpu->FetchInstruction();
			InstructionPtr instr = mcpu->DecodeInstruction(Opcode);
			mcpu->ExecuteInstruction(Opcode,instr);

			//Now lets check to see of the value of 
			unsigned int ActualValue = mcpu->DataRegisterRead(0);

			Assert::AreEqual<unsigned int>(ExpectedValue,ActualValue);
			delete mcpu;
		}
		/*[TestMethod]
		void movepTest()
		{

			//test if the movep command functions correctly
			PU68K *mcpu = new CPU68K;
			//Create ROM Area
			unsigned char RomArea[] = {0x10,0x19,0x34,0x56,0x78,0x12};	//Move.b (A1)+ to D0 
			unsigned int ExpectedValue = 0x04;
			
			//Initialize the CPU with a specific rom area
			mcpu->Initialize((unsigned int)&RomArea[0]);

			//Set up Registers to Known values
			mcpu->DataRegisterWrite(0,0x555);
			mcpu->AddressRegisterWrite(1,0x03);

			//Run the Test Instruction
			short Opcode = mcpu->FetchInstruction();
			InstructionPtr instr = mcpu->DecodeInstruction(Opcode);
			mcpu->ExecuteInstruction(Opcode,instr);

			//Now lets check to see of the value of 
			unsigned int ActualValue = mcpu->AddressRegisterRead(1);

			Assert::AreEqual<unsigned int>(ExpectedValue,ActualValue);
			delete mcpu;
		}*/
		[TestMethod]
		void moveqnegTest()
		{

			//test if the moveq command functions correctly
			CPU68K *mcpu = new CPU68K;
			//Create ROM Area
			unsigned char RomArea[] = {0x70,0xFF};	//Moveq #0xFF to D0 
			unsigned int ExpectedValue = 0xFFFFFFFF;
			//Initialize the CPU with a specific rom area
			mcpu->Initialize((unsigned int)&RomArea[0]);

			//Set up Registers to Known values
			mcpu->DataRegisterWrite(0,0x555);
			

			//Run the Test Instruction
			short Opcode = mcpu->FetchInstruction();
			InstructionPtr instr = mcpu->DecodeInstruction(Opcode);
			mcpu->ExecuteInstruction(Opcode,instr);

			//Now lets check to see of the value of 
			unsigned int ActualValue = mcpu->DataRegisterRead(0);

			Assert::AreEqual<unsigned int>(ExpectedValue,ActualValue);
			delete mcpu;


		}
		[TestMethod]
		void moveqposTest()
		{

			//test if the moveq command functions correctly
			CPU68K *mcpu = new CPU68K;
			//Create ROM Area
			unsigned char RomArea[] = {0x70,0x7F};	//Moveq #0x7F to D0 
			unsigned int ExpectedValue = 0x7F;
			//Initialize the CPU with a specific rom area
			mcpu->Initialize((unsigned int)&RomArea[0]);

			//Set up Registers to Known values
			mcpu->DataRegisterWrite(0,0x555);
			

			//Run the Test Instruction
			short Opcode = mcpu->FetchInstruction();
			InstructionPtr instr = mcpu->DecodeInstruction(Opcode);
			mcpu->ExecuteInstruction(Opcode,instr);

			//Now lets check to see of the value of 
			unsigned int ActualValue = mcpu->DataRegisterRead(0);

			Assert::AreEqual<unsigned int>(ExpectedValue,ActualValue);
			delete mcpu;


		}
		[TestMethod]
		void moveawordposTest()
		{

			//test if the movea command functions correctly
			CPU68K *mcpu = new CPU68K;
			//Create ROM Area
			unsigned char RomArea[] = {0x30,0x40};	//Moveq #0x7F to D0 
			unsigned int ExpectedValue = 0x555;
			//Initialize the CPU with a specific rom area
			mcpu->Initialize((unsigned int)&RomArea[0]);

			//Set up Registers to Known values
			mcpu->DataRegisterWrite(0,0x555);
			

			//Run the Test Instruction
			short Opcode = mcpu->FetchInstruction();
			InstructionPtr instr = mcpu->DecodeInstruction(Opcode);
			mcpu->ExecuteInstruction(Opcode,instr);

			//Now lets check to see of the value of 
			unsigned int ActualValue = mcpu->AddressRegisterRead(0);

			Assert::AreEqual<unsigned int>(ExpectedValue,ActualValue);
			delete mcpu;


		}
		[TestMethod]
		void moveawordnegTest()
		{

			//test if the movea command functions correctly
			CPU68K *mcpu = new CPU68K;
			//Create ROM Area
			unsigned char RomArea[] = {0x30,0x40};	//Moveq #0x7F to D0 
			unsigned int ExpectedValue = 0xFFFFFF55;
			//Initialize the CPU with a specific rom area
			mcpu->Initialize((unsigned int)&RomArea[0]);

			//Set up Registers to Known values
			mcpu->DataRegisterWrite(0,0xFF55);
			

			//Run the Test Instruction
			short Opcode = mcpu->FetchInstruction();
			InstructionPtr instr = mcpu->DecodeInstruction(Opcode);
			mcpu->ExecuteInstruction(Opcode,instr);

			//Now lets check to see of the value of 
			unsigned int ActualValue = mcpu->AddressRegisterRead(0);

			Assert::AreEqual<unsigned int>(ExpectedValue,ActualValue);
			delete mcpu;


		}
		[TestMethod]
		void movealongTest()
		{

			//test if the movea command functions correctly
			CPU68K *mcpu = new CPU68K;
			//Create ROM Area
			unsigned char RomArea[] = {0x20,0x40};	//Moveq #0x7F to D0 
			unsigned int ExpectedValue = 0x12349555;
			//Initialize the CPU with a specific rom area
			mcpu->Initialize((unsigned int)&RomArea[0]);

			//Set up Registers to Known values
			mcpu->DataRegisterWrite(0,0x12349555);
			

			//Run the Test Instruction
			short Opcode = mcpu->FetchInstruction();
			InstructionPtr instr = mcpu->DecodeInstruction(Opcode);
			mcpu->ExecuteInstruction(Opcode,instr);

			//Now lets check to see of the value of 
			unsigned int ActualValue = mcpu->AddressRegisterRead(0);

			Assert::AreEqual<unsigned int>(ExpectedValue,ActualValue);
			delete mcpu;


		}
	};
}
