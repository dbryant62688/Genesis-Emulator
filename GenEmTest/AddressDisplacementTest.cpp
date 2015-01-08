#include "stdafx.h"
#include "..\CPU68K\68KCPU.h"

using namespace System;
using namespace System::Text;
using namespace System::Collections::Generic;
using namespace	Microsoft::VisualStudio::TestTools::UnitTesting;

namespace GenEmTest
{
	[TestClass]
	public ref class AddressDisplacementTest
	{
	public: 
		[TestMethod]
		void ARInDirectAddressModeByteIncrementTest()
		{
			//THe goal here is to test if the Address Register InDirect Address with Post Increment Mode works as expected
			CPU68K *mcpu = new CPU68K;
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

		};
		[TestMethod]
		void ARInDirectAddressModeWordIncrementTest()
		{
			//THe goal here is to test if the Address Register InDirect Address Post Increment Mode works as expected
			CPU68K *mcpu = new CPU68K;
			//Create ROM Area
			unsigned char RomArea[] = {0x30,0x19,0x34,0x56,0x78,0x12};	//Move.w (A1) to D0
			unsigned int ExpectedValue = 0x05;
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

		};
		[TestMethod]
		void ARInDirectAddressModeLongIncrementTest()
		{
			//THe goal here is to test if the Address Register InDirect Address Post Increment Mode works as expected
			CPU68K *mcpu = new CPU68K;
			//Create ROM Area
			unsigned char RomArea[] = {0x20,0x19,0x34,0x56,0x78,0x12};	//Move.l (A1)+ to D0
			unsigned int ExpectedValue = 0x06;
			//Initialize the CPU with a specific rom area
			mcpu->Initialize((unsigned int)&RomArea[0]);

			//Set up Registers to Known values
			mcpu->DataRegisterWrite(0,0x555);
			mcpu->AddressRegisterWrite(1,0x02);

			//Run the Test Instruction
			short Opcode = mcpu->FetchInstruction();
			InstructionPtr instr = mcpu->DecodeInstruction(Opcode);
			mcpu->ExecuteInstruction(Opcode,instr);

			//Now lets check to see of the value of 
			unsigned int ActualValue = mcpu->AddressRegisterRead(1);

			Assert::AreEqual<unsigned int>(ExpectedValue,ActualValue);
			delete mcpu;

		};

		[TestMethod]
		void ARInDirectAddressModeByteDecrementTest()
		{
			//THe goal here is to test if the Address Register InDirect Address with Pre Decrement Mode works as expected
			CPU68K *mcpu = new CPU68K;
			//Create ROM Area
			unsigned char RomArea[] = {0x10,0x21,0x34,0x56,0x78,0x12,056,0x67,0x11,0x22,0x33,0x4f};	//Move.b -(A1) to D0 
			unsigned int ExpectedValue = 0x06;
			//Initialize the CPU with a specific rom area
			mcpu->Initialize((unsigned int)&RomArea[0]);

			//Set up Registers to Known values
			mcpu->DataRegisterWrite(0,0x555);
			mcpu->AddressRegisterWrite(1,0x07);

			//Run the Test Instruction
			short Opcode = mcpu->FetchInstruction();
			InstructionPtr instr = mcpu->DecodeInstruction(Opcode);
			mcpu->ExecuteInstruction(Opcode,instr);

			//Now lets check to see of the value of 
			unsigned int ActualValue = mcpu->AddressRegisterRead(1);

			Assert::AreEqual<unsigned int>(ExpectedValue,ActualValue);
			delete mcpu;

		};
		[TestMethod]
		void ARInDirectAddressModeWordDecrementTest()
		{
			//THe goal here is to test if the Address Register InDirect Address with Pre Decrement Mode works as expected
			CPU68K *mcpu = new CPU68K;
			//Create ROM Area
			unsigned char RomArea[] = {0x30,0x21,0x34,0x56,0x78,0x12,056,0x67,0x11,0x22,0x33,0x4f};	//Move.w -(A1) to D0 
			unsigned int ExpectedValue = 0x05;
			//Initialize the CPU with a specific rom area
			mcpu->Initialize((unsigned int)&RomArea[0]);

			//Set up Registers to Known values
			mcpu->DataRegisterWrite(0,0x555);
			mcpu->AddressRegisterWrite(1,0x07);

			//Run the Test Instruction
			short Opcode = mcpu->FetchInstruction();
			InstructionPtr instr = mcpu->DecodeInstruction(Opcode);
			mcpu->ExecuteInstruction(Opcode,instr);

			//Now lets check to see of the value of 
			unsigned int ActualValue = mcpu->AddressRegisterRead(1);

			Assert::AreEqual<unsigned int>(ExpectedValue,ActualValue);
			delete mcpu;

		};
		[TestMethod]
		void ARInDirectAddressModeLongDecrementTest()
		{
			//THe goal here is to test if the Address Register InDirect Address with Pre Decrement Mode works as expected
			CPU68K *mcpu = new CPU68K;
			//Create ROM Area
			unsigned char RomArea[] = {0x020,0x21,0x34,0x56,0x78,0x12,056,0x67,0x11,0x22,0x33,0x4f};	//Move.l -(A1) to D0 
			unsigned int ExpectedValue = 0x03;
			//Initialize the CPU with a specific rom area
			mcpu->Initialize((unsigned int)&RomArea[0]);

			//Set up Registers to Known values
			mcpu->DataRegisterWrite(0,0x555);
			mcpu->AddressRegisterWrite(1,0x07);

			//Run the Test Instruction
			short Opcode = mcpu->FetchInstruction();
			InstructionPtr instr = mcpu->DecodeInstruction(Opcode);
			mcpu->ExecuteInstruction(Opcode,instr);

			//Now lets check to see of the value of 
			unsigned int ActualValue = mcpu->AddressRegisterRead(1);

			Assert::AreEqual<unsigned int>(ExpectedValue,ActualValue);
			delete mcpu;

		};

		[TestMethod]
		void ARInDirectAddressModeByteDisplacementTest()
		{
			//THe goal here is to test if the Address Register InDirect Address with Displacement Mode works as expected
			CPU68K *mcpu = new CPU68K;
			//Create ROM Area
			unsigned char RomArea[] = {0x10,0x29,0x00,0x01,0x78,0x12,056,0x67,0x11,0x22,0x33,0x4f};	//Move.b $1(A1) to D0 
			unsigned int ExpectedValue = 0x512;
			//Initialize the CPU with a specific rom area
			mcpu->Initialize((unsigned int)&RomArea[0]);

			//Set up Registers to Known values
			mcpu->DataRegisterWrite(0,0x555);
			mcpu->AddressRegisterWrite(1,0x04);

			//Run the Test Instruction
			short Opcode = mcpu->FetchInstruction();
			InstructionPtr instr = mcpu->DecodeInstruction(Opcode);
			mcpu->ExecuteInstruction(Opcode,instr);

			//Now lets check to see of the value of 
			unsigned int ActualValue = mcpu->DataRegisterRead(0);

			Assert::AreEqual<unsigned int>(ExpectedValue,ActualValue);
			delete mcpu;

		};
		[TestMethod]
		void ARInDirectAddressModeWordDisplacementTest()
		{
			//THe goal here is to test if the Address Register InDirect Address with Displacement Mode works as expected
			CPU68K *mcpu = new CPU68K;
			//Create ROM Area
			unsigned char RomArea[] = {0x30,0x29,0x00,0x01,0x78,0x12,056,0x67,0x11,0x22,0x33,0x4f};	//Move.w $1(A1) to D0 
			unsigned int ExpectedValue = 0x7812;
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
			unsigned int ActualValue = mcpu->DataRegisterRead(0);

			Assert::AreEqual<unsigned int>(ExpectedValue,ActualValue);
			delete mcpu;

		};
		[TestMethod]
		void ARInDirectAddressModeLongDisplacementTest()
		{
			//THe goal here is to test if the Address Register InDirect Address with Displacement Mode works as expected
			CPU68K *mcpu = new CPU68K;
			//Create ROM Area
			unsigned char RomArea[] = {0x20,0x29,0x00,0x01,0x78,0x12,0x56,0x67,0x11,0x22,0x33,0x4f};	//Move.l $1(A1) to D0 
			unsigned int ExpectedValue = 0x78125667;
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
			unsigned int ActualValue = mcpu->DataRegisterRead(0);

			Assert::AreEqual<unsigned int>(ExpectedValue,ActualValue);
			delete mcpu;

		};


		[TestMethod]
		void ARInDirectAddressModeByteIndexDisplacementTest()
		{
			//THe goal here is to test if the Address Register InDirect Address with IndexDisplacement Mode works as expected
			CPU68K *mcpu = new CPU68K;
			//Create ROM Area
			unsigned char RomArea[] = {0x10,0x31,0x10,0x02,0x78,0x12,0x56,0x67,0x11,0x22,0x33,0x4f};	//Move.b $1(A1,D1) to D0 
			unsigned int ExpectedValue = 0x511;
			//Initialize the CPU with a specific rom area
			mcpu->Initialize((unsigned int)&RomArea[0]);

			//Set up Registers to Known values
			mcpu->DataRegisterWrite(0,0x555);
			mcpu->AddressRegisterWrite(1,0x04);
			mcpu->DataRegisterWrite(1,0x02);

			//Run the Test Instruction
			short Opcode = mcpu->FetchInstruction();
			InstructionPtr instr = mcpu->DecodeInstruction(Opcode);
			mcpu->ExecuteInstruction(Opcode,instr);

			//Now lets check to see of the value of 
			unsigned int ActualValue = mcpu->DataRegisterRead(0);

			Assert::AreEqual<unsigned int>(ExpectedValue,ActualValue);
			delete mcpu;

		};
		[TestMethod]
		void ARInDirectAddressModeWordIndexDisplacementTest()
		{
			//THe goal here is to test if the Address Register InDirect Address with IndexDisplacement Mode works as expected
			CPU68K *mcpu = new CPU68K;
			//Create ROM Area
			unsigned char RomArea[] = {0x30,0x31,0x10,0x02,0x78,0x12,0x56,0x67,0x11,0x22,0x33,0x4f};	//Move.w $1(A1,D1) to D0 
			unsigned int ExpectedValue = 0x1122;
			//Initialize the CPU with a specific rom area
			mcpu->Initialize((unsigned int)&RomArea[0]);

			//Set up Registers to Known values
			mcpu->DataRegisterWrite(0,0x555);
			mcpu->AddressRegisterWrite(1,0x04);
			mcpu->DataRegisterWrite(1,0x02);

			//Run the Test Instruction
			short Opcode = mcpu->FetchInstruction();
			InstructionPtr instr = mcpu->DecodeInstruction(Opcode);
			mcpu->ExecuteInstruction(Opcode,instr);

			//Now lets check to see of the value of 
			unsigned int ActualValue = mcpu->DataRegisterRead(0);

			Assert::AreEqual<unsigned int>(ExpectedValue,ActualValue);
			delete mcpu;

		};
		[TestMethod]
		void ARInDirectAddressModeLongIndexDisplacementTest()
		{
			//THe goal here is to test if the Address Register InDirect Address with IndexDisplacement Mode works as expected
			CPU68K *mcpu = new CPU68K;
			//Create ROM Area
			unsigned char RomArea[] = {0x20,0x31,0x10,0x02,0x78,0x12,0x56,0x67,0x11,0x22,0x33,0x4f};	//Move.b $1(A1,D1) to D0 
			unsigned int ExpectedValue = 0x1122334f;
			//Initialize the CPU with a specific rom area
			mcpu->Initialize((unsigned int)&RomArea[0]);

			//Set up Registers to Known values
			mcpu->DataRegisterWrite(0,0x555);
			mcpu->AddressRegisterWrite(1,0x04);
			mcpu->DataRegisterWrite(1,0x02);

			//Run the Test Instruction
			short Opcode = mcpu->FetchInstruction();
			InstructionPtr instr = mcpu->DecodeInstruction(Opcode);
			mcpu->ExecuteInstruction(Opcode,instr);

			//Now lets check to see of the value of 
			unsigned int ActualValue = mcpu->DataRegisterRead(0);

			Assert::AreEqual<unsigned int>(ExpectedValue,ActualValue);
			delete mcpu;

		};
	};
}
