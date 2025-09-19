#include <cstdint>
#include <iostream>
#include <bitset>

using namespace std;

using Byte = uint8_t;
using Word = uint16_t;
using Sentence = uint32_t;

union GPR
{
    Word X;
    struct
    {
        Byte H;
        Byte L;
    };
};

struct Memory
{
    static constexpr Sentence MAX_MEM = 1024 * 1024;
    Byte Data[MAX_MEM];

    void INITIALISE()
    {
        for ( Sentence i=0; i < MAX_MEM; i++ )
        {
            if(i == MAX_MEM - 1) break;
            Data[i] = 0;
            Data[i+1] = 0;
            Data[i+2] = 0;
            Data[i+3] = 0;
            Data[i+4] = 0;
            Data[i+5] = 0;
            Data[i+6] = 0;
            Data[i+7] = 0;
            i = i + 7;
        }
    }
};

struct CPU
{
    //Main Registers
    GPR A{};          //Accumulator Register with AH and AL
    GPR B{};          //Base Register with BH and BL
    GPR C{};          //Count Register with CH and CL
    GPR D{};          //Data Register with DH and DL

    //Index Registers
    Word SI{};        //Source Index
    Word DI{};        //Destination Index
    Word BP{};        //Base Pointer
    Word SP{};        //Stack Pointer

    //Program Counter
    Word IP{};        //Instruction Pointer

    //Segment Registers
    Word CS{};        //Code Segment
    Word DS{};        //Data Segment
    Word ES{};        //Extra Segment
    Word SS{};        //Stack Segment

    //Status Register (Flags per bit)
    bitset<16> FlagRegister();
    Byte CF:1;      //Carry Flag
    Byte PF:1;      //Parity Flag
    Byte AF:1;      //Auxiliary Carry Flag
    Byte ZF:1;      //Zero Flag
    Byte SF:1;      //Sign Flag
    Byte TF:1;      //Trap Flag
    Byte IF:1;      //Interrupt Flag
    Byte DF:1;      //Direction Flag
    Byte OF:1;      //Overflow Flag

    void RESET( Memory& memory )
    {

        IP = 0x0000;
        CS = 0xffff;
        DS = ES = SS = 0x0000;
        CF = PF = AF = ZF = SF = OF = 0b0;
        memory.INITIALISE();
    }

    void EXECUTE( Sentence Ticks, Memory& memory )
    {
        cout<<"Ticks: "<<Ticks<<endl; //hello
    }
};

int main()
{
    CPU cpu;
    Memory mem;
    cpu.RESET( mem );
    cpu.EXECUTE( 2, mem );
    return 0;
}
