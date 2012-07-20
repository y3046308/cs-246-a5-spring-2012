#include "student.h"
#include "PRNG.h"
#include "flavour.h"

PRNG prng;

/*
  purpose: initializes student
  precondition: printer, Nameserver, WATCardOffice, unsigned int, unsigned int
  postcondition: None
*/
Student::Student( Printer &prt, NameServer &nameServer, WATCardOffice &cardOffice, 
                  unsigned int id, unsigned int maxPurchases)
{
    student_printer = &prt;
    student_server = &nameserver;
    student_office = &cardOffice;
    student_id = id;      
    how_many = prng(1, MaxPurchases);  
    how_many_bought = 0 ;
    student_flavour = prng(3);
    myCard = new WATCard;
    curr_mach = student_server->getMachine(student_id);
    
    transfer(id, 5, myCard);         
    
    // printer prints that student is about to select his or her flavour of drink
    // and decides how many sodas does he or she needs
    student_printer->print(Printer::Student, student_id, 'S', flavour, how_many);    
    // printer prints that student just selected the designated vending machine
    student_printer->print(Printer::Student, student_id, 'V', curr->getId());
}

/*
  purpose: destory student
  precondition: NONE
  postcondition: Student
*/
Student::~Student()
{
    student_printer = NULL;
    student_server = NULL;
    student_office = NULL;
    student_id = 0;
    how_many = 0;
    how_many_bought = 0 ;
    student_flavour = NULL;
    delete myCard;
    curr_mach = NULL;
    // printer prints that student finished buying everything he needs
    student_printer->print(Printer::Student, student_id, 'F');
}

/*
  purpose: returns a boolean value based on student's action 
  precondition: None
  postcondition: Boolean
*/
bool Student::action()
{
    if (how_many_bought == how_many) // when student purchase everything in the list
    {
        return false;
    }
    
    if (myCard->curr_balance() < curr_mach->cost()) // if there is insufficient fund, 
    {
        // continously transfer $3 to the card until we can buy at least one soda
        while (myCard->curr_balance() < curr_mach->cost()) 
        {
            student_printer->print(Printer::Student, id, 't', 3);
            student_office->transfer(id, 3, *myCard);
            student_printer->print(Printer::Student, id, 'T', myCard->curr_balance());                         
        }
        return true;
    }
    // status when trying to purchase a soda
    VendingMachine::Status stock = curr->buy(student_flavour, myCard);
    
    if (stock == BUY)      // student successfully bought a soda
    {
       how_many_bought += 1;
       student_printer->print(Printer::Student, id, 'B',  myCard->curr_balance());
       return true;
    }
    else if (stock == STOCK)  // soda unavailable                  
    {
         // find another machine
         curr_mach = student_server->getMachine(student_id);
         return true;                                       
    }
    
    if (myCard == NULL) // card destroyed by vending machine
    {
        student_printer->print(Printer::Student, id, 'D');
        myCard = new WATCard(); 

        student_printer->print(Printer::Student, id, 't', 5); 
        student_office->transfer(id, 5, *myCard); // transfer $5 to empty card
        student_printer->print(Printer::Student, id, 'T', myCard->curr_balance());     
    }
    
}
