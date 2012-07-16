#ifndef __WATCARD_H__
#define __WATCARD_H__

class WATCard {
      private:
                unsigned int balance;
      public:
             WATCard();
             void add_fund(unsigned int amount);
             void sub_fund(unsigned int amount);
};

#endif
