/**
 * @file Set.hpp
 * @author The VLE Development Team.
 * @brief Set Value a container to Value class.
 */

/*
 * Copyright (c) 2004, 2005 The vle Development Team
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

#ifndef UTILS_VALUE_SET_HPP
#define UTILS_VALUE_SET_HPP

#include <vle/value/Value.hpp>
#include <vector>

namespace vle { namespace value {

    /**
     * @brief Set Value a container to Value class.
     * @author The VLE Development Team.
     */
    class Set : public Value
    {
    public:
        typedef std::vector < Value* > VectorValue;

        Set() { }

        Set(xmlpp::Element* root);

        virtual ~Set();

        virtual Value::type getType() const
        { return Value::SET; }

        /**
         * Add a value into the set. Be carrefull, the data are not clone, the use
         * the pointer. Don't delete buffer.
         *
         * @param value the Value to add.
         */
        void addValue(Value* value);

        virtual Value* clone() const;

        inline VectorValue & getValue()
        { return m_value; }

        inline const VectorValue& getValue() const
        { return m_value; }

        virtual std::string toFile() const;

        virtual std::string toString() const;

        virtual std::string toXML() const;

    private:
        VectorValue m_value;
    };

}} // namespace vle value
#endif
