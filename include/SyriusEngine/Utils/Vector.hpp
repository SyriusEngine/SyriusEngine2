#pragma once

#include "../Include.hpp"
#include "../Debug.hpp"

namespace Syrius{

    inline Size defaultGrowFunc(Size previousSize){
        return previousSize * 2;
    }

    typedef Size (*GrowFunc)(Size previousSize);

    template<typename T>
    class Iterator {
    public:
        using iterator_category = std::random_access_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = T*;
        using reference = T&;

        Iterator(pointer ptr) : m_Ptr(ptr) {}

        reference operator*() const { return *m_Ptr; }
        pointer operator->() const { return m_Ptr; }

        Iterator& operator++() {
            m_Ptr++;
            return *this;
        }

        Iterator operator++(int) {
            Iterator tmp = *this;
            ++(*this);
            return tmp;
        }

        Iterator& operator--() {
            m_Ptr--;
            return *this;
        }

        Iterator operator--(int) {
            Iterator tmp = *this;
            --(*this);
            return tmp;
        }

        reference operator[](Size index){
            return *(m_Ptr + index);
        }

        bool operator==(const Iterator& other) const{
            return m_Ptr == other.m_Ptr;
        }

        bool operator!=(const Iterator& other) const{
            return m_Ptr != other.m_Ptr;
        }

        bool operator<(const Iterator& other) const{
            return m_Ptr < other.m_Ptr;
        }

        bool operator>(const Iterator& other) const{
            return m_Ptr > other.m_Ptr;
        }

        bool operator<=(const Iterator& other) const{
            return m_Ptr <= other.m_Ptr;
        }

        bool operator>=(const Iterator& other) const{
            return m_Ptr >= other.m_Ptr;
        }

        Iterator operator+(Size offset) const{
            return Iterator(m_Ptr + offset);
        }

        Iterator operator-(Size offset) const{
            return Iterator(m_Ptr - offset);
        }

    private:
        pointer m_Ptr;
    };


    template<typename T>
    class SR_API Vector{
    public:
        Vector():
        m_Count(0),
        m_Size(2), // default size
        m_Data(nullptr),
        m_GrowFunc(defaultGrowFunc){
            m_Data = (T*) malloc(sizeof(T) * m_Size);

        }

        Vector(Size size):
        m_Count(0),
        m_Size(size),
        m_Data(nullptr),
        m_GrowFunc(defaultGrowFunc){
            m_Data = (T*) malloc(sizeof(T) * m_Size);;
        }

        ~Vector(){
            for (Size i = 0; i < m_Count; ++i){
                m_Data[i].~T();
            }
            free(m_Data);
        }

        template<typename... Args>
        void emplaceBack(Args&&... args){
            if (m_Count == m_Size){
                resize();
            }
            new (m_Data + m_Count++) T(std::forward<Args>(args)...);
        }

        const T& operator[](Size index) const {
            SR_PRECONDITION(index < m_Count, SR_MESSAGE_SOURCE::SR_MESSAGE_GENERAL, "Index out of bounds");
            return m_Data[index];
        }

        T& operator[](Size index){
            SR_PRECONDITION(index < m_Count, SR_MESSAGE_SOURCE::SR_MESSAGE_GENERAL, "Index out of bounds");
            return m_Data[index];
        }

        const T& at(Size index) const {
            SR_PRECONDITION(index < m_Count, SR_MESSAGE_SOURCE::SR_MESSAGE_GENERAL, "Index out of bounds");
            return m_Data[index];
        }

        T& at(Size index){
            SR_PRECONDITION(index < m_Count, SR_MESSAGE_SOURCE::SR_MESSAGE_GENERAL, "Index out of bounds");
            return m_Data[index];
        }

        Iterator<T> begin(){
            return Iterator<T>(m_Data);
        }

        Iterator<T> end(){
            return Iterator<T>(m_Data + m_Count);
        }

        T& back(){
            SR_PRECONDITION(m_Count > 0, SR_MESSAGE_SOURCE::SR_MESSAGE_GENERAL, "Vector is empty");
            return m_Data[m_Count - 1];
        }

        const T& back() const{
            SR_PRECONDITION(m_Count > 0, SR_MESSAGE_SOURCE::SR_MESSAGE_GENERAL, "Vector is empty");
            return m_Data[m_Count - 1];
        }

        void popBack(){
            SR_PRECONDITION(m_Count > 0, SR_MESSAGE_SOURCE::SR_MESSAGE_GENERAL, "Vector is empty");
            m_Data[--m_Count].~T();
        }

        void clear(){
            for (Size i = 0; i < m_Count; ++i){
                m_Data[i].~T();
            }
            m_Count = 0;
        }


    private:

        void resize(){
            SR_PRECONDITION(m_GrowFunc != nullptr, SR_MESSAGE_SOURCE::SR_MESSAGE_GENERAL, "Grow function is not set");
            SR_PRECONDITION(m_Size > 0, SR_MESSAGE_SOURCE::SR_MESSAGE_GENERAL, "Size is 0");

            auto newSize = m_GrowFunc(m_Size);

            /**
             *  The main difference with an STD vector is that the objects are simply moved to the old location,
             *  their destructors are not called. The destructors are called when the vector is destroyed.
             */
            T* newData = (T*) malloc(sizeof(T) * newSize);
            memcpy(newData, m_Data, sizeof(T) * m_Count);

            free(m_Data);

            m_Data = newData;
            m_Size = newSize;
        }

    private:
        Size m_Count; // number of elements
        Size m_Size; // size of the array
        T* m_Data;
        GrowFunc m_GrowFunc;



    };

}