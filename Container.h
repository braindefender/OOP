//
// Created by Nikita Shirokov on 2019-05-18.
//

#ifndef OOP_CONTAINER_H
#define OOP_CONTAINER_H
template <class T>
class Container {
private:
    struct Node {
        T * value;
        Node * prev;
        Node * next;
        Node(T * value, Node * prev, Node * next);
        ~Node();
    };

    Node * m_head;
    int m_count;

    void removeNode(Node * node) {
        node->prev->next = node->next;
        node->next->prev = node->prev;
        delete(node);
        m_count -= 1;
    }
public:
    class Iterator {
        friend class Container;
    public:
        T * iterItem(){
            return this->iterNode->value;
        }

        void next() {
            Node * t_head = this->iterList->m_head;
            Node * t_next = this->iterNode->next;
            if (t_next == t_head) {
                t_next = t_next->next;
            }
            this->iterNode = t_next;
        }

        void prev() {
            Node * t_head = this->iterList->m_head;
            Node * t_prev = this->iterNode->prev;
            if (t_prev == t_head){
                t_prev = t_prev->prev;
            }
            this->iterNode = t_prev;
        }

        bool operator==(Container<T>::Iterator const & right) const {
            return ((this->iterList == right.iterList) && (this->iterNode == right.iterNode));
        }

    private:
        Node * iterNode;
        const Container<T> * iterList;
    };

    Container() {
        Node * node = new Node(nullptr, nullptr, nullptr);
        node->prev = node;
        node->next = node;
        this->m_head = node;
        m_count = 0;
    }

    ~Container() {
        this->clear();
    }

    T * unshift(T * elem) {
        Node * temp = new Node(elem, m_head, m_head->next);
        m_head->next->prev = temp;
        m_head->next = temp;
        m_count += 1;
        return temp->value;
    }

    T * push(T * elem) {
        Node * temp = new Node(elem, m_head->prev, m_head);
        m_head->prev->next = temp;
        m_head->prev = temp;
        m_count += 1;
        return temp->value;
    }

    void shift() {
        Node * temp = m_head->next;
        try {
            if (temp != m_head){
                this->removeNode(temp);
            } else {
                throw std::exception();
            }
        } catch (std::exception & e) {
            std::cout << "Container exception: list is empty";
        }
    }

    void pop() {
        Node * temp = m_head->prev;
        try {
            if (temp != m_head){
                this->removeNode(temp);
            } else {
                throw std::exception();
            }
        } catch (std::exception & e) {
            std::cout << "Container exception: list is empty";
        }
    }

    void clear() {
        Node * node = m_head->next;
        while (node != m_head) {
            Node * temp = node;
            node = node->next;
            delete temp;
        }
        m_head->prev = m_head;
        m_head->next = m_head;
        m_count = 0;
    }

    T * getFirst() const {
        return m_head->next->value;
    }

    T * getLast() const {
        return m_head->prev->value;
    }

    int getLength() const {
        return m_count;
    }

    bool isEmpty() const {
        return m_count == 0;
    }

    Iterator begin();
    Iterator end();

};

template <class T>
typename Container<T>::Iterator Container<T>::begin() {
    Container<T>::Iterator iterator;
    iterator.iterList = this;
    iterator.iterNode = this->m_head->next;
    return iterator;
}

template <class T>
typename Container<T>::Iterator Container<T>::end(){
    Container<T>::Iterator iterator;
    iterator.iterList = this;
    iterator.iterNode = this->m_head->prev;
    return iterator;
}

template <class T>
Container<T>::Node::Node(T * value, Node * prev, Node * next) {
    this->value = value;
    this->prev = prev;
    this->next = next;
}

template<class T>
Container<T>::Node::~Node() {
    delete value;
}

#endif //OOP_CONTAINER_H
