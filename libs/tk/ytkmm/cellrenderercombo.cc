// Generated by gmmproc 2.45.3 -- DO NOT MODIFY!


#include <glibmm.h>

#include <ytkmm/cellrenderercombo.h>
#include <ytkmm/private/cellrenderercombo_p.h>


// -*- c++ -*-
/* $Id: cellrenderercombo.ccg,v 1.3 2006/05/10 20:59:27 murrayc Exp $ */

/* 
 *
 * Copyright 2004 The gtkmm Development Team
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free
 * Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */
 
#include <ytk/ytk.h>

///This is used only by signal_changed's generated implementation.
static GtkTreeModel* _get_model(GtkCellRendererCombo* renderer)
{
  if(!renderer)
    return 0;

  GtkTreeModel* combo_model = 0;
  g_object_get(G_OBJECT(renderer), "model", &combo_model, NULL);
  return combo_model;
}

namespace Gtk
{

Glib::PropertyProxy_Base CellRendererCombo::_property_renderable()
{
  return CellRendererText::_property_renderable();
}

} //namespace Gtk

namespace
{


static void CellRendererCombo_signal_changed_callback(GtkCellRendererCombo* self, const gchar* p0,GtkTreeIter* p1,void* data)
{
  using namespace Gtk;
  typedef sigc::slot< void,const Glib::ustring&,const TreeModel::iterator& > SlotType;

  CellRendererCombo* obj = dynamic_cast<CellRendererCombo*>(Glib::ObjectBase::_get_current_wrapper((GObject*) self));
  // Do not try to call a signal on a disassociated wrapper.
  if(obj)
  {
    try
    {
      if(sigc::slot_base *const slot = Glib::SignalProxyNormal::data_to_slot(data))
        (*static_cast<SlotType*>(slot))(Glib::convert_const_gchar_ptr_to_ustring(p0)
, TreeModel::iterator(_get_model(self), p1)
);
    }
    catch(...)
    {
       Glib::exception_handlers_invoke();
    }
  }
}

static const Glib::SignalProxyInfo CellRendererCombo_signal_changed_info =
{
  "changed",
  (GCallback) &CellRendererCombo_signal_changed_callback,
  (GCallback) &CellRendererCombo_signal_changed_callback
};


} // anonymous namespace


namespace Glib
{

Gtk::CellRendererCombo* wrap(GtkCellRendererCombo* object, bool take_copy)
{
  return dynamic_cast<Gtk::CellRendererCombo *> (Glib::wrap_auto ((GObject*)(object), take_copy));
}

} /* namespace Glib */

namespace Gtk
{


/* The *_Class implementation: */

const Glib::Class& CellRendererCombo_Class::init()
{
  if(!gtype_) // create the GType if necessary
  {
    // Glib::Class has to know the class init function to clone custom types.
    class_init_func_ = &CellRendererCombo_Class::class_init_function;

    // This is actually just optimized away, apparently with no harm.
    // Make sure that the parent type has been created.
    //CppClassParent::CppObjectType::get_type();

    // Create the wrapper type, with the same class/instance size as the base type.
    register_derived_type(gtk_cell_renderer_combo_get_type());

    // Add derived versions of interfaces, if the C type implements any interfaces:

  }

  return *this;
}


void CellRendererCombo_Class::class_init_function(void* g_class, void* class_data)
{
  BaseClassType *const klass = static_cast<BaseClassType*>(g_class);
  CppClassParent::class_init_function(klass, class_data);


}


Glib::ObjectBase* CellRendererCombo_Class::wrap_new(GObject* o)
{
  return manage(new CellRendererCombo((GtkCellRendererCombo*)(o)));

}


/* The implementation: */

CellRendererCombo::CellRendererCombo(const Glib::ConstructParams& construct_params)
:
  Gtk::CellRendererText(construct_params)
{
  }

CellRendererCombo::CellRendererCombo(GtkCellRendererCombo* castitem)
:
  Gtk::CellRendererText((GtkCellRendererText*)(castitem))
{
  }

CellRendererCombo::~CellRendererCombo()
{
  destroy_();
}

CellRendererCombo::CppClassType CellRendererCombo::cellrenderercombo_class_; // initialize static member

GType CellRendererCombo::get_type()
{
  return cellrenderercombo_class_.init().get_type();
}


GType CellRendererCombo::get_base_type()
{
  return gtk_cell_renderer_combo_get_type();
}


CellRendererCombo::CellRendererCombo()
:
  // Mark this class as non-derived to allow C++ vfuncs to be skipped.
  Glib::ObjectBase(0),
  Gtk::CellRendererText(Glib::ConstructParams(cellrenderercombo_class_.init()))
{
  

}


Glib::SignalProxy2< void,const Glib::ustring&,const TreeModel::iterator& > CellRendererCombo::signal_changed()
{
  return Glib::SignalProxy2< void,const Glib::ustring&,const TreeModel::iterator& >(this, &CellRendererCombo_signal_changed_info);
}


Glib::PropertyProxy< Glib::RefPtr<Gtk::TreeModel> > CellRendererCombo::property_model() 
{
  return Glib::PropertyProxy< Glib::RefPtr<Gtk::TreeModel> >(this, "model");
}

Glib::PropertyProxy_ReadOnly< Glib::RefPtr<Gtk::TreeModel> > CellRendererCombo::property_model() const
{
  return Glib::PropertyProxy_ReadOnly< Glib::RefPtr<Gtk::TreeModel> >(this, "model");
}

Glib::PropertyProxy< int > CellRendererCombo::property_text_column() 
{
  return Glib::PropertyProxy< int >(this, "text-column");
}

Glib::PropertyProxy_ReadOnly< int > CellRendererCombo::property_text_column() const
{
  return Glib::PropertyProxy_ReadOnly< int >(this, "text-column");
}

Glib::PropertyProxy< bool > CellRendererCombo::property_has_entry() 
{
  return Glib::PropertyProxy< bool >(this, "has-entry");
}

Glib::PropertyProxy_ReadOnly< bool > CellRendererCombo::property_has_entry() const
{
  return Glib::PropertyProxy_ReadOnly< bool >(this, "has-entry");
}


} // namespace Gtk


