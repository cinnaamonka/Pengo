#pragma once
#include <thread>
#include <mutex>

namespace GameEngine
{
    template <typename T, size_t Capacity>
    class RingBuffer final
    {
    public:
        RingBuffer() : m_Head(0), m_Tail(0) {}
        ~RingBuffer() = default;
        RingBuffer(const RingBuffer& other) = delete;
        RingBuffer& operator=(const RingBuffer& other) = delete;
        RingBuffer(RingBuffer&& other) noexcept = delete;
        RingBuffer& operator=(RingBuffer&& other) noexcept = delete;

        const T& GetFront() const
        {
            assert(m_Head != m_Tail && "RingBuffer is empty");
            return m_Array[m_Head];
        }
        const T& PullFront()
        {
            assert(m_Head != m_Tail && "RingBuffer is empty");
            const T& value = m_Array[m_Head];
            m_Head = (m_Head + 1) % Capacity;
            return value;
        }
        T& PushBack()
        {
            assert((m_Tail + 1) % Capacity != m_Head && "RingBuffer overflow");
            T& value = m_Array[m_Tail];
            m_Tail = (m_Tail + 1) % Capacity;
            return value;
        }
        void PushBack(const T& value)
        {
            PushBack() = value;
        } 

        size_t GetPending() const
        {
            return (m_Head != m_Tail) ? (m_Tail > m_Head ? m_Tail - m_Head : Capacity - m_Head + m_Tail) : 0; 
        }

        size_t GetMaxPending() const 
        {
            return Capacity;
        }

    private:

        std::array<T, Capacity> m_Array{};
        size_t m_Head;
        size_t m_Tail;
    };
};
