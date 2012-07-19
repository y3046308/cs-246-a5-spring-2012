#ifndef __WATCARD_H__
#define __WATCARD_H__

class WATCard {
      private:
                unsigned int balance;
      public:
             WATCard();
             unsigned int curr_balance();
             void add_fund(unsigned int amount);
             void sub_fund(unsigned int amount);
};

#endif
