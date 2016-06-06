// stash.cpp

#include "stash.hpp"

stash::stash()
{
    pItemList =  new array <item *, NUM_ITEMS>;
}

// This function will build a list of items based on a list.
void stash::get_items()
{
    string strFileName = "items.txt";

    string strBuffer;
    ifstream items_file(strFileName);

    if(items_file.is_open())
    {
        int ixItem = 0;
        getline(items_file, strBuffer);      // Skip first line.
        while(getline(items_file, strBuffer) && ixItem < NUM_ITEMS)
        {
            item * temp_item_ptr = new item;
            process_item_info(strBuffer, temp_item_ptr);
            (*pItemList)[ixItem] = temp_item_ptr;

            //cout << (*pItemList)[ixItem]->get_itemName() << endl;         // for DEBUGGING

            ixItem++;
        }
        items_file.close();
    }
    else
        cout << "Error opening file.";
}

void stash::process_item_info(string strLine, item * itemPtr)
{
    int found = strLine.find("|", 0);
    string strTemp;
    int temp;

    // Item name.
    if(found > -1)
    {
        strTemp = strLine.substr(0, found);
        strLine.assign(strLine.substr(found + 1));      // Move forward in the string.
        itemPtr->set_itemName(strTemp);
        //cout << itemPtr->get_itemName();        // for DEBUGGING
    }

    found = strLine.find("|", 0);

    // Item description.
    if(found > -1)
    {
        strTemp = strLine.substr(0, found);
        strLine.assign(strLine.substr(found + 1));
        itemPtr->set_itemDes(strTemp);
        //cout << itemPtr->get_itemDes();        // for DEBUGGING
    }

    found = strLine.find("|", 0);

    // Item weight.
    if(found > -1)
    {
        strTemp = strLine.substr(0, found);
        temp = atoi(strTemp.c_str());
        strLine.assign(strLine.substr(found + 1));
        itemPtr->set_itemWeight(temp);
        //cout << itemPtr->get_itemWeight();        // for DEBUGGING
    }

    // Item damage.
    if(found > -1)
    {
        strTemp = strLine;
        temp = atoi(strTemp.c_str());
        itemPtr->set_itemDamage(temp);
        //cout << itemPtr->get_itemDamage();        // for DEBUGGING
    }

    cout << endl;       // for DEBUGGING
}
