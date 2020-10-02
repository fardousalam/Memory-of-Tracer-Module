#include <systemc.h>
#include "memory_top.h"
int sc_main (int argc, char* argv[])
{
top_mem top_memory("TOP MEMORY");
sc_start();
return 0;
}
