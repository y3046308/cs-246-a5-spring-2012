#include "student.h"
#include "PRNG.h"
#include "flavour.h"

PRNG prng;

Student::Student( Printer &prt, NameServer &nameServer, WATCardOffice &cardOffice, 
                  unsigned int id, unsigned int maxPurchases)
{
    student_printer = &prt;
    student_server = &nameserver;
    student_office = &cardOffice;
    student_id = id;      
    how_many = prng(1, MaxPurchases);  
    how_many_bought = 0 ;
    int temp = prng(3);
      
    if (temp == 0)
    {
       student_flavour = BlackCherry;
    }  
    else if (temp == 1)
    {
       student_flavour = CreamSoda;
    }  
    else if (temp == 2)
    {
       student_flavour = RootBeer;
    }   
    else
    {
        student_flavour = JazzLime;
    }
    myCard = new WATCard;
    curr = student_server->getMachine(student_id);
    
    transfer(id, 5, myCard);         
    
    student_printer->print(Printer::Student, student_id, 'S', flavour, how_many);    
    student_printer->print(Printer::Student, student_id, 'V', curr->getId());
}

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
    curr = NULL;
    student_printer->print(Printer::Student, student_id, 'F');
}

bool Student::action()
{
    if (how_many_bought == 0)
    {
        return false;
    }
    
    while (
    
    VendingMachine::Status stock = curr->buy(student_flavour, myCard);
    
    if (stock == 
    
    int rand_broken = prng(1,10);
    
    if (rand_broken == 1)
    {
    
    }
}
