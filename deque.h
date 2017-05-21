#ifndef DEQUE_H
#define DEQUE_H

#include <iterator>

using namespace std;

template< typename value_type>
class DEQUE
{    
    friend class ITERATOR;
private:
    struct NODE
    {
        value_type value;
        NODE *next;
        NODE *prev;
    };

    class ITERATOR : public iterator <bidirectional_iterator_tag, value_type>
    {
        friend class DEQUE<value_type>;
    private:
        NODE *point;
    public:
        ITERATOR(){ point = nullptr; }
        ITERATOR(NODE *p){ point = p; }
        ITERATOR(const ITERATOR& another){ point = another.point; }

        bool operator==(const ITERATOR another);
        bool operator!=(const ITERATOR another);

        ITERATOR& operator ++();
        ITERATOR& operator --();
        value_type& operator *();
    };

private:
    NODE *head;
    NODE *tail;
    unsigned int size;

public:

    typedef ITERATOR iterator;

    explicit DEQUE();
    DEQUE(value_type value, unsigned int count);
   ~DEQUE();

    iterator begin();
    iterator end  ();

    value_type front();
    value_type back ();

    void push_back (value_type);
    void push_front(value_type);

    void pop_back ();
    void pop_front();
    void erase    (value_type finder);
    void sort     ();

    bool         empty  ();
    bool         exist  (value_type some);
    value_type   find   (int pos);
    unsigned int getSize();
};

template<typename value_type>
value_type DEQUE<value_type>::find(int pos)
{
    if(pos >= size) return -1;

    NODE *ret = head;
    while(pos)
    {
        ret = ret->next;
        pos--;
    }
    return ret->value;
}

template<typename value_type>
void DEQUE<value_type>::erase(value_type finder)
{
    NODE *f = head;
    while(f)
    {
        if(f->value == finder)
        {
            if(f->prev)
            {
                f->prev->next = f->next;
            }
            if(f->next)
            {
                f->next->prev = f->prev;
            }
            f->next = f->prev = nullptr;
            delete f;
            return;
        }
        f = f->next;
    }
}

template<typename value_type>
DEQUE<value_type>::DEQUE()
{
    head = tail = nullptr;
    size = 0;
}

template<typename value_type>
DEQUE<value_type>::DEQUE(value_type value, unsigned int count)
{
    size = count;
    for(unsigned int i = 0; i < count; i++)
    {
        NODE *current = new NODE;
        current->value = value;
        current->next = nullptr;
        current->prev = tail;

        if(tail) tail->next = current;
        tail = current;
        if(!head) head = current;
        current = nullptr;
    }
}

template< typename value_type >
typename DEQUE<value_type>::iterator DEQUE<value_type>::begin()
{
    return iterator(head);
}

template< typename value_type >
typename DEQUE<value_type>::iterator DEQUE<value_type>::end()
{
    return iterator(nullptr);
}

template<typename value_type>
value_type DEQUE<value_type>::front()
{
    return head->value;
}

template<typename value_type>
value_type DEQUE<value_type>::back()
{
    return tail->value;
}

template<typename value_type>
void DEQUE<value_type>::push_back(value_type value)
{
    size++;
    NODE *current = new NODE;
    current->value = value;
    current->next = nullptr;
    current->prev = tail;

    if(tail) tail->next = current;
    tail = current;
    if(!head) head = current;
}

template<typename value_type>
void DEQUE<value_type>::push_front(value_type value)
{
    size++;
    NODE *current = new NODE;
    current->value = value;
    current->next = head;
    current->prev = nullptr;

    if(head) head->prev = current;
    head = current;
    if(!tail) tail = current;
}

template<typename value_type>
void DEQUE<value_type>::pop_back()
{
   if(size == 0) return;

   size--;
   NODE *deleter = tail;
   tail = tail->prev;

   if(tail) tail->next = nullptr;
   if(head == deleter) head = nullptr;
   delete deleter;
}

template<typename value_type>
void DEQUE<value_type>::pop_front()
{
    if(size == 0) return;

    size--;
    NODE *deleter = head;
    head = head->next;

    if(head) head->prev = nullptr;
    if(tail == deleter) tail = nullptr;
    delete deleter;
}

template<typename value_type>
bool DEQUE<value_type>::empty()
{
    return size == 0 ? true : false;
}

template<typename value_type>
bool DEQUE<value_type>::exist(value_type some)
{
    NODE *finder = head;
    while(finder)
    {
        if(finder->value == some)
        {
            return true;
        }
    }

    return false;
}

template<typename value_type>
unsigned int DEQUE<value_type>::getSize()
{
    return size;
}

template<typename value_type>
DEQUE<value_type>::~DEQUE()
{
    NODE *deleter = head;
    NODE *previous;
    while(deleter)
    {
        previous = deleter;
        deleter = deleter->next;
        delete previous;
    }
}

template<typename value_type>
bool DEQUE<value_type>::ITERATOR::operator ==(const ITERATOR another)
{
    return point == another.point;
}

template<typename value_type>
bool DEQUE<value_type>::ITERATOR::operator !=(const ITERATOR another)
{
    return point != another.point;
}

template<typename value_type>
typename DEQUE<value_type>::ITERATOR& DEQUE<value_type>::ITERATOR::operator++()
{
    point = point->next;
    return (*this);
}

template<typename value_type>
typename DEQUE<value_type>::ITERATOR& DEQUE<value_type>::ITERATOR::operator --()
{
    point = point->prev;
    return (*this);
}

template<typename value_type>
value_type& DEQUE<value_type>::ITERATOR::operator *()
{
    return point->value;
}

template<typename value_type>
void DEQUE<value_type>::sort()// ДОРАБОТАТЬ
{
    for(NODE *ender  = tail; ender != head; ender = ender->prev)
    {
        NODE *sorter = head;
        sorter = sorter->next;
        while(sorter)
        {
            if(sorter->value > sorter->prev->value)
            {
                NODE *first  = sorter->prev->prev;
                NODE *second = sorter->prev;
                NODE *third  = sorter->next;

                if(first)
                {
                    first->next = sorter;
                }
                sorter->prev = first;
                if(third)
                {
                    third->prev = second;
                }
                second->next = third;
                sorter->next = second;
                second->prev = sorter;
            }
            if(sorter == ender) break;
            sorter = sorter->next;
        }
    }

}

#endif // DEQUE_H
