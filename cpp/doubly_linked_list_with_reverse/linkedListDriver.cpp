/*
Copyright (c) 2022 John I. Krassikoff

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/


#include "dLinkedList.h"

int main()
{
    std::cout << " Using a doubly linked list." << std::endl;
    dLinkedList<double> dlist;

    try {
        dlist.insert_head_node(1.0);
        dlist.insert_last_node(6.5);
        dlist.insert_last_node(2.7);
        dlist.insert_last_node(3.5);
        dlist.insert_last_node(2.1);
        std::cout << " The list:" << std::endl;
        dlist.display_list();
        std::cout << " Reverse the list:" << std::endl;
        dlist.reverse_list();
        dlist.display_list();
        dlist.delete_head_node();
        dlist.delete_node(1.0);
        std::cout << " Delete the head and the node corresponding to value of 1.0:" << std::endl;
        dlist.display_list();
    }
    catch (List_Is_Empty_Exception& e) {
        std::cout << e.what() << std::endl;
    }

    return 0;
}
