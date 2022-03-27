//
// Copyright 2022 John I. Krassikoff
//
// This program is free software : you can redistribute itand /or modify
// it under the terms of the GNU General Public License as published
// by the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program.If not, see < https://www.gnu.org/licenses/>.
//

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
