#include <iostream>
#include <bitset>                                          //Might or might not use it
#include <cstring>                                         //memset()
#include <cstdint>

using namespace std;

using UI8 = uint8_t;                                       // For ease of use
using UI16 = uint16_t;                                     // For ease of use
using UI32 = uint32_t;                                     // For ease of use

//General Purpose Registers
union GPR
{
    UI16 X;                                                //X for AX, BX, CX and DX
    struct
    {
        UI8 H;                                             //High for AH, BH, CH, DH
        UI8 L;                                             //Low  for AL, BL, CL, DL
    };
};

//Status Register (Flags Are bits)
union FLAG{
    UI16 Flags;
    struct {
        UI16 CF : 1;                                        //Carry Flag
        UI16    : 1;                                        //Reserved
        UI16 PF : 1;                                        //Parity Flag
        UI16    : 1;                                        //Reserved
        UI16 AF : 1;                                        //Auxiliary Carry Flag
        UI16    : 1;                                        //Reserved
        UI16 ZF : 1;                                        //Zero Flag
        UI16 SF : 1;                                        //Sign Flag
        UI16 TF : 1;                                        //Trap Flag
        UI16 IF : 1;                                        //Interrupt Flag
        UI16 DF : 1;                                        //Direction Flag
        UI16 OF : 1;                                        //Overflow Flag
        UI16    : 4;                                        //Reserved
    };
};

struct Memory
{
    static constexpr UI32 MAX_MEM = 1024 * 1024;            //Max Memory of 1MB for 8086
    UI32 AMA;                                               //Absolute Memory Address (Calculated from IP and CS)
    UI8 Data[MAX_MEM];

    void INITIALISE()
    {
        memset(Data, 0x00, MAX_MEM * sizeof(Data[0]));  //Sets all byte element to 0x00
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
    UI16 SI;                                                //Source Index
    UI16 DI;                                                //Destination Index
    UI16 BP;                                                //Base Pointer
    UI16 SP;                                                //Stack Pointer

    //Program Counter
    UI16 IP;                                                //Instruction Pointer

    //Segment Registers
    UI16 CS;                                                //Code Segment
    UI16 DS;                                                //Data Segment
    UI16 ES;                                                //Extra Segment
    UI16 SS;                                                //Stack Segment

    //Status Flag Register
    FLAG FR;

    //Prefetch Queue for Instructions
    UI8 IQ[6];

    void RESET( Memory& memory )
    {
        IP = 0x0000;
        CS = 0xffff;
        DS = ES = SS = 0x0000;
        memset(IQ, 0x00, 6 * sizeof(IQ[0]));            //Clears Instruction Prefetch Queue
        FR.Flags = 0x00000000;
        if (IP == 0x0000 && CS == 0xffff) {
            memory.AMA = (CS * 0x10) + IP;
        }
        memory.INITIALISE();
    }

    void STARUP() {

    }

    void EXECUTE( UI32 Cycles, Memory& memory )
    {
        cout<<"\nCycles: "<<Cycles<<"\n";
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