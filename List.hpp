#ifndef LIST_HPP
#define LIST_HPP
#include <iostream>


// двухсвязный список
template<typename T>
class List {
  
    private:
    class Node{

        public:
        T data_;
        Node *next_;
        Node *prev_;
        Node(T data =  T(), Node *next = nullptr, Node *prev=nullptr ): data_(data), next_(next), prev_(prev){} 
    };
    

    Node *head_;
    Node *tail_;
    size_t size_;

    public:

    //геттеры
    Node* getHead()const {return head_;}
    Node* getTail() const {return tail_;}
    size_t getSize() const {return size_;}
    bool isEmpty () const {return size_ ==0; }  
    bool isSearch(const T& key) const {
        
        Node* current = head_;
        while (current) {
            if (current->data_ == key){
                return 1;
            }
            Node* next = current->next_;  
            current = next;                
        }
        return 0;
    }

    // геттер данных головы и хвоста
    T* getHeadData() const {return head_->data_;}    
    T* getTailData() const {return tail_->data_;}

    /* КОНСТРУКТОРЫ */

    // Конструктор инициализации    
    List() : head_(nullptr), tail_(nullptr), size_(0) {}
    
    // Конструктор с параметором
    explicit List(const T& value) {
        try
        {
            head_ = new Node(value);
            tail_ = head_;
            size_ = 1;        
        }
        catch(const std::bad_alloc& e)
        {
            throw ("FATAL ERROR! : memory allocation error while init");
        }
    
    }

