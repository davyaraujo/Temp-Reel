#include "Chrono.h"

Chrono::Chrono()
{

}  

void Chrono::restart(){
    m_startTime = timespec_now();
    m_stopTime = m_startTime;
}

timespec Chrono::stop(){
    m_stopTime = timespec_now();
    return (operator-(m_stopTime,m_startTime));
}

bool Chrono::isActice(){
    if (operator==(m_stopTime,m_startTime)){
        return true;
    }
    return false;
    
}

timespec Chrono::lap(){
    if (isActice()){
        return(operator-(timespec_now(),m_startTime));
    }
    else{
        return (operator-(m_stopTime,m_startTime));
    }
}


double Chrono::lap_ms(){
    return timespec_to_ms(lap());
}
