#include "playthread.h"

playthread::playthread()
{

}

void playthread::stop()
{
    stopped=true;
    m_yaoqi.setBrun(false);

}

void playthread::run()
{
    stopped=false;
    m_yaoqi.run();
    m_yaoqi.setBrun(true);
}
