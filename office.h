#ifndef __WATCARDOFFICE_H__
#define __WATCARDOFFICE_H__

#include "printer.h"
#include "Watcard.h"

class WATCardOffice {
      private:
              Printer *office_printer;
      public:
             WATCardOffice( Printer &prt );
             ~WATCardOffice();
             WATCard *create( unsigned int id, unsigned int amount );
             void transfer( unsigned int id, unsigned int amount, WATCard &card );
};

#endif
