/**
 * @file vle/vpz/Condition.cpp
 * @author The VLE Development Team
 * See the AUTHORS or Authors.txt file
 */

/*
 * VLE Environment - the multimodeling and simulation environment
 * This file is a part of the VLE environment
 * http://www.vle-project.org
 *
 * Copyright (C) 2003-2007 Gauthier Quesnel quesnel@users.sourceforge.net
 * Copyright (C) 2007-2010 INRA http://www.inra.fr
 * Copyright (C) 2003-2010 ULCO http://www.univ-littoral.fr
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */


#include <vle/vpz/Condition.hpp>
#include <vle/utils/Debug.hpp>
#include <vle/utils/Algo.hpp>
#include <vle/value/Value.hpp>
#include <vle/value/Set.hpp>
#include <vle/value/Deleter.hpp>
#include <boost/utility.hpp>

namespace vle { namespace vpz {

Condition::Condition(const std::string& name) :
    Base(),
    m_name(name)
{
}

Condition::Condition(const Condition& cnd) :
    Base(cnd),
    m_name(cnd.m_name),
    m_last_port(cnd.m_last_port),
    m_ispermanent(cnd.m_ispermanent)
{
    for (ConditionValues::const_iterator it = cnd.m_list.begin();
         it != cnd.m_list.end(); ++it) {
        m_list[it->first] = dynamic_cast < value::Set*>(it->second->clone());
    }
}

Condition::~Condition()
{
    std::stack < value::Value* > lst;

    for (iterator it = m_list.begin(); it != m_list.end(); ++it) {
        if (it->second) {
            lst.push(it->second);
        }
    }

    value::deleter(lst);
}

void Condition::write(std::ostream& out) const
{
    out << "<condition name=\"" << m_name.c_str() << "\" >\n";

    for (ConditionValues::const_iterator it = m_list.begin(); it !=
         m_list.end();
         ++it) {
        out << " <port "
            << "name=\"" << it->first.c_str() << "\" "
            << ">\n";

        assert(it->second);
        const value::VectorValue& val(value::toSet(*it->second));
        for (value::VectorValue::const_iterator jt = val.begin();
             jt != val.end(); ++jt) {
            (*jt)->writeXml(out);
            out << "\n";
        }
        out << "</port>\n";
    }
    out << "</condition>\n";
}

void Condition::portnames(std::list < std::string >& lst) const
{
    lst.resize(m_list.size());
    std::transform(m_list.begin(), m_list.end(), lst.begin(),
                   utils::select1st < ConditionValues::value_type >());
}

void Condition::add(const std::string& portname)
{
    m_list.insert(std::make_pair < std::string, value::Set* >(
            portname, value::Set::create()));
    m_last_port.assign(portname);
}

void Condition::del(const std::string& portname)
{
    m_list.erase(portname);
}

void Condition::rename(const std::string& oldportname, const std::string& newportname)
{
	value::Set values = getSetValues(oldportname);
	value::Set::const_iterator it;
	add(newportname);
	for (it = values.begin(); it != values.end(); ++it) {
		value::Value *v = *it;
		addValueToPort(newportname, *v);
	}
	del(oldportname);
}

void Condition::addValueToPort(const std::string& portname,
                               value::Value* value)
{
    ConditionValues::iterator it = m_list.find(portname);

    if (it == m_list.end()) {
        value::Set* newset = value::Set::create();
        newset->add(value);

        m_list.insert(std::make_pair < std::string, value::Set* >(
                portname, newset));
        m_last_port.assign(portname);
    } else {
        it->second->add(value);
    }
}

void Condition::addValueToPort(const std::string& portname,
                               const value::Value& value)
{
    ConditionValues::iterator it = m_list.find(portname);

    if (it == m_list.end()) {
        value::Set* newset = value::Set::create();
        newset->add(value);

        m_list.insert(std::make_pair < std::string, value::Set* >(
                portname, newset));
        m_last_port.assign(portname);
    } else {
        it->second->add(value);
    }
}

void Condition::setValueToPort(const std::string& portname,
                               const value::Value& value)
{
    ConditionValues::iterator it = m_list.find(portname);

    if (it == m_list.end()) {
        throw utils::ArgError(fmt(
                _("Condition %1% have no port %2%")) % m_name % portname);
    }

    it->second->clear();
    it->second->add(value);
}

void Condition::clearValueOfPort(const std::string& portname)
{
    ConditionValues::iterator it = m_list.find(portname);

    if (it == m_list.end()) {
        throw utils::ArgError(fmt(
                _("Condition %1% have no port %2%")) % m_name % portname);
    }

    it->second->clear();
}

value::Map* Condition::firstValues() const
{
    value::Map* result = new value::Map();

    for (const_iterator it = m_list.begin(); it != m_list.end(); ++it) {
        if (it->second->size() > 0) {
            result->add(it->first, it->second->get(0));
        } else {
            throw(utils::ArgError(fmt(
                        "Build a empty first values for condition %1%.") %
                    m_name));
        }
    }

    return result;
}

const value::Set& Condition::getSetValues(const std::string& portname) const
{
    ConditionValues::const_iterator it = m_list.find(portname);

    if (it == m_list.end()) {
        throw utils::ArgError(fmt(_("Condition %1% have no port %2%")) % m_name
                              % portname);
    }

    assert(it->second);
    return *it->second;
}

value::Set& Condition::getSetValues(const std::string& portname)
{
    ConditionValues::iterator it = m_list.find(portname);

    if (it == m_list.end()) {
        throw utils::ArgError(fmt(_("Condition %1% have no port %2%")) % m_name
                              % portname);
    }

    assert(it->second);
    return *it->second;
}

const value::Value& Condition::firstValue(const std::string& portname) const
{
    return *getSetValues(portname).get(0);
}

const value::Value& Condition::nValue(const std::string& portname,
                                      size_t i) const
{
    return *getSetValues(portname).get(i);
}

value::Set& Condition::lastAddedPort()
{
    ConditionValues::iterator it = m_list.find(m_last_port);

    if (it == m_list.end()) {
        throw utils::ArgError(fmt(_("Condition %1% have no port %2%")) % m_name
                              % m_last_port);
    }

    assert(it->second);
    return *it->second;
}

void Condition::rebuildValueSet()
{
    for (ConditionValues::iterator it = m_list.begin(); it != m_list.end();
         ++it) {
        it->second = new value::Set();
    }
}

}} // namespace vle vpz
