#include <iostream>
#include <bitset>                                           //Might or might not use it
#include <cstring>                                          //memset()
#include <cstdint>

using namespace std;

using Byte = uint8_t;                                       // For ease of use
using Word = uint16_t;                                      // For ease of use
using Sentence = uint32_t;                                  // For ease of use

//General Purpose Registers
union GPR
{
    Word X;                                                 //X for AX, BX, CX and DX
    struct
    {
        Byte H;                                             //High for AH, BH, CH, DH
        Byte L;                                             //Low  for AL, BL, CL, DL
    };
};

//Status Register (Flags Are bits)
union FLAG{
    Word Flags;
    struct {
        Word CF : 1;                                        //Carry Flag
        Word    : 1;                                        //Reserved
        Word PF : 1;                                        //Parity Flag
        Word    : 1;                                        //Reserved
        Word AF : 1;                                        //Auxiliary Carry Flag
        Word    : 1;                                        //Reserved
        Word ZF : 1;                                        //Zero Flag
        Word SF : 1;                                        //Sign Flag
        Word TF : 1;                                        //Trap Flag
        Word IF : 1;                                        //Interrupt Flag
        Word DF : 1;                                        //Direction Flag
        Word OF : 1;                                        //Overflow Flag
        Word    : 4;                                        //Reserved
    };
};

struct Memory
{
    static constexpr Sentence MAX_MEM = 1024 * 1024;        //Max Memory of 8086
    Sentence AMA;                                           //Absolute Memory Address (Calculated from IP and CS)
    Byte Data[MAX_MEM];

    void INITIALISE()
    {
        memset(Data, 0x00, MAX_MEM * sizeof(Data[0]));  // Sets all byte element to 0x00
    }
};

struct CPU
{
    //Main Registers
    GPR A;                                                  //Accumulator Register
    GPR B;                                                  //Base Register
    GPR C;                                                  //Count Register
    GPR D;                                                  //Data Register

    //Index Registers
    Word SI;                                                //Source Index
    Word DI;                                                //Destination Index
    Word BP;                                                //Base Pointer
    Word SP;                                                //Stack Pointer

    //Program Counter
    Word IP;                                                //Instruction Pointer

    //Segment Registers
    Word CS;                                                //Code Segment
    Word DS;                                                //Data Segment
    Word ES;                                                //Extra Segment
    Word SS;                                                //Stack Segment

    //Status Flag Register
    FLAG FR;

    void RESET( Memory& memory )
    {
        IP = 0x0000;
        CS = 0xffff;
        DS = ES = SS = 0x0000;
        FR.Flags = 0;
        if (IP == 0x0000 && CS == 0xffff) {
            memory.AMA = (CS * 0x10) + IP;
        }
        memory.INITIALISE();
    }

    void EXECUTE( Sentence Ticks, Memory& memory )
    {
        cout<<"\nTicks: "<<Ticks<<"\n";
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
