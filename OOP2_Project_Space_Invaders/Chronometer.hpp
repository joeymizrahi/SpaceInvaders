#pragma once
#include <SFML/System/Clock.hpp>

namespace sftools
{
    class Chronometer
    {
    public:
		//-----------------------------------------------------------------------------
        Chronometer(sf::Time initialTime = sf::Time::Zero)
        {
            reset();
            add(initialTime);
        }
		//-----------------------------------------------------------------------------
        sf::Time add(sf::Time time)
        {
            m_time += time;

            if (m_state == STOPPED) m_state = PAUSED;

            return getElapsedTime();
        }
		//-----------------------------------------------------------------------------
        sf::Time reset(bool start = false)
        {
            sf::Time time = getElapsedTime();

            m_time = sf::Time::Zero;
            m_state = STOPPED;

            if (start) resume();

            return time;
        }
		//-----------------------------------------------------------------------------
        sf::Time pause()
        {
            if (isRunning())
            {
                m_state = PAUSED;
                m_time += m_clock.getElapsedTime();
            }
            return getElapsedTime();
        }
		//-----------------------------------------------------------------------------
        sf::Time resume()
        {
            if (!isRunning())
            {
                m_state = RUNNING;
                m_clock.restart();

            }
            return getElapsedTime();
        }
		//-----------------------------------------------------------------------------
        sf::Time toggle()
        {
            if (isRunning())    pause();
            else                resume();

            return getElapsedTime();
        }
		//-----------------------------------------------------------------------------
        bool isRunning() const
        {
            return m_state == RUNNING;
        }
		//-----------------------------------------------------------------------------
        sf::Time getElapsedTime() const
        {
            switch (m_state) {
                case STOPPED:
                    return sf::Time::Zero;

                case RUNNING:
                    return m_time + m_clock.getElapsedTime();

                case PAUSED:
                    return m_time;

				default:
					return sf::Time::Zero;
            }
        }
		//-----------------------------------------------------------------------------
        operator sf::Time() const
        {
            return getElapsedTime();
        }

    private:
        enum { STOPPED, RUNNING, PAUSED } m_state;  //!< state
        sf::Time m_time;                            //!< time counter
        sf::Clock m_clock;                          //!< clock
    };
}