    // Конструктор копирования
    List(const List& other) : head_(nullptr), tail_(nullptr), size_(0) {
        if (other.size_ ==0) {return;}

      try
      {
        head_ = new Node(other.head_->data_);
        Node* currentThis = head_;
        Node* currentOther = other.head_->next_;

        while (currentOther){
            Node* newNode = new Node(currentOther->data_);
            newNode->prev_ = currentThis;
            currentThis->next_ = newNode;
            
            currentThis = newNode;
            currentOther = currentOther->next_;
        }

        tail_ = currentThis;
        size_ = other.size_;

      }
      catch(const std::exception& e)
      {
         while (head_) {
            Node* temp = head_;
            head_ = head_->next_;
            delete temp;
      }

    throw std::runtime_error("FATAL ERROR! : memory allocation error while copyng");  
    }

    }

// конструктор перемещения
List(List&& other): head_(nullptr), tail_(nullptr), size_(0) {
    if (other.size_ ==0){return; }
        swap(other);
  
}

//Деструктор
~List(){

       Node* current = head_;
        while (current) {
            Node* next = current->next_;  
            delete current;                
            current = next;                
        }
        head_ =  nullptr;
        tail_ = nullptr;
        size_ = 0;
}

/* ОПЕРАТОРЫ ПРИСВАЕВАНИЯ */

// оператор копирующего присваения
List& operator=(const List& other){
    List tmp(other);
    this->swap(tmp);
    return *this;
}

// оператор перемещающего присваения
List& operator=(List&& other) noexcept {

    if (this != &other){
        List tmp(std::move(other));
        this->swap(tmp);
        
    }
    return *this;
}

/* ВСТАВКА УЗЛОВ */

// Копирующая вставка
void insert(const T& value){

    size_t oldSize = size_;
    Node* oldHead = head_;
    Node* oldTail = tail_;

    try
    {
        Node* newNode = new Node(value);
            if (!head_) {
            head_  = newNode;
            tail_ = newNode;
        } 

        else {
            Node* current = head_;
            while (current && current->data_ < value) {
                current = current->next_;
            }
            
            if (!current) { 
                newNode->prev_ = tail_;
                tail_->next_ = newNode;
                tail_ = newNode;
            }
            else if (current == head_) { 
                newNode->next_ = head_;
                head_->prev_ = newNode;
                head_ = newNode;
            }
            else { 
                newNode->prev_ = current->prev_;
                newNode->next_ = current;

                current->prev_->next_ = newNode;
                current->prev_ = newNode;
            }
        }
        
        size_++;
    }
    catch(const std::exception& e)
    {
        head_ = oldHead;
        tail_ = oldTail;
        size_ = oldSize;
        throw std::runtime_error("Erorr! : insert error");
    }
    
}

// Перемещающая вставка
void insert(T&& value) {
    size_t oldSize = size_;
    Node* oldHead = head_;
    Node* oldTail = tail_;

    try {
        Node* newNode = new Node(std::move(value));
        if (!head_) {
            head_ =  newNode;
            tail_ = newNode;
        } 
        else {
            Node* current = head_;
            while (current && current->data_ < newNode->data_) {
                current = current->next_;
            }
                
            if (!current) {
                newNode->prev_ = tail_;
                tail_->next_ = newNode;
                tail_ = newNode;
            }
            else if (current == head_) {
                newNode->next_ = head_;
                head_->prev_ = newNode;
                head_ = newNode;
            }
            else {
                newNode->prev_ = current->prev_;
                newNode->next_ = current;
                    
                current->prev_->next_ = newNode;
                current->prev_ = newNode;
            }
        }
            
        size_++;
        }
        catch(const std::exception& e) {
            head_ = oldHead;
            tail_ = oldTail;
            size_ = oldSize;
            throw std::runtime_error("Error! : move insert error");
        }
    }


/* УДАЛЕНИЕ */

void removeHead(){

    if (!head_) return;

    Node* oldHead = head_;
    head_ = oldHead->next_;
    if (head_){
        head_->prev_ = nullptr;
    }
    else{
        tail_ = nullptr;
    }

    delete oldHead;
    size_--;
}

void clear(){
    if (!head_){
        return;
    }
    
    Node* current = head_;
    while (current){
        Node* next = current->next_;
        delete current;                
        current = next;  
    }
    tail_ = nullptr;
    head_ = nullptr;
    size_ = 0;
}

/* МЕТОДЫ ЗАДАНИЯ ДВА */

//  Удаление ряда элементов
void removeKey (const T& keyBegin, const T& keyEnd){
    if (keyBegin > keyEnd || !head_){
        return;
    }

    Node* current = head_;
    while (current){
        Node* next = current->next_;
        if (current->data_ >= keyBegin && current->data_ <= keyEnd){
             if (current->prev_) {
                    current->prev_->next_ = current->next_;
                } else {
                    head_ = current->next_; 
                }   
                if (current->next_) {
                    current->next_->prev_ = current->prev_;
                } else {
                    tail_ = current->prev_; 
                }
                delete current;
                size_--;
            }
            current = next;
        }
    }


// операция +=
List& operator+=(const T& value){
    insert(value);
    return *this;
}

/* МЕТОДЫ ЗАДАНИЯ 3 */

// замена одного ключа на другой
void replace(const T& keyOld, const T& keyNew) {
        size_t count = 0;
        Node* current = head_;
        
        while (current) {
            Node* next = current->next_;
            if (current->data_ == keyOld) {
                if (current->prev_) {
                    current->prev_->next_ = current->next_;
                } else {
                    head_ = current->next_;
                }
                if (current->next_) {
                    current->next_->prev_ = current->prev_;
                } else {
                    tail_ = current->prev_;
                }
                delete current;
                count++;
                size_--;
            }
            
            current = next;
            }
        for (size_t i = 0; i < count; ++i) {
            insert(keyNew);
    }
}

// Слияние списков
void merge(List& other) {
        if (this == &other) {
            return;}
        Node* current = other.head_;

        while (current) {
            Node* next = current->next_;
            if (current->prev_) {
                current->prev_->next_ = current->next_;
            } else {
                other.head_ = current->next_;
            }
            if (current->next_) {
                current->next_->prev_ = current->prev_;
            } else {
                other.tail_ = current->prev_;
            }
            
            if (!head_) {
                head_ = current;
                tail_  = current;
                current->prev_ = nullptr;
                current->next_ = nullptr;
            } 
            else {
                Node* position = head_;
                while (position && position->data_ < current->data_) {
                    position = position->next_;
                }
                
                if (!position) { 
                    current->prev_ = tail_;
                    current->next_ = nullptr;
                    tail_->next_ = current;
                    tail_ = current;
                }
                else if (position == head_) { 
                    current->prev_ = nullptr;
                    current->next_ = head_;
                    head_->prev_ = current;
                    head_ = current;
                }
                else { 
                    current->prev_ = position->prev_;
                    current->next_ = position;
                    position->prev_->next_ = current;
                    position->prev_ = current;
                }
            }
            
            size_++;
            other.size_--;
            current = next;
        }
        

        other.head_ = nullptr;
        other.tail_ = nullptr;
        other.size_ = 0;
    }




/* ИНЫЕ МЕТОДЫ */

// print
void print(){
    if (!head_){ 
        return; 
    }
    try
    {
        Node* current = head_;
        while(current){
        Node* next = current->next_;
        std::cout<<current->data_<<' ';
        current = next;
    }
    std::cout<<std::endl;
    }
    catch(const std::exception& e){
        throw std::runtime_error("Error! : print method error");
    }
}


// swap 
void swap(List& other) noexcept {
    std::swap(head_, other.head_);
    std::swap(tail_, other.tail_);
    std::swap(size_, other.size_);
}
};
#endif