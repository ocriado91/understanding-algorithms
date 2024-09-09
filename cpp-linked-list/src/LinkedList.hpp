#ifndef LINKED_LIST_HPP
#define LINKED_LIST_HPP

#include <exception>

class ListNodeException:public std::exception
{
    public:
        ListNodeException(std::string message): message(message) {};
        const char* what() const throw() {return message.c_str();}
    private:
        std::string message;
};

// A Linked List is a data structure that allows to
// handle dynamic data. The basic structure is a node
// and each node consists of two fields:
//  - value: stored data
//  - next: node pointer to the next node
// ┌────────────┬──────────┐      ┌────────────┬──────────┐
// │            │          │      │            │          │
// │  value     │  next    ├─────►│  value     │  next    ├─────► nullptr
// │            │          │      │            │          │
// └────────────┴──────────┘      └────────────┴──────────┘
//         node1                          node2
//
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}

    void append(ListNode* newNode)
    {
        this->next = newNode;
    }

    void insert(const unsigned int position,
                ListNode* newNode)
    {
        ListNode* next = this->next;
        for(unsigned int idx = 0; idx <= position; idx++) {
            if (position == idx) {
                newNode->next = this->next;
                this->append(newNode);
            }
        }
    }

    size_t size() {
        unsigned int count = 0;
        ListNode *nextNode= this->next;
        while (nextNode->next != nullptr) {
            nextNode = nextNode->next;
            count++;
        }
        return count;
    }

    void append(int val)
    {

        // Find the last element in the list
        ListNode* current = this;
        while (current->next != nullptr) {
            current = current->next;
        }

        // Append the new element to the end of the list
        current->next = new ListNode(val);
    }

    void insert(int val, const unsigned int position)
    {

        // Check position value
        if (position > this->size()+1) {
            std::string msg = "ERROR: Position value ("
                + std::to_string(position)
                + ") exceeds the size of list ("
                + std::to_string(this->size()) + ")";
            throw ListNodeException(msg);
        }

        // Save current pointer
        ListNode* current = this;

        // Create pointer with new value
        ListNode* newNode = new ListNode(val);

        // Check if insert into head position
        if (position == 0) {

            // Create a copy of head
            ListNode* head = new ListNode(current->val);
            head->next = current->next;

            // Transform head attributes
            current->val = val;
            current->next = head;
        } else {

            // Insert into no-head position
            int counter = 0;

            // Element by element until tail element
            while(current != nullptr && counter < 100) {

                // Node from previous position, points to newNode
                if (counter+1 == position) {
                    newNode->next = current->next;
                    current->next = newNode;
                }
                // Increment counter
                counter++;
                // Move to next element
                current = current->next;
            }
        }
    }

    std::string toString(std::string delimiter = ";")
    {
        std::string result = "[";
        ListNode* current = this;
        while (current != nullptr) {
            result += std::to_string(current->val);
            if (current->next != nullptr) {
                result += delimiter;
            }
            current = current->next;
        }

        result += "]";

        return result;
    }

    void remove(unsigned int position)
    {
        // Check position
        if (position > this->size()) {
            std::string msg = "ERROR: Position value ("
                + std::to_string(position)
                + ") exceeds the size of list ("
                + std::to_string(this->size()) + ")";
            throw ListNodeException(msg);
        }
        unsigned int counter = 0;
        ListNode* current = this;
        while (current != nullptr) {

            if (counter+1 == position) {
                current->next = current->next->next;
            }

            // Increment counter
            counter++;
            // Move to the next position
            current = current->next;
        }
    }
};

ListNode* vector2ListNode(std::vector<int>& data)
{
    ListNode* list = nullptr;
    for (auto it: data) {
        if (nullptr == list) {
            list = new ListNode(it);
        } else {
            list->append(it);
        }
    }

    return list;
}

ListNode* mergeTwoList(ListNode* list1, ListNode* list2)
{

    ListNode* mergedList = nullptr;
    while (list1 != nullptr && list2 != nullptr) {

        // Insert first value
        if (mergedList == nullptr) {
            mergedList = new ListNode(list1->val);
            mergedList->append(list2->val);
        } else {
            mergedList->append(list1->val);
            mergedList->append(list2->val);
        }

        // Move lists to next element
        list1 = list1->next;
        list2 = list2->next;
    }

    return mergedList;
}

#endif