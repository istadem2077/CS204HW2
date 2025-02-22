/*
 * Ismayil Taghi-Zada 33582
 * Start: 22.02.2025
 * End: WIP
 */

#include <iostream>
#include <string>
#include <fstream>


typedef struct Node {
    std::string word;
    int count;
    Node* next;
} Node;

bool checkFile(const std::string& filename) {
    std::ifstream file(filename);
    return file.is_open();
}

bool checkWord(Node* head, const std::string& word) {
    Node* current = head;
    while (current->next != nullptr) {
        if (current->word == word) return true;
    }
    return false;
}

void openFile (const char * str, std::ifstream& file) {
    std::string filename;
    std::string msg = str;
    do {
        std::cout << msg << std::endl;
        std::getline(std::cin, filename);
        if (checkFile(filename)) {
            file.open(filename);
        }
        else {
            std::cout << "The file couldn't be opened." << std::endl;
            msg = "Please enter a valid file name:";
        }

    } while (!checkFile(filename));
}

Node* push(Node* head, const std::string& word, int count) {
    if (head != nullptr) {
        if (head->count > count) { // push before head
            Node* temp = new Node;
            temp->word = word;
            temp->count = count;
            temp->next = head;
            head = temp;
        }
        else if (head->count < count) { // push after head
            Node* temp = new Node;
            temp->word = word;
            temp->count = count;
            if (head->next != nullptr) {
                temp->next = head->next;
            }
            head->next = temp;
        }
        else {
            Node* temp = new Node;
            temp->word = word;
            temp->count = count;
            if (word > head->word) {
                if (head->next != nullptr) {
                    temp->next = head->next;
                }
                head->next = temp;
            }
            else if (word < head->word) {
                if (head->next != nullptr) {
                    temp->next = head;
                }
                head = temp;
            }
        }
    }
    else {
        Node *temp = new Node;
        temp->word = word;
        temp->count = count;
        temp->next = nullptr;
        head = temp;
    }
    return head;
}


// Deallocate each element in singly linked list
void dealloc(Node* head) {
    Node* ptr = head;
    while (ptr != nullptr) {
        Node* next = ptr->next;
        delete ptr;
        ptr = next;
    }
}

int main() {
    std::ifstream file1;
    std::ifstream file2;
    openFile("Please enter the first file name:", file1);
    openFile("Please enter the second file name:", file2);


    Node* list1 = nullptr;
    Node* list2 = nullptr;
    Node* common = nullptr;


    dealloc (list1);
    dealloc (list2);
    dealloc (common);
    return 0;
}
