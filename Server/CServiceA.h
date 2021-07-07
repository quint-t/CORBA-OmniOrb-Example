#ifndef CSERVICEA_H
#define CSERVICEA_H

#include "../Data.hh"

class CServiceA_i : public POA_Data::ServiceA,
                    public PortableServer::RefCountServantBase
{
public:
    CServiceA_i();
    virtual ~CServiceA_i();
    virtual char *HelloWorld(const char *) override;
    virtual CORBA::Boolean Div(CORBA::Long, CORBA::Long, CORBA::Long &) override;
    virtual void CaesarCipher(char *&, CORBA::Short) override;
};

#endif // CSERVICEA_H