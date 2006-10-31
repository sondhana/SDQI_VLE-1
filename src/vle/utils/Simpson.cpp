/** 
 * @file Simpson.cpp
 * @brief An implementation of Simpson's method to calculate the integrals.
 * @author The vle Development Team
 * @date lun, 06 fév 2006 16:54:12 +0100
 */

/*
 * Copyright (C) 2006 - The vle Development Team
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
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 */

#include <vle/utils/Simpson.hpp>

namespace vle { namespace utils {

double Simpson::compute()
{
    double h=(v_b-v_a)/v_n;
    double (&f)(double)=*v_f;

    double sum1=f(v_a)+f(v_b);

    double sum2=0.0;
    for(int j=2;j<=v_n-2;j+=2)
        sum2+=f(v_a+j*h);

    double sum3=0.0;
    for(int j=1;j<=v_n-1;j+=2)
        sum3+=f(v_a+j*h);

    return (sum1+2.0*sum2+4.0*sum3)*h/3.0;
}

}} // namespace vle utils
