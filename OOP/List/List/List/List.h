#pragma once

#include <iostream>

template <typename T>
class List
{
	struct Node;

public:
	template <typename ItemType>
	class TemplateIterator;
	using iterator = TemplateIterator<T>;
	using const_iterator = TemplateIterator<const T>;
public:
	List();
	~List();

	iterator begin();
	iterator end();
	const_iterator begin() const;
	const_iterator end() const;

	int size() const;
	void clear();
	void swap(List& other);
	void push_front(const T& value);
	void append(const T& value);
	void insert(int pos, const T& value);
	void insert_after(const T& key, const T& value);
	iterator insert(iterator pos, const T& value);
	void pop_front();
	void pop_back();
	void erase(int pos);
	void erase(const T& key);
	iterator erase(iterator pos);
	iterator erase(iterator first, iterator last);
	const T& max() const;
	T min() const;
	bool isEmpty() const;
	void input();
	void print() const;
	iterator find(const T& value);
	const_iterator find(const T& value) const;

private:
	int m_size = 0;
	Node* m_head = nullptr;
	Node* m_tail = nullptr;
};

template <typename T>
struct List<T>::Node
{
	Node(Node* next = nullptr, Node* prev = nullptr);
	Node(const T& value, Node* next = nullptr, Node* prev = nullptr);

	T value;
	Node* next = nullptr;
	Node* prev = nullptr;
};

template <typename T>
template <typename ItemType>
class List<T>::TemplateIterator
{
    friend class List<T>;
public:
	using value_type = ItemType;
	using reference = ItemType&;
	using pointer = ItemType*;
	using iterator_category = std::bidirectional_iterator_tag;
	using difference_type = int;

	TemplateIterator(Node* node);

	ItemType& operator*();
	const ItemType& operator*() const;
	TemplateIterator operator++();
	TemplateIterator operator--();
	TemplateIterator operator++(int);
	TemplateIterator operator--(int);
	TemplateIterator operator=(const TemplateIterator& other);
	bool operator==(const TemplateIterator& other) const;
	bool operator!=(const TemplateIterator& other) const;
	ItemType& operator[](int index);
	const ItemType& operator[](int index) const;
	TemplateIterator operator+(const List<T>& other) const;
	TemplateIterator operator+=(const List<T>& other);

private:
	Node* m_node = nullptr;
};

template <typename T>
List<T>::List()
    : m_head(new Node())
    , m_tail(new Node())
{
    m_head->next = m_tail;
    m_tail->prev = m_head;
}

template <typename T>
List<T>::~List()
{
    clear();
    delete m_head;
    delete m_tail;
}

template <typename T> typename
List<T>::iterator List<T>::begin()
{
    return iterator(m_head->next);
}

template <typename T> typename
List<T>::iterator List<T>::end()
{
    return iterator(m_tail);
}

template <typename T>
typename List<T>::const_iterator List<T>::begin() const
{
    return const_iterator(m_head->next);
}

template <typename T>
typename List<T>::const_iterator List<T>::end() const
{
    return const_iterator(m_tail);
}

template <typename T>
int List<T>::size() const
{
    return m_size;
}

template <typename T>
void List<T>::clear()
{
    if (!size())
    {
        return;
    }

    Node* runner = m_head->next;
    while (runner != m_tail)
    {
        Node* node = runner;
        runner = runner->next;
        delete node;
    }
    m_head->next = m_tail;
    m_tail->prev = m_head;
    m_size = 0;
}

template <typename T>
void List<T>::swap(List& other) {
    std::swap(m_head, other.m_head);
    std::swap(m_tail, other.m_tail);
    std::swap(m_size, other.m_size);
}

template <typename T>
void List<T>::push_front(const T& value) {
    Node* node = new Node(value, m_head->next, m_head);
    m_head->next->prev = node;
    m_head->next = node;
    ++m_size;
}

template <typename T>
void List<T>::append(const T& value)
{
    Node* node = new Node(value, m_tail, m_tail->prev);
    m_tail->prev->next = node;
    m_tail->prev = node;
    ++m_size;
}

template <typename T>
void List<T>::insert(int pos, const T& value) {
    if (pos < 0 || pos > m_size) {
        throw std::out_of_range("Position out of range");
    }
    if (pos == m_size) {
        append(value);
        return;
    }
    Node* current = m_head->next;
    for (int i = 0; i < pos; ++i) {
        current = current->next;
    }
    Node* node = new Node(value, current, current->prev);
    current->prev->next = node;
    current->prev = node;
    ++m_size;
}

template <typename T>
void List<T>::insert_after(const T& key, const T& value) {
    Node* current = m_head->next;
    while (current != m_tail && current->value != key) {
        current = current->next;
    }
    if (current == m_tail) {
        return;
    }
    Node* node = new Node(value, current->next, current);
    current->next->prev = node;
    current->next = node;
    ++m_size;
}

template <typename T> typename
List<T>::iterator List<T>::insert(iterator pos, const T& value) {
    Node* node = new Node(value, pos.m_node, pos.m_node->prev);
    pos.m_node->prev->next = node;
    pos.m_node->prev = node;
    ++m_size;
    return iterator(node);
}

template <typename T>
void List<T>::pop_front() {
    if (m_size == 0) {
        throw std::out_of_range("List is empty");
    }
    Node* node = m_head->next;
    m_head->next = node->next;
    node->next->prev = m_head;
    delete node;
    --m_size;
}

template <typename T>
void List<T>::pop_back() {
    if (m_size == 0) {
        throw std::out_of_range("List is empty");
    }
    Node* node = m_tail->prev;
    m_tail->prev = node->prev;
    node->prev->next = m_tail;
    delete node;
    --m_size;
}

template <typename T>
void List<T>::erase(int pos) {
    if (pos < 0 || pos >= m_size) {
        throw std::out_of_range("Position out of range");
    }
    iterator it = begin();
    while (pos > 0) {
        it++;
        pos--;
    }
    erase(it);
}

template <typename T>
void List<T>::erase(const T& key) {
    erase(find(key));
}

template <typename T>
typename List<T>::iterator List<T>::erase(iterator pos) {
    if (pos == end()) {
        return pos;
    }
    Node* node = pos.m_node;
    node->prev->next = node->next;
    node->next->prev = node->prev;
    delete node;
    --m_size;
    return iterator(node->next);
}

template <typename T>
typename List<T>::iterator List<T>::erase(iterator first, iterator last) {
    if (first == last || first == end())
        return last;

    Node* current = first.m_node;
    while (current != last.m_node) {
        Node* next = current->next;
        current->prev->next = current->next;
        current->next->prev = current->prev;
        delete current;
        --m_size;
        current = next;
    }
    return last;
}

template <typename T>
const T& List<T>::max() const {
    if (m_size == 0) {
        static T default_value{};
        return default_value;
    }
    const_iterator it = begin();
    const_iterator max = it;
    it++;
    for (; it != end(); ++it) {
        if (*it > *max) {
            max = it;
        }
    }
    return *max;
}

template <typename T>
T List<T>::min() const {
    if (m_size == 0) {
        throw std::out_of_range("List is empty");
    }
    T min_value = std::numeric_limits<T>::max();
    for (const_iterator it = begin(); it != end(); ++it) {
        if (*it < min_value) {
            min_value = *it;
        }
    }
    return min_value;
}

template <typename T>
bool List<T>::isEmpty() const {
    return m_size == 0;
}

template <typename T>
void List<T>::input() {
    clear();
    T value;
    while (std::cin >> value) {
        append(value);
    }
}

template <typename T>
void List<T>::print() const
{
    // Print with iterator
    for (const_iterator it = begin(); it != end(); ++it)
    {
        std::cout << *it << ' ';
    }
    std::cout << "\n";
}

template <typename T>
typename List<T>::iterator List<T>::find(const T& value) {
    for (iterator it = begin(); it != end(); ++it) {
        if (*it == value) {
            return it;
        }
    }
    return end();
}

