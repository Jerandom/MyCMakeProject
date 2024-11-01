#include "Singleton/SingletonClass.h"
#include "QRGenerator/QrCodeInterface.h"
#include "CMakeLibrary.h"
#include "SubjectClass.h"

template<typename T>
T* SingletonClass<T>::SingletonInstance = nullptr;

template <typename T>
T& SingletonClass<T>::instance() 
{
    if (nullptr == SingletonInstance)
    {
        SingletonInstance = new T;
    }
    return *SingletonInstance;
}
 
template class SingletonClass<SubjectClass>;
template class SingletonClass<CMakeLibrary>;
template class SingletonClass<QrCodeInterface>;
