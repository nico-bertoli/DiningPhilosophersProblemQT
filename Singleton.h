#ifndef SINGLETON_H
#define SINGLETON_H

template <typename T>
class Singleton
{
//---------------------------------------------------------- Fields
public:
    static T& Instance()
    {
        static T instance;
        return instance;
    }

//---------------------------------------------------------- Methods
public:
    //prevent copy
    Singleton(const Singleton&) = delete;
    Singleton& operator = (const Singleton&) = delete;
    Singleton(Singleton&&) = delete;
    Singleton& operator = (const Singleton&&) = delete;

protected:
    // prevent direct instantiation
    Singleton() = default;
    virtual ~Singleton() = default;
};

#endif