template <typename T>
typename List<T>::const_iterator List<T>::find(const T& value) const {
    for (const_iterator it = begin(); it != end(); ++it) {
        if (*it == value) {
            return it;
        }
    }
    return end();
}

template <typename T>
List<T>::Node::Node(Node* next, Node* prev)
    : next(next)
    , prev(prev)
{}

template <typename T>
List<T>::Node::Node(const T& value, Node* next, Node* prev)
    : value(value)
    , next(next)
    , prev(prev)
{}

template <typename T>
template <typename ItemType>
List<T>::TemplateIterator<ItemType>::TemplateIterator(Node* node)
    : m_node(node)
{}

template <typename T>
template <typename ItemType>
ItemType& List<T>::TemplateIterator<ItemType>::operator*()
{
    return m_node->value;
}

template <typename T>
template <typename ItemType>
const ItemType& List<T>::TemplateIterator<ItemType>::operator*() const
{
    return m_node->value;
}

template <typename T>
template <typename ItemType>
typename List<T>::template
TemplateIterator<ItemType> List<T>::TemplateIterator<ItemType>::operator++()
{
    m_node = m_node->next;
    return *this;
}

template <typename T>
template <typename ItemType>
typename List<T>::template
TemplateIterator<ItemType> List<T>::TemplateIterator<ItemType>::operator--()
{
    m_node = m_node->prev;
    return *this;
}

template <typename T>
template <typename ItemType>
typename List<T>::template
TemplateIterator<ItemType> List<T>::TemplateIterator<ItemType>::operator++(int)
{
    TemplateIterator old = *this;
    m_node = m_node->next;
    return old;
}

template <typename T>
template <typename ItemType>
typename List<T>::template
TemplateIterator<ItemType> List<T>::TemplateIterator<ItemType>::operator--(int)
{
    TemplateIterator old = *this;
    m_node = m_node->prev;
    return old;
}

template <typename T>
template <typename ItemType>
bool List<T>::TemplateIterator<ItemType>::operator==(const TemplateIterator& other) const
{
    return (m_node == other.m_node);
}

template <typename T>
template <typename ItemType>
bool List<T>::TemplateIterator<ItemType>::operator!=(const TemplateIterator& other) const
{
    return (m_node != other.m_node);
}

template <typename T>
template <typename ItemType>
typename List<T>::template
TemplateIterator<ItemType> List<T>::TemplateIterator<ItemType>::operator=(const TemplateIterator& other) {
    m_node = other.m_node;
    return *this;
}

template <typename T>
template <typename ItemType>
ItemType& List<T>::TemplateIterator<ItemType>:: operator[](int index) {
    if (index < 0 || index >= m_size) {
        throw std::out_of_range("Index out of range");
    }
    Node* current = m_head->next;
    for (int i = 0; i < index; ++i) {
        current = current->next;
    }
    return current->data;
}

template <typename T>
template <typename ItemType>
const ItemType& List<T>::TemplateIterator<ItemType>::operator[](int index) const {
    if (index < 0 || index >= m_size) {
        throw std::out_of_range("Index out of range");
    }
    Node* current = m_head->next;
    for (int i = 0; i < index; ++i) {
        current = current->next;
    }
    return current->data;
}

template <typename T>
template <typename ItemType>
typename List<T>::template
TemplateIterator<ItemType> List<T>::TemplateIterator<ItemType>::operator+(const List<T>& other) const {
    List<T> result = *this;
    for (const_iterator it = other.begin(); it != other.end(); ++it) {
        result.push_back(*it);
    }
    return result;
}

template <typename T>
template <typename ItemType>
typename List<T>::template
TemplateIterator<ItemType> List<T>::TemplateIterator<ItemType>:: operator+=(const List<T>& other) {
    for (const_iterator it = other.begin(); it != other.end(); ++it) {
        this->push_back(*it);
    }
    return *this;
}