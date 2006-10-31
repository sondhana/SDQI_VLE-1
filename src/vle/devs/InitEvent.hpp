/**
 * @file InitEvent.hpp
 * @author The VLE Development Team.
 * @brief Initialisation event use to initialise models using initialisation
 * port. To each port, a Value objet can be attached.
 */

/*
 * Copyright (c) 2004, 2005 The VLE Development Team.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA
 * 02111-1307, USA.
 */

#ifndef DEVS_INIT_EVENT_HPP
#define DEVS_INIT_EVENT_HPP

#include <vle/devs/Event.hpp>

namespace vle { namespace devs {

    /**
     * @brief Initialisation event use to initialise models using initialisation
     * port. To each port, a Value objet can be attached.
     *
     */
    class InitEvent : public Event
    {
    public:
	InitEvent(const Time& time, sAtomicModel* model,
		  const std::string& portName) :
            Event(time, model),
            m_portName(portName)
        { }

	InitEvent(InitEvent const & event) :
            Event(event),
            m_portName(event.m_portName)
        { }

	virtual ~InitEvent()
        { }

	inline const std::string & getPortName() const
        { return m_portName; }

	virtual bool isExternal() const;

	virtual bool isInit() const;

	virtual bool isInternal() const;

	virtual bool isState() const;

	inline bool onPort(std::string const & portName) const
        { return m_portName == portName; }

    private:
	std::string         m_portName;
    };

}} // namespace vle devs

#endif
