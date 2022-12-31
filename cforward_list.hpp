//
// Invisparent
// Wang Chenyi, Henan University
// 20221229 1830
//

#ifndef CFORWARD_LIST_H
#define CFORWARD_LIST_H

#include <initializer_list>

template<typename T>
class cforward_list_innerdat;

template<typename T>
class cforward_list;

template<typename T>
class cforward_list_innerdat {
    friend class cforward_list<T>;

private:
    explicit cforward_list_innerdat<T>(const T &inT) : dat(inT), next(nullptr) {}

    T dat;
    cforward_list_innerdat<T> *next;
};

template<typename T>
class cforward_list {
public:
    explicit cforward_list<T>() : firstInnerdat(nullptr) {}

    cforward_list(const std::initializer_list<T> &inIL) {
        bool isFirst = true;
        cforward_list_innerdat<T> *ptr;
        for (const T &inT: inIL)
            if (isFirst) {
                firstInnerdat = new cforward_list_innerdat<T>(inT);
                ptr = firstInnerdat;
                isFirst = false;
            } else {
                ptr->next = new cforward_list_innerdat<T>(inT);
                ptr = ptr->next;
            }
    }

    class iterator {
        friend class cforward_list<T>;

    public:
        explicit iterator(cforward_list_innerdat<T> *inPtr = nullptr) : iteratorPtr(inPtr) {}

        T &operator*() {
            return iteratorPtr->dat;
        }

        T &operator++() {
            iteratorPtr = iteratorPtr->next;
            return iteratorPtr->dat;
        }

        bool operator!=(const iterator iter) {
            return iteratorPtr != iter.iteratorPtr;
        }

    private:
        cforward_list_innerdat<T> *iteratorPtr;
    };

    cforward_list<T>::iterator begin() {
        return cforward_list<T>::iterator(firstInnerdat);
    }

    cforward_list<T>::iterator end() {
        return cforward_list<T>::iterator(nullptr);
    }

    cforward_list<T>::iterator before_begin() {
        return cforward_list<T>::iterator(nullptr);
    }

    void erase_after(iterator iter) {
        if (iter.iteratorPtr == nullptr) {
            cforward_list_innerdat<T> *originalBegin = firstInnerdat;
            firstInnerdat = firstInnerdat->next;
            delete originalBegin;
        } else {
            cforward_list_innerdat<T> *deleteElement = iter.iteratorPtr->next;
            iter.iteratorPtr->next = iter.iteratorPtr->next->next;
            delete deleteElement;
        }
    }

    void insert_after(iterator iter, const T &inT) {
        if (iter.iteratorPtr == nullptr) {
            cforward_list_innerdat<T> *originalBegin = firstInnerdat;
            firstInnerdat = new cforward_list_innerdat<T>(inT);
            firstInnerdat->next = originalBegin;
        } else {
            cforward_list_innerdat<T> *originalNext = iter.iteratorPtr->next;
            iter.iteratorPtr->next = new cforward_list_innerdat<T>(inT);
            iter.iteratorPtr->next->next = originalNext;
        }
    }

    ~cforward_list() {
        if (firstInnerdat != nullptr) {
            cforward_list_innerdat<T> *ptrA = firstInnerdat, *ptrB = firstInnerdat->next;
            while (ptrB != nullptr) {
                delete ptrA;
                ptrA = ptrB;
                ptrB = ptrB->next;
            }
        }
    }

private:
    cforward_list_innerdat<T> *firstInnerdat;
};

#endif //CFORWARD_LIST_H
