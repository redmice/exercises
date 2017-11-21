#include <iostream>
#include <vector>
#include <string>

struct MyList {
    std::string data;
    MyList *next;

    MyList(std::string s) : data(s), next(nullptr) {};
};

void split (MyList* source, MyList** middle);
void sortmerge (MyList** source);
MyList* merge (MyList* source, MyList* middle);

void split (MyList* source, MyList** middle){
    MyList* slow = source;
    MyList* fast = source->next;
    
    while (fast != nullptr){
        fast = fast->next;
        if (fast != nullptr){
            slow = slow->next;
            fast = fast->next;
        }
    }
    *middle = slow->next;
    slow->next = nullptr;
}

void sortmerge (MyList** head){
    MyList* middle;
    MyList* source = *head;

    if ((source == nullptr) || (source->next == nullptr)){
        return;
    }
    
    split (source, &middle);
    std::cout << "check";
    sortmerge(&source);
    sortmerge(&middle);
    *head = merge(source, middle);
}

MyList* merge (MyList* a, MyList* b) {
    MyList* result;

    if (a == nullptr){
        return b;
    }
    if (b == nullptr){
        return a;
    }
    int cmp = a->data.compare(b->data);
    if (cmp <= 0){
        result = a;
        result->next = merge(result->next, b);
    }
    else {
        result = b;
        result->next = merge(a, result->next);
    }
    return result;
}

void push(MyList** head, std::string data){
    MyList* newElem = new MyList(data);
    newElem->next = *head;
    *head = newElem;
}

int main (){
    std::vector<std::string> test = {
        "Esto es una prueba de ordenacion",
        "de cadenas de caracteres en una lista",
        "enlazada usando mergesort",
        "probado con un monton de cadenas de caracteres",
        "y como ves hay algunas que estan repetidas",
        "de cadenas de caracteres en una lista",
        "enlazada usando mergesort",
        "probado con un monton de cadenas de caracteres",
        "y como ves hay algunas que estan repetidas",
        "de cadenas de caracteres en una lista",
        "enlazada usando mergesort",
        "probado con un monton de cadenas de caracteres",
        "y como ves hay algunas que estan repetidas",
        "ZZZZZZZ es la ultima del abecedario"};
    MyList* head;
    for (auto& s : test) {
        push(&head, s);
    }
    sortmerge (&head);
    MyList* runner = head;
    while (runner != nullptr) {
        std::cout << runner->data << std::endl;
        runner = runner->next;
    }
    return 0;
}
