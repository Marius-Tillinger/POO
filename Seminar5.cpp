// #include <iostream>
// #include <stdexcept>
// using namespace std;


// template<class T> class List;
// template <class T>
// ostream& operator << (ostream& os, const List<T>& l);


// template <class T>
// struct node {
//     T val;
//     node* next;
//     node(T val) {
//         this->val = val;
//         this->next = NULL;
//     }
// };

// template <class T>
// class List {


// private:
//     int listSize;



// node<T>* startPtr;
// node<T>* endPtr;

// public:
//     List();

//     T popBack();
//     void pushBack(T val);

//     bool isEmpty();

//     friend ostream& operator << <T>(ostream& os, const List<T>& l);

//     ~List();

// };


// template <class T>
// ostream& operator << (ostream& os, const List<T>& l) {

//     node<T>* startNode = l.startPtr;
//     while(startNode != NULL) {
//         os << startNode->val << " ";
//         startNode = startNode->next;

//     }
//     os << "\n";
//     return os;
// }

// template <class T>
// List<T>:: List() {
//     this->listSize = 0;
//         this->startPtr = NULL;
//         this->endPtr = NULL;
// }


// template <class T>
// bool List<T>:: isEmpty() {
//     return this->listSize == 0;
// }

// template <class T>
// List<T>:: ~List() {
//     while(!this->isEmpty()) {
//         this->popBack();
//     }
// }

// template <class T>
// void List<T>::pushBack(T val) {

//     node<T>* newNode = new node<T>(val);
//     if(this->startPtr == NULL) {
//         this->startPtr = newNode;
//         this->endPtr = newNode;

//     }
//     else {
//         this->endPtr->next = newNode;
//         this->endPtr = newNode;
//     }

//     this->listSize++;

// }

// template <class T>
// T List<T>::popBack() {


//     T val;
//     if(this->startPtr == NULL) {
//         throw out_of_range("Lista este goala");
//     }

//     val = this->endPtr->val;

//     node<T>* aux = this->endPtr;
//     this->listSize--;


//     // 1 singur nod
//     if(this->startPtr->next == NULL) {

//         this->startPtr = NULL;
//         this->endPtr = NULL;
//         delete aux;
//         return val;
//     }

//     node<T>* start = this->startPtr;
//     while(start->next->next) {
//         start = start->next;
//     }

//     this->endPtr = start;
//     this->endPtr->next = NULL;
//     delete aux;

//     return val;

// }

// int main()
// {

//     List<int> lst = List<int>();
//     for(int i=0;i<5;i++) {
//         lst.pushBack(i);
//     }

//     lst.popBack();

//     cout << lst;
//     return 0;
// }



#include <iostream>
#include <vector>
#include <algorithm>
#include <stdexcept>

using namespace std;

template <class T>
class Stack {
    T* ptr;
    unsigned capacity;
    int top;
public:
    Stack();
    Stack(const Stack<T>&);
    void push(const T&);
    T peek() const;
    void pop();
    ~Stack();
    Stack<T>& operator=(const Stack<T>&);
    vector<T> multiPop (unsigned);

    template <class U>
    friend ostream& operator<< (ostream&, const Stack<U>&);

    template <class U>
    friend istream& operator>> (istream&, Stack<U>&);

};

template<class T> Stack<T>& Stack<T> :: operator= (const Stack<T>&S){
    if(&S==this)
        return *this;
    delete[] ptr;
    capacity = S.capacity;
    ptr = new T[S.capacity];
    copy(S.ptr, S.ptr + capacity, ptr);
    top = S.top;
    return *this;
}


template<class T> vector<T> Stack<T>::multiPop(unsigned range){
    vector<T> v;
    if(range>top+1)
        throw invalid_argument("Nu exista atatea elemente");
    for(int i=0; i<range; i++){
        v.push_back(peek());
        pop();
    }
    return v;
}

template<class T> void Stack<T>::pop(){
    if (top == -1)
        throw out_of_range("Stiva este vida");
    top--;
}

template<class T> T Stack<T>::peek() const{
    if (top == -1)
        throw out_of_range("Stiva este vida");
    return ptr[top];
}

template<class T> ostream& operator<< (ostream& os, const Stack<T>& s){
    for (int i = s.top; i >= 0; i--)
        os<<s.ptr[i]<<" ";
    os<<endl;
    return os;
}

template<class T> istream& operator>>(istream& is,  Stack<T>& s){
    int no_elem;
    is >> no_elem;
    s.top = -1;
    if (no_elem > s.capacity){
        delete []s.ptr;
        s.ptr = new T[no_elem];
        s.capacity = no_elem;
    }

    for (int i = 0; i < no_elem; i++)
        is >> s.ptr[i];

    return is;
}


template <class T> Stack <T>::Stack(){
    this -> capacity = 10;
    this -> ptr = new T[10];
    this -> top = -1;
}

template <class T> Stack <T>::~Stack(){
    this -> capacity = 0;
    this -> top = -1;
    delete[] this -> ptr;
}

template <class T> void Stack <T>::push(const T &val){
    if(top >= capacity - 1){
        capacity += 10;
        T *newPtr = new T[capacity];
        copy(ptr, ptr + capacity, newPtr);
        delete[] ptr;
        ptr = newPtr;
    }

    top++;
    ptr[top] = val;
}

template <class T> Stack <T>::Stack(const Stack<T> &S) : capacity(S.capacity){
    ptr = new T[S.capacity];
    copy(S.ptr, S.ptr + capacity, ptr);
    top = S.top;
}

int main () {

    Stack<int> s;
    s.push(10);
    s.push(15);

    Stack<int> s2(s);
    s2.push(-5);

    cout<<s;
    cout<<"---------\n";
    cout<<s2<<endl;
    Stack<int> s3;
    s3=s2;
    cout<<s3;
    return 0;
}