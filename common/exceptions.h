#ifndef EXCEPTIONS
#define EXCEPTIONS
#include <QString>
class Exception {
public:
    enum class Type {
        File,
        NotSupported
    };
    Exception(Type t, QString _msg):
        type(t), msg(_msg) {}

    Type type;
    QString msg;   
};

#endif // EXCEPTIONS

