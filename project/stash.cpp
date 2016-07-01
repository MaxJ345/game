// stash.cpp

#include "stash.hpp"

stash::stash()
{
    pItemList =  new array <item *, MAX_NUM_ITEMS>;
    numItems = 0;
    for(int ixItem = 0; ixItem < MAX_NUM_ITEMS; ixItem++)
    {
        (*pItemList)[ixItem] = NULL;
    }
}

// This function will build a list of items based on a list.
void stash::add_items()
{
    string strFileName = "items.txt";

    string strBuffer;
    ifstream items_file(strFileName);

    if(items_file.is_open())
    {
        int ixItem = 0;
        getline(items_file, strBuffer);      // Skip first line.
        while(getline(items_file, strBuffer) && ixItem < MAX_NUM_ITEMS)
        {
            item * temp_item_ptr = new item;
            process_item_info(strBuffer, temp_item_ptr);
            (*pItemList)[ixItem] = temp_item_ptr;
            numItems++;

            //cout << (*pItemList)[ixItem]->get_itemName() << endl;         // for DEBUGGING

            ixItem++;
        }
        items_file.close();
    }
    else
        cout << "Error opening file.";
}

string stash::get_item_list(bool bShowDes, bool bShowWeight, bool bShowDamage)
{
    string strResult = "";
    for(int ixItem = 0; ixItem < numItems && ixItem < MAX_NUM_ITEMS; ixItem++)
    {
        item * temp_item;
        temp_item = (*pItemList)[ixItem];

        if(temp_item == NULL)
            continue;

        if(ixItem == 0)
            strResult += "\n";

        strResult += temp_item->get_itemName();

        if(bShowDes)
            strResult += " | " + temp_item->get_itemDes();

        //if(bShowWeight)
        //    strResult += " | " + temp_item->get_itemWeight();     // Commented out because I have no way of converting from int (item weight) to string (result).

        //if(bShowDamage)
        //    strResult += " | " + temp_item->get_itemDamage();     // Commented out because I have no way of converting from int (item damage) to string (result).

        strResult += "\n";
    }

    return strResult;
}

int stash::get_num_items()
{
    return numItems;
}

item * stash::get_item(int nIndex, bool bTakeFromStash)
{
    if(nIndex >= 0 && nIndex < MAX_NUM_ITEMS)
    {
        item * temp_item_ptr;
        temp_item_ptr = (*pItemList)[nIndex];

        if(bTakeFromStash == true)
        {
            numItems--;
            (*pItemList)[nIndex] = NULL;
        }

        return temp_item_ptr;
    }

    return NULL;
}

bool stash::add_item(item * newItem)
{
    if(newItem != NULL)
    {
        if(numItems < MAX_NUM_ITEMS)
        {
            for(int ixItem = 0; ixItem < MAX_NUM_ITEMS; ixItem++)
            {
                if((*pItemList)[ixItem] == NULL)
                {
                    (*pItemList)[ixItem] = newItem;
                    numItems++;
                    return true;
                }
            }
        }
    }

    return false;
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
