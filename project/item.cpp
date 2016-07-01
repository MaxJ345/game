// item.cpp

#include "item.hpp"

item::item()
{

}

void item::set_itemName(string name)
{
    itemName = name;
}

void item::set_itemDes(string des)
{
    itemDes = des;
}

void item::set_itemWeight(int weight)
{
    itemWeight = weight;
}

void item::set_itemDamage(int damage)
{
    itemDamage = damage;
}

string item::get_itemName()
{
    return itemName;
}

string item::get_itemDes()
{
    return itemDes;
}

int item::get_itemWeight()
{
    return itemWeight;
}

int item::get_itemDamage()
{
    return itemDamage;
}
