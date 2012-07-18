#include "student.h"
#include "PRNG.h"

PRNG prng;

Student::Student( Printer &prt, NameServer &nameServer, WATCardOffice &cardOffice, 
                  unsigned int id, unsigned int maxPurchases)
{
    student_id = id;      
    how_many = prng(1, MaxPurchases);  
    flavour = prng(3); 
    transfer(id, 5, myCard);         
	
	if ( vending maching destroys a students WATCard ){
		create a new WATCard with $0 balance and transferring the same initial $5 to the card with WATCardOffice
	}                
	
	else if ( vending machine delivered a bottle of soda){
		student drinks it and returns true
	}
	
	else { (check WATCard for insufficient funds to purchase a bottle of soda)
		if ( there are insufficient funds){
			a student transfers $3 to their WATCard from the WATCard office until there is
			sufficient funds to buy at least one soda and returns true
			
			
			
		}
				
	}
	
		
}



/*
When a student has purchased all the soda initially selected, then action returns false. 

A student then attempts to buy a bottle of soda from the vending machine.
 - If the vending machine destroys a student’s WATCard, the student must create a new one by creating a WATCard (dynamically)
 with $0 balance and transferring the same initial $5 to the card via the WATCardOffice. 
	
 - If the vending machine delivered a bottle of soda, the student drinks it and returns true.

 - Otherwise, a student checks their WATCard for insufficient funds (less than VendingMachine::cost()) to purchase a bottle of
 soda. 
	
      - If there is insufficient funds, a student transfers $3 to their WATCard from the WATCard office until there is 
	sufficient funds to buy at least one soda and returns true; 
      - the next time action is called, the student attempts to buy a soda with the new money. If the vending machine is out
        of the student’s favourite flavour, the student must obtain a new vending machine from the name server and return 
        true; the next time action is called, the student attempts to buy a soda at the new vending machine.
*/
