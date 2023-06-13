#include "logininstance.h"

// 声明
LoginInstance LoginInstance::m_login;
LoginInstance *LoginInstance::getInstance()
{
    return &m_login;
}

void LoginInstance::setUserName(QString name)
{
    m_user = name;
}

QString LoginInstance::getName()
{
    return m_user;
}

LoginInstance::LoginInstance()
{

}

LoginInstance::LoginInstance(const LoginInstance &t)
{

}
