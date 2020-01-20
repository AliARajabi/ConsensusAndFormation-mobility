//
// Generated file, do not edit! Created by nedtool 4.6 from FormPkt.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#include <iostream>
#include <sstream>
#include "FormPkt_m.h"

USING_NAMESPACE


// Another default rule (prevents compiler from choosing base class' doPacking())
template<typename T>
void doPacking(cCommBuffer *, T& t) {
    throw cRuntimeError("Parsim error: no doPacking() function for type %s or its base class (check .msg and _m.cc/h files!)",opp_typename(typeid(t)));
}

template<typename T>
void doUnpacking(cCommBuffer *, T& t) {
    throw cRuntimeError("Parsim error: no doUnpacking() function for type %s or its base class (check .msg and _m.cc/h files!)",opp_typename(typeid(t)));
}




// Template rule for outputting std::vector<T> types
template<typename T, typename A>
inline std::ostream& operator<<(std::ostream& out, const std::vector<T,A>& vec)
{
    out.put('{');
    for(typename std::vector<T,A>::const_iterator it = vec.begin(); it != vec.end(); ++it)
    {
        if (it != vec.begin()) {
            out.put(','); out.put(' ');
        }
        out << *it;
    }
    out.put('}');
    
    char buf[32];
    sprintf(buf, " (size=%u)", (unsigned int)vec.size());
    out.write(buf, strlen(buf));
    return out;
}

// Template rule which fires if a struct or class doesn't have operator<<
template<typename T>
inline std::ostream& operator<<(std::ostream& out,const T&) {return out;}

Register_Class(FormPkt);

FormPkt::FormPkt(const char *name, int kind) : ::cPacket(name,kind)
{
    this->destAddr_var = LAddress::L3BROADCAST;
    this->srcAddr_var = LAddress::L3BROADCAST;
    this->positionX_var = 0.00;
    this->positionY_var = 0.00;
    this->speedX_var = 0.00;
    this->speedY_var = 0.00;
    this->accelerationX_var = 0.00;
    this->accelerationY_var = 0.00;
}

FormPkt::FormPkt(const FormPkt& other) : ::cPacket(other)
{
    copy(other);
}

FormPkt::~FormPkt()
{
}

FormPkt& FormPkt::operator=(const FormPkt& other)
{
    if (this==&other) return *this;
    ::cPacket::operator=(other);
    copy(other);
    return *this;
}

void FormPkt::copy(const FormPkt& other)
{
    this->destAddr_var = other.destAddr_var;
    this->srcAddr_var = other.srcAddr_var;
    this->positionX_var = other.positionX_var;
    this->positionY_var = other.positionY_var;
    this->speedX_var = other.speedX_var;
    this->speedY_var = other.speedY_var;
    this->accelerationX_var = other.accelerationX_var;
    this->accelerationY_var = other.accelerationY_var;
}

void FormPkt::parsimPack(cCommBuffer *b)
{
    ::cPacket::parsimPack(b);
    doPacking(b,this->destAddr_var);
    doPacking(b,this->srcAddr_var);
    doPacking(b,this->positionX_var);
    doPacking(b,this->positionY_var);
    doPacking(b,this->speedX_var);
    doPacking(b,this->speedY_var);
    doPacking(b,this->accelerationX_var);
    doPacking(b,this->accelerationY_var);
}

void FormPkt::parsimUnpack(cCommBuffer *b)
{
    ::cPacket::parsimUnpack(b);
    doUnpacking(b,this->destAddr_var);
    doUnpacking(b,this->srcAddr_var);
    doUnpacking(b,this->positionX_var);
    doUnpacking(b,this->positionY_var);
    doUnpacking(b,this->speedX_var);
    doUnpacking(b,this->speedY_var);
    doUnpacking(b,this->accelerationX_var);
    doUnpacking(b,this->accelerationY_var);
}

LAddress::L3Type& FormPkt::getDestAddr()
{
    return destAddr_var;
}

void FormPkt::setDestAddr(const LAddress::L3Type& destAddr)
{
    this->destAddr_var = destAddr;
}

LAddress::L3Type& FormPkt::getSrcAddr()
{
    return srcAddr_var;
}

void FormPkt::setSrcAddr(const LAddress::L3Type& srcAddr)
{
    this->srcAddr_var = srcAddr;
}

double FormPkt::getPositionX() const
{
    return positionX_var;
}

void FormPkt::setPositionX(double positionX)
{
    this->positionX_var = positionX;
}

double FormPkt::getPositionY() const
{
    return positionY_var;
}

void FormPkt::setPositionY(double positionY)
{
    this->positionY_var = positionY;
}

double FormPkt::getSpeedX() const
{
    return speedX_var;
}

void FormPkt::setSpeedX(double speedX)
{
    this->speedX_var = speedX;
}

double FormPkt::getSpeedY() const
{
    return speedY_var;
}

void FormPkt::setSpeedY(double speedY)
{
    this->speedY_var = speedY;
}

double FormPkt::getAccelerationX() const
{
    return accelerationX_var;
}

