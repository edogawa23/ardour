/*
 * Copyright (C) 2011-2014 David Robillard <d@drobilla.net>
 * Copyright (C) 2011-2016 Paul Davis <paul@linuxaudiosystems.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#pragma once

#include <memory>
#include <string>

#include "evoral/Parameter.h"

#include "ardour/automation_control.h"
#include "ardour/automation_list.h"

namespace ARDOUR {

class Session;
class Pannable;

class LIBARDOUR_API PanControllable : public AutomationControl
{
  public:
	PanControllable (Session& s, std::string name, Pannable* o, Evoral::Parameter param, Temporal::TimeDomainProvider const & tdp)
		: AutomationControl (s,
		                     param,
		                     ParameterDescriptor(param),
		                     std::shared_ptr<AutomationList>(new AutomationList(param, tdp)),
		                     name)
		, owner (o)
	{}

	std::string get_user_string () const;

  private:
	Pannable* owner;
	void actually_set_value (double, PBD::Controllable::GroupControlDisposition group_override);
};

} // namespace

