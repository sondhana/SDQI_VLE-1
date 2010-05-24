/**
 * @file vle/gvle/TupleBox.hpp
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

#ifndef GUI_TUPLEBOX_HPP
#define GUI_TUPLEBOX_HPP

#include <gtkmm.h>
#include <vle/value/Tuple.hpp>
#include <boost/multi_array.hpp>

namespace vle { namespace gvle {

class TupleBox : public Gtk::Dialog
{
public:
    TupleBox(value::Tuple* t);
    virtual ~TupleBox();

    void run();

private:
    typedef boost::multi_array<Gtk::Entry*, 1> array_type;

    Gtk::ScrolledWindow* mScroll;
    Gtk::Table* mTable;
    value::Tuple* mValue;
    array_type* mArray;

    void makeTable();
};

    }} // namespace vle gvle

#endif