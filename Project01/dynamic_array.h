//
//  dynamic_array.h
//  Project01
//
//  Created by Ольга Полевик on 03.08.2021.
//

#ifndef dynamic_array_h
#define dynamic_array_h

using namespace std;

template <class Data>
class dynamic_array
{
public:
    explicit dynamic_array (int n)
    {
        if (n > 0)
        {
            m_data = new Data[n];
        }
        else
        {
            m_data = nullptr;
        }
        m_size = n;
        m_capacity = n;
    };
    dynamic_array(const dynamic_array<Data> & a)
    {
        m_size = a.m_size;
        m_capacity = m_size;
        if (m_size != 0)
        {
            m_data = new Data[m_size];
        }
        else
        {
            m_data = nullptr;
        }
        for (int i = 0; i < m_size; ++i)
        {
            m_data[i] = a.m_data[i];
        }
    }
    
    ~dynamic_array()
    {
        delete[] m_data;
    }
    
    void resize(int size)
    {
        if (size > m_capacity)
        {
            int new_capacity = max(size, m_size * 2);
            Data * new_data = new Data[new_capacity];
            for (int i = 0; i < m_size; ++i)
            {
                new_data[i] = m_data[i];
            }
            delete[] m_data;
            m_data = new_data;
            m_capacity = new_capacity;
        }
        m_size = size;
    }
    
    void push_back(const Data& val)
    {
        resize(m_size + 1);
        m_data[m_size - 1] = val;
    }
    
    int size() const
    {
        return m_size;
    }
    
    Data& operator[] (int i)
    {
        return m_data[i];
    }
    
private:
    int m_size = 0;
    int m_capacity = 0;
    Data *m_data = nullptr;
};

template<class Data>
ostream & operator << (ostream & out, dynamic_array<Data> a)
{
    for (int i = 0; i < a.size(); ++i)
    {
        out << a[i] << " ";
    }
    return out;
}
#endif /* dynamic_array_h */
