#include <iostream>
#include <vector>

#include "LinkedList.hpp"

int main()
{
    ListNode node1 = ListNode(14);
    ListNode node2 = ListNode(10);
    ListNode node3 = ListNode(5);
    ListNode node4 = ListNode(42);

    node1.append(&node2);
    node2.append(&node3);
    node3.append(&node4);

    std::cout << "Size = " << node1.size() << std::endl;

    ListNode newNode = ListNode(84);

    node1.insert(2, &newNode);

    std::cout << "First element = " << node1.val << std::endl;
    std::cout << "Second element = " << node1.next->val << std::endl;
    std::cout << "Third element = " << node1.next->next->val << std::endl;
    std::cout << "Fourth element = " << node1.next->next->next->val << std::endl;

}