void FormPkt::setAccelerationX(double accelerationX)
{
    this->accelerationX_var = accelerationX;
}

double FormPkt::getAccelerationY() const
{
    return accelerationY_var;
}

void FormPkt::setAccelerationY(double accelerationY)
{
    this->accelerationY_var = accelerationY;
}

class FormPktDescriptor : public cClassDescriptor
{
  public:
    FormPktDescriptor();
    virtual ~FormPktDescriptor();

    virtual bool doesSupport(cObject *obj) const;
    virtual const char *getProperty(const char *propertyname) const;
    virtual int getFieldCount(void *object) const;
    virtual const char *getFieldName(void *object, int field) const;
    virtual int findField(void *object, const char *fieldName) const;
    virtual unsigned int getFieldTypeFlags(void *object, int field) const;
    virtual const char *getFieldTypeString(void *object, int field) const;
    virtual const char *getFieldProperty(void *object, int field, const char *propertyname) const;
    virtual int getArraySize(void *object, int field) const;

    virtual std::string getFieldAsString(void *object, int field, int i) const;
    virtual bool setFieldAsString(void *object, int field, int i, const char *value) const;

    virtual const char *getFieldStructName(void *object, int field) const;
    virtual void *getFieldStructPointer(void *object, int field, int i) const;
};

Register_ClassDescriptor(FormPktDescriptor);

FormPktDescriptor::FormPktDescriptor() : cClassDescriptor("FormPkt", "cPacket")
{
}

FormPktDescriptor::~FormPktDescriptor()
{
}

bool FormPktDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<FormPkt *>(obj)!=NULL;
}

const char *FormPktDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int FormPktDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 8+basedesc->getFieldCount(object) : 8;
}

unsigned int FormPktDescriptor::getFieldTypeFlags(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeFlags(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISCOMPOUND,
        FD_ISCOMPOUND,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
    };
    return (field>=0 && field<8) ? fieldTypeFlags[field] : 0;
}

const char *FormPktDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "destAddr",
        "srcAddr",
        "positionX",
        "positionY",
        "speedX",
        "speedY",
        "accelerationX",
        "accelerationY",
    };
    return (field>=0 && field<8) ? fieldNames[field] : NULL;
}

int FormPktDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='d' && strcmp(fieldName, "destAddr")==0) return base+0;
    if (fieldName[0]=='s' && strcmp(fieldName, "srcAddr")==0) return base+1;
    if (fieldName[0]=='p' && strcmp(fieldName, "positionX")==0) return base+2;
    if (fieldName[0]=='p' && strcmp(fieldName, "positionY")==0) return base+3;
    if (fieldName[0]=='s' && strcmp(fieldName, "speedX")==0) return base+4;
    if (fieldName[0]=='s' && strcmp(fieldName, "speedY")==0) return base+5;
    if (fieldName[0]=='a' && strcmp(fieldName, "accelerationX")==0) return base+6;
    if (fieldName[0]=='a' && strcmp(fieldName, "accelerationY")==0) return base+7;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *FormPktDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldTypeStrings[] = {
        "LAddress::L3Type",
        "LAddress::L3Type",
        "double",
        "double",
        "double",
        "double",
        "double",
        "double",
    };
    return (field>=0 && field<8) ? fieldTypeStrings[field] : NULL;
}

const char *FormPktDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldProperty(object, field, propertyname);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        default: return NULL;
    }
}

int FormPktDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    FormPkt *pp = (FormPkt *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string FormPktDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    FormPkt *pp = (FormPkt *)object; (void)pp;
    switch (field) {
        case 0: {std::stringstream out; out << pp->getDestAddr(); return out.str();}
        case 1: {std::stringstream out; out << pp->getSrcAddr(); return out.str();}
        case 2: return double2string(pp->getPositionX());
        case 3: return double2string(pp->getPositionY());
        case 4: return double2string(pp->getSpeedX());
        case 5: return double2string(pp->getSpeedY());
        case 6: return double2string(pp->getAccelerationX());
        case 7: return double2string(pp->getAccelerationY());
        default: return "";
    }
}

bool FormPktDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    FormPkt *pp = (FormPkt *)object; (void)pp;
    switch (field) {
        case 2: pp->setPositionX(string2double(value)); return true;
        case 3: pp->setPositionY(string2double(value)); return true;
        case 4: pp->setSpeedX(string2double(value)); return true;
        case 5: pp->setSpeedY(string2double(value)); return true;
        case 6: pp->setAccelerationX(string2double(value)); return true;
        case 7: pp->setAccelerationY(string2double(value)); return true;
        default: return false;
    }
}

const char *FormPktDescriptor::getFieldStructName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        case 0: return opp_typename(typeid(LAddress::L3Type));
        case 1: return opp_typename(typeid(LAddress::L3Type));
        default: return NULL;
    };
}

void *FormPktDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    FormPkt *pp = (FormPkt *)object; (void)pp;
    switch (field) {
        case 0: return (void *)(&pp->getDestAddr()); break;
        case 1: return (void *)(&pp->getSrcAddr()); break;
        default: return NULL;
    }
}


