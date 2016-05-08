// item.hpp

#ifndef ITEM_HPP_INCLUDED     // if item.hpp hasn't been included yet...
#define ITEM_HPP_INCLUDED     // #define this so the compiler knows it has been included

#include "includes.hpp"

class item
{
public:
    item();

    string get_itemName();
    string get_itemDes();
    int get_itemWeight();
    int get_itemDamage();

    void set_itemName(string name);
    void set_itemDes(string des);
    void set_itemWeight(int weight);
    void set_itemDamage(int damage);

private:
    string itemName;
    string itemDes;
    int itemWeight;
    int itemDamage;

} ;

#endif  // ITEM_HPP_INCLUDED
