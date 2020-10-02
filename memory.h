#ifndef MEMORY_H
#define MEMORY_H
#include <systemc.h>
#include <tlm.h>
#include <tlm_utils/simple_initiator_socket.h>
#include <tlm_utils/simple_target_socket.h>

using namespace sc_core;
using namespace std;
using namespace sc_dt;

SC_MODULE (Initiator)
{
public:

  tlm_utils::simple_initiator_socket<Initiator, 32> socket;

  //SC_HAS_PROCESS(Initiator);
  virtual void thread_process();
  SC_CTOR(Initiator):socket("Initiator_Socket")
  {
    SC_THREAD(thread_process);
  }

private:
  int data;

};


SC_MODULE (Target)
{
public:

  tlm_utils::simple_target_socket<Target, 32> socket;

  //SC_HAS_PROCESS(Target);

  SC_CTOR(Target):socket("Target_Socket")
  {
    socket.register_b_transport(this, &Target::b_transport);

    // Initialize memory with random data
    for (int i = 0; i < SIZE; i++)
      mem[i] = 0xAA000000 | (rand() % 256);

    //SC_THREAD();
    //SC_THREAD();
  }
  virtual void b_transport (tlm::tlm_generic_payload& trans, sc_time& delay);

private:
  enum {SIZE=256};
  int mem[SIZE];

};
#endif
