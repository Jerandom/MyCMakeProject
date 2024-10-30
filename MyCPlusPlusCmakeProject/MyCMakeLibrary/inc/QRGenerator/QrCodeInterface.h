#ifndef _QRCODE_INTERFACE_H
#define _QRCODE_INTERFACE_H

#include "MainAPI/MainAPI.h"
#include "Singleton/SingletonClass.h"
#include <string>

class MAINDLL_API QrCodeInterface : 
    public SingletonClass<QrCodeInterface>
{
    friend class SingletonClass<QrCodeInterface>;

protected:
    QrCodeInterface();
    virtual ~QrCodeInterface();

public:
    void generateQRImage(std::string content, int scale);

    void generateHighResQRCode(const std::string& text, int scale, int border);

private:

};

#endif /* _QRCODE_INTERFACE_H */
