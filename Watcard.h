#ifndef __WATCARD_H__
#define __WATCARD_H__
#include <map>

class WATCard {
      protected:
                unsigned int id, balance;
                stu_list lst;
      public:
             typedef map<unsigned int, unsigned int> stu_list;
             WATCard();
             void add_fund(unsigned int account_id, unsigned int amount);
             void sub_fund(unsigned int account_id, unsigned int amount);
};

#endif
