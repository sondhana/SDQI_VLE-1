/**
 * @file vle/gvle/TableBox.cpp
 * @author The VLE Development Team
 */

/*
 * VLE Environment - the multimodeling and simulation environment
 * This file is a part of the VLE environment (http://vle.univ-littoral.fr)
 * Copyright (C) 2003 - 2008 The VLE Development Team
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


#include <vle/gvle/TableBox.hpp>
#include <vle/utils/Tools.hpp>

using namespace vle;

namespace vle
{
namespace gvle {
TableBox::TableBox(value::Table* t):
        Gtk::Dialog("Table",true,true),
        mValue(t)
{
    add_button(Gtk::Stock::APPLY, Gtk::RESPONSE_APPLY);
    add_button(Gtk::Stock::CANCEL, Gtk::RESPONSE_CANCEL);

    mScroll = new Gtk::ScrolledWindow();
    mScroll->set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
    get_vbox()->pack_start(*mScroll);

    mTable = new Gtk::Table(t->height(), t->width(), true);
    mScroll->add(*mTable);
    makeTable();
    resize(300,200);

    show_all();
}

TableBox::~TableBox()
{
    hide_all();
    delete mScroll;
    delete mTable;

    for (index i = 0; i != mValue->height(); ++i) {
        for (index j = 0; j != mValue->width(); ++j) {
            delete(*mArray)[j][i];
        }
    }
    delete mArray;
}

void TableBox::run()
{
    int ret = Gtk::Dialog::run();
    if (ret ==  Gtk::RESPONSE_APPLY) {
        value::TableValue& table = mValue->value();
        for (index i = 0; i != mValue->height(); ++i) {
            for (index j = 0; j != mValue->width(); ++j) {
                table[j][i] = utils::to_double((*mArray)[j][i]->get_text());
            }
        }
    }
}

void TableBox::makeTable()
{
    mArray = new array_type(boost::extents[mValue->width()][mValue->height()]);
    for (index i = 0; i != mValue->height(); ++i) {
        for (index j = 0; j != mValue->width(); ++j) {
            (*mArray)[j][i] = new Gtk::Entry();
            (*mArray)[j][i]->set_width_chars(10);
            (*mArray)[j][i]->set_text(utils::to_string(mValue->get(j, i)));
            (*mArray)[j][i]->set_editable(true);
            mTable->attach(*(*mArray)[j][i], j , j+1, i, i+1, Gtk::FILL, Gtk::FILL);
        }
    }
}

}
} // namespace vle gvle
