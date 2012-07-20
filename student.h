#ifndef __STUDENT_H__
#define __STUDENT_H__
#include "printer.h"
#include "nameserver.h"
#inlcude "office.h"
#include "flavour.h"

class Student {
      unsigned int student_id, how_many, how_many_bought ;
      Flavours student_flavour;
      WATcard *myCard;
      Printer *student_printer;
      Nameserver *student_server;
      WATCardOffice *student_office;
      VendingMachine *curr_mach;
  public:
        Student( Printer &prt, NameServer &nameServer, WATCardOffice &cardOffice, unsigned int id, unsigned int maxPurchases );
        bool action();
};

#endif
