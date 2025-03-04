/*
 * Name-Surname-ID: Ismayil Taghi-Zada 33582
 * Start: 22.02.2025
 * End: 04.04.2025
 * Email: ismayil.taghi-zada@sabanciuniv.edu
 * GitHub: istadem2077
 */

#include <iostream>
#include <fstream>


struct Node {
    std::string word;
    int count;
    Node* next;

    Node(std::string w, int c) : word(std::move(w)), count(c), next(nullptr) {}
};

class List {
    private:
        Node* head;
        void deleteList(const Node* node);

    public:
    List() : head(nullptr) {}
    ~List() {
        deleteList(head);
    }

    void ins(const std::string& word, int count = 1);
    void insSort(Node* node);
    void del(const std::string& word);
    void print();
    bool exists(const std::string& word);
    bool increm(const std::string& word);
    Node* returnNode(const std::string& word);
};

// Class functions' implementations

// Recursive deletion, from end, back to start
void List::deleteList(const Node *node) {
    if (!node) return;
    deleteList(node->next);
    delete node;
}

void List::print() {
    Node* current = head;
    int counter = 1;
    while (current) {
        std::cout << current->word << "(" << current->count << ") " << "--> ";
        if (counter == 5) {
            std::cout << std::endl;
            counter = 0;
        }
        current = current->next;
        counter++;
    }
    std::cout << "--||" << std::endl;
}

bool List::exists(const std::string& word) {
    if (head) {
        Node* current = head;
        while (current) {
            if (current->word == word) return true;
            current = current->next;
        }
    }
    return false;
}

bool List::increm(const std::string &word) {
    if (head) {
        Node* current = head;
        while (current != nullptr) {
            if (current->word == word) {
                current->count += 1;
                int temp_count = current->count;
                del(word);
                ins(word, temp_count);
                return true;
            }
            current = current->next;
        }
    }
    return false;
}

// Returns the address of the node to operate with structure fields
Node* List::returnNode(const std::string& word) {
    if (head) {
        Node* current = head;
        while (current) {
            if (current->word == word) return current;
            current = current->next;
        }
    }
    return nullptr;
}

void List::ins(const std::string& word, int count) {
    Node* newNode = new Node(word, count);
    insSort(newNode);
}


// Sorted insertion
void List::insSort(Node* node) {
    Node* prev = nullptr;
    Node* current = head;

    while (current && (current->count < node->count ||
                      (current->count == node->count && current->word < node->word))) {
        prev = current;
        current = current->next;
                      }

    node->next = current;
    if (!prev) {
        head = node;
    } else {
        prev->next = node;
    }
}

// Plain old deletion
void List::del(const std::string &word) {
    if (!head) {
        return;
    }

    if (head->word == word) {
        Node* temp = head;
        head = head->next;
        delete temp;
        return;
    }

    Node* current = head;
    Node* previous = nullptr;

    while (current && current->word != word) {
        previous = current;
        current = current->next;
    }

    if (!current) {
        return;
    }

    previous->next = current->next;
    delete current;
}
// End class functions' implementations




// Helper functions

// Just check if the file is successfully opened
bool checkFile(const std::string& filename) {
    std::ifstream file(filename);
    return file.is_open();
}

// Open file, pass ifstream parameter by reference to get it back in main function.
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
// End Helper function



int main() {
    std::ifstream file1;
    std::ifstream file2;
    openFile("Please enter the first file name:", file1);
    openFile("Please enter the second file name:", file2);


    List list1, list2, common;
    std::string w1, w2;
    bool read1 = true, read2 = true;

    while (read1 || read2) {
        if (read1 && file1 >> w1) { std::cout << "Processing the word \"" << w1 << "\" from the 1st file."<< std::endl; }
        else { read1 = false; w1 = "@"; } // Since no digits are allowed, I use it indicator that reading has failed

        if (read2 && file2 >> w2) { std::cout << "Processing the word \"" << w2 << "\" from the 2nd file."<< std::endl; }
        else { read2 = false; w2 = "@"; }

        if (read1 || read2) {
            bool w1_in_common = common.increm(w1);
            bool w2_in_common = common.increm(w2);
            bool w12_in_common = w1_in_common && w2_in_common;

            if (!w12_in_common && w1 == w2 && (w1 != "@" || w2 != "@")) {
                common.ins(w1, 2);
            }
            else {
                bool w1_l1 = list1.increm(w1), w2_l2 = list2.increm(w2), w1_l2 = list2.exists(w1), w2_l1 = list1.exists(w2);

                if (w1 != "@" && !w1_l1 && !w1_l2 && !w1_in_common) { // Word 1 exists nowhere
                    list1.ins(w1);
                }
                else if (w1 != "@" &&!w1_l1 && w1_l2 && !w1_in_common) { // Word 1 only exists in List
                    common.ins(w1, list2.returnNode(w1)->count+1);
                    list2.del(w1);
                }

                if (w2 != "@" && !w2_l2 && !w2_l1 && !w2_in_common) { // Word 2 exists nowhere
                    list2.ins(w2);
                }
                else if (w2 != "@" &&!w2_l2 && w2_l1 && !w2_in_common) { // Word 2 only exists in List 1
                    common.ins(w2, list1.returnNode(w2)->count+1);
                    list1.del(w2);
                }
            }


            std::cout << std::endl;
            std::cout << "List for File 1:" << std::endl;
            list1.print();
            std::cout << std::endl;
            std::cout << "List for File 2:" << std::endl;
            list2.print();
            std::cout << std::endl;
            std::cout << "Common List:" << std::endl;
            common.print();
            std::cout << std::endl << "#############" << std::endl << std::endl;
        }
        else {
            std::cout << "End of Files." << std::endl;
            read1 = false; read2 = false;
        }
    }

    file1.close();
    file2.close();
    // Linked lists are being deallocated by Class destructor.
    return 0;
}