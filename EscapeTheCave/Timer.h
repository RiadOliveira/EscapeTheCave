/**********************************************************************************
// Timer (Arquivo de Cabe�alho)
// 
// Cria��o:     02 Abr 2011
// Atualiza��o: 10 Ago 2021
// Compilador:  Visual C++ 2022
//
// Descri��o:   Usa um contador de alta precis�o para medir o tempo.
//
**********************************************************************************/

#ifndef _PROGJOGOS_TIMER_H_
#define _PROGJOGOS_TIMER_H_

// -------------------------------------------------------------------------------

#include <windows.h>            // acesso ao contador de alta precis�o do Windows

// -------------------------------------------------------------------------------

class Timer
{
private:
    LARGE_INTEGER start, end;   // valores de in�cio e fim do contador
    LARGE_INTEGER freq;         // freq��ncia do contador
    bool stoped;                // estado da contagem
    
public:
    Timer();                    // constructor

    void  Start();              // inicia/retoma contagem do tempo
    void  Stop();               // p�ra contagem do tempo
    float Reset();              // reinicia contagem e retorna tempo transcorrido
    float Elapsed();            // retorna tempo transcorrido em segundos    
    bool  Elapsed(float secs);  // verifica se transcorreu "secs" segundos
    bool NotStarted();
}; 

// -------------------------------------------------------------------------------

// Fun��es Inline

inline bool Timer::Elapsed(float secs)
{ return (Elapsed() >= secs ? true : false); }

inline bool Timer::NotStarted() { return start.QuadPart == 0 && end.QuadPart == 0; }

// -------------------------------------------------------------------------------

#endif