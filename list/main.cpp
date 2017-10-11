#include <iostream>

#import <unordered_set>
#import <vector>

template <class T>
class Node {
        Node *next;
        T data;
        public:
        Node (T d): next(nullptr), data(d) {}

        Node (const std::vector<T>& v) {
            data = v[0];
            next = nullptr;
            for (auto i=1; i<v.size(); i++) {
                appendNext(v[i]);
            }
        }

        T getData () { return data; }
        void setData (T d) { data = d; }
        Node* getNext() { return next; }
        void setNext(Node *n) { next = n; }

        void appendNext (T d) {
            Node *last = this;
            Node *end = new Node(d);
            while (last->getNext() != nullptr) {
                last = last->getNext();
            }
            last->setNext(end);
        }

        friend std::ostream& operator<< (std::ostream& stream, Node head) {
            stream << "{";
            Node *runner = &head;
            while (runner != nullptr) {
                stream << runner->getData() << ",";
                runner = runner->getNext();
            }
            stream << "}\n";
            return stream;
        }

};

Node<int> removeDup (Node<int> &head) {
    std::unordered_set<int> elementHash;
    elementHash.insert(head.getData());
    Node<int> *previous = &head;
    Node<int> *runner = head.getNext();
    while (runner != nullptr) {
        if (elementHash.find(runner->getData()) != elementHash.end()) {
            previous->setNext(runner->getNext());
            delete (runner);
            runner = previous->getNext();
        } else {
            elementHash.insert(runner->getData());
            previous = runner;
            runner = runner->getNext();
        }
    }
    return head;
}

int kthToLast (Node<int> head, int kth) {

    Node<int> *runner = &head;
    Node<int> *offset =&head;

    for (auto i=0; i < kth; i++) {
        runner = runner->getNext();
        if (runner == nullptr) {
            throw std::out_of_range("the list must have at least kth elements");
        }
    }
    while (runner != nullptr) {
        runner = runner->getNext();
        offset = offset->getNext();
    }
    return offset->getData();
}



Node<int>* partition (Node<int> head, int key) {
    Node<int> *left = nullptr;
    Node<int> *right = nullptr;
    Node<int> *runner = &head;
    while (runner != nullptr) {
        if (runner->getData() < key){
            if (left == nullptr){
                left = new Node<int> (runner->getData());
            }
            else {
                left->appendNext(runner->getData());
            }
        }
        else {
            if (right == nullptr){
                right = new Node<int> (runner->getData());
            }
            else {
                right->appendNext(runner->getData());
            }
        }
        runner = runner->getNext();
    }
    runner = left;
    while (runner->getNext() != nullptr){
        runner = runner->getNext();
    }
    runner->setNext(right);
    return left;
}


int listToInt(Node<int> *n) {
    int result = 0;
    int factor = 1;
    Node<int> * runner = n;
    while (runner != nullptr) {
        result += (runner->getData() * factor);
        factor *= 10;
        runner = runner->getNext();
    }
    return result;
}

Node<int> intToList (int n) {
    Node<int> *result = nullptr;
    int rest = n;
    do {
        int digit = rest % 10;
        rest /= 10;
        if (result == nullptr) {
            result = new Node<int>(digit);
        }
        else{
            result->appendNext(digit);
        }
    }
    while (rest != 0);
    return *result;
}

Node<int> sumLists (Node<int> *n1, Node<int> *n2) {
    int sum = listToInt(n1) + listToInt(n2);
    return intToList (sum);
}


Node<int> *intersection (Node<int> l1, Node<int> l2) {
    std::unordered_set<Node<int> *> links;
    Node<int> * runner = &l1;
    while (runner->getNext() != nullptr) {
        links.insert (runner->getNext());
        runner = runner->getNext();
    }
    runner = &l2;
    while (runner->getNext() != nullptr) {
        if (links.find(runner->getNext()) != links.end()) {
            return runner->getNext();
        }
        runner = runner->getNext();
    }
    return nullptr;
}


Node<int> *detectLoop (Node<int> head) {
    Node<int> *runner = &head;
    std::unordered_set<Node<int> *> links;
    while (links.find(runner->getNext()) == links.end()) {
        links.insert(runner->getNext());
        runner = runner->getNext();
        if (runner == nullptr){
            return runner;
        }
    }
    return runner->getNext();
}

Node<int> *detectLoop2 (Node<int> head) {
    Node<int> *slowRunner = &head;
    Node<int> *fastRunner = &head;

    while ((slowRunner != nullptr) && (fastRunner != nullptr)) {
        slowRunner = slowRunner->getNext();
        fastRunner = fastRunner->getNext()->getNext();
        if (slowRunner == fastRunner) {
            break;
        }
    }
    if ((slowRunner == nullptr) || (fastRunner == nullptr)){
        return nullptr;
    }
    slowRunner = &head;
    while (slowRunner != fastRunner){
        slowRunner = slowRunner->getNext();
        fastRunner = fastRunner->getNext();
    }
    return slowRunner;

}



 int main() {


     Node<int> loop1({3, 2, 4, 8, 4, 6, 8, 9});

     Node<int> *runner1 = &loop1;
     Node<int> *inter = runner1;
     while (runner1->getData() != 8){
         runner1 = runner1->getNext();
     }
     inter = runner1;
     while (runner1->getNext() != nullptr) {
         runner1 = runner1 ->getNext();
     }
     runner1->setNext(inter);

     Node<int> *loop = detectLoop(loop1);

     std::cout << "-=-=-=- detectLoop -=-=-=-\n";
     std::cout << "Loop at node: " << loop->getData() << "\n";
     loop = detectLoop2(loop1);
     std::cout << "Loop at node: " << loop->getData() << "\n";


     Node<int> inter1({3, 2, 4, 8, 4, 6, 8, 9});
     Node<int> inter2({3, 9, 5, 6, 1});
     Node<int> *runner = &inter1;
     Node<int> *lastS2 = &inter2;
     while (lastS2->getData() != 1){
         lastS2 = lastS2->getNext();
     }
     while (runner->getData() != 4) {
         runner = runner ->getNext();
     }
     lastS2->setNext(runner);

     Node<int> *intersect = intersection(inter1,inter2);

     std::cout << "-=-=-=- Intersection -=-=-=-\n";
     std::cout << "Intersection at node: " << intersect->getData() << "\n";

     std::cout << "-=-=-=- sumlist -=-=-=-\n";

     Node<int> listHead({1, 57, 1, 1, 2, 8, 9, 389347, 3, 389347});

     Node<int> s1({3, 2, 4});
     Node<int> s2({3, 9});
     std::cout << "-=-=-=- sumlist -=-=-=-\n";
     std::cout << sumLists(&s1, &s2) << "\n";


     std::cout << "-=-=-=- partition -=-=-=-\n";
     std::cout << *partition(listHead, 57) << "\n";

     std::cout << "-=-=-=- Kth -=-=-=-\n";
     std::cout << kthToLast(listHead, 1) << "\n";

     std::cout << "-=-=-=- removeDup -=-=-=-\n";
     std::cout << removeDup (listHead) << "\n";

     std::cout << "-=-=-=- Kth -=-=-=-\n";

     return 0;
}