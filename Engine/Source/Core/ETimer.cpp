#include "ETimer.h"

void Time::Tick()
{
	clock19::duration duration = clock19::now() - m_startTime;
	m_time = duration.count() / (float)clock19::duration::period::den;

	duration = clock19::now() - m_frameTime;
	m_deltaTime = duration.count() / (float)clock19::duration::period::den;
	
	m_frameTime = clock19::now();
}
