#pragma once

#include "MainAPI/MainAPI.h"
#include "Singleton/SingletonClass.h"
#include <string>

class MAINDLL_API QrCodeManager : 
    public SingletonClass<QrCodeManager>
{
    friend class SingletonClass<QrCodeManager>;

protected:
    QrCodeManager();
    virtual ~QrCodeManager();

public:
    void generateQRImage(std::string content, int scale);

private:

};
