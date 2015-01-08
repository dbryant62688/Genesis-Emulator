#include "MemoryRegion.h"


#define MEMREALADDR(x,y) (y - x.StartAddress + x.RealOffset)
#define MEMPTRREALADDR(x,y) (y - x->StartAddress + x->RealOffset)


unsigned int MemoryMap::GetRealAddress(unsigned int Addr)
{
	for(int x = 0;x<regioncnt;x++)
	{
		if(Addr >= memregion[x].StartAddress && Addr <= memregion[x].EndAddress)
			return MEMREALADDR(memregion[x],Addr);
	}
	return 0;
}

MemRegion* MemoryMap::GetMemRegion(unsigned int Addr)
{
	for(int x = 0;x<regioncnt;x++)
	{
		if(Addr >= memregion[x].StartAddress && Addr <= memregion[x].EndAddress)
			return &memregion[x];
	}
	return 0;
}


void MemoryMap::MemoryWriteByte(unsigned int Addr,unsigned char Value)
{
	MemRegion* memLocation =  GetMemRegion(Addr);
	if(memLocation)
	{
		unsigned int realAddr = MEMPTRREALADDR(memLocation,Addr);
		if(memLocation->Flag == PORT)
		{
		}
		else
		{
			(*(unsigned char*)realAddr) = Value;
		}
	}
}
void MemoryMap::MemoryWriteWord(unsigned int Addr,unsigned short Value)
{
	MemRegion* memLocation =  GetMemRegion(Addr);
	if(memLocation)
	{
		unsigned char Data1 = (Value&0xFF00)>> 8;
		unsigned char Data2 = (Value&0x00FF);

		unsigned int realAddr = MEMPTRREALADDR(memLocation,Addr);
		if(memLocation->Flag == PORT)
		{
		}
		else
		{
			//Assume all writes are Little endian so lets swap
			(*(unsigned char*)realAddr) = Data2;
			(*(unsigned char*)(realAddr+1)) = Data1;
		}
	}
}
void MemoryMap::MemoryWriteLong(unsigned int Addr,unsigned int Value)
{
	MemRegion* memLocation =  GetMemRegion(Addr);
	if(memLocation)
	{
		unsigned char Data1 = (Value&0xFF000000)>> 24;
		unsigned char Data2 = (Value&0x00FF0000)>>16;
		unsigned char Data3 = (Value&0x0000FF00)>>8;
		unsigned char Data4 = (Value&0x000000FF);

		unsigned int realAddr = MEMPTRREALADDR(memLocation,Addr);

		if(memLocation->Flag == PORT)
		{
		}
		else
		{
			//assume all writes are little endian so we need to swap
			(*(unsigned char*)realAddr)	   = Data4;
			(*(unsigned char*)(realAddr+1)) = Data3;
			(*(unsigned char*)(realAddr+2)) = Data2;
			(*(unsigned char*)(realAddr+3)) = Data1;
		}
	}
}
unsigned char MemoryMap::MemoryReadByte(unsigned int Addr)
{
	MemRegion* memLocation =  GetMemRegion(Addr);
	if(memLocation)
	{
		if(memLocation->Flag == PORT)
		{
		}
		else
		{
			unsigned int realAddr = MEMPTRREALADDR(memLocation,Addr);
			unsigned char Data = (*(unsigned char*)(realAddr));
			return Data;
		}
	}
	else
		return 0;
}
unsigned short MemoryMap::MemoryReadWord(unsigned int Addr)
{
	MemRegion* memLocation =  GetMemRegion(Addr);
	if(memLocation)
	{
		if(memLocation->Flag == PORT)
		{
		}
		else
		{
			unsigned int realAddr = MEMPTRREALADDR(memLocation,Addr);
			//This is done to prevent memory alignment issues.(need to find a faster way to do this...TO MANY CYCLES!!!!)
			unsigned char Byte1 = (unsigned char)(*(unsigned char*)realAddr);
			unsigned char Byte2 = (unsigned char)(*(unsigned char*)(realAddr+1));
			unsigned short Data =  Byte1<<8 | Byte2;	//Assume all data comng from memory is Big Endian so lets swap. This will swap it
			return Data;
		}
	}
	else
		return 0;
}
unsigned int MemoryMap::MemoryReadLong(unsigned int Addr)
{
	MemRegion* memLocation =  GetMemRegion(Addr);
	if(memLocation)
	{
		if(memLocation->Flag == PORT)
		{
		}
		else
		{
			unsigned int realAddr = MEMPTRREALADDR(memLocation,Addr);
			//This is done to prevent memory alignment issues.(need to find a faster way to do this...TO MANY CYCLES!!!!)
			unsigned char Byte1 = (unsigned char)(*(unsigned char*)realAddr);
			unsigned char Byte2 = (unsigned char)(*(unsigned char*)(realAddr+1));
			unsigned char Byte3 = (unsigned char)(*(unsigned char*)(realAddr+2));
			unsigned char Byte4 = (unsigned char)(*(unsigned char*)(realAddr+3));

			unsigned long Data =  Byte1<<24 | Byte2<<16 | Byte3<<8 | Byte4;	//Assume all data is BIG endian so lets swap
			return Data;
		}
	}
	else
		return 0;
}