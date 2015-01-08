#ifndef _MEM_H
#define _MEM_H


#define MEMORY 0
#define PORT 1

struct MemRegion
{
	unsigned int StartAddress;					//Start Address In the m68000 memory area
	unsigned int EndAddress;					//End Address in the m68000 memory area
	unsigned int RealOffset;					//Actual memory offset
	unsigned int Flag;							//Determine if this is areal memory region or a port
	void (*WriteFunc)(unsigned int data);		//Function to write data to the port ( only used if Flag set to PORT)
	unsigned int (*ReadFunc)(unsigned int data);	//Function to read data from port (only used if Flag is set to PORT)
};


class MemoryMap
{
public:
	unsigned int GetRealAddress(unsigned int Addr);
	MemRegion* GetMemRegion(unsigned int Addr);
	void MemoryWriteByte(unsigned int Addr,unsigned char Value);
	void MemoryWriteWord(unsigned int Addr,unsigned short Value);
	void MemoryWriteLong(unsigned int Addr,unsigned int Value);
	unsigned char MemoryReadByte(unsigned int Addr);
	unsigned short MemoryReadWord(unsigned int Addr);
	unsigned int MemoryReadLong(unsigned int Addr);

	unsigned int MemoryRead(unsigned int Addr);
	MemRegion memregion[10];
	int regioncnt;
};
#